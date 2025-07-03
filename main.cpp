#include <iostream>
#include <utility>
#include <vector>
#include <map>
#include <fstream>

#include "Client.h"
#include "CC.h"

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
    CC::bonificoEntrata("qwe", 5);
//20
    CC::bonificoEntrata("1263298d", 400);
    CC::saveinFile("fileSave/fileSave.txt");
    CC::readFile("fileSave/fileSave.txt");
    return 0;
}