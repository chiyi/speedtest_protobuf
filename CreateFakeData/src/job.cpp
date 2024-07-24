#include "job.h"

#ifndef job_cpp
#define job_cpp

Job::Job()
{
 this->settings = Job::Settings();
}

Job::Job(int id, TRandom3 *rndm, Job::Settings settings)
 : _id(id), _rndm(rndm)
{
 this->settings = settings;
}

void Job::run()
{
 double res=0.;
 for (int idx=0; idx<=1000; idx++)
 {
  if ((idx+1)%100==0 && JobsHandler::GLOBAL_CANCEL_FLAG.load())
   break;
  res += this->_rndm->Gaus(77, 30);
 }
 std::this_thread::sleep_for(std::chrono::seconds(1));
 if (JobsHandler::GLOBAL_CANCEL_FLAG.load())
  std::cout << "Job id#" << _id << " was cancelled" << std::endl;
 else
  std::cout << "Job id#" << _id << " with result=" << res << std::endl;
}

#endif
