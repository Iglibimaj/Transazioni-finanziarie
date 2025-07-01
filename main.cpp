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

    CC(const std::string &Iban, const std::string &Cognome, const std::string &Nome, float Valore) {
        auto it = ContoCorrente.find(Iban);
        if (Valore < 0) {
            std::cerr << "Errore nella creazione del conto: Il conto non può essere creato con valore negativo";
            return;
        }
        if (it != ContoCorrente.end()) {
            std::cerr << "Errore nella creazione del conto corrente: IBAN già in uso";
            return;
        }
        ContoCorrente.insert({Iban, {Cognome, Nome, Valore}});
    }

    void searchIban(const std::string &Iban) const {
        auto it = ContoCorrente.find(Iban);
        if (it != ContoCorrente.end()) {
            const auto &account = it->second;
            std::cout << "Il conto corrente del signor/a " << account.Cognome << " " << account.Nome
                      << " in questo momento ha " << account.Valore << " euro.\n";
        } else {
            std::cout << "IBAN non trovato.\n";
        }
    }

    void bonificoEntrata(const std::string &Iban, float valore) {
        if (valore <= 0) {
            std::cerr << "Bonifico non possibile: il bonifico in entrata non può essere negativo o uguale a zero\n";
            return;
        }
            auto it = ContoCorrente.find(Iban);
            if (it != ContoCorrente.end()) {
                it->second.Valore += valore;
                it->second.fileEntrate.emplace_back(Iban, valore);
            } else {
                std::cerr << "Bonifico non possibile: IBAN non trovato per bonifico in entrata.\n";
                return;
            }
    }

    void bonificoUscita(const std::string &Iban, float valore) {
        if (valore <= 0) {
            std::cerr << "Bonifico non possibile: il bonifico in uscita non può essere negativo o uguale a zero\n";
            return;
        } else {
            auto it = ContoCorrente.find(Iban);
            if (it != ContoCorrente.end()) {
                it->second.Valore -= valore;
                it->second.fileUscite.emplace_back(Iban, valore);
            } else {
                std::cerr << "Bonifico non possibile: IBAN non trovato per bonifico in uscita.\n";
                return;
            }
            if (it->second.Valore - valore < 0) {
                std::cerr << "Bonifico non possibile: il conto andrebbe in negativo";
                return;
            }
        }
    }


    void leggiEntrate(const std::string &Iban) const {
        auto it = ContoCorrente.find(Iban);
        if (it != ContoCorrente.end()) {
            const auto &account = it->second;
            std::cout << "Entrate per il conto " << Iban << ":\n";
            for (const auto &entrate: account.fileEntrate) {
                std::cout << "IBAN: " << entrate.first << ", Valore: " << entrate.second << " euro\n";
            }
        } else {
            std::cout << "Conto non trovato.\n";
        }
    }

    void leggiUscite(const std::string &Iban) const {
        auto it = ContoCorrente.find(Iban);
        if (it != ContoCorrente.end()) {
            const auto &account = it->second;
            std::cout << "Uscite per il conto " << Iban << ":\n";
            for (const auto &uscite: account.fileUscite) {
                std::cout << "IBAN: " << uscite.first << ", Valore: " << uscite.second << " euro\n";
            }
        } else {
            std::cout << "Conto non trovato.\n";
        }
    }

    void saveinFile(const std::string &nomeFile) const {
        std::ofstream outFile(nomeFile);
        if (!outFile) {
            std::cerr << "Errore nell'aprire il file.\n";
            return;
        }
        for (const auto &item: ContoCorrente) {
            outFile << item.first << ":"
                    << item.second.Cognome << " "
                    << item.second.Nome << " "
                    << item.second.Valore << "\n";
        }
    }
};

int main() {
    return 0;
}