#ifndef TRANSAZIONI_FINANZIARIE_CC_H
#define TRANSAZIONI_FINANZIARIE_CC_H

#include <vector>
#include "Cliente.h"

class CC {
private:
    Cliente &cliente;
    float saldo;
    int nEntrate;
    int nUscite;
    std::vector<float> entrate;
    std::vector<float> uscite;

public:
    CC(Cliente &cliente, float saldo);

    void bonificoEntrata(float valore);
    void bonificoUscita(float valore);

    void leggiEntrate() const;
    void leggiUscite() const;

    int getNumeroEntrate() const;
    int getNumeroUscite() const;
    const Cliente& getCliente() const;
    float getSaldo() const;
};

#endif // TRANSAZIONI_FINANZIARIE_CC_H