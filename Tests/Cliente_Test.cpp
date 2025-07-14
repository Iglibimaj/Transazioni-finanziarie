#include "gtest/gtest.h"
#include "Cliente.h"
class Cliete_Test:public ::testing::Test{
protected:
    std::unique_ptr<Cliente> cliente;
    void SetUp( )override{
        cliente=std::make_unique<Cliente>("Bimaj","Igli","123");
    }
    void TearDown() override{}
};

TEST_F(Cliete_Test,testCliente){
    EXPECT_EQ(cliente->getCognome(),"Bimaj");
    EXPECT_EQ(cliente->getNome(),"Igli");
    EXPECT_EQ(cliente->getCf(),"123");
}