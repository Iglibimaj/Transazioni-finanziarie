#include <iostream>
#include <vector>
#include <map>
#include <fstream>

class CC {
public:
    struct AccountInfo {
        std::string Cognome;
        std::string Nome;
        float Valore;
        std::vector<std::pair<std::string, float>> fileEntrate;
        std::vector<std::pair<std::string, float>> fileUscite;
    };

    std::map<std::string, AccountInfo> ContoCorrente;

    CC(const std::string& Iban, const std::string& Cognome, const std::string& Nome, float Valore) {
        ContoCorrente.insert({Iban, {Cognome, Nome, Valore}});
    }

    void bonificoEntrata(const std::string& Iban, float valore) {
        auto it = ContoCorrente.find(Iban);
        if (it != ContoCorrente.end()) {
            it->second.Valore += valore;
            it->second.fileEntrate.emplace_back(Iban, valore);
        } else {
            std::cerr << "Errore: IBAN non trovato per bonifico di entrata.\n";
        }
    }

    void bonificoUscita(const std::string& Iban, float valore) {
        auto it = ContoCorrente.find(Iban);
        if (it != ContoCorrente.end()) {
            it->second.Valore -= valore;
            it->second.fileUscite.emplace_back(Iban, valore);
        } else {
            std::cerr << "Errore: IBAN non trovato per bonifico di uscita.\n";
        }
    }

    void searchIban(const std::string& Iban) const {
        auto it = ContoCorrente.find(Iban);
        if (it != ContoCorrente.end()) {
            const auto& account = it->second;
            std::cout << "Il conto corrente del signor/a " << account.Cognome << " " << account.Nome
                      << " in questo momento ha " << account.Valore << " euro.\n";
        } else {
            std::cout << "IBAN non trovato.\n";
        }
    }

    void leggiEntrate(const std::string& Iban) const {
        auto it = ContoCorrente.find(Iban);
        if (it != ContoCorrente.end()) {
            const auto& account = it->second;
            std::cout << "Entrate per il conto " << Iban << ":\n";
            for (const auto& entrate : account.fileEntrate) {
                std::cout << "IBAN: " << entrate.first << ", Valore: " << entrate.second << " euro\n";
            }
        } else {
            std::cout << "Conto non trovato.\n";
        }
    }

    void leggiUscite(const std::string& Iban) const {
        auto it = ContoCorrente.find(Iban);
        if (it != ContoCorrente.end()) {
            const auto& account = it->second;
            std::cout << "Uscite per il conto " << Iban << ":\n";
            for (const auto& uscite : account.fileUscite) {
                std::cout << "IBAN: " << uscite.first << ", Valore: " << uscite.second << " euro\n";
            }
        } else {
            std::cout << "Conto non trovato.\n";
        }
    }

    void saveinFile(const std::string& nomeFile) const {
        std::ofstream outFile(nomeFile);
        if (!outFile) {
            std::cerr << "Errore nell'aprire il file.\n";
            return;
        }
        for (const auto& item : ContoCorrente) {
            outFile << item.first << ":"
                    << item.second.Cognome << " "
                    << item.second.Nome << " "
                    << item.second.Valore << "\n";
        }
        if (!outFile.good()) {
            std::cerr << "Errore durante la scrittura del file.\n";
        }
    }
};

int main(){
    return 0;
}