#include "gtest/gtest.h"
#include "Banca.h"

class BancaTest: public ::testing::Test{
protected:
    Banca banca;
    std::shared_ptr<Cliente> cliente;
    std::unique_ptr<CC> cc;
    void SetUp() override {
        cliente=std::make_shared<Cliente>("Igli","Bimaj","123");
        cc=std::make_unique<CC>(*cliente,0);
        banca.aggiungiConto("123",*cc);
    }
};

TEST_F(BancaTest,AggiungiContoCorretto){
    EXPECT_NO_THROW(banca.aggiungiConto("1234",*cc));
}

TEST_F(BancaTest,SearchIbanTrovato){
    CC& cc1=Banca::searchIban("123");
    EXPECT_EQ(cc->getSaldo(),0);
}

TEST_F(BancaTest, SearchIbanNonTrovato) {
    CC& cc1 = banca.searchIban("999");
    EXPECT_EQ(cc1.getSaldo(), 0);
    EXPECT_EQ(cc1.getCliente().getNome(), "");
    EXPECT_EQ(cc1.getCliente().getCognome(), "");
    EXPECT_EQ(cc1.getCliente().getCf(), "");
}


