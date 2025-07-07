#include "CC.h"
#include "Client.h"

int main() {
    Cliente cliente1{"Rossi", "Mario", "RSSMRA80A01H501Z"};
    Cliente cliente2{"Bianchi", "Luigi", "BNCGLG85B01H501Y"};

    CC conto1("IT1234567890", cliente1, 0);
    CC conto2("IT0987654321", cliente2, 0);

    CC::searchIban("IT1234567890");
    CC::searchIban("IT0987654321");
    CC::searchIban("sds");

    CC::bonificoEntrata("IT1234567890", 500);
    CC::bonificoEntrata("IT0987654321", 200);
    CC::bonificoUscita("ca",2);

    CC::bonificoUscita("IT1234567890", 300);
    CC::bonificoUscita("IT0987654321", 100);
    CC::bonificoUscita("IT1234567890",200);

    CC::leggiEntrate("IT1234567890");
    CC::leggiUscite("IT1234567890");
    CC::leggiEntrate("IT0987654321");
    CC::leggiUscite("IT0987654321");

    CC::getNuscite("IT1234567890");

    CC::saveinFile("fileSave/fileSave.txt");
    CC::readFile("fileSave/fileSave.txt");

    return 0;
}