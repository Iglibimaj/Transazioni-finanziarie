#include "Banca.h"

int main(){
    Cliente cliente("Bimaj","Igli","123");
    Cliente cliente1("Giovanni","zero","gg");

    CC conto(cliente,0);
    CC conto1(cliente1,0);

    Banca banca;

    banca.aggiungiConto("123",conto);
    banca.aggiungiConto("12345",conto1);

    Banca::displayCC("123");

    Banca::searchIban("123").bonificoEntrata(400);

    Banca::searchIban("12345").bonificoEntrata(200);

    Banca::searchIban("123").bonificoUscita(100);

    Banca::searchIban("123").bonificoUscita(200);

    Banca::searchIban("12345").bonificoUscita(50);

    Banca::searchIban("1234").bonificoEntrata(200);

    Banca::searchIban("123").leggiEntrate();
    Banca::searchIban("123").leggiUscite();

    Banca::searchIban("12345").leggiEntrate();
    Banca::searchIban("12345").leggiUscite();

    Banca::displayCC("123");
    Banca::displayCC("12345");

    banca.saveinFile("saveFile/saveFile.txt");
    banca.readFile("saveFile/saveFile.txt");

}