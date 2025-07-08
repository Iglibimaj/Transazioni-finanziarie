#include <memory>
#include "gtest/gtest.h"
#include "Client.h"
#include "CC.h"

class TransazioniFinanziarieTest : public ::testing::Test {
protected:
    std::unique_ptr<Cliente> cliente;
    std::unique_ptr<CC> cc;

    void SetUp() override {
        CC::resetStaticState();
        cliente = std::make_unique<Cliente>("Bimaj", "Igli", "BMJGLI03D26D583G");
        cc = std::make_unique<CC>("123", *cliente, 0);
    }

    void TearDown() override {

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

TEST_F(TransazioniFinanziarieTest, TestBonificoEntrata) {
    CC::bonificoEntrata("123", 100);
    EXPECT_EQ(CC::getSaldo("123"), 100) << "Il saldo dovrebbe essere aggiornato a 100.";
    EXPECT_EQ(CC::getNentrate("123"), 1) << "Il numero di entrate dovrebbe essere 1.";
}


