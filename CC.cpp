#include "CC.h"
#include "iostream"

CC::CC(Cliente &cliente, float saldo):cliente(cliente),saldo(saldo),nEntrate(0),nUscite(0) {

}

void CC::bonificoEntrata(float valore) {
    if(valore<=0){
        std::cout<<"Il bonifico in entrata non può essere negativo o uguale a zero";
        return;
    }
    nEntrate++;
    saldo+=valore;
    entrate.push_back(valore);
}

void CC::bonificoUscita(float valore) {
    if(valore<=0){
        std::cout<<"Il bonifico in uscita non può essere negativo o uguale a zero";
        return;
    }
    if(valore>saldo){
        std::cout<<"Bonifico in uscita non possibile il conto andrebbe in negativo";
    }
    nUscite++;
    saldo-=valore;
    uscite.push_back(valore);
}

void CC::leggiEntrate() const {
    const auto& cliente=getCliente();
    std::cout<<"Entrate per "<<cliente.getCognome()<<" "<< cliente.getNome()<<":\n";
    for(const auto& importo:entrate){
        std::cout<<"+"<<importo<<" ";
    }
    std::cout<<"\n\n";
}

void CC::leggiUscite() const {
    const auto& cliente=getCliente();
    std::cout<<"Uscite per "<<cliente.getCognome()<<" "<< cliente.getNome()<<":\n";
    for(const auto& importo:uscite){
        std::cout<<"-"<<importo<<" ";
    }
    std::cout<<"\n\n";
}

int CC::getNumeroEntrate() const {return nEntrate;};
int CC::getNumeroUscite() const {return nUscite;};
const Cliente& CC::getCliente() const {return cliente;};
float CC::getSaldo() const {return saldo;};