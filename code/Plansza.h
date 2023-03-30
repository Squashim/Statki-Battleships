#ifndef STATKI_PLANSZA_H
#define STATKI_PLANSZA_H

#include <iostream>
#include <random>
#include "Statek.h"

using namespace std;

const int LIMIT_STRZALOW = 75;

class Plansza{
private:
    int x;
    char** plansza;
public:
    Plansza(int x);
    ~Plansza();
    char zwrocPole(int w, int k);
    void ustawPole(int w, int k, char wartosc);
    void pokazPlansze(int licznik, const vector<Statek*>& flota, bool czyPrzegrana);
    void edytujPlansze(int w, int k, int rozmiar, int kierunek, Statek* statek);
    static void wylosujPoziomeMiejsce(int &w, int &k, int rozmiar);
    static void wylosujPionoweMiejsce(int &w, int &k, int rozmiar);
    bool czyMoznaUstawicStatek(int wiersz, int kolumna, int dlugosc, int kierunek);
    void umiescStatek(Statek* statek, int kierunek);
    static void znajdzStatek(vector<Statek*> &flota, char pole);
    static char intToChar(int i);


};

#endif //STATKI_PLANSZA_H
