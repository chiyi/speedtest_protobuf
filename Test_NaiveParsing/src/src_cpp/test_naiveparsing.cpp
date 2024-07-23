#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <zlib.h>
#include "fake_anadata.pb.h"

#include "TSystem.h"
#include "TBase64.h"
#include "TString.h"
#include "TMath.h"

// user-defined functions
bool chk_para(int argc, char *argv[]);
void usage();
std::vector<std::string> get_filenames(const std::string& filename_fmt);
void apply_aggregation(std::map<std::string, int> &out, std::string inpfile);
void aggdistribution_boxes(std::map<std::string, int> &out, const fake_data::analysis::FakeAnaData &data);
void print_result(const std::map<std::string, int> &out);


int main(int argc, char *argv[])
{
 std::map<std::string, int> res;
 std::vector<std::string> files;

 if(!chk_para(argc, argv))
 {
  usage();
  return 2;
 }

 files = get_filenames(argv[1]);
 for (auto file : files)
 {
  std::cout << "processing " << file << "......\n";
  apply_aggregation(res, file);
 }
 print_result(res);

 return 0;
}





bool chk_para(int argc, char *argv[])
{
 if(argc<=1)
  return false;

 auto filenames = get_filenames(argv[1]);
 if (filenames.size()==0)
  return false;
 if(gSystem->AccessPathName(filenames[0].c_str()))
  return false;

 return true;
}

void usage()
{
 std::cout << "usage(): ./test_cpp_naiveparsing /data/fakedata_*.txt\n";
 std::cout << "./test_cpp_naiveparsing {input filename wildcard}" << std::endl;
}

std::vector<std::string> get_filenames(const std::string& filename_fmt)
{
 std::vector<std::string> res;
 int from=0;
 TString cmd, filenames, tok;

 cmd = TString::Format("ls %s", filename_fmt.c_str());
 filenames = gSystem->GetFromPipe(cmd.Data());
 while (filenames.Tokenize(tok, from, "\n"))
  res.push_back((std::string)tok);
 
 return res;
}

void apply_aggregation(std::map<std::string, int> &out, std::string inpfile)
{
 const int size_gzbuf=2097152;
 int from=0, errnum=0, bytesRead=0, size_repeated_history=0;
 std::string outbin;
 const TString delim="\001\002\003\004\005\006\007\010";
 char gzbuf[size_gzbuf];
 TString line, all_lines, errmsg;
 fake_data::analysis::FakeAnaData data;
 gzFile gzfs;


 // gz IO
 gzfs = gzopen(inpfile.c_str(), "rb");
 while ((bytesRead = gzread(gzfs, gzbuf, size_gzbuf)) > 0)
  all_lines.Append(gzbuf, bytesRead);
 gzerror(gzfs, &errnum);
 if(errnum != Z_OK)
 {
  errmsg = gzerror(gzfs, &errnum);
  std::cerr << "Error reading file: code=" << (int)errnum << ", " << errmsg.Data() << std::endl;
  exit(EXIT_FAILURE);
 }
 gzclose(gzfs);

 while (all_lines.Tokenize(line, from, "\n"))
 {
  if (!line.EndsWith(delim))
  {
   std::cout << "WARN: Unexpected Newline detected !!!\n";
   continue;
  }
  data.Clear();
  line = line(0, line.Length() - 8);
  line = TBase64::Decode(line.Data());
  outbin = std::string(line, line.Length());
  if (!data.ParseFromString(outbin))
  {
   std::cout << "WARN: Parse Failed.\n";
   continue;
  }
  
  aggdistribution_boxes(out, data);
 }
}

void aggdistribution_boxes(std::map<std::string, int> &out, const fake_data::analysis::FakeAnaData &data)
{
 int bin_cost = 0;

 out["nevents"] += data.history_size();
 for (const auto &history_i : data.history())
 {
  out["nboxes"] += history_i.boxes_size();
  for (const auto &box_j : history_i.boxes())
  {
   bin_cost = box_j.cost()>0 ? TMath::Floor(10*TMath::Log10(box_j.cost())) : -99;
   out[std::to_string(bin_cost)] += box_j.count();
  }
 }
}

void print_result(const std::map<std::string, int> &out)
{
 for(const auto &pair_i : out)
  std::cout << TString::Format("bin_10log10 %s:%d", pair_i.first.c_str(), pair_i.second) << "\n";
}

