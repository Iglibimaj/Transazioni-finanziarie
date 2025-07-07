#include "gtest/gtest.h"
#include "Client.h"
#include "CC.h"

class TransazioniFinanziarieTest : public ::testing::Test {
protected:
    Cliente* cliente;
    CC* cc;

    // Constructor initializes pointers to nullptr
    TransazioniFinanziarieTest() : cliente(nullptr), cc(nullptr) {}

    void SetUp() override {
        cliente = new Cliente("Bimaj", "Igli", "BMJGLI03D26D583G");
        cc = new CC("123", *cliente, 0); // Initialize with valid data
        CC::bonificoEntrata("123",3);
    }

    void TearDown() override {
        delete cliente;
        delete cc;
    }
};

TEST_F(TransazioniFinanziarieTest, TestSaldoIniziale) {
EXPECT_EQ(CC::getNentrate("123"),0)<<"non dovrebbero esserci entrate";
EXPECT_EQ(CC::getNuscite("123"),0)<<"non dovrebbero esserci uscite";
EXPECT_EQ(CC::getSaldo("123"), 0) << "Il saldo iniziale dovrebbe essere 100.";
}

TEST_F(TransazioniFinanziarieTest, TestBonificoEntrata) {
    CC::bonificoEntrata("123", 500);
    EXPECT_EQ(CC::getSaldo("123"), 500) << "Il saldo dovrebbe essere aggiornato a 500.";
    EXPECT_EQ(CC::getNentrate("123"), 1) << "Il numero di entrate dovrebbe essere 1.";
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

TEST_F(TransazioniFinanziarieTest, TestIBANNonEsistente) {
    EXPECT_EQ(CC::getSaldo("999"), 0) << "Il saldo di un IBAN inesistente dovrebbe essere 0.";
    EXPECT_EQ(CC::getNentrate("999"), 0) << "Il numero di entrate di un IBAN inesistente dovrebbe essere 0.";
    EXPECT_EQ(CC::getNuscite("999"), 0) << "Il numero di uscite di un IBAN inesistente dovrebbe essere 0.";
}

TEST_F(TransazioniFinanziarieTest, TestSaldoNegativoNonConsentito) {
    CC::bonificoEntrata("123", 50);
    CC::bonificoUscita("123", 100);
    EXPECT_EQ(CC::getSaldo("123"), 50) << "Il saldo non dovrebbe andare in negativo.";
}


