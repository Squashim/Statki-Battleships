#include "Statek.h"

using namespace std;

int Statek::licznik = 0;

Statek::Statek(int d, string n, char z) : dlugosc(d), nazwa(n), znak(z), trafienia(0), id(licznik++){}
bool Statek::czyZatopiony() {
    return trafienia == dlugosc;
}
string Statek::zwrocNazwe(){
    return nazwa;
}
int Statek::zwrocRozmiar() {
    return dlugosc;
}
void Statek::trafienie(){
    trafienia++;
}
int Statek::zwrocId() {
    return id;
}
Statek::~Statek(){
    cout<<"Statek o nazwie "<<nazwa<<" zatonal"<<endl;
}

Lodz_Podwodna::Lodz_Podwodna() : Statek(1,"Lodz podwodna", 'L') {}
Niszczyciel::Niszczyciel() : Statek(2, "Niszczyciel", 'N') {}
Pancernik::Pancernik() : Statek(3, "Pancernik", 'P') {}
Transportowiec::Transportowiec() : Statek(4, "Transportowiec", 'T') {}