#include "Client.h"
#include "CC.h"

//Classi che rappresentano transazioni finanziarie su un conto corrente (ingresso e uscita).
//Le classi devono essere in grado di leggere e salvare i dati su file.

int main() {
    Cliente cliente("Bimaj", "Igli", "BMJGLI32F34F534A");
    CC cc("12fe534", cliente, 0);

    Cliente cliente1("dds", "adsa", "asd");
    CC cc2("qwe", cliente1, 0);

    Cliente cliente2("Francesco", "Rossi", "FRNRSS123d46f");
    CC cc3("1263298d", cliente2, 0);

    CC::bonificoEntrata("12fe534", 500);
    CC::bonificoEntrata("12fe534", 1500);
    CC::bonificoUscita("12fe534", 500);
//1600
    CC::bonificoEntrata("qwe", 25);
//20
    CC::bonificoEntrata("1263298d", 400);
    CC::saveinFile("saveFile/saveFile.txt");
    CC::readFile("saveFile/saveFile.txt");
    return 0;
}
//creazione header
//correzione read fatto
//unittesting Googletest
//path relativi fatto