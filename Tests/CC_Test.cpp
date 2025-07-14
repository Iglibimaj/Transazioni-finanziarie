#include "gtest/gtest.h"
#include "Cliente.h"
#include "CC.h"

class CC_Test:public ::testing::Test{
protected:
    std::unique_ptr<Cliente> cliente;
    std::unique_ptr<CC> cc;
    void SetUp() override{
        cliente=std::make_unique<Cliente>("Bimaj","Igli","123");
        cc= std::make_unique<CC>(*cliente,0);
    }
    void TearDown() override {
        cc.reset();
        cliente.reset();
    }
};

TEST_F(CC_Test,TestBonificoEntrata){
    cc->bonificoEntrata(500);
    EXPECT_EQ(cc->getSaldo(),500);
}

TEST_F(CC_Test,TestBonificoUscita){
    cc->bonificoEntrata(500);
    cc->bonificoUscita(500);
    EXPECT_EQ(cc->getSaldo(),0);
}

TEST_F(CC_Test,TestNumeroEntrate){
    cc->bonificoEntrata(500);
    EXPECT_EQ(cc->getNumeroEntrate(),1);
}

TEST_F(CC_Test,TestNumeroUscite){
    cc->bonificoEntrata(500);
    cc->bonificoUscita(500);
    EXPECT_EQ(cc->getNumeroUscite(),1);
}