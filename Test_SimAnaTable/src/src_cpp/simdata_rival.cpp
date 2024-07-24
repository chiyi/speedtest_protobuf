#include "simdata_rival.h"

#ifndef SimData_Rival_cxx
#define SimData_Rival_cxx

SimData_Rival::SimData_Rival()
{
}

SimData_Rival::SimData_Rival(std::string hashed_name, long ts_max, double val_sim)
 :hashed_name(hashed_name), ts_max(ts_max), val_sim(val_sim)
{
}

std::string SimData_Rival::ToString()
{
 std::string res;
 res = TString::Format("(%s, %ld, %10.0lf)", hashed_name.c_str(), ts_max, val_sim);
 return res;
}
#endif
