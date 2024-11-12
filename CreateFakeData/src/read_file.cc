#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <zlib.h>
#include <google/protobuf/util/json_util.h>
#include "turbob64.h"
#include "fake_anadata.pb.h"

#include "TSystem.h"
#include "TString.h"

// user-defined functions
bool chk_para(int argc, char *argv[]);
void usage();
std::vector<std::string> get_filenames(const std::string& filename_fmt);
void read_file(std::string inpfile);
void print_data(int ith_line, const fake_data::analysis::FakeAnaData &outobj);


int main(int argc, char *argv[])
{
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
  read_file(file);
 }
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
 std::cout << "usage(): ./read_file /data/fakedata_*.txt\n";
 std::cout << "./read_file {input filename wildcard}" << std::endl;
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

void read_file(std::string inpfile)
{
 const int size_gzchar=1000000;
 unsigned int len_b64dec=0;
 int ith_line=0, from=0, errnum=0;
 const TString delim="\001\002\003\004\005\006\007\010\n";
 char gzbuf[size_gzchar];
 TString line, errmsg;
 std::vector<uint8_t> bin_decoded(4194304);
 std::vector<TString> all_lines;
 fake_data::analysis::FakeAnaData outobj;
 gzFile gzfs;


 gzfs = gzopen(inpfile.c_str(), "rb");
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

 for (auto const &r_line: all_lines)
 {
  if (!r_line.EndsWith(delim))
  {
   std::cout << "WARN: Unexpected Newline detected !!!\n";
   continue;
  }
  line = r_line(0, r_line.Length() - delim.Length());
  len_b64dec = tb64dec(
   reinterpret_cast<const unsigned char*>(line.Data()),
   line.Length(),
   bin_decoded.data()
  );
  if (!outobj.ParseFromArray(reinterpret_cast<const char*>(bin_decoded.data()), len_b64dec))
  {
   std::cout << "WARN: Parse Failed.\n";
   continue;
  }
  
  if (ith_line < 20)
   print_data(ith_line, outobj);
  
  ith_line++;
 }
}

void print_data(int ith_line, const fake_data::analysis::FakeAnaData &outobj)
{
 std::string json_string;

 std::cout << "Print Record #" << ith_line << ":{\n";
 google::protobuf::util::JsonPrintOptions options;
 options.add_whitespace = true;
 options.preserve_proto_field_names = true;
 auto status_convert = google::protobuf::util::MessageToJsonString(outobj, &json_string, options);
 std::cout << "JSON conversion: " << status_convert << "\n";
 std::cout << json_string << "\n";
 std::cout << "} //record end" << std::endl;
}
