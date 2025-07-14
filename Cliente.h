#ifndef TRANSAZIONI_FINANZIARIE_CLIENTE_H
#define TRANSAZIONI_FINANZIARIE_CLIENTE_H
#include "string"
class Cliente{
public:
    Cliente(std::string cognome,std::string nome,std::string cf);
    [[nodiscard]] std::string getNome() const;
    [[nodiscard]] std::string getCognome() const;
    [[nodiscard]] std::string getCf() const;

private:
    std::string Cognome;
    std::string Nome;
    std::string Cf;
};



#endif //TRANSAZIONI_FINANZIARIE_CLIENTE_H
