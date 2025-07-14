#include "Cliente.h"

Cliente::Cliente(std::string cognome, std::string nome, std::string cf):
        Cognome(std::move(cognome)),Nome(std::move(nome)),Cf(std::move(cf)){}

std::string Cliente::getNome() const {return Nome;}
std::string Cliente::getCognome() const {return Cognome;}
std::string Cliente::getCf() const {return Cf;}