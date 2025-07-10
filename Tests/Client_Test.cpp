//
// Created by bimaj on 08/07/2025.
//
#include "iostream"
#include "gtest/gtest.h"
#include "Client.h"

TEST(ClientTest,InizializzazioneCostruttoreCliente){
    Cliente cliente("Bimaj","Igli","BMJGLI03D26D583G");
    EXPECT_EQ(cliente.getCognome(),"Bimaj");
    EXPECT_EQ(cliente.getNome(),"Igli");
    EXPECT_EQ(cliente.getCf(),"BMJGLI03D26D583G");
}