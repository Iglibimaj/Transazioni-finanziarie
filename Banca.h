#ifndef TRANSAZIONI_FINANZIARIE_BANCA_H
#define TRANSAZIONI_FINANZIARIE_BANCA_H

#include "iostream"
#include "CC.h"
#include "map"
class Banca {
public:
    void aggiungiConto(const std::string &iban,const CC &cc);
    static CC &searchIban(const std::string &iban);
    static void displayCC(const std::string &iban);
    void saveinFile(const std::string &nomeFile);
    void readFile(const std::string &nomeFile);

private:
    static std::map<std::string, CC> ContoCorrente;
};


#endif //TRANSAZIONI_FINANZIARIE_BANCA_H
