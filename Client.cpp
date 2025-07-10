#ifndef TRANSAZIONI_FINANZIARIE_CC_H
#define TRANSAZIONI_FINANZIARIE_CC_H

#include "iostream"
#include "Client.h"
#include "map"

Cliente::Cliente(std::string cognome, std::string nome, std::string cf)
        : Cognome(std::move(cognome)), Nome(std::move(nome)), CF(std::move(cf)) {}
const std::string &Cliente::getNome() const {
    return Nome;
}
void Cliente::setNome(const std::string &nome) {
    Cliente::Nome = nome;
}
const std::string &Cliente::getCognome() const {
    return Cognome;
}
void Cliente::setCognome(const std::string &cognome) {
    Cliente::Cognome = cognome;
}
const std::string &Cliente::getCf() const {
    return CF;
}

void Cliente::setCf(const std::string &cf) {
    Cliente::CF = cf;
}
#endif //TRANSAZIONI_FINANZIARIE_CC_H