#include <iostream>
#include <string>
#include <list>
#include <cstdlib>
#include <unistd.h>
#include <time.h>
#include <chrono>
#include <thread>

using namespace std;

class Auto{
    private:
        static Auto* instance;
        double costo;
        string modello;
        list<string> funzionalita;
        
    protected:
        Auto(){}
        void setCosto(double c) { costo = c; }
        void setModello(string m) { modello = m; }

    public:
        static Auto* Instance( string tipo ) {
            if(instance == 0)
                if(tipo == "Berlina"){
                    instance = new Auto();
                    instance -> setCosto(30000.0);
                    instance -> setModello("Berlina");
                }
                if(tipo == "Cabrio"){
                    instance = new Auto();
                    instance -> setCosto(15000.0);
                    instance -> setModello("Cabrio");
                }
                if(tipo == "Touring"){
                    instance = new Auto();
                    instance -> setCosto(43000.0);
                    instance -> setModello("Touring");
                }

            return instance;
        }
        float getCosto() { return costo; }
        string getModello() { return modello; }
        void aggiungiFunzionalita (string f, double d){
            this->funzionalita.push_back(f);
            this->costo += d;
        }
        void stampa() {
            system("clear"); cout << "\nLOADING...\n" << endl;
            srand(time(NULL)); unsigned int wait = rand() % 10+3;
            for(int i = 0 ; i < wait ; i++){ 
                cout << "*" ; 
                cout.flush();
                this_thread::sleep_for(chrono::milliseconds(1000) );
            }
            cout << endl;
            cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
            cout << "  MARCA: BMW" << endl;
            cout << "  MODELLO: " << this->modello << endl;
            cout << "  COSTO: " << this->costo << " €" << endl;
            cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n" << endl;
            cout << "#### FUNZIONALIA' EXTRA ####" << endl ;
            for(auto i : this->funzionalita)
                cout << i << endl ;
            cout << "############################" << endl ;
        }   
};

class Optional{
    private:
        string nome;
        double prezzo;
    public:
        Optional (string n, double p) : nome(n), prezzo(p){ }
        string getNome() { return this->nome; }
        double getPrezzo() { return this->prezzo; }
        void stampa(){ cout << nome << " - " << prezzo << " €" << endl; }
};

/*@@@@@@@@@@@@@@@@@@@@@@@@@@
*     F U N Z I O N I 
*@@@@@@@@@@@@@@@@@@@@@@@@@@*/

template <class T>
void funzionalitaAggiuntive(T* o){
    cout << "Ti mostreremo tutto ciò che puoi aggiungere, scrivi '1' e invia se vuoi accettare, altrimenti 0." << endl;

    list<Optional*> optional;
    optional.push_back(new Optional("[Compressore portatile]", 181.0));
    optional.push_back(new Optional("[Trasmettitore FM Bluetooth]", 91.0));
    optional.push_back(new Optional("[Proiettore HUD smartphone]", 71.0));
    optional.push_back(new Optional("[Ventole di raffreddamento]", 231.0));
    optional.push_back(new Optional("[\"Blob\" in gel per la pulizia]", 421.0));
    optional.push_back(new Optional("[Supporto smartphone con ricarica]", 31.0));

    int input;
    for(auto i:optional){
        i->stampa();
        cin >> input;
        if (input == 1){
            o->aggiungiFunzionalita(i->getNome(), i->getPrezzo());
            cout << "Optional aggiunto con successo!\n" << endl;
        }
        else if (input == 0){
            cout << "L'optional proposto è stato scartato con successo!\n" << endl;
        }
        else{
            cout << "Errore nell'inserimento! L'optional non è stato aggiunto.\n" << endl;
        }
        
    }

}

/*@@@@@@@@@@@@@@@@@@@@@@@@@@
*         M A I N
*@@@@@@@@@@@@@@@@@@@@@@@@@@*/

Auto* Auto::instance = 0;

int main(){
    char command;
    cout << "Benvenuto! Vuoi comprare una macchina? [Y,N] ->" ;
    cin >> command;
    if(command == 'N'){
        cout << "Arrivederci!" << endl;
        return 0;
    }
    while(command != 'Y'){
        cout << "Hai \ninserito un comando errato!" << endl;
        cout << "Vuoi comprare una macchina? [Y,N] ->" ;
        cin >> command;
    }
    cout << "Siamo lieti di presentarti il nostro nuovo sistema capace di modellare perfettametne ciò che desideri!" << endl;

    cout << "\nQuesti sono tutti i modelli BMW attualmente disponibili: " << endl;
    
    int modello;
    cout << "\nInserisci il numero indicato e premi Invio in base al modello che t'interessa!" << endl;
    cout << "[Berlina] -> - 1" << endl;
    cout << "[Cabrio] -> - 2" << endl;
    cout << "[Touring] -> - 3" << endl;
    cin >> modello;

    Auto* macchina;

    switch (modello)
    {
    case 1:{
        macchina = Auto::Instance("Berlina");
        break;
    }
    case 2:{
        macchina = Auto::Instance("Cabrio");
        break;
    }
    case 3:{
        macchina = Auto::Instance("Touring");
        break;
    }
    default:
        cout << "Errore rilevato nell'inserimento!";
        return 0;
    }
    
    cout << "Prezzo di partenza: " << macchina->getCosto() << " €" << endl;
    funzionalitaAggiuntive(macchina);
    macchina->stampa();

return 0;    
}
