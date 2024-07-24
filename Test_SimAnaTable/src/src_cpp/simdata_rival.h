#ifndef _SIMDATA_RIVAL_H_
#define _SIMDATA_RIVAL_H_

#include <iostream>
#include <string>
#include "TString.h"

class SimData_Rival
{
 public:
  SimData_Rival();
  SimData_Rival(std::string hashed_name, int64_t ts_max, double val_sim);
  int64_t ts_max=0;
  double val_sim=0.;
  std::string hashed_name="";
  std::string ToString();
};
#endif

