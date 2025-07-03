//
// Created by bimaj on 03/07/2025.
//
#include "fstream"
#include "CC.h"
std::map<std::string, std::pair<CC::ClientInfo, float>> CC::ContoCorrente;
std::vector<std::pair<std::string, float>> CC::fileEntrate;
std::vector<std::pair<std::string, float>> CC::fileUscite;

CC::CC(std::string iban, const Cliente &cliente, float saldo)
        : Iban(std::move(iban)), Cognome(cliente.Cognome), Nome(cliente.Nome), CF(cliente.CF), Saldo(saldo) {
    if (ContoCorrente.find(iban) != ContoCorrente.end()) {
        std::cerr << "Errore nella creazione del conto corrente: IBAN già in uso.\n";
        return;
    }
    if (Saldo < 0) {
        std::cerr << "Errore nella creazione del conto: Il conto non può essere creato con valore negativo.\n";
        return;
    }
    ContoCorrente.insert({Iban, {{Cognome, Nome, CF}, Saldo}});
}
void CC::searchIban(const std::string &iban) { auto it = ContoCorrente.find(iban);
    if (it != ContoCorrente.end()) {
        const auto &account = it->second;
        std::cout << "Il conto corrente del signor/a " << account.first.Cognome << " " << account.first.Nome
                  <<" codice fiscale "<<account.first.CF<< " in questo momento ha " << account.second << " euro.\n";
    } else {
        std::cout << "IBAN non trovato.\n";
    }
}

void CC::bonificoEntrata(const std::string &iban, float valore) {
    if (valore <= 0) {
        std::cerr << "Bonifico non possibile: il bonifico in entrata non può essere negativo o uguale a zero\n";
        return;
    }
    auto it = ContoCorrente.find(iban);
    if (it != ContoCorrente.end()) {
        auto &account = it->second;
        account.second += valore;
        fileEntrate.emplace_back(iban,valore);

    } else {
        std::cerr << "Bonifico non possibile: IBAN non trovato per bonifico in entrata.\n";
        return;
    }
}

void CC::bonificoUscita(const std::string &iban, float valore) {if (valore <= 0) {
        std::cerr << "Bonifico non possibile: il bonifico in uscita non può essere negativo o uguale a zero\n";
        return;
    }
    auto it = ContoCorrente.find(iban);
    if (it != ContoCorrente.end()) {
        auto &account = it->second;
        if (account.second - valore < 0) {
            std::cerr << "Bonifico non possibile: il conto andrebbe in negativo";
            return;
        }
        account.second -= valore;
        fileUscite.emplace_back(iban, valore);

    } else {
        std::cerr << "Bonifico non possibile: IBAN non trovato per bonifico in uscita.\n";
        return;
    }
}

void CC::leggiEntrate(const std::string &iban) {
    auto it = ContoCorrente.find(iban);
    if (it != ContoCorrente.end()) {
        const auto &account = it->second;
        std::cout << "Entrate per il conto " << iban << ":\n";
        for (const auto &entrate: CC::fileEntrate) {
            std::cout << "IBAN: " << entrate.first << ", Valore: " << entrate.second << " euro\n";
        }
    } else {
        std::cout << "Conto non trovato.\n";
    }
}

void CC::leggiUscite(const std::string &iban) {
    auto it = ContoCorrente.find(iban);
    if (it != ContoCorrente.end()) {
        const auto &account = it->second;
        std::cout << "Uscite per il conto " << iban << ":\n";
        for (const auto &uscite: CC::fileUscite) {
            std::cout << "IBAN: " << uscite.first << ", Valore: " << uscite.second << " euro\n";
        }
    } else {
        std::cout << "Conto non trovato.\n";
    }
}

void CC::saveinFile(const std::string &nomeFile) {
    std::ofstream outFile(nomeFile);
    if (!outFile) {
        std::cerr << "Errore nell'aprire il file.\n";
        return;
    }
    for (const auto &it: ContoCorrente) {
        auto it2=it.second;
        outFile << it.first << " " << it2.first.Cognome << " " <<
                it2.first.Nome <<" "<<it2.first.CF<< " " << it2.second
                << "\n";
    }
    std::cout << "Dati salvati correttamente nel file: " << nomeFile << "\n";
}

void CC::readFile(const std::string &nomeFile) {
    std::ifstream inFile(nomeFile);
    if (!inFile) {
        std::cerr << "Errore nell'aprire il file per la lettura.\n";
        return;
    }
    CC::ContoCorrente.clear();
    std::string iban, cognome, nome, cf;
    float saldo;
    while (inFile >> iban >> cognome >> nome >> cf >> saldo) {
        CC::ContoCorrente[iban] = {{cognome, nome, cf}, saldo};
    }
    if (CC::ContoCorrente.empty()) {
        std::cerr << "Nessun dato è stato letto dal file.\n";
    } else {
        std::cout << "Dati caricati correttamente. Numero di conti: "
                  << CC::ContoCorrente.size() << "\n";
    }
    for (const auto &it: ContoCorrente) {
        const auto &account = it.second;
        std::cout << "Il conto " << it.first << " intesato al signor/a " << account.first.Cognome << " "
                  << account.first.Nome << " codice fiscale " << account.first.CF << " ha un saldo di "
                  << account.second << " Euro" << std::endl;
    }
}
