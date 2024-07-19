#ifndef _JOB_H_
#define _JOB_H_

#include <iostream>
#include <thread>
#include <chrono>
#include "TRandom3.h"
#include "JobsHandler.h"

class Job
{
 public:
  class Settings
  {
   public:
  };
  Job();
  Job(int id, TRandom3 *rndm, Job::Settings settings);
  Settings settings;
  virtual void run();
 private:
  int _id;
  TRandom3 *_rndm;
};

#endif
