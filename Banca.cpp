#include "Banca.h"
#include "fstream"
#include "iostream"
#include "sstream"
#include "utility"

std::map<std::string, CC> Banca::ContoCorrente;

void Banca::aggiungiConto(const std::string &iban, const CC &cc) {
    if (ContoCorrente.find(iban) != ContoCorrente.end()) {
        std::cout << "L'IBAN " << iban << " è già stato utilizzato. \n";
        return;
    }
    ContoCorrente.insert({iban, cc});
    std::cout << "Conto con IBAN" << iban << " aggiunto correttamente. \n";
    std::cout << "\n";
}

CC &Banca::searchIban(const std::string &iban) {
    auto it = ContoCorrente.find(iban);
    if (it != ContoCorrente.end()) {
        return it->second;
    }
    std::ostringstream oss;
    oss << "Iban" << iban << " non trovato per una operazione bancaria\n\n";
    std::cout << oss.str();
    static Cliente cliente("", "", "");
    static CC dummy(cliente, 0);
    return dummy;
}

void Banca::displayCC(const std::string &iban) {
    auto it = ContoCorrente.find(iban);
    if (it != ContoCorrente.end()) {
        const auto &cliente = it->second.getCliente();
        std::cout << "IBAN: " << iban << "\n"
                  << "Cognome: " << cliente.getCognome() << "\n"
                  << "Nome: " << cliente.getNome() << "\n"
                  << "CF: " << cliente.getCf() << "\n"
                  << "Saldo: " << it->second.getSaldo() << "\n\n";
    } else {
        std::cout << "Iban " << iban << " non trovato per il display.\n\n";
    }
}

void Banca::saveinFile(const std::string &nomeFile) {
    std::ofstream outFile(nomeFile);
    if (!outFile) {
        std::cerr << "Errore nell'aprire il file.\n";
        return;
    }
    for (const auto &it: ContoCorrente) {
        const auto &account = it.second.getCliente();
        outFile << it.first << " " << account.getCognome() << " "
                << account.getNome() << " " << account.getCf() << " "
                << it.second.getSaldo() << "\n";
    }
    std::cout << "Dati salvati correttamente nel file: " << nomeFile << "\n\n";
}

void Banca::readFile(const std::string &nomeFile) {
    std::ifstream inFile(nomeFile);
    if (!inFile) {
        std::cerr << "Errore nell'apertura del file " << nomeFile << "\n";
        return;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        std::istringstream iss(line);
        std::string iban, cognome, nome, cf;
        float saldo;
        if (iss >> iban >> cognome >> nome >> cf >> saldo) {
            Cliente letturaCliente(cognome, nome, cf);
            CC letturaConto(letturaCliente, saldo);
            ContoCorrente.emplace(iban, std::move(letturaConto));
        }
    }

    std::cout << "Conti caricati: " << ContoCorrente.size() << "\n";
    for (const auto &[iban, conto]: ContoCorrente) {
        const auto &cliente = conto.getCliente();
        std::cout << "Il conto con IBAN: " << iban
                  << " intestato al signor/a " << cliente.getCognome() << " " << cliente.getNome() << " (codice fiscale "
                  << cliente.getCf() << ") ha un saldo di " << conto.getSaldo() << " Euro\n";
    }

}