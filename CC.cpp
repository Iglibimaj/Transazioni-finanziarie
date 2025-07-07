#include "fstream"
#include "CC.h"

std::map<std::string, std::pair<CC::ClientInfo, float>> CC::ContoCorrente;
std::map<std::string, std::vector<float>> CC::fileEntrate;
std::map<std::string, std::vector<float>> CC::fileUscite;

CC::CC(const std::string &iban, const Cliente &cliente, float saldo)
        : Iban(iban), Cognome(cliente.Cognome), Nome(cliente.Nome), CF(cliente.CF), Saldo(saldo) {
    if (ContoCorrente.find(iban) != ContoCorrente.end()) {
        std::cerr << "Errore nella creazione del conto corrente: IBAN già in uso.\n";
        return;
    }
    if (Saldo < 0) {
        std::cerr << "Errore nella creazione del conto: Il conto non può essere creato con valore negativo.\n";
        return;
    }
    ClientInfo info = {Cognome, Nome, CF};
    ContoCorrente[Iban] = {info, Saldo};
    fileEntrate[iban] = {};
    fileUscite[iban] = {};
}

void CC::searchIban(const std::string &iban) {
    auto it = ContoCorrente.find(iban);
    if (it != ContoCorrente.end()) {
        std::cout << "IBAN: " << iban << "\n"
                  << "Cognome: " << it->second.first.Cognome << "\n"
                  << "Nome: " << it->second.first.Nome << "\n"
                  << "CF: " << it->second.first.CF << "\n"
                  << "Saldo: " << it->second.second << "\n"
                  <<"\n";
    } else {
        std::cout << "Iban "<<iban<<" non trovato\n";
        std::cout<<"\n";
    }
}

void CC::bonificoEntrata(const std::string &iban, float valore) {
    if (valore <= 0) {
        std::cerr << "Bonifico non possibile: il bonifico in entrata non può essere negativo o uguale a zero\n";
        return;
    }
    auto it = ContoCorrente.find(iban);
    if (it != ContoCorrente.end()) {
        auto &acc = it->second;
        acc.second += valore;
        fileEntrate[iban].emplace_back( valore);
    } else {
        std::cerr << "Bonifico non possibile: IBAN non trovato per bonifico in entrata.\n";
    }
}

void CC::bonificoUscita(const std::string &iban,float valore) {
    if (valore <= 0) {
        std::cerr << "Bonifico non possibile: il bonifico in uscita non può essere negativo o uguale a zero\n";
        return;
    }
    auto it = ContoCorrente.find(iban);
    if (it != ContoCorrente.end()) {
        auto &account = it->second;
        if (account.second - valore < 0) {
            std::cerr << "Bonifico non possibile: il conto andrebbe in negativo\n";
            return;
        }
        account.second -= valore;
        fileUscite[iban].emplace_back(valore);
    } else {
        std::cerr << "Bonifico non possibile: IBAN non trovato per bonifico in uscita.\n";
    }
}

void CC::leggiEntrate(const std::string& iban) {
    auto it = fileEntrate.find(iban);
    if (it != fileEntrate.end()) {
        std::cout << "Entrate per il conto " << iban << ":\n";
        for (const auto& entrata : it->second) {
            std::cout << "Valore: " << entrata << " euro\n";
        }
        std::cout << "\n";
    } else {
        std::cerr << "Errore: IBAN non trovato per leggere le entrate.\n";
    }
}

void CC::leggiUscite(const std::string& iban) {
    auto it = fileUscite.find(iban);
    if (it != fileUscite.end()) {
        std::cout << "Uscite per il conto " << iban << ":\n";
        for (const auto& uscita : it->second) {
            std::cout << "Valore: " << uscita << " euro\n";
        }
        std::cout << "\n";
    } else {
        std::cerr << "Errore: IBAN non trovato per leggere le uscite.\n";
    }
}

void CC::saveinFile(const std::string &nomeFile) {
    std::ofstream outFile(nomeFile);
    if (!outFile) {
        std::cerr << "Errore nell'aprire il file.\n";
        return;
    }
    for (const auto &it : ContoCorrente) {
        const auto &account = it.second;
        outFile << it.first << " " << account.first.Cognome << " "
                << account.first.Nome << " " << account.first.CF << " "
                << account.second << "\n";
    }
    std::cout << "Dati salvati correttamente nel file: " << nomeFile << "\n";
    std::cout<<"\n";
}

void CC::readFile(const std::string &nomeFile) {
    std::ifstream inFile(nomeFile);
    if (!inFile) {
        std::cerr << "Errore nell'aprire il file per la lettura.\n";
        return;
    }
    ContoCorrente.clear();
    std::string iban, cognome, nome, cf;
    float saldo;
    while (inFile >> iban >> cognome >> nome >> cf >> saldo) {
        ContoCorrente[iban] = {{cognome, nome, cf}, saldo};
    }
    if (ContoCorrente.empty()) {
        std::cerr << "Nessun dato è stato letto dal file.\n";
    } else {
        std::cout << "Dati caricati correttamente. Numero di conti: "
                  << ContoCorrente.size() << "\n";
    }
    for (const auto &it : ContoCorrente) {
        const auto &account = it.second;
        std::cout << "Il conto " << it.first << " intesato al signor/a "
                  << account.first.Cognome << " " << account.first.Nome
                  << " codice fiscale " << account.first.CF
                  << " ha un saldo di " << account.second << " Euro\n";
    }
}

