#include <iostream>
#include <utility>
#include <vector>
#include <map>
#include <fstream>
//Classi che rappresentano transazioni finanziarie su un conto corrente (ingresso e uscita).
//Le classi devono essere in grado di leggere e salvare i dati su file.

class Cliente {
public:
    std::string Cognome;
    std::string Nome;
    std::string CF;

    Cliente(std::string cognome, std::string nome, std::string cf)
            : Cognome(std::move(cognome)), Nome(std::move(nome)), CF(std::move(cf)) {}
};

class CC {
public:
    std::string Iban;
    std::string Cognome;
    std::string Nome;
    std::string CF;

    struct AccountInfo {
        std::string Cognome;
        std::string Nome;
        float Valore{};
        std::string CF;
        std::vector<std::pair<std::string, float>> fileEntrate;
        std::vector<std::pair<std::string, float>> fileUscite;
    };

    static std::map<std::string, AccountInfo> ContoCorrente;

    CC(std::string iban, const Cliente &cliente, float valore)
            : Iban(std::move(iban)), Cognome(cliente.Cognome), Nome(cliente.Nome), CF(cliente.CF) {
        if (ContoCorrente.find(iban) != ContoCorrente.end()) {
            std::cerr << "Errore nella creazione del conto corrente: IBAN già in uso.\n";
            return;
        }
        if (valore < 0) {
            std::cerr << "Errore nella creazione del conto: Il conto non può essere creato con valore negativo.\n";
            return;
        }
        ContoCorrente.insert({Iban, {Cognome, Nome, valore,CF}});
    }

    static void searchIban(const std::string &iban) {
        auto it = ContoCorrente.find(iban);
        if (it != ContoCorrente.end()) {
            const auto &account = it->second;
            std::cout << "Il conto corrente del signor/a " << account.Cognome << " " << account.Nome
                      <<" codice fiscale "<<account.CF<< " in questo momento ha " << account.Valore << " euro.\n";
        } else {
            std::cout << "IBAN non trovato.\n";
        }
    }

    static void bonificoEntrata(const std::string &iban, float valore) {
        if (valore <= 0) {
            std::cerr << "Bonifico non possibile: il bonifico in entrata non può essere negativo o uguale a zero\n";
            return;
        }
        auto it = ContoCorrente.find(iban);
        if (it != ContoCorrente.end()) {
            it->second.Valore += valore;
            it->second.fileEntrate.emplace_back(iban, valore);
        } else {
            std::cerr << "Bonifico non possibile: IBAN non trovato per bonifico in entrata.\n";
            return;
        }
    }

    static void bonificoUscita(const std::string &iban, float valore) {
        if (valore <= 0) {
            std::cerr << "Bonifico non possibile: il bonifico in uscita non può essere negativo o uguale a zero\n";
            return;
        }
        auto it = ContoCorrente.find(iban);
        if (it != ContoCorrente.end()) {
            if (it->second.Valore - valore < 0) {
                std::cerr << "Bonifico non possibile: il conto andrebbe in negativo";
                return;
            }
            it->second.Valore -= valore;
            it->second.fileUscite.emplace_back(iban, valore);
        } else {
            std::cerr << "Bonifico non possibile: IBAN non trovato per bonifico in uscita.\n";
            return;
        }


    }


    static void leggiEntrate(const std::string &iban) {
        auto it = ContoCorrente.find(iban);
        if (it != ContoCorrente.end()) {
            const auto &account = it->second;
            std::cout << "Entrate per il conto " << iban << ":\n";
            for (const auto &entrate: account.fileEntrate) {
                std::cout << "IBAN: " << entrate.first << ", Valore: " << entrate.second << " euro\n";
            }
        } else {
            std::cout << "Conto non trovato.\n";
        }
    }

    static void leggiUscite(const std::string &iban) {
        auto it = ContoCorrente.find(iban);
        if (it != ContoCorrente.end()) {
            const auto &account = it->second;
            std::cout << "Uscite per il conto " << iban << ":\n";
            for (const auto &uscite: account.fileUscite) {
                std::cout << "IBAN: " << uscite.first << ", Valore: " << uscite.second << " euro\n";
            }
        } else {
            std::cout << "Conto non trovato.\n";
        }
    }

    static void saveinFile(const std::string &nomeFile) {
        std::ofstream outFile(nomeFile);
        if (!outFile) {
            std::cerr << "Errore nell'aprire il file.\n";
            return;
        }
        for (const auto &item: ContoCorrente) {
            outFile << item.first << " " << item.second.Cognome << " " <<
                    item.second.Nome <<" "<<item.second.CF<< " " << item.second.Valore
                    << "\n";
        }
        std::cout << "Dati salvati correttamente nel file: " << nomeFile << "\n";
    }

    static void readFile(const std::string &nomeFile) {
        std::ifstream inFile(nomeFile);
        if (!inFile) {
            std::cerr << "Errore nell'aprire il file per la lettura.\n";
            return;
        }
        CC::ContoCorrente.clear();
        std::string iban, cognome, nome, cf;
        float valore;
        while (inFile >> iban >> cognome >> nome >> cf >> valore) {
            CC::ContoCorrente[iban] = {cognome, nome, valore, cf}; // Corrected assignment order
        }
        if (CC::ContoCorrente.empty()) {
            std::cerr << "Nessun dato è stato letto dal file.\n";
        } else {
            std::cout << "Dati caricati correttamente. Numero di conti: "
                      << CC::ContoCorrente.size() << "\n";
        }
        for (const auto &it: ContoCorrente) {
            const auto &account = it.second;
            std::cout << "Il conto " << it.first << " intesato al signor/a " << account.Cognome << " "
                      << account.Nome << " codice fiscale " << account.CF << " ha un saldo di "
                      << account.Valore << " Euro" << std::endl;
        }
    }
};


std::map<std::string, CC::AccountInfo> CC::ContoCorrente;

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