#ifndef gen_event_blockz_cc
#define gen_event_blockz_cc
#include <string>
#include "fake_anadata.pb.h"

#include "TRandom3.h"

#include "gen_event_common.cc"
#include "gen_blockz.cc"
fake_data::analysis::Event gen_randevt_blkz(int ievt, TRandom3 &rndm, int offset, double sigma);


fake_data::analysis::Event gen_randevt_blkz(int ievt, TRandom3 &rndm, int offset, double sigma)
{
 //message Event
 fake_data::analysis::Event res;

 int size_boxes=0;
 int64_t ts=0;
 double score=0.;

 //int64 timestamp = 1;
 ts = gen_evtts(offset, rndm, sigma);
 res.set_timestamp(ts);

 //fake_data.reduced.BlockXCollection blockx = 2;
 //fake_data.reduced.BlockYCollection blocky = 3;

 //fake_data.reduced.BlockZCollection blockz = 4;
 *res.mutable_blockz() = gen_randblkz(ievt, ts, rndm);

 //double score = 5;
 score = res.blockz().score();
 res.set_score(score);

 //repeated Box boxes = 6;
 size_boxes = (int) rndm.Gaus(5, ievt % 10);
 res.mutable_boxes()->Reserve(size_boxes);
 for (int idx=0; idx<size_boxes; ++idx)
  *res.add_boxes() = gen_randbox(rndm);

 return res;
}
#endif

