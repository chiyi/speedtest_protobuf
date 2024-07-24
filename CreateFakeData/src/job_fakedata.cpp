#include "job_fakedata.h"

#ifndef b_DEBUG
#define b_DEBUG 0
#endif

#ifndef job_fakedata_cpp
#define job_fakedata_cpp

Job_fakedata::Job_fakedata()
{
 this->settings = Job_fakedata::Settings_fakedata();
}

Job_fakedata::Job_fakedata(int part_id, TRandom3 *rndm, Job_fakedata::Settings_fakedata settings)
 : _id(part_id), _rndm(rndm)
{
 this->settings = settings;
 this->_out_prefix = settings.out_prefix;
 this->_nrows_parti = (settings.nrows_tail > 0 && part_id == settings.nparts) ? settings.nrows_tail : settings.nrows_part;
}

void Job_fakedata::run()
{
 std::vector<fake_data::analysis::FakeAnaData> res;

 res.resize(this->_nrows_parti);
 auto it_fakedata = res.begin();
 for (int ievt=0; ievt<this->_nrows_parti; ++ievt, ++it_fakedata)
 {
  if ((ievt+1)%100==0 && JobsHandler::GLOBAL_CANCEL_FLAG.load())
   break;
  create_ith_fakedata(this->_id, it_fakedata, (unsigned int)ievt, *(this->_rndm));
 }

 if (this->_nrows_parti == 0 && b_DEBUG>=2)
 {
  for (auto it=res.begin(); it!=res.end(); it++)
  {
   std::cout << it->history_size() << "\n";
   std::cout << it->blockz().blockz().cat_tree() << std::endl;
  }
 }

 if (JobsHandler::GLOBAL_CANCEL_FLAG.load())
  std::cout << "Job id#" << this->_id << " was cancelled" << std::endl;

 write_files(res);

 if (JobsHandler::GLOBAL_CANCEL_FLAG.load())
  std::cout << "Job id#" << this->_id << " was cancelled" << std::endl;
}

void Job_fakedata::write_files(const std::vector<fake_data::analysis::FakeAnaData> &res)
{
 TString outfilename;

 std::string delim, outbin;
 TString outstr;
 gzFile gzfs;


 delim = "\001\002\003\004\005\006\007\010\n";
 outfilename = TString::Format("%s_%d.txt.gz", this->_out_prefix.c_str(), this->_id);
 for (const auto &row : res)
 {
  outbin = row.SerializeAsString();
  outstr += TBase64::Encode(outbin.c_str(), outbin.length());
  outstr += delim;
  if (JobsHandler::GLOBAL_CANCEL_FLAG.load())
   break;
 }
  
 std::cout << "writing " << outfilename << "...\n";
 gzfs = gzopen(outfilename.Data(), "wb");
 if (gzfs == NULL)
 {
  std::cerr << "Error opening file: " << outfilename << std::endl;
  exit(EXIT_FAILURE);
 }
 if (gzwrite(gzfs, outstr.Data(), outstr.Length()) == -1)
 {
  std::cerr << "Error writing to file" << std::endl;
  exit(EXIT_FAILURE);
 }


 if (gzclose(gzfs) != Z_OK)
 {
  std::cerr << "Error closing file" << std::endl;
  exit(EXIT_FAILURE);
 }
}

#endif
