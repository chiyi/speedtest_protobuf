#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <numeric>
#include <algorithm>
#include <zlib.h>
#include "turbob64.h"
#include "fake_anadata.pb.h"

#include "TSystem.h"
#include "TString.h"
#include "TMath.h"

//user defined header
#include "simdata_rival.h"
#include "simdata_rival.cpp"
bool chk_para(int argc, char *argv[]);
void usage();
std::vector<std::string> get_filenames(const std::string& filename_fmt);
void simulate_analysis(std::map<std::string, SimData_Rival> &out, std::string inpfile);
bool filter_0_activated(const fake_data::analysis::FakeAnaData &data);
void cal_rival(std::map<std::string, SimData_Rival> &out, std::string hashed_name, const fake_data::analysis::FakeAnaData &data);
double get_log10median(const fake_data::analysis::FakeAnaData &data, char selblock);
bool filter_1_activated(const fake_data::analysis::Event &history_i, char selblock);
double cal_log10(double value);
void write_result(const std::map<std::string, SimData_Rival> &out);


int main(int argc, char *argv[])
{
 std::map<std::string, SimData_Rival> res;
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
  simulate_analysis(res, file);
 }

 write_result(res);
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
 std::cout << "usage(): ./test_simanatable /data/fakedata_*.txt\n";
 std::cout << "./test_simanatable {input filename wildcard}" << std::endl;
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

void simulate_analysis(std::map<std::string, SimData_Rival> &out, std::string inpfile)
{
 const int size_gzchar=1000000;
 unsigned int len_b64dec=0;
 int from=0, errnum=0, size_repeated_history=0;
 const TString delim="\001\002\003\004\005\006\007\010\n";
 char gzbuf[size_gzchar];
 TString line, errmsg;
 std::vector<uint8_t> bin_decoded(4194304);
 std::vector<TString> all_lines;
 fake_data::analysis::FakeAnaData data;
 gzFile gzfs;


 // gz IO
 gzfs = gzopen(inpfile.c_str(), "rb");
 if (!gzfs)
 {
  std::cerr << "Error opening file: " << inpfile << std::endl;
  exit(EXIT_FAILURE);
 }
 while (gzgets(gzfs, gzbuf, size_gzchar) != nullptr)
  all_lines.push_back(gzbuf);
 gzerror(gzfs, &errnum);
 if(errnum != Z_OK)
 {
  errmsg = gzerror(gzfs, &errnum);
  std::cerr << "Error reading file: code=" << (int)errnum << ", " << errmsg.Data() << std::endl;
  exit(EXIT_FAILURE);
 }
 gzclose(gzfs);

 // data rows
 for (auto const &r_line: all_lines)
 {
  //if (!line.EndsWith(delim))
  if (!r_line.EndsWith(delim))
  {
   std::cout << "WARN: Unexpected Newline detected !!!\n";
   continue;
  }
  data.Clear();
  line = r_line(0, r_line.Length() - delim.Length());
  len_b64dec = tb64dec(
   reinterpret_cast<const unsigned char*>(line.Data()),
   line.Length(),
   bin_decoded.data()
  );
  if (!data.ParseFromArray(reinterpret_cast<const char*>(bin_decoded.data()), len_b64dec))
  {
   std::cout << "WARN: Parse Failed.\n";
   continue;
  }

  if(filter_0_activated(data))
   continue;

  cal_rival(out, data.hashed_name(), data);
 }
}

bool filter_0_activated(const fake_data::analysis::FakeAnaData &data)
{
 return data.hashed_name().length() < 5 || data.hashed_name().length() >= 40 || data.history_size() <= 0;
}

void cal_rival(std::map<std::string, SimData_Rival> &out, std::string hashed_name, const fake_data::analysis::FakeAnaData &data)
{
 int64_t ts_max=0;
 double val_x=0., val_y=0., val_z=0.;
 double val_sim=0.;

 ts_max = out[hashed_name].ts_max;
 val_sim = out[hashed_name].val_sim;
 val_x = get_log10median(data, 'x');
 val_y = get_log10median(data, 'y');
 val_z = get_log10median(data, 'z');
 val_sim += val_x + val_y * 888 + val_z * 88888;
 for (const auto &history_i : data.history())
  ts_max = std::max(ts_max, history_i.timestamp());

 out[hashed_name].hashed_name = hashed_name;
 out[hashed_name].ts_max = ts_max;
 out[hashed_name].val_sim = val_sim;
}

double get_log10median(const fake_data::analysis::FakeAnaData &data, char selblock)
{
 double res=0.;
 unsigned int size=0;
 std::vector<double> vec_score;

 for (const auto &history_i : data.history())
  if (filter_1_activated(history_i, selblock))
   vec_score.push_back( cal_log10(history_i.score()) );
 size = vec_score.size();

 if(size == 0) return res;

 res = TMath::Median(size, vec_score.data());

 return res;
}

bool filter_1_activated(const fake_data::analysis::Event &history_i, char selblock)
{
 bool res = false;
 switch(selblock)
 {
  case 'x':
   res = history_i.has_blockx() && !history_i.blockx().id_z().empty();
   break;
  case 'y':
   res = history_i.has_blocky() && !history_i.blocky().id_z().empty();
   break;
  case 'z':
   res = history_i.has_blockz() && !history_i.blockz().id_z().empty();
   break;
 }
 return res;
}

double cal_log10(double value)
{
 return value>0 ? TMath::Log10(value) : -9.9;
}

void write_result(const std::map<std::string, SimData_Rival> &out)
{
 int idx=0;

 std::ofstream ofs("table/cppsim_result.txt", std::ofstream::out | std::ofstream::trunc);
 for (const auto &pair_i : out)
 {
  auto key = pair_i.first;
  auto value = pair_i.second;
  ofs << TString::Format("%10d-th: %s => %s\n", idx, key.c_str(), value.ToString().c_str());
  idx++;
 }
 ofs.close();
}
