#ifndef gen_event_common_cc
#define gen_event_common_cc
#include <vector>
#include <string>
#include "TDatime.h"
#include "TRandom3.h"

int64_t gen_evtts(int offset, TRandom3 &rndm, double sigma);
fake_data::analysis::Box gen_randbox(TRandom3 &rndm);


int64_t gen_evtts(int offset, TRandom3 &rndm, double sigma)
{
 int64_t res = TDatime().Convert() + (int64_t) rndm.Gaus(60+offset, sigma);
 return res;
}

fake_data::analysis::Box gen_randbox(TRandom3 &rndm)
{
 //message Box
 fake_data::analysis::Box res;

 int count=0;
 double cost=0.;
 std::string color;
 std::vector<std::string> colors =
 {
  "White", "Black", "Gray", "Red", "Green", "Blue", "Yellow", "Magenta", "Cyan",
  "Orange", "Spring", "Teal", "Azure", "Violet", "Pink"
 };

 //string color = 1;
 color = colors[(int) rndm.Uniform(0., 15.)];
 res.set_color(color);

 //double cost = 2;
 cost = rndm.Gaus(200., 10.);
 res.set_cost(cost);

 //int32 count = 3;
 count = rndm.Poisson(3);
 res.set_count(count);

 return res;
}
#endif

