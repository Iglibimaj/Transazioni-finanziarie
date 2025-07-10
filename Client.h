//
// Created by bimaj on 03/07/2025.
//

#ifndef TRANSAZIONI_FINANZIARIE_CLIENT_H
#define TRANSAZIONI_FINANZIARIE_CLIENT_H

class Cliente {
public:
    std::string Cognome;
    std::string Nome;
    std::string CF;

    Cliente(std::string cognome, std::string nome, std::string cf);

    [[nodiscard]] const std::string &getNome() const;
    void setNome(const std::string &nome);
    [[nodiscard]] const std::string &getCognome() const;
    void setCognome(const std::string &cognome);
    [[nodiscard]] const std::string &getCf() const;
    void setCf(const std::string &cf);
};



#endif //TRANSAZIONI_FINANZIARIE_CLIENT_H
