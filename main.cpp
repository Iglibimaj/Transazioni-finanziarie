#include "CC.h"
#include "Client.h"

int main() {
    Cliente cliente1{"Rossi", "Mario", "RSSMRA80A01H501Z"};
    Cliente cliente2{"Bianchi", "Luigi", "BNCGLG85B01H501Y"};

    CC conto1("IT1234567890", cliente1, 1000);
    CC conto2("IT0987654321", cliente2, 500);

    CC::searchIban("IT1234567890");
    CC::searchIban("IT0987654321");
    CC::searchIban("INVALID_IBAN");

    conto1.bonificoEntrata(500);
    conto2.bonificoEntrata(600);
    conto1.bonificoEntrata(300);
    conto2.bonificoEntrata(100);

    conto1.bonificoUscita(300);
    conto2.bonificoUscita(200);
    conto1.bonificoUscita(500);
    conto2.bonificoUscita(100);

    conto1.leggiEntrate();
    conto2.leggiEntrate();

    conto1.leggiUscite();
    conto2.leggiUscite();

    CC::saveinFile("fileSave/fileSave.txt");
    CC::readFile("fileSave/fileSave.txt");

    return 0;
}