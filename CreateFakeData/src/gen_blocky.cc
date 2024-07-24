#ifndef gen_blocky_cc
#define gen_blocky_cc
#include <string>
#include "reduced_blocky.pb.h"

#include "TRandom3.h"
#include "TString.h"

#include "gen_block_common.cc"
fake_data::reduced::BlockYCollection gen_randblky(int ievt, int64_t ts, TRandom3 &rndm);


fake_data::reduced::BlockYCollection gen_randblky(int ievt, int64_t ts, TRandom3 &rndm)
{
 //message BlockYCollection
 fake_data::reduced::BlockYCollection res;

 int size_cards=0;
 std::string id, idz, id_c1, id_c2, cat_a, cat_b, cat_tree, player, zone;

 //string id = 1;
 id = gen_id(ievt, ts, rndm);
 res.set_id(id); 

 //string id_z = 2;
 idz = gen_idz(rndm);
 res.set_id_z(idz);

 //string id_c1 = 3;
 id_c1 = TString::Format("C1_%05d", (int) rndm.Uniform(0., 100000.));
 res.set_id_c1(id_c1);

 //string id_c2 = 4;
 id_c2 = TString::Format("C2_%X", (int) rndm.Uniform(0., 256));
 res.set_id_c2(id_c2);

 //string cat_tree = 5;
 gen_cats(cat_a, cat_b, cat_tree, rndm);
 res.set_cat_tree(cat_tree);

 //repeated Card cards = 6;
 size_cards = std::max(0, (int) rndm.Gaus(100, 70));
 res.mutable_cards()->Reserve(size_cards);
 for (int idx=0; idx<size_cards; ++idx)
  *res.add_cards() = gen_randcard(rndm);

 //string player = 7;
 player = gen_player(rndm);
 res.set_player(player);
	
 //string zone = 8;
 zone = TString::Format("%03d", (UInt_t) rndm.Uniform(0., 1000.));
 res.set_zone(zone);

 return res;
}
#endif

