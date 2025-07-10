#ifndef TRANSAZIONI_FINANZIARIE_CC_H
#define TRANSAZIONI_FINANZIARIE_CC_H

#include "iostream"
#include "Client.h"
#include "map"
#include "vector"

class CC {
public:
    struct ClientInfo {
        std::string Cognome;
        std::string Nome;
        std::string CF;
    };

    static std::map<std::string, std::pair<ClientInfo, float>> ContoCorrente;
    static std::map<std::string, std::vector<float>> fileEntrate;
    static std::map<std::string, std::vector<float>> fileUscite;
    static std::map<std::string, int> nEntrate;
    static std::map<std::string, int> nUscite;


    CC(const std::string &iban, const Cliente &cliente, float saldo);

    static void searchIban(const std::string &iban);

    static void bonificoEntrata(const std::string &iban, float valore);

    static void bonificoUscita(const std::string &iban, float valore);

    static void leggiEntrate(const std::string &iban);

    static void leggiUscite(const std::string &iban);

    static void saveinFile(const std::string &nomeFile);

    static void readFile(const std::string &nomeFile);

    static float getSaldo(const std::string &iban);

    static int getNuscite(const std::string &iban);

    static int getNentrate(const std::string &iban);

    static void resetStaticState();

    const std::string& getIban(){
        return Iban;
    }

        private:
    std::string Iban;
    std::string Cognome;
    std::string Nome;
    std::string CF;
    float Saldo;
};

#endif //TRANSAZIONI_FINANZIARIE_CC_H