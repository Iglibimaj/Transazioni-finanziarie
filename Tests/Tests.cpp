#include "gtest/gtest.h"
#include "Client.h"
#include "CC.h"

class TransazioniFinanziarieTest : public ::testing::Test {
protected:
    Cliente* cliente;
    CC* cc;

    TransazioniFinanziarieTest() : cliente(nullptr), cc(nullptr) {} // Initialize pointers to nullptr

    void SetUp() override {

        CC::resetStaticState();
        cliente = new Cliente("Bimaj", "Igli", "BMJGLI03D26D583G");
        cc = new CC("123", *cliente, 0);
    }

    void TearDown() override {
        delete cc;
        delete cliente;
    }
};

TEST_F(TransazioniFinanziarieTest, TestSaldoIniziale) {
    EXPECT_EQ(CC::getNentrate("123"), 0) << "Non dovrebbero esserci entrate";
    EXPECT_EQ(CC::getNuscite("123"), 0) << "Non dovrebbero esserci uscite";
    EXPECT_EQ(CC::getSaldo("123"), 0) << "Il saldo iniziale dovrebbe essere 0.";
}

TEST_F(TransazioniFinanziarieTest, TestBonificoUscita) {
    CC::bonificoEntrata("123", 500);
    CC::bonificoUscita("123", 200);
    EXPECT_EQ(CC::getSaldo("123"), 300) << "Il saldo dovrebbe essere aggiornato a 300.";
    EXPECT_EQ(CC::getNuscite("123"), 1) << "Il numero di uscite dovrebbe essere 1.";
}

TEST_F(TransazioniFinanziarieTest, TestTransazioniMultiple) {
    CC::bonificoEntrata("123", 100);
    CC::bonificoEntrata("123", 200);
    CC::bonificoUscita("123", 150);
    EXPECT_EQ(CC::getSaldo("123"), 150) << "Il saldo dovrebbe essere 150.";
    EXPECT_EQ(CC::getNentrate("123"), 2) << "Il numero di entrate dovrebbe essere 2.";
    EXPECT_EQ(CC::getNuscite("123"), 1) << "Il numero di uscite dovrebbe essere 1.";
}



