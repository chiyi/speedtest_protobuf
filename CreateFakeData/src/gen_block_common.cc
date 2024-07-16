#ifndef gen_block_common_cc
#define gen_block_common_cc
#include <string>
#include "card.pb.h"

#include "TString.h"
#include "TRandom3.h"
#include "TMath.h"

std::string gen_id(int ievt, int64_t ts, TRandom3 &rndm);
std::string gen_idz(TRandom3 &rndm);
void gen_cats(std::string &cat_a, std::string &cat_b, std::string &cat_tree, TRandom3 &rndm);
Card gen_randcard(TRandom3 &rndm);
std::string gen_cat_a(TRandom3 &rndm);


std::string gen_id(int ievt, int64_t ts, TRandom3 &rndm)
{
 std::string res;

 TString id, tail;

 id = TString::Format("%016X_%li", ievt, ts);
 tail = TString::Format("%X", id.Hash());
 res = TString::Format("rcrd_%d_%s_%s", (int) rndm.Uniform(0., 16.), id.Data(), tail(4, tail.Length()-4).Data());

 return res;
} 

std::string gen_idz(TRandom3 &rndm)
{
 return (std::string) (TString::Format("%X", (int) rndm.Uniform(0., 10000.)));
}

void gen_cats(std::string &cat_a, std::string &cat_b, std::string &cat_tree, TRandom3 &rndm)
{
 bool b_tmp=false;
 char cat_base='\0';
 cat_a="", cat_b="", cat_tree="";
 TString branch="]::[";
 TString cat_tail;

 // basic tree
 cat_a = gen_cat_a(rndm);
 cat_tree = "[" + cat_a;
 b_tmp = rndm.Binomial(1, 0.5);
 if (b_tmp)
 {
  cat_b = TString::Format("%s_%d", cat_a.c_str(), (int) rndm.Uniform(0., 100.));
  cat_tree += branch + cat_b;
  b_tmp = rndm.Binomial(1, 0.5);
  if (b_tmp)
  {
   cat_tail = TString::Format("%s_%d", cat_b.c_str(), (int) rndm.Uniform(0., 36.));
   b_tmp = rndm.Binomial(1, 0.5);
   cat_tree += branch + cat_tail;
   if (b_tmp)
   {
    cat_tail = TString::Format("%s_%d", cat_tail.Data(), (int) rndm.Uniform(0., 10.));
    cat_tree += branch + cat_tail;
 }}}
 cat_tree += "]";

 // super tree
 b_tmp = rndm.Binomial(1, 0.5);
 if (b_tmp)
 {
  cat_base = (char) (88 + (UInt_t) rndm.Uniform(0., 3.));
  cat_tail = TString::Format("X%c_%d", cat_base, (int) rndm.Uniform(0., 10.));
  b_tmp = rndm.Binomial(1, 0.5);
  cat_tree += TString(" ; [") + cat_tail;
  if (b_tmp)
   cat_tail += branch + TString::Format("%s_%d", cat_tail.Data(), (int) rndm.Uniform(0., 10.));
  cat_tree += "]";
 }
}

Card gen_randcard(TRandom3 &rndm)
{
 //message Card
 Card res;

 char base='\0';
 int idn=0, count=0;
 double value_1=0., value_2=0., value_3=0.;
 std::string id, name, cat;

 //string id = 1;
 base = (char) (65 + (UInt_t) rndm.Uniform(0., 26.));
 idn = (int) rndm.Uniform(0., 256.);
 id = TString::Format("UCard%c_%02d", base, idn);
 res.set_id(id);

 //string name = 2;
 name = TString::Format("%c %X", base, idn);
 res.set_name(name);

 //string cat = 3;
 for (int idx=0; idx<3; idx++)
  cat += TString::Format("%c", (65 + (UInt_t) rndm.Uniform(0., 26.)));
 res.set_cat(cat);

 //int32 count = 4;
 count = (int) rndm.Uniform(1., 5.);
 res.set_count(count);

 //double value_1 = 5;
 value_1 = TMath::Max(0., TMath::Floor(rndm.Gaus(2500., 1000.)));
 res.set_value_1(value_1);

 //double value_2 = 6;
 value_2 = TMath::Max(0., TMath::Floor(rndm.Gaus(3500., 1000.)));
 res.set_value_2(value_2);

 //double value_3 = 7;
 value_3 = (double) rndm.Poisson(3);
 res.set_value_3(value_3);

 return res;
}

std::string gen_cat_a(TRandom3 &rndm)
{
 std::string res;

 char cat_base='\0';
 cat_base = (char) (65 + (UInt_t) rndm.Uniform(0., 26.));
 res = TString::Format("%c_%d", cat_base, (int) rndm.Uniform(0., 5.));

 return res;
}

std::string gen_player(TRandom3 &rndm)
{
 return (std::string) TString::Format("%X", (UInt_t) rndm.Uniform(0., 1.0e16));
}
#endif

