#ifndef gen_blockx_cc
#define gen_blockx_cc
#include <string>
#include <vector>
#include "blocktype.pb.h"
#include "opponent.pb.h"
#include "reduced_blockx.pb.h"
#include "card.pb.h"

#include "TRandom3.h"

fake_data::reduced::BlockXCollection gen_randblkx(int ievt, int64_t ts, TRandom3 &rndm);
std::string gen_country(TRandom3 &rndm);
Opponent gen_opponents(TRandom3 &rndm);

std::string gen_id(int ievt, int64_t ts, TRandom3 &rndm);
std::string gen_idz(TRandom3 &rndm);
std::string gen_cat_a(TRandom3 &rndm);
std::string gen_player(TRandom3 &rndm);
Card gen_randcard(TRandom3 &rndm);


fake_data::reduced::BlockXCollection gen_randblkx(int ievt, int64_t ts, TRandom3 &rndm)
{
 //message BlockXCollection
 fake_data::reduced::BlockXCollection res;

 bool is_a=false;
 int size_opponents=0, size_cards=0, int_blocktype=0;
 int32_t block_i=0;
 BlockType block_type;
 std::string id, idz, cat_a, player, title, country, block_name;
 

 //string id = 1;
 id = gen_id(ievt, ts, rndm);
 res.set_id(id);

 //string id_z = 2;
 idz = gen_idz(rndm);
 res.set_id_z(idz);

 //string cat_a = 3;
 cat_a = gen_cat_a(rndm);
 res.set_cat_a(cat_a);

 //string player = 4;
 player = gen_player(rndm);
 res.set_player(player);

 //string title = 5;
 title = TString::Format("%03X", (UInt_t) rndm.Uniform(0., 4096.));
 res.set_title(title);
 
 //string country = 6;
 country = gen_country(rndm);
 res.set_country(country);
 
 //int32 block_i = 7;
 block_i = ievt % 256;
 res.set_block_i(block_i);

 //bool is_a = 8;
 is_a = rndm.Binomial(1, 0.2) > 0;
 res.set_is_a(is_a);

 //repeated Opponent opponents = 9;
 size_opponents = std::max(0, (int) rndm.Gaus(20, 30));
 res.mutable_opponents()->Reserve(size_opponents);
 for (int idx=0; idx<size_opponents; ++idx)
  *res.add_opponents() = gen_opponents(rndm);
 
 //BlockType block_type = 10;
 int_blocktype = std::min(4 + (int)rndm.Poisson(2), 10);
 if (rndm.Binomial(1, 0.2) > 0)
  int_blocktype = 1;
 block_type = static_cast<BlockType>(int_blocktype);

 //string block_name = 11;
 if (int_blocktype == 1)
  block_name = TString::Format("%s_%d", "X", (int)rndm.Uniform(0., 100.));
 else
  block_name = BlockType_Name(block_type);

 //repeated Card cards = 12;
 size_cards = std::max(0, (int) rndm.Gaus(200, 30));
 res.mutable_cards()->Reserve(size_cards);
 for (int idx=0; idx<size_cards; ++idx)
  *res.add_cards() = gen_randcard(rndm);

 return res;
}

std::string gen_country(TRandom3 &rndm)
{
 std::string res;

 int size=0;
 std::vector<std::string> country_code =
 {
  "AFG","ALB","DZA","ASM","AND","AGO","AIA","ATA","ATG","ARG",
  "ARM","ABW","AUS","AUT","AZE","BHS","BHR","BGD","BRB","BLR",
  "BEL","BLZ","BEN","BMU","BTN","BOL","BES","BIH","BWA","BVT",
  "BRA","IOT","BRN","BGR","BFA","BDI","CPV","KHM","CMR","CAN",
  "CYM","CAF","TCD","CHL","CHN","CXR","CCK","COL","COM","COD",
  "COG","COK","CRI","HRV","CUB","CUW","CYP","CZE","CIV","DNK",
  "DJI","DMA","DOM","ECU","EGY","SLV","GNQ","ERI","EST","SWZ",
  "ETH","FLK","FRO","FJI","FIN","FRA","GUF","PYF","ATF","GAB",
  "GMB","GEO","DEU","GHA","GIB","GRC","GRL","GRD","GLP","GUM",
  "GTM","GGY","GIN","GNB","GUY","HTI","HMD","VAT","HND","HKG",
  "HUN","ISL","IND","IDN","IRN","IRQ","IRL","IMN","ISR","ITA",
  "JAM","JPN","JEY","JOR","KAZ","KEN","KIR","PRK","KOR","KWT",
  "KGZ","LAO","LVA","LBN","LSO","LBR","LBY","LIE","LTU","LUX",
  "MAC","MDG","MWI","MYS","MDV","MLI","MLT","MHL","MTQ","MRT",
  "MUS","MYT","MEX","FSM","MDA","MCO","MNG","MNE","MSR","MAR",
  "MOZ","MMR","NAM","NRU","NPL","NLD","NCL","NZL","NIC","NER",
  "NGA","NIU","NFK","MNP","NOR","OMN","PAK","PLW","PSE","PAN",
  "PNG","PRY","PER","PHL","PCN","POL","PRT","PRI","QAT","MKD",
  "ROU","RUS","RWA","REU","BLM","SHN","KNA","LCA","MAF","SPM",
  "VCT","WSM","SMR","STP","SAU","SEN","SRB","SYC","SLE","SGP",
  "SXM","SVK","SVN","SLB","SOM","ZAF","SGS","SSD","ESP","LKA",
  "SDN","SUR","SJM","SWE","CHE","SYR","TWN","TJK","TZA","THA",
  "TLS","TGO","TKL","TON","TTO","TUN","TUR","TKM","TCA","TUV",
  "UGA","UKR","ARE","GBR","UMI","USA","URY","UZB","VUT","VEN",
  "VNM","VGB","VIR","WLF","ESH","YEM","ZMB","ZWE","ALA"
 };

 size = country_code.size();
 res = country_code[(int)rndm.Uniform(0, size)];
 
 return res;
}

Opponent gen_opponents(TRandom3 &rndm)
{
 //message Opponent
 Opponent res;

 bool b_tmp;
 int int_type=0;
 Opponent::Type type;
 uint32_t time_1, time_2, time_3, time_4, time_5, time_6;
 uint64_t id=0;
 std::string name, cat;
 TString tmpstr;

 //Type type = 1;
 int_type = std::min(1 + (int) rndm.Exp(4), 8);
 type = static_cast<Opponent::Type>(int_type);
 res.set_type(type);

 //uint64 id = 2;
 tmpstr = TString::Format("%d_%X", int_type, (int)rndm.Uniform(0., 100.));
 id = tmpstr.Hash();
 res.set_id(id);

 //string name = 3;
 name = TString::Format("[%d] %X", int_type, (int)rndm.Uniform(0., 10000.));
 res.set_name(name);

 //uint32 time_1 = 4;
 time_1 = (uint32_t) rndm.Exp(1.0e6);
 res.set_time_1(time_1);

 //uint32 time_2 = 5;
 b_tmp = rndm.Binomial(1, 0.9);
 if (b_tmp)
 {
  time_2 = (uint32_t) rndm.Exp(1.0e5);
  res.set_time_2(time_2);
 }

 //uint32 time_3 = 6;
 b_tmp = rndm.Binomial(1, 0.7);
 if (b_tmp)
 {
  time_3 = (uint32_t) rndm.Exp(1.0e4);
  res.set_time_3(time_3);
 }

 //uint32 time_4 = 7;
 b_tmp = rndm.Binomial(1, 0.5);
 if (b_tmp)
 {
  time_4 = (uint32_t) rndm.Exp(1.0e3);
  res.set_time_4(time_4);
 }

 //uint32 time_5 = 8;
 b_tmp = rndm.Binomial(1, 0.3);
 if (b_tmp)
 {
  time_5 = (uint32_t) rndm.Exp(1.0e2);
  res.set_time_5(time_5);
 }

 //uint32 time_6 = 9;
 b_tmp = rndm.Binomial(1, 0.1);
 if (b_tmp)
 {
  time_6 = (uint32_t) rndm.Exp(10);
  res.set_time_6(time_6);
 }

 //string cat = 10;
 for (int idx=0; idx<7; idx++)
  cat += TString::Format("%c", (97 + (UInt_t) rndm.Uniform(0., 26.)));
 res.set_cat(cat);

 return res;
}

#endif

