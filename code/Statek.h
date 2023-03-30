#ifndef STATKI_STATEK_H
#define STATKI_STATEK_H

#include <iostream>
#include <string>

using namespace std;

class Statek{
private:
    int dlugosc;
    int trafienia;
    int id;
    static int licznik;
    char znak;
    string nazwa;
public:
    Statek(int d, string n, char z);
    bool czyZatopiony();
    string zwrocNazwe();
    int zwrocRozmiar();
    void trafienie();
    int zwrocId();
    virtual ~Statek();
};

class Lodz_Podwodna : public Statek{
public:
    Lodz_Podwodna();
};

class Niszczyciel : public Statek{
public:
    Niszczyciel();
};

class Pancernik : public Statek{
public:
    Pancernik();
};

class Transportowiec : public Statek{
public:
    Transportowiec();
};

#endif //STATKI_STATEK_H
