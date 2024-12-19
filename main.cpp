#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;
struct Pacient {
    string nume;
    int varsta;
    int severitate;
    int id;

    // Comparator pentru prioritizare
    bool operator<(const Pacient& other) const {
        if (severitate == other.severitate)
            return id > other.id; // Mai vechi are prioritate
        return severitate < other.severitate; // Severitatea mai mare are prioritate
    }
};

class Spital {
private:
    priority_queue<Pacient> coada;
    int id_counter = 0; // Contor pentru identificarea ordinii de sosire

public:
    void adaugaPacient(const string& nume, int varsta, int severitate) {
        Pacient pacient = {nume, varsta, severitate, id_counter++};
        coada.push(pacient);
        cout << "Pacientul " << nume << " a fost adaugat cu succes!\n";
    }

    void afiseazaPacienti() {
        if (coada.empty()) {
            cout << "Nu exista pacienti in coada.\n";
            return;
        }

        // Copie a cozii pentru iterare
        priority_queue<Pacient> temp = coada;
        cout << left << setw(15) << "Nume"
                  << setw(10) << "Varsta"
                  << setw(15) << "Severitate"
                  << "\n";
        cout << string(40, '-') << "\n";
        while (!temp.empty()) {
            Pacient p = temp.top();
            temp.pop();
            cout << left <<setw(15) << p.nume
                      << setw(10) << p.varsta
                      << setw(15) << p.severitate
                      << "\n";
        }
    }

    void eliminaPacient() {
        if (coada.empty()) {
            cout << "Nu exista pacienti de eliminat.\n";
            return;
        }
        Pacient tratat = coada.top();
        coada.pop();
        cout << "Pacientul " << tratat.nume << " a fost tratat si eliminat din coada.\n";
    }

    void cautaPacient(const string& nume) {
        // Copie a cozii pentru cautare
        priority_queue<Pacient> temp = coada;
        bool gasit = false;

        while (!temp.empty()) {
            Pacient p = temp.top();
            temp.pop();
            if (p.nume == nume) {
                cout << "Pacient gasit: \n";
                cout << "Nume: " << p.nume << ", Varsta: " << p.varsta
                          << ", Severitate: " << p.severitate << "\n";
                gasit = true;
                break;
            }
        }

        if (!gasit) {
            cout << "Pacientul " << nume << " nu a fost gasit.\n";
        }
    }
};

int main() {
    Spital spital;
    int optiune;

    do {
        cout << "\n--- Sistem de gestionare a cozii intr-un spital ---\n";
        cout << "1. Adauga pacient\n";
        cout << "2. Afiseaza pacienti\n";
        cout << "3. Elimina pacient\n";
        cout << "4. Cauta pacient\n";
        cout << "5. Iesire\n";
        cout << "Alegerea ta: ";
        cin >> optiune;
        cin.ignore(); // Pentru a consuma newline-ul ramas

        switch (optiune) {
            case 1: {
                string nume;
                int varsta, severitate;
                cout << "Introduceti numele pacientului: ";
                getline(cin, nume);
                cout << "Introduceti varsta pacientului: ";
                cin >> varsta;
                cout << "Introduceti severitatea cazului (1-10): ";
                cin >> severitate;
                spital.adaugaPacient(nume, varsta, severitate);
                break;
            }
            case 2:
                spital.afiseazaPacienti();
                break;
            case 3:
                spital.eliminaPacient();
                break;
            case 4: {
                string nume;
                cout << "Introduceti numele pacientului de cautat: ";
                getline(cin, nume);
                spital.cautaPacient(nume);
                break;
            }
            case 5:
                cout << "Iesire din program. La revedere!\n";
                break;
            default:
                cout << "Optiune invalida. Incercati din nou.\n";
        }
    } while (optiune != 5);

    return 0;
}
