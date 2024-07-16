#ifndef gen_blockz_cc
#define gen_blockz_cc
#include <string>
#include "reduced_blockz.pb.h"
#include "card.pb.h"

#include "TRandom3.h"
#include "TString.h"
#include "TMath.h"

#include "gen_block_common.cc"
fake_data::reduced::BlockZCollection gen_randblkz(int ievt, int64_t ts, TRandom3 &rndm);
fake_data::reduced::BlockZCollection::EXT_alpha gen_ext(TRandom3 &rndm);


fake_data::reduced::BlockZCollection gen_randblkz(int ievt, int64_t ts, TRandom3 &rndm)
{
 //message BlockZCollection
 fake_data::reduced::BlockZCollection res;

 int int_target=0;
 double score=0.;
 std::string id, id_z, cat_a, cat_b, cat_tree, id_1, id_2, id_3;
 fake_data::reduced::BlockZCollection::Target target;

 //string id = 1;
 id = gen_id(ievt, ts, rndm);
 res.set_id(id);

 //string id_z = 2;
 id_z = gen_idz(rndm);
 res.set_id_z(id_z);

 //string cat_a = 3;
 //string cat_b = 4;
 //string cat_tree = 5;
 gen_cats(cat_a, cat_b, cat_tree, rndm);
 res.set_cat_a(cat_a);
 res.set_cat_b(cat_b);
 res.set_cat_tree(cat_tree);

 //repeated Card cards = 6;
 res.mutable_cards()->Reserve(5);
 for (int idx=0; idx<5; ++idx)
  *res.add_cards() = gen_randcard(rndm);

 //double score = 7;
 for (const Card &card : res.cards())
  score += card.value_1() * card.count() + TMath::Power(card.value_2() / card.value_1() / card.count(), card.value_3()) + TString(card.name()).Hash() % 10;
 score = TMath::Cos(0.001 * TMath::Pi() * score);
 score *= score;
 res.set_score(score);

 //Target target = 8;
 int_target = (int) rndm.Uniform(0., 5.);
 target = static_cast<fake_data::reduced::BlockZCollection::Target>(int_target);
 res.set_target(target);

 //string version = 9;
 res.set_version("0.0.0");

 //string id_1 = 10;
 id_1 = TString::Format("id1_%X", (int) rndm.Uniform(0., 100.));
 res.set_id_1(id_1);

 //string id_2 = 11;
 id_2 = TString::Format("id2_%X", (int) rndm.Uniform(0., 100.));
 res.set_id_2(id_2);

 //string id_3 = 12;
 id_3 = TString::Format("id3_%X", (int) rndm.Uniform(0., 10.));
 res.set_id_3(id_3);

 //EXT_alpha ext = 13;
 if (rndm.Binomial(1, 0.5))
  *res.mutable_ext() = gen_ext(rndm);

 return res;
}

fake_data::reduced::BlockZCollection::EXT_alpha gen_ext(TRandom3 &rndm)
{
 //message EXT_alpha
 fake_data::reduced::BlockZCollection::EXT_alpha res;

 TString text;

 //int32 table = 1;
 res.set_table(1);
 //string id = 2;
 res.set_id("alpha");
 //int32 value_a = 3;
 res.set_value_a(1);
 //int32 value_b = 4;
 res.set_value_b(1);
 //int32 value_c = 5;
 res.set_value_c((int) rndm.Uniform(0., 256.));
 //int32 value_d = 6;
 res.set_value_d((int) rndm.Uniform(0., 256.));

 //int64 chksum = 7;
 text = TString::Format("%d %d %d %d", res.value_a(), res.value_b(), res.value_c(), res.value_d());
 res.set_chksum(text.Hash());

 return res;
}
#endif

