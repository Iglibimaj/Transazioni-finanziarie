#include "fstream"
#include "CC.h"

std::map<std::string, std::pair<CC::ClientInfo, float>> CC::ContoCorrente;
std::map<std::string, std::vector<float>> CC::fileEntrate;
std::map<std::string, std::vector<float>> CC::fileUscite;
std::map<std::string, int> CC::nEntrate;
std::map<std::string, int> CC::nUscite;


CC::CC(const std::string &iban, const Cliente &cliente, float saldo)
        : Iban(iban), Cognome(cliente.Cognome), Nome(cliente.Nome), CF(cliente.CF), Saldo(saldo) {
    if (ContoCorrente.find(iban) != ContoCorrente.end()) {
        std::cout << "Errore nella creazione del conto corrente: IBAN già in uso.\n";
        return;
    }
    if (Saldo < 0) {
        std::cout << "Errore nella creazione del conto: Il conto non può essere creato con valore negativo.\n";
        return;
    }
    ClientInfo info = {Cognome, Nome, CF};
    ContoCorrente[Iban] = {info, Saldo};
    fileEntrate[Iban] = {};
    fileUscite[Iban] = {};
    nEntrate[Iban] = 0;
    nUscite[Iban] = 0;


}

void CC::searchIban(const std::string &iban) {
    auto it = ContoCorrente.find(iban);
    if (it != ContoCorrente.end()) {
        std::cout << "IBAN: " << iban << "\n"
                  << "Cognome: " << it->second.first.Cognome << "\n"
                  << "Nome: " << it->second.first.Nome << "\n"
                  << "CF: " << it->second.first.CF << "\n"
                  << "Saldo: " << it->second.second << "\n"
                  << "\n";
    } else {
        std::cout << "Iban " << iban << " non trovato\n";
        std::cout << "\n";
    }
}

void CC::bonificoEntrata(const std::string &iban, float valore) {
    if (valore <= 0) {
        std::cout << "Bonifico non possibile: il bonifico in entrata non può essere negativo o uguale a zero\n";
        std::cout << "\n";
        return;
    }
    auto it = ContoCorrente.find(iban);
    if (it != ContoCorrente.end()) {
        auto &acc = it->second;
        acc.second += valore;
        fileEntrate[iban].emplace_back(valore);
        nEntrate[iban]++;
    } else {
        std::cout << "Bonifico non possibile, IBAN " << iban << " non trovato per bonifico in entrata.\n";
        std::cout << "\n";
    }
}

void CC::bonificoUscita(const std::string &iban, float valore) {
    if (valore <= 0) {
        std::cout << "Bonifico in uscita non possibile per il conto con IBAN "<<iban<<": il bonifico in uscita non può essere negativo o uguale a zero\n";
        std::cout << "\n";
        return;
    }
    auto it = ContoCorrente.find(iban);
    if (it != ContoCorrente.end()) {
        auto &account = it->second;
        if (account.second - valore < 0) {
            std::cout << "Bonifico in uscita non possibile per il conto con IBAN "<<iban <<": il conto andrebbe in negativo\n";
            std::cout << "\n";
            return;
        }
        account.second -= valore;
        fileUscite[iban].emplace_back(valore);
        nUscite[iban]++;
    } else {
        std::cout << "Bonifico non possibile: IBAN " << iban << " non trovato per bonifico in uscita.\n";
        std::cout << "\n";
    }
}

void CC::leggiEntrate(const std::string &iban) {
    auto it = fileEntrate.find(iban);
    if (it != fileEntrate.end()) {
        std::cout << "Entrate per il conto " << iban << ":\n";
        for (const auto &entrata: it->second) {
            std::cout << "Valore: " << entrata << " euro\n";
        }
        std::cout << "\n";
    } else {
        std::cout << "Impossibile ottenere le entrate: IBAN " << iban << " non trovato per leggere le entrate.\n";
        std::cout << "\n";
    }
}

void CC::leggiUscite(const std::string &iban) {
    auto it = fileUscite.find(iban);
    if (it != fileUscite.end()) {
        std::cout << "Uscite per il conto " << iban << ":\n";
        for (const auto &uscita: it->second) {
            std::cout << "Valore: " << uscita << " euro\n";
        }
        std::cout << "\n";
    } else {
        std::cout << "Impossibile lggere le uscite: IBAN " << iban << " non trovato per leggere le uscite.\n";
        std::cout << "\n";
    }
}

void CC::saveinFile(const std::string &nomeFile) {
    std::ofstream outFile(nomeFile);
    if (!outFile) {
        std::cout << "Errore nell'aprire il file.\n";
        return;
    }
    for (const auto &it: ContoCorrente) {
        const auto &account = it.second;
        outFile << it.first << " " << account.first.Cognome << " "
                << account.first.Nome << " " << account.first.CF << " "
                << account.second << "\n";
    }
    std::cout << "Dati salvati correttamente nel file: " << nomeFile << "\n";
    std::cout << "\n";
}

void CC::readFile(const std::string &nomeFile) {
    std::ifstream inFile(nomeFile);
    if (!inFile) {
        std::cout << "Errore nell'aprire il file per la lettura.\n";
        return;
    }
    ContoCorrente.clear();
    std::string iban, cognome, nome, cf;
    float saldo;
    while (inFile >> iban >> cognome >> nome >> cf >> saldo) {
        ContoCorrente[iban] = {{cognome, nome, cf}, saldo};
    }
    if (ContoCorrente.empty()) {
        std::cout << "Nessun dato è stato letto dal file.\n";
    } else {
        std::cout << "Dati caricati correttamente. Numero di conti: "
                  << ContoCorrente.size() << "\n";
    }
    for (const auto &it: ContoCorrente) {
        const auto &account = it.second;
        std::cout << "Il conto " << it.first << " intesato al signor/a "
                  << account.first.Cognome << " " << account.first.Nome
                  << " codice fiscale " << account.first.CF
                  << " ha un saldo di " << account.second << " Euro\n";
    }
}

float CC::getSaldo(const std::string &iban) {
    auto it = ContoCorrente.find(iban);
    if (it != ContoCorrente.end()) {
        return it->second.second;
    }
    std::cout << "Lettura saldo non possibile: IBAN " << iban << " non esistente.\n";
    return 0;
}

int CC::getNuscite(const std::string &iban) {
    auto it = nUscite.find(iban);
    if (it != nUscite.end()) {
        std::cout << "Numero uscite per il conto " << iban << ": " << it->second << "\n";
        return it->second;
    }
    std::cout << "Numero uscite non ottenibile: IBAN " << iban << " non trovato.\n";
    return 0;
}

int CC::getNentrate(const std::string &iban) {
    auto it = nEntrate.find(iban);
    if (it != nEntrate.end()) {
        std::cout << "Numero entrate per il conto " << iban << ": " << it->second << "\n";
        return it->second;
    }
    std::cout << "Numero entrate non ottenibile: IBAN " << iban << " non trovato.\n";
    return 0;
}

void CC::resetStaticState() {
    ContoCorrente.clear();
    fileEntrate.clear();
    fileUscite.clear();
    nEntrate.clear();
    nUscite.clear();
}


