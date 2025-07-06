#ifndef TRANSAZIONI_FINANZIARIE_CC_H
#define TRANSAZIONI_FINANZIARIE_CC_H

#include "iostream"
#include "Client.h"
#include "map"

// Constructor for Cliente
Cliente::Cliente(std::string cognome, std::string nome, std::string cf)
        : Cognome(std::move(cognome)), Nome(std::move(nome)), CF(std::move(cf)) {}

#endif //TRANSAZIONI_FINANZIARIE_CC_H