#ifndef _JOBSHANDLER_H_
#define _JOBSHANDLER_H_

#include <atomic>
#include <signal.h>

class JobsHandler
{
 public:
  static std::atomic<bool> GLOBAL_CANCEL_FLAG;
  static void HANDLE_SIGINT(int signum)
  {
   if (signum == SIGINT)
    GLOBAL_CANCEL_FLAG.store(true);
  }
};
#endif
