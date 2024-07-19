#ifndef _JOBS_SCHEDULER_H_
#define _JOBS_SCHEDULER_H_

#include <iostream>
#include <map>
#include <thread>
#include <queue>
#include <signal.h>
#include "TString.h"
#include "TRandom3.h"
#include "TDatime.h"
#include "JobsHandler.h"

template <typename JobType>
class JobsScheduler
{
 public:
  JobsScheduler(unsigned int NJobs, unsigned int NThreads, TRandom3 *rndm, JobType job);
  bool fully_occupied();
  bool complete();
  void run_jobs();

 private:
  const unsigned int _num_jobs, _num_threads;
  unsigned int _queue_size=0;
  std::queue<std::thread> _job_queue;
  TRandom3 *_rndm;
  JobType _job;
  std::map<unsigned int, JobType*> _jobs;
  void join_leadingjob();
};

#endif
