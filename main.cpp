#include <iostream>
#include <vector>
#include <map>
#include <ostream>
#include <fstream>

class CC {
public:
    struct AccountInfo {
        std::string Cognome;
        std::string Nome;
        float Valore;
        std::vector<std::pair<int, float>> fileEntrate;
        std::vector<std::pair<int, float>> fileUscite;

    };

    std::map<std::string , AccountInfo> ContoCorrente;
    int transazioniCounterEntrata = 1;
    int transactionCounterUscita = 1;


    void bonificoEntrata(std::string& Iban, float valore) {
        auto it = ContoCorrente.find(Iban);
        if (it != ContoCorrente.end()) {
            it->second.Valore += valore;
            it->second.fileEntrate.emplace_back(Iban, valore);
            transazioniCounterEntrata++;
            std::cout<<"";
        }
    }

    void bonifocoUscita(std::string Iban, float valore) {
        auto it = ContoCorrente.find(Iban);
        if (it != ContoCorrente.end()) {
            it->second.Valore -= valore;
            it->second.fileUscite.emplace_back(Iban, valore);
            transactionCounterUscita++;
        }
    }

    void createCC(std::string& Iban, const std::string &Cognome, const std::string &Nome, float Valore) {
        ContoCorrente.insert({Iban, {Cognome, Nome, Valore}});
    }

    void searchIban(std::string& Iban) {
        auto it = ContoCorrente.find(Iban);
        if (it != ContoCorrente.end()) {
            const auto &account = it->second;
            std::cout << "Il conto corrente del signor/a " << account.Cognome << " " << account.Nome
                      << " in questo momento ha " << account.Valore << " euro.\n";
        }
    };

    void leggiEntrate(std::string& Iban) {
        auto it = ContoCorrente.find(Iban);
        if (it != ContoCorrente.end()) {
            const auto &account = it->second;
            std::cout << "Entrate per il conto " << Iban << ":\n";
            for (const auto &entrate : account.fileEntrate) {
                std::cout << "Transazione n." << entrate.first << ": " << entrate.second << " euro\n";
            }
        } else {
            std::cout << "Conto non trovato.\n";
        }
    }

    void leggiUscite(std::string& Iban){
        auto it= ContoCorrente.find(Iban);
        if(it!=ContoCorrente.end()){
            const auto &account=it->second;
            std::cout<<"Uscite per il cont "<<Iban<<"\n";
            for (const auto &uscite : account.fileUscite) {
                std::cout << "Transazione #" << uscite.first << ": " << uscite.second << " euro\n";
            }
        }
        else {
            std::cout << "Conto non trovato.\n";
        }
    }
};





int main() {
    //Classi che rappresentano transazioni finanziarie su un conto corrente(ingresso e uscita).
    //Le classi devono essere in grado di leggere e salvare i dati su file.

    return 0;
}

