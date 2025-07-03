//
// Created by bimaj on 03/07/2025.
//

#include "iostream"
#include "Client.h"
Cliente::Cliente(std::string cognome, std::string nome, std::string cf)
        :Cognome(std::move(cognome)), Nome(std::move(nome)), CF(std::move(cf)) {}

