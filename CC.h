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

    CC(const std::string& iban, const Cliente& cliente, float saldo);

    static void searchIban(const std::string& iban) ;
    void bonificoEntrata(float valore);
    void bonificoUscita(float valore);
    void leggiEntrate() const;
    void leggiUscite() const;
    static void saveinFile(const std::string& nomeFile) ;
    static void readFile(const std::string& nomeFile) ;

private:
    std::string Iban;
    std::string Cognome;
    std::string Nome;
    std::string CF;
    float Saldo;
    std::vector<std::pair<std::string, float>> fileEntrate;
    std::vector<std::pair<std::string, float>> fileUscite;
};

#endif //TRANSAZIONI_FINANZIARIE_CC_H