#include <iostream>
#include "blocktype.pb.h"
#include "card.pb.h"
#include "opponent.pb.h"
#include "reduced_blockx.pb.h"
#include "reduced_blocky.pb.h"
#include "reduced_blockz.pb.h"
#include "fake_anadata.pb.h"

#include "TDatime.h"

BlockType GenSample_BlockType();
Card GenSample_Card();
Opponent GenSample_Opponent();
fake_data::reduced::BlockXCollection GenSample_BlockXCollection(Opponent opponent, BlockType blktype, Card card);
fake_data::reduced::BlockYCollection GenSample_BlockYCollection(Card card);
fake_data::reduced::BlockZCollection GenSample_BlockZCollection(Card card);
fake_data::analysis::FakeAnaData GenSample_FakeAnaData(fake_data::reduced::BlockXCollection blk_x, fake_data::reduced::BlockYCollection blk_y, fake_data::reduced::BlockZCollection blk_z);

int main()
{
 BlockType blktype = GenSample_BlockType();
 Card card = GenSample_Card();
 Opponent opponent = GenSample_Opponent();
 fake_data::reduced::BlockXCollection blk_x = GenSample_BlockXCollection(opponent, blktype, card);
 fake_data::reduced::BlockYCollection blk_y = GenSample_BlockYCollection(card);
 fake_data::reduced::BlockZCollection blk_z = GenSample_BlockZCollection(card);
 fake_data::analysis::FakeAnaData data = GenSample_FakeAnaData(blk_x, blk_y, blk_z);

 std::cout << "Print fake data\n";
 std::cout << blk_x.opponents(0).name() << std::endl;
 std::cout << blk_x.cards(0).name() << std::endl;
 std::cout << blk_y.cards(0).name() << std::endl;
 std::cout << blk_z.ext().chksum() << std::endl;
 std::cout << data.title() << std::endl;
 std::cout << data.history(0).timestamp() << std::endl;
 std::cout << data.history(0).blockz().score() << std::endl;
 return 0;
}




BlockType GenSample_BlockType()
{
 return BlockType::X;
}

Card GenSample_Card()
{
 Card res;
 res.set_id("B_1");
 res.set_name("BlueE");
 res.set_cat("D");
 res.set_count(2);
 res.set_value_1(3500.);
 res.set_value_2(3500.);
 res.set_value_3(0.);
 return res;
}

Opponent GenSample_Opponent()
{
 Opponent res;
 res.set_type(Opponent::Player);
 res.set_id(0);
 res.set_name("AAA");
 res.set_time_1(1111);
 res.set_time_2(1121);
 res.set_time_3(1231);
 res.set_time_4(2341);
 res.set_time_5(3452);
 res.set_time_6(4563);
 res.set_cat("anonymous");
 return res;
}

fake_data::reduced::BlockXCollection GenSample_BlockXCollection(Opponent opponent, BlockType blktype, Card card)
{
 fake_data::reduced::BlockXCollection res;
 res.set_id("rec_0");
 res.set_id_z("C");
 res.set_is_a(true);

 *res.add_opponents() = Opponent(opponent);
 //std::vector<Opponent> opponents({opponent});
 //for (const auto& opponent : opponents)
 // *res.add_opponents() = opponent;

 res.set_block_type(blktype);
 res.set_block_name("X_00000000");

 *res.add_cards() = Card(card);
 return res;
}

fake_data::reduced::BlockYCollection GenSample_BlockYCollection(Card card)
{
 fake_data::reduced::BlockYCollection res;
 res.set_id("rec_0");
 *res.add_cards() = Card(card);
 return res;
}

fake_data::reduced::BlockZCollection GenSample_BlockZCollection(Card card)
{
 fake_data::reduced::BlockZCollection res;
 res.set_id("rec_0");
 *res.add_cards() = Card(card);
 res.set_score(0.997);
 res.set_target(fake_data::reduced::BlockZCollection::A);

 fake_data::reduced::BlockZCollection::EXT_alpha tmp;
 tmp.set_table(9);
 tmp.set_chksum(16829);
 *res.mutable_ext() = tmp;

 return res;
}

fake_data::analysis::FakeAnaData GenSample_FakeAnaData(fake_data::reduced::BlockXCollection blk_x, fake_data::reduced::BlockYCollection blk_y, fake_data::reduced::BlockZCollection blk_z)
{
 fake_data::analysis::FakeAnaData res;
 res.set_title("fake ana data");

 fake_data::analysis::Event evtblk_z;
 *evtblk_z.mutable_blockz() = blk_z;
 *res.mutable_blockz() = evtblk_z;

 fake_data::analysis::Event tmp;
 tmp.set_timestamp(TDatime().Convert());
 *tmp.mutable_blockx() = blk_x;
 *tmp.mutable_blocky() = blk_y;
 *tmp.mutable_blockz() = blk_z;
 tmp.set_score(0.65535);
 *res.add_history() = tmp;

 return res;
}

