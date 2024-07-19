#ifndef _JOB_FAKEDATA_H_
#define _JOB_FAKEDATA_H_

#include <iostream>
#include <string>
#include <vector>
#include <zlib.h>
#include <thread>
#include "fake_anadata.pb.h"
#include "TString.h"
#include "TBase64.h"
#include "TRandom3.h"
#include "job.h"
#include "JobsHandler.h"
#include "gen_fakeanadata.cc"

class Job_fakedata : public Job
{
 public:
  class Settings_fakedata : public Job::Settings
  {
   public:
   int nparts;
   int nrows_part;
   int nrows_tail;
   std::string out_prefix;
  };
  Job_fakedata();
  Job_fakedata(int id, TRandom3 *rndm, Job_fakedata::Settings_fakedata settings);
  Job_fakedata::Settings_fakedata settings;
  void run() override;
 private:
  int _id;
  int _nrows_parti;
  std::string _out_prefix;
  TRandom3 *_rndm;
  void write_files(const std::vector<fake_data::analysis::FakeAnaData> &res);
};

#endif
