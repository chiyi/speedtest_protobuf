#include "JobsHandler.h"

#ifndef JOBSHANDLER_CPP
#define JOBSHANDLER_CPP
std::atomic<bool> JobsHandler::GLOBAL_CANCEL_FLAG{false};
#endif
