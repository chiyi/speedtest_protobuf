#include "jobs_scheduler.h"

#ifndef jobs_scheduler_cpp
#define jobs_scheduler_cpp

template <typename JobType>
JobsScheduler<JobType>::JobsScheduler(unsigned int NJobs, unsigned int NThreads, TRandom3 *rndm, JobType job)
 : _num_jobs(NJobs), _num_threads(NThreads), _rndm(rndm), _job(job)
{
}

template <typename JobType>
bool JobsScheduler<JobType>::fully_occupied()
{
 this->_queue_size = this->_job_queue.size();
 return this->_queue_size >= this->_num_threads;
}

template <typename JobType>
bool JobsScheduler<JobType>::complete()
{
 this->_queue_size = this->_job_queue.size();
 return this->_queue_size == 0;
}

template <typename JobType>
void JobsScheduler<JobType>::join_leadingjob()
{
 this->_job_queue.front().join();
 this->_job_queue.pop();
}

template <typename JobType>
void JobsScheduler<JobType>::run_jobs()
{
 signal(SIGINT, JobsHandler::HANDLE_SIGINT);

 for (unsigned int idxjob=0; idxjob<this->_num_jobs; ++idxjob)
 {
  if (this->fully_occupied())
  {
   std::cout << TString::Format("[%s]: %s=%d", TDatime().AsString(), "Waiting for another complete jobs before adding, NJobs_running", this->_queue_size) << std::endl;
   this->join_leadingjob();
  }
  _jobs[idxjob] = new JobType(idxjob+1, this->_rndm, this->_job.settings);
  _job_queue.push(std::thread(&JobType::run, this->_jobs[idxjob]));
  //_job_queue.push(std::thread([job = _jobs[idxjob]] { job->run(); } ));  if for Job*
 }

 while (!this->complete())
 {
  this->join_leadingjob();
  std::cout << TString::Format("[%s]: %s=%d", TDatime().AsString(), "NJobs_running", this->_queue_size) << std::endl;
 }
}

#endif
