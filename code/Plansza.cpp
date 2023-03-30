#include "Plansza.h"

using namespace std;

Plansza::Plansza(int x) : x(x){
    plansza = new char*[x];
    for(int i=0; i<x; i++){
        plansza[i] = new char[x];
        for(int j=0; j<x;j++){
            plansza[i][j] = 'o';
        }
    }
}
Plansza::~Plansza(){
    for(int i=0; i<x; i++){
        delete[] plansza[i];
    }
    delete[] plansza;
}
char Plansza::zwrocPole(int w, int k){
    return plansza[w][k];
}
void Plansza::ustawPole(int w, int k, char wartosc){
    plansza[w][k] = wartosc;
}
void Plansza::pokazPlansze(int licznik, const vector<Statek*>& flota, bool czyPrzegrana){
    cout<<"                           Licznik  strzalow: "<<licznik<<" ("<<LIMIT_STRZALOW<<") - limit"<<endl;
    cout<<"                           Statki do zatopienia: "<<flota.size()<<endl;
    cout<<"    A B C D E F G H I J   "<<endl;
    for(int i=0; i<x; i++){
        cout<<"["<<i<<"] ";
        for(int j=0; j<x; j++){
            switch (plansza[i][j]) {
                case '*':
                    cout<<"\033[31m"<<"*"<<"\033[0m"<<" ";
                    break;
                case 'X':
                    cout<<"\033[32m"<<"X"<<"\033[0m"<<" ";
                    break;
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    czyPrzegrana ? cout<<"\033[33m"<<'O'<<"\033[0m"<<" ": cout<<'o'<<" ";
                    break;
                default:
                    cout<<'o'<<" ";
            }
        }
        cout<<endl;
    }
    cout<<endl;
}
void Plansza::edytujPlansze(int w, int k, int rozmiar, int kierunek, Statek* statek){
    int indeksStatku = statek->zwrocId();
    char wartoscStatku = intToChar(indeksStatku);

    if(kierunek == 1){
        for(int i=0; i<rozmiar; i++){
            plansza[w][k] = wartoscStatku;
            k++;
        }
    } else {
        for(int i=0; i<rozmiar; i++){
            plansza[w][k] = wartoscStatku;
            w++;
        }
    }
}
void Plansza::wylosujPoziomeMiejsce(int &w, int &k, int rozmiar){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist_k(0, 10-rozmiar);
    uniform_int_distribution<int> dist_w(0,9);
    w = dist_w(gen);
    k = dist_k(gen);
}
void Plansza::wylosujPionoweMiejsce(int &w, int &k, int rozmiar){
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<int> dist_w(0, 10-rozmiar);
    uniform_int_distribution<int> dist_k(0, 9);

    w = dist_w(gen);
    k = dist_k(gen);

}
char Plansza::intToChar(int i){
    string id = to_string(i);
    char const *n_char = id.c_str();
    return *n_char;
}
bool Plansza::czyMoznaUstawicStatek(int wiersz, int kolumna, int dlugosc, int kierunek){
    if (kierunek == 1) {
        if ((kolumna + dlugosc - 1) > 9) {
            return false;
        }
        else {
            for (int i = -1; i <= dlugosc; i++) {  // zmieniamy zakres pętli
                if (wiersz-1 >= 0 && kolumna+i >= 0 && kolumna+i <= 9 && plansza[wiersz-1][kolumna+i] != 'o') {  // sprawdzamy górną kratkę
                    return false;
                }
                if (wiersz+1 <= 9 && kolumna+i >= 0 && kolumna+i <= 9 && plansza[wiersz+1][kolumna+i] != 'o') {  // sprawdzamy dolną kratkę
                    return false;
                }
                if (wiersz+i >= 0 && kolumna+i <= 9 && plansza[wiersz][kolumna+i] != 'o') {  // sprawdzamy kratki na bokach
                    return false;
                }
            }
        }
    }
    else if (kierunek == 0) {
        if ((wiersz + dlugosc - 1) > 9) {
            return false;
        }
        else {
            for (int i = -1; i <= dlugosc; i++) {  // zmieniamy zakres pętli
                if (wiersz+i >= 0 && kolumna-1 >= 0 && kolumna-1 <= 9 && plansza[wiersz+i][kolumna-1] != 'o') {  // sprawdzamy lewą kratkę
                    return false;
                }
                if (wiersz+i >= 0 && kolumna+1 <= 9 && plansza[wiersz+i][kolumna+1] != 'o') {  // sprawdzamy prawą kratkę
                    return false;
                }
                if (wiersz+i >= 0 && wiersz+i <= 9 && plansza[wiersz+i][kolumna] != 'o') {  // sprawdzamy kratki na górze i dole
                    return false;
                }
            }
        }
    }
    return true;
}
void Plansza::umiescStatek(Statek* statek, int kierunek){
    bool poprawnie = false;
    int rozmiar = statek->zwrocRozmiar();
    int w, k;
    while(!poprawnie){
        if(kierunek == 1){
            wylosujPoziomeMiejsce(w, k,rozmiar);
            if(czyMoznaUstawicStatek(w, k, rozmiar, kierunek)){
                edytujPlansze(w, k, rozmiar, kierunek, statek);
                poprawnie = true;
            }
        } else {
            wylosujPionoweMiejsce(w, k, rozmiar);
            if(czyMoznaUstawicStatek(w, k, rozmiar, kierunek)){
                edytujPlansze(w, k, rozmiar, kierunek, statek);
                poprawnie = true;

            }
        }
    }
}
void Plansza::znajdzStatek(vector<Statek*> &flota, char pole){
    int znak;
    char wartosc;
    string nazwa;
    for(int i=0; i<flota.size(); i++){
        znak = flota[i]->zwrocId();
        wartosc = intToChar(znak);
        if(wartosc == pole){
            flota[i]->trafienie();
            cout<<"Trafiles w statek o nazwie: "<<flota[i]->zwrocNazwe()<<" (dlugosc: "<<flota[i]->zwrocRozmiar()<<")"<<endl;
            if(flota[i]->czyZatopiony()){
                cout<<"Trafiony zatopiony!!"<<endl;
                delete flota[i];
                flota.erase(flota.begin()+i);
            }
        }
    }
}