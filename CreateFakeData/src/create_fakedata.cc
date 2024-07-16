#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "fake_anadata.pb.h"

#include "TSystem.h"
#include "TBase64.h"
#include "TString.h"
#include "TRandom3.h"

// user-defined functions
#include "gen_fakeanadata.cc"
bool chk_para(int argc, char *argv[]);
void usage();
void write_files(const std::vector<fake_data::analysis::FakeAnaData> &res, char out_prefix[]);


int main(int argc, char *argv[])
{
 std::vector<fake_data::analysis::FakeAnaData> res;

 int nrows=0;
 TRandom3 rndm;


 if(!chk_para(argc, argv))
 {
  usage();
  return 2;
 }

 rndm.SetSeed(13931);
 nrows = TString(argv[1]).Atoi();
 std::cout << "To generate " << nrows << " records of fake data." << std::endl;
 res.resize(nrows);
 auto it_fakedata = res.begin();
 for (int ievt=0; ievt<nrows; ++ievt, ++it_fakedata)
  create_ith_fakedata(it_fakedata, ievt, rndm);

 for (auto it=res.begin(); it!=res.end(); it++)
 {
  std::cout << it->history_size() << "\n";
  std::cout << it->blockz().blockz().cat_tree() << std::endl;
 }

 write_files(res, argv[2]);

 return 0;
}




bool chk_para(int argc, char *argv[])
{
 int nrows=0;
 TString outdir;

 if(argc<=2)
  return false;

 nrows = TString(argv[1]).Atoi();
 if(nrows<=0)
 {
  std::cout << "nrows=" << nrows << " <= 0\n";
  return false;
 }

 outdir = gSystem->GetDirName(argv[2]);
 if(gSystem->AccessPathName(outdir))
 {
  std::cout << "outdir " << outdir << " fault!\n";
  return false;
 }

 return true;
}

void usage()
{
 std::cout << "usage(): ./create_fakedata 10 /data/fakedata\n";
 std::cout << "./create_fakedata {number of records} {output filename prefix}" << std::endl;
}

void write_files(const std::vector<fake_data::analysis::FakeAnaData> &res, char out_prefix[])
{
 TString outfilename;

 int ith=0;
 std::string delim, outbin, outstr;

 delim = "\001\002\003\004\005\006\007\010\n";
 outfilename = TString::Format("%s_1.txt", out_prefix);
 std::ofstream output_file(outfilename.Data(), std::ios::trunc);
 std::cout << "writing " << outfilename << "...\n";
 for (const auto &row : res)
 {
  outbin = row.SerializeAsString();
  outstr = TBase64::Encode(outbin.c_str(), outbin.length());
  output_file.write(outstr.c_str(), outstr.size());
  output_file << delim;
  if(ith==0)
  {
   std::cout << outstr << "\n";
   ith++;
 }}
 if (!output_file.good())
  std::cerr << "Error writing to file " << outfilename << std::endl;

 output_file.close();
}

