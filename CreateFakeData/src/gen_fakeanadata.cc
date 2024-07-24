#ifndef gen_fakeanadata_cc
#define gen_fakeanadata_cc
#include <vector>
#include <string>
#include "fake_anadata.pb.h"

#include "TF1.h"
#include "TH1I.h"
#include "TRandom.h"
#include "TRandom3.h"
#include "TString.h"
#include "TAxis.h"

#include "gen_blockx.cc"
#include "gen_blocky.cc"
#include "gen_blockz.cc"
#include "gen_event_blockz.cc"
void create_ith_fakedata(int job_id, std::vector<fake_data::analysis::FakeAnaData>::iterator &it, int ievt, TRandom3 &rndm);
std::string gen_hashed_name(TRandom3 &rndm);
fake_data::analysis::Event gen_randevt(int job_id, int ievt, TRandom3 &rndm, const fake_data::analysis::Event &evtblkz);


void create_ith_fakedata(int job_id, std::vector<fake_data::analysis::FakeAnaData>::iterator &it, int ievt, TRandom3 &rndm)
{
 //message FakeAnaData
 fake_data::analysis::FakeAnaData &res = *it;

 int size_history=0;

 //string title = 1;
 res.set_title("ana_0");
 //string hashed_name = 2;
 res.set_hashed_name(gen_hashed_name(rndm));
 //Event blockz = 3;
 *res.mutable_blockz() = gen_randevt_blkz(ievt, rndm, 0, 10);

 //repeated Event history = 4;
 size_history = std::max(0, (int) rndm.Gaus(10, ievt%10));
 res.mutable_history()->Reserve(size_history);
 for (int idx=0; idx<size_history; ++idx)
  *res.add_history() = gen_randevt(job_id, ievt, rndm, res.blockz());
 *res.add_history() = res.blockz();
}

std::string gen_hashed_name(TRandom3 &rndm)
{
 std::string res;

 double x=0.,y=0.;
 TString tmp;
 rndm.Circle(x, y, 99);
 tmp = TString::Format("%lfx%lf", x, y);
 res = TString::Format("hashed_%u", tmp.Hash());

 return res;
}

fake_data::analysis::Event gen_randevt(int job_id, int ievt, TRandom3 &rndm, const fake_data::analysis::Event &evtblkz)
{
 //message Event
 fake_data::analysis::Event res;

 int size_boxes=0;
 int64_t ts=0;
 double score=0.;
 std::string blks;
 TString hname, f1name;
 TF1 *f_blk;
 TH1I *htmp;
 
 hname = TString::Format("htmp_%d", job_id);
 htmp = new TH1I(hname.Data(), "int-discrete probability", 5, 0., 5.);
 htmp->Fill("X",0.); htmp->Fill("XY",0.); htmp->Fill("Y",0.); htmp->Fill("YZ",0.); htmp->Fill("Z",0.);

 // int64 timestamp = 1;
 ts = evtblkz.timestamp() - (int64_t) rndm.Gaus(100+ievt%1000, 300);
 res.set_timestamp(ts);

 //fake_data.reduced.BlockXCollection blockx = 2;
 //fake_data.reduced.BlockYCollection blocky = 3;
 //fake_data.reduced.BlockZCollection blockz = 4;
 f1name = TString::Format("f_blk_%d", job_id);
 f_blk = new TF1(f1name.Data(), "exp([0]*x)", 0., 5.);
 f_blk->SetParameter(0, -(ievt % 5 + 1) / 10.);
 htmp->FillRandom(f1name, 1000);
 blks = htmp->GetXaxis()->GetBinLabel(htmp->FindBin(htmp->GetRandom()));
 for (char c : blks)
 {
  switch (c)
  {
   case 'X':
    *res.mutable_blockx() = gen_randblkx(ievt, ts, rndm);
    break;
   case 'Y':
    *res.mutable_blocky() = gen_randblky(ievt, ts, rndm);
    break;
   case 'Z':
    *res.mutable_blockz() = gen_randblkz(ievt, ts, rndm);
    break;
  }
 }

 //double score = 5;
 score += res.blockx().is_a() * 0.01 + res.blocky().cards_size() * 0.1 + res.blockz().score();
 res.set_score(score);

 //repeated Box boxes = 6;
 size_boxes = (int) rndm.Gaus(20, ievt%30);
 res.mutable_boxes()->Reserve(size_boxes);
 for (int idx=0; idx<size_boxes; ++idx)
  *res.add_boxes() = gen_randbox(rndm);

 delete f_blk;
 delete htmp;
 return res;
}
#endif

