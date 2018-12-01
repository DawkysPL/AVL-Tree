#ifndef WEZEL_H
#define WEZEL_H
#include <iostream>
#include <windows.h>
#include <algorithm>
#define ROZMIAR 32

using namespace std;

struct Wezel
{
  Wezel * ojciec;  // WEZEL WYZEJ
  Wezel * lewa;    // WEZEL PO LEWEJ
  Wezel * prawa;  // WEZEL PO PRAWEJ
  int wartosc; // PRZECHOWYWANA WARTOSC
  int wysokosc; // ROWNOWAGA WEZLA
  int wysokosc_GENERALNA; // WYSOKOSC WEZLA
};

// METODY ROTACJI

void RR(Wezel * &korzen, Wezel * &A);
void LL(Wezel * &korzen, Wezel * &A);

// METODY PODSTAWOWE

void DODAJ(Wezel * &korzen); //wskaznik na referencje
Wezel * USUN(Wezel * &korzen,Wezel *x);
Wezel * znajdz_najmniejsza_wartosc_w_X_PRAWEJ(Wezel * p);
Wezel * znajdz(Wezel *korzen, int wartosc);

// METODY OBLICZENIOWE

int oblicz_WYSOKOSC(Wezel *p);
int zrob_BALANS(Wezel *p);
void aktualizacja_ROTOWANIE_PO_DELETE(Wezel * korzen, Wezel * &korzen2);
void aktualizacja_WYSOKOSCI_GENERALNEJ(Wezel * &korzen);
void aktualizacja_WYSOKOSCI(Wezel * &korzen);
void UWOLNIJ(Wezel * V);


// METODY WYSWIETLAJACE DRZEWO

void wyswietl_INORDER(Wezel * korzen);
void wyswietl_POSTORDER(Wezel * &korzen);
void wyswietl_PREORDER(Wezel * &korzen);
void ustaw_kursor(int x, int y);
void WYSWIETL_DRZEWO(Wezel * korzen);
#endif // WEZEL_H

// ZAPAMIETAJ CWOKU ZE JAK ROBISZ SKAN REKURENCJA TO JEDNA WARTOSC MOZE BYC & TA SAMA
