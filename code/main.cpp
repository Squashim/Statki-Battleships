#include "Statek.h"
#include "Plansza.h"
#include <bits/stdc++.h>
using namespace std;
// Funkcja losujaca kierunek ustawienia statku na planszy
int wylosujKierunek(){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, 1);
    int losowa=dist(gen);
    if(losowa == 1){
        return 1;
    } else{
        return 0;
    }
}
// Funkcja wyswietlajaca zasady gry
void Info() {
    cout << "                       # Gra w statki #\n";
    cout << "         ---------------------------------------------\n";
    cout << "                            Zasady\n";
    cout << "         ---------------------------------------------\n";
    cout << "Twoim zadaniem jest zatopienie wszystkich 10 statkow przeciwnika.\n";
    cout << "\n";
    cout << "                      1 statek 4-kratkowy\n";
    cout << "                      2 statki 3-kratkowe\n";
    cout << "                      3 statki 2-kratkowe\n";
    cout << "                      4 statki 1-kratkowe\n";
    cout << "\n";
    cout << "1) Wpisuj koordynaty np. B5, C9\n";
    cout << "2) Ilosc strzalow jest ograniczona\n";
    cout << "3) Wygrywasz jesli zatopisz wszystkie statki i nie zabraknie ci strzalow\n";
    cout << "4) Milej gry!\n";
    cout << "\n";
    cout << "\n";
    system("pause");
    system("cls");
}
// Funkcja usuwajaca statki z pamieci
void usunFlote(vector<Statek*> flota){
    for (auto & i : flota) {
        delete i;
    }
    flota.clear();
}

// Głowna funkcja programu
int main() {
    bool graTrwa = true;
    string koordynaty;
    char trafione;
    int wiersz, kolumna;
    int licznikStrzalow = 0;
    bool poprawneDane = false;
    Plansza plansza(10);
    //Stworzenie obiektow statkow
    vector<Statek*> flota = {new Lodz_Podwodna(), new Lodz_Podwodna(), new Lodz_Podwodna(),
                             new Lodz_Podwodna(), new Niszczyciel(), new Niszczyciel(),
                             new Niszczyciel(), new Pancernik(), new Pancernik(),
                             new Transportowiec()};

//    Umieszczenie statkow na planszy
    for(auto & i : flota){
        plansza.umiescStatek(i, wylosujKierunek());
    }

    Info();

    while(graTrwa && licznikStrzalow < LIMIT_STRZALOW){
        plansza.pokazPlansze(licznikStrzalow, flota, false);
        poprawneDane = false;
        do{
            if(flota.empty()) {
                cout << "Gratulacje wszystkie statki zostaly zatopione!!" << endl << "Wygrales!!" << endl;
                system("pause");
                graTrwa = false;
                break;
            }
            cout << "Podaj pole w ktore chcesz trafic (Np. A5): "; cin >> koordynaty;
            transform(koordynaty.begin(), koordynaty.end(), koordynaty.begin(), ::toupper);
            if (koordynaty.length() <= 1 || koordynaty.length() > 2 || koordynaty[0] < 'A' || koordynaty[0] > 'J' || koordynaty[1] < '0' || koordynaty[1] > '9') {
                continue;
            }else{
                wiersz = (int)koordynaty[1] - '0';
                kolumna = (int)((koordynaty[0])+5)%10;
                poprawneDane = true;
            }
        } while (!poprawneDane);

        trafione = plansza.zwrocPole(wiersz, kolumna);
        licznikStrzalow++;

        if(graTrwa){
            if(trafione == 'o') {
                cout << "Nie trafiles!!"<<endl;
                plansza.ustawPole(wiersz, kolumna, '*');
            } else if(trafione == '*' || trafione == 'X'){
                cout << "Trafiles w miejsce, ktore sprawdziles. Strzal zmarnowany!!"<<endl;
            } else{
                Plansza::znajdzStatek(flota, trafione);
                plansza.ustawPole(wiersz, kolumna, 'X');
            }
            system("pause");
            system("cls");
        }
    }
    if(licznikStrzalow>=LIMIT_STRZALOW){
        plansza.pokazPlansze(licznikStrzalow, flota, true);
        cout<<"Przekroczyles limit strzalow! Przegrales!"<<endl;
        system("pause");
    }
    usunFlote(flota);
    return 0;
}
