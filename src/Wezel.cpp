#include "Wezel.h"
// Funkcja znajdz znajduje wezel ktory zawiera wartosc szukana przez uzytkownika
// w przypadku gdy nie znajdzie zwraca NULL'A
Wezel * znajdz(Wezel *korzen, int wartosc)
{
        while(korzen != NULL && korzen->wartosc != wartosc)
        {
            if(korzen->wartosc < wartosc)
            {
              korzen = korzen->prawa;
            }
            else
            {
                korzen = korzen->lewa;
            }
        }
        return korzen;
}

// USUWA DRZEWO Z PAMIECI
void UWOLNIJ(Wezel * V)
{
    if(V)
    {
        UWOLNIJ(V->lewa);
        UWOLNIJ(V->prawa);
        delete V;
    }
}

// ROTACJA RIGHT RIGHT
void RR(Wezel * &korzen, Wezel * &A)
{
    Wezel *B = A->prawa, *p = A->ojciec;

    A->prawa = B->lewa;
    if(A->prawa){A->prawa->ojciec = A;}

    B->lewa = A;
    B->ojciec = p;
    A->ojciec = B;
    if(p)
    {
        if(p->lewa == A){p->lewa = B;}
        else {p->prawa = B;}
    }
    else
        korzen = B;

}

// ROTACJA LEFT LEFT
void LL(Wezel * &korzen, Wezel * &A)
{
    Wezel *B = A->lewa, *p = A->ojciec;

    A->lewa = B->prawa;
    if(A->lewa)
    {
        A->lewa->ojciec = A;
    }
    B->prawa = A;
    B->ojciec = p;
    A->ojciec = B;

    if(p != NULL)
    {
        if(p->lewa == A){ p->lewa = B;}
        else {p->prawa = B;}
    }
    else
    {
        korzen = B;
    }
}

// ZWRACA WYSOKOSC WEZLA JEZELI GO NIE MA ZWRACA 0 A JEZELI ISTNIEJE > 0
int oblicz_WYSOKOSC(Wezel *p)
{
    if( p == NULL )
    {
        return 0;
    }
    return p->wysokosc_GENERALNA;
}

// FUNKCJA KTORA ZWRACA WARTOSC STRUKTURY wysokosc ODPOWIADAJACA ROWNOWADZE WEZLA
int zrob_BALANS(Wezel *p)
{
    if(p == NULL)
    {
        return 0;
    }
    return (oblicz_WYSOKOSC(p->lewa)-oblicz_WYSOKOSC(p->prawa));
}

// FUNKCJA KTORA AKTUALIZUJE WARTOSCI WYSOKOSCI WEZLA KAZDEGO WEZLA PO WYKONANEJ OPERACJI
void aktualizacja_WYSOKOSCI_GENERALNEJ(Wezel * &korzen)
{
    Wezel *p;
    p = korzen;
    if(p == NULL)
    {
        return;
    }
    aktualizacja_WYSOKOSCI_GENERALNEJ(korzen->lewa);
    aktualizacja_WYSOKOSCI_GENERALNEJ(korzen->prawa);
    p->wysokosc_GENERALNA = max(oblicz_WYSOKOSC(p->lewa),oblicz_WYSOKOSC(p->prawa)) +1;
}

// FUNKCJA KTORA AKTUALIZUJE WARTOSC BALANSU KAZDEGO WEZLA PO WYKONANEJ OPERACJI
void aktualizacja_WYSOKOSCI(Wezel * &korzen)
{
    Wezel *p;
    p = korzen;
    if(p == NULL)
    {
        return;
    }
    aktualizacja_WYSOKOSCI(p->lewa);
    aktualizacja_WYSOKOSCI(p->prawa);
    p->wysokosc = zrob_BALANS(p);
}

// FUNKCJA KTORA ZNAJDUJE NAJMNIEJSZA WARTOSC WEZLA Z PRAWEGO PODDRZEWA
Wezel * znajdz_najmniejsza_wartosc_w_X_PRAWEJ(Wezel * p)
{
    p = p->prawa;
    while(p != NULL && p->lewa != NULL)
    {
        p = p->lewa;
    }
    return p;
}

// FUNKCJA KTOREJ ZADANIEM JEST DOPOROWADZENIE DRZEWA DO ROWNOWAGI PO USUNIECIU JAKIEGOS WEZLA
void aktualizacja_ROTOWANIE_PO_DELETE(Wezel * korzen, Wezel * &korzen2)
{
    Wezel *p, *ojciec_ojcow, *ojciec;
    p = korzen;
    if( korzen == NULL )
    {
        return;
    }
    aktualizacja_ROTOWANIE_PO_DELETE(korzen->lewa,korzen2);
    aktualizacja_ROTOWANIE_PO_DELETE(korzen->prawa,korzen2);

    if(p->ojciec != NULL)
    {
        ojciec = p->ojciec;
        if(ojciec->ojciec != NULL)
        {
            ojciec_ojcow = ojciec->ojciec;
            if(ojciec_ojcow->wysokosc > 1 && ojciec->wysokosc>=0)
            {
                //cout<<"ROTOWANIE LL DELETE       " <<ojciec_ojcow->wartosc; Sleep(10000);
                LL(korzen2,ojciec_ojcow);
            }
            if(ojciec_ojcow->wysokosc > 1 && ojciec->wysokosc < 0)
            {
                //cout<<"ROTOWANIE LR DELETE       " <<ojciec_ojcow->wartosc; Sleep(10000);
                RR(korzen2,ojciec);
                LL(korzen2,ojciec_ojcow);
            }
            if(ojciec_ojcow->wysokosc < -1 && ojciec->wysokosc <= 0)
            {
                //cout<<"ROTOWANIE RR DELETE       " <<ojciec_ojcow->wartosc; Sleep(10000);
                RR(korzen2,ojciec_ojcow);
            }
            if(ojciec_ojcow->wysokosc < -1 && ojciec->wysokosc > 0)
            {
                //cout<<"ROTOWANIE RL DELETE       " <<ojciec_ojcow->wartosc; Sleep(10000);
                LL(korzen2,ojciec);
                RR(korzen2,ojciec_ojcow);
            }
        }
    }
    aktualizacja_WYSOKOSCI_GENERALNEJ(korzen2);
    aktualizacja_WYSOKOSCI(korzen2);
}


// FUNKCJA USUWAJACA WEZEL
Wezel * USUN(Wezel * &korzen,Wezel *x)
{
    if(korzen == NULL)
        return korzen;

    //wezel bez synow
if(x->lewa == NULL && x->prawa == NULL)
{
    if(x->ojciec == NULL)
    {
        korzen = NULL;
    }
    else
    {
        if(x->ojciec->lewa == x)
        {
            x->ojciec->lewa = NULL;
        }
        else
        {
            x->ojciec->prawa = NULL;
        }
    }
    x->ojciec = NULL;
}
// wezel z JEDNYM synem

if(x->prawa != NULL && x->lewa == NULL)
{
    if(x->ojciec != NULL)
    {
        x->prawa->ojciec = x->ojciec;
        if(x->ojciec->prawa == x) {x->ojciec->prawa = x->prawa; }
        else {x->ojciec->lewa = x->prawa;}
    }
    else
    {
        korzen = x->prawa;
        x->prawa->ojciec = NULL;
    }
}
else if(x->lewa != NULL && x->prawa == NULL)
{
    if(x->ojciec != NULL)
    {
        x->lewa->ojciec = x->ojciec;
        if(x->ojciec->lewa == x) {x->ojciec->lewa = x->lewa; }
        else {x->ojciec->prawa = x->lewa;}
    }
    else
    {
        korzen = x->lewa;
        x->lewa->ojciec = NULL;
    }
}

// wezel z DWOMA synami :(

if(x->lewa != NULL && x->prawa != NULL)
{
Wezel * pomoc = znajdz_najmniejsza_wartosc_w_X_PRAWEJ(x);
if(pomoc->prawa != NULL && pomoc->prawa->wartosc < pomoc->ojciec->wartosc)
{
    pomoc->prawa->ojciec = pomoc->ojciec;
    pomoc->ojciec->lewa = pomoc->prawa;
}

if(pomoc->ojciec == x)
{
    //cout<<"POKA OJCA " <<pomoc->ojciec->wartosc<<"       POKA POMOC    "<<pomoc->wartosc;
    //Sleep(10000);
    if(x->ojciec != NULL)
    {
        pomoc->ojciec = x->ojciec;

        if(x->ojciec->prawa == x)
        {
           x->ojciec->prawa = pomoc;
        }
        else
        {
            x->ojciec->lewa = pomoc;
        }
        pomoc->lewa = x->lewa;
        x->lewa->ojciec = pomoc;
    }
    else
        if(korzen == x && pomoc->ojciec == x)
    {
        pomoc->ojciec = NULL;
        korzen = pomoc;
        pomoc->lewa = x->lewa;
        x->lewa->ojciec = pomoc;
    }

}
else
{

    if(pomoc->ojciec->lewa == pomoc)
    {
        pomoc->ojciec->lewa = NULL;
    }
    if(pomoc->ojciec->prawa == pomoc)
    {
        pomoc->ojciec->prawa = NULL;
    }
    if(pomoc->prawa != NULL)
    {
        pomoc->ojciec->lewa = pomoc->prawa;
    }
    if(x->ojciec != NULL)
    {
        pomoc->ojciec = x->ojciec;

        if(x->ojciec->lewa == x)
        {
            x->ojciec->lewa = pomoc;
        }
        else
        {
            x->ojciec->prawa = pomoc;
        }
    }
    else
    {
        korzen = pomoc;
        pomoc->ojciec = NULL;
    }
    if(pomoc->lewa == NULL)
    {
       pomoc->lewa = x->lewa;
    }
    if(pomoc->prawa == NULL)
    {
       pomoc->prawa = x->prawa;
    }
    x->lewa->ojciec = pomoc;
    x->prawa->ojciec = pomoc;
}

}
aktualizacja_WYSOKOSCI_GENERALNEJ(korzen);
aktualizacja_WYSOKOSCI(korzen);
aktualizacja_ROTOWANIE_PO_DELETE(korzen,korzen);

return x;
}


// FUNKCJA DODAJACA WEZEL
void DODAJ(Wezel * &korzen) //wskaznik na referencje
{
    int liczba;
    cout<< "Jaka liczbe dodac do drzewa AVL: ";
    cin>> liczba;
    cout<<"\n";
    Wezel *w, *p, *ojciec_ojcow; // w - nowy wezel , p "ojciec"

    w = new Wezel;
    w->lewa = w->prawa = w->ojciec = NULL;
    w->wartosc = liczba;
    w->wysokosc = 0;
    w->wysokosc_GENERALNA = 1;
    p = korzen;

    if( p == NULL)
    {
        korzen = w;
    }
    else
    {
        while(1)
        if(liczba < p->wartosc)   // Jak ojciec wieksza wartosc to w lewo
        {
            if(p->lewa==NULL) //Jak ojciec nie ma lewego syna to zrob mu tego syna
            {
                p->lewa=w;
                //wysokosci(korzen);
                break;         // znalazles syna to wyjdz z petli
            }
            p = p->lewa;
             // jak ma syna to przejdz do niego i powtorz
        }
        else
        {
            if(p->prawa==NULL)
            {
                p->prawa=w;
                //wysokosci(korzen);
                break;
            }
            p = p->prawa;
        }
       aktualizacja_WYSOKOSCI_GENERALNEJ(korzen);
        w ->ojciec = p;


        int t=0;
        if(p->wysokosc !=0) {p->wysokosc =0; } // bo wartosci -1/0/1
        else
        {
            if(p->lewa == w){p->wysokosc = 1; } // bo bylo =0
            else
            {
                p->wysokosc = -1;
            }
            ojciec_ojcow = p->ojciec;
            t = 0;
            while(ojciec_ojcow != NULL)
            {
                if(ojciec_ojcow->wysokosc != 0)  // OHO BILANS ZABURZONY
                {
                    t = 1;
                    break;
                }

                if(ojciec_ojcow->lewa == p) {ojciec_ojcow->wysokosc= 1;} // BO dodalismy syna P
                else
                {
                    ojciec_ojcow->wysokosc = -1;
                }

                p =ojciec_ojcow;     // i znow w gore
                ojciec_ojcow = ojciec_ojcow->ojciec;
            }

            if( t == 1)  // Ojciec ojcow ma nadwage trzeba rotowac
            {
                if(ojciec_ojcow->wysokosc == 1)
                {
                    if(ojciec_ojcow->prawa == p){ojciec_ojcow->wysokosc=0;} // BO DODALISMY DO WEZLA Z NADWAGA  Z LEWEJ COS PO PRAWEJ
                    else
                    {
                        if(p->wysokosc == 0 || p->wysokosc ==1){ LL(korzen,ojciec_ojcow); aktualizacja_WYSOKOSCI_GENERALNEJ(korzen); aktualizacja_WYSOKOSCI(korzen);} //rotacja LL


                     if(p->wysokosc == -1)
                    {
                        Wezel *C = p->prawa;
                        if( C != NULL)
                        {
                            RR(korzen,p);
                            LL(korzen,ojciec_ojcow);
                            aktualizacja_WYSOKOSCI_GENERALNEJ(korzen); aktualizacja_WYSOKOSCI(korzen);
                        }
                    }
                    }
                }
                if(ojciec_ojcow->wysokosc == -1)
                {

                    if(ojciec_ojcow->lewa ==p){ojciec_ojcow->wysokosc=0;}
                    else
                    {
                        if(p->wysokosc == 0 || p->wysokosc == -1){  RR(korzen,ojciec_ojcow); aktualizacja_WYSOKOSCI_GENERALNEJ(korzen); aktualizacja_WYSOKOSCI(korzen);}// ROTACJA RR

                    if(p->wysokosc == 1)
                    {
                        Wezel *C = p->lewa;
                        if( C != NULL)
                        {
                            LL(korzen,p);
                            RR(korzen,ojciec_ojcow);
                            aktualizacja_WYSOKOSCI_GENERALNEJ(korzen); aktualizacja_WYSOKOSCI(korzen);
                        }
                    }
                    }
                }
            }
        }
    }
}

// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------
// FUNKCJE ODPOWIADAJACE WYSWIETLANIU DRZEWA
// -----------------------------------------------------------------------------------------------------------
void wyswietl_INORDER(Wezel * korzen)
{
    if(korzen == NULL)
    {
        return;
    }
    wyswietl_INORDER(korzen->lewa);
    cout<<korzen->wartosc<<"    ";
    wyswietl_INORDER(korzen->prawa);
}

void wyswietl_PREORDER(Wezel * &korzen)
{
    if(korzen == NULL)
    {
        return;
    }
    cout<<korzen->wartosc<<"    ";
    wyswietl_PREORDER(korzen->lewa);
    wyswietl_PREORDER(korzen->prawa);
}

void wyswietl_POSTORDER(Wezel * &korzen)
{
    if(korzen == NULL)
    {
        return;
    }
    wyswietl_POSTORDER(korzen->lewa);
    wyswietl_POSTORDER(korzen->prawa);
    cout<<korzen->wartosc<<"    ";
}


void ustaw_kursor(int x, int y)
{
  COORD c;
  c.X=x-1;
  c.Y=y-1;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

void WYSWIETL_DRZEWO(Wezel * korzen)
{
    bool pusty[ROZMIAR];
    int dane[ROZMIAR];
    int wysokosc_wezla[ROZMIAR];
    int wysokosc_polozenia[ROZMIAR];
    Wezel *p;

    Wezel * Wezelki[ROZMIAR];

    p = korzen;

     for(int i=1; i<ROZMIAR; i++)
    {
        pusty[i] = true; //pusty nie ma wezla
        dane[i] = -997;
        wysokosc_wezla[i] = 666;
        wysokosc_polozenia[i] = 999;
    }

    if( p == NULL)
    {
        ;//cout << "Drzewo jest puste. Dodaj liczby.";
    }
    else
    {
        pusty[1] = false;  // jest wezel
        dane[1] = p->wartosc;
        wysokosc_wezla[1] = p->wysokosc;
        wysokosc_polozenia[1] = p->wysokosc_GENERALNA;
        if(p->lewa != NULL) // 2 WEZEL
        {
            Wezelki[2] = p->lewa; pusty[2] = false; dane[2] = Wezelki[2]->wartosc; wysokosc_wezla[2] = Wezelki[2]->wysokosc; wysokosc_polozenia[2] = Wezelki[2]->wysokosc_GENERALNA;
            if(Wezelki[2]->lewa != NULL) // 4 WEZEL
            {
                Wezelki[4] = Wezelki[2]->lewa; pusty[4] = false; dane[4] = Wezelki[4]->wartosc; wysokosc_wezla[4] = Wezelki[4]->wysokosc; wysokosc_polozenia[4] = Wezelki[4]->wysokosc_GENERALNA;
                if(Wezelki[4]->lewa != NULL) // 8 WEZEL
                {
                    Wezelki[8] = Wezelki[4]->lewa; pusty[8] = false; dane[8] = Wezelki[8]->wartosc; wysokosc_wezla[8] = Wezelki[8]->wysokosc; wysokosc_polozenia[8] = Wezelki[8]->wysokosc_GENERALNA;
                    if(Wezelki[8]->lewa != NULL) // 16 WEZEL
                    {
                        Wezelki[16] = Wezelki[8]->lewa; pusty[16] = false; dane[16] = Wezelki[16]->wartosc; wysokosc_wezla[16] = Wezelki[16]->wysokosc; wysokosc_polozenia[16] = Wezelki[16]->wysokosc_GENERALNA;
                    }
                    if(Wezelki[8]->prawa != NULL) // 17 WEZEL
                    {
                        Wezelki[17] = Wezelki[8]->prawa; pusty[17] = false; dane[17] = Wezelki[17]->wartosc; wysokosc_wezla[17] = Wezelki[17]->wysokosc; wysokosc_polozenia[17] = Wezelki[17]->wysokosc_GENERALNA;
                    }
                }
                if(Wezelki[4]->prawa != NULL) // 9 WEZEL
                {
                    Wezelki[9] = Wezelki[4]->prawa; pusty[9] = false; dane[9] = Wezelki[9]->wartosc; wysokosc_wezla[9] = Wezelki[9]->wysokosc; wysokosc_polozenia[9] = Wezelki[9]->wysokosc_GENERALNA;
                    if(Wezelki[9]->prawa != NULL) // 19 WEZEL
                    {
                        Wezelki[19] = Wezelki[9]->prawa; pusty[19] = false; dane[19] = Wezelki[19]->wartosc; wysokosc_wezla[19] = Wezelki[19]->wysokosc; wysokosc_polozenia[19] = Wezelki[19]->wysokosc_GENERALNA;
                    }
                    if(Wezelki[9]->lewa != NULL) // 18 WEZEL
                    {
                        Wezelki[18] = Wezelki[9]->lewa; pusty[18] = false; dane[18] = Wezelki[18]->wartosc; wysokosc_wezla[18] = Wezelki[18]->wysokosc; wysokosc_polozenia[18] = Wezelki[18]->wysokosc_GENERALNA;
                    }
                }
            }
            if(Wezelki[2]->prawa != NULL) // 5 WEZEL
            {
                Wezelki[5] = Wezelki[2]->prawa; pusty[5] = false; dane[5] = Wezelki[5]->wartosc; wysokosc_wezla[5] = Wezelki[5]->wysokosc; wysokosc_polozenia[5] = Wezelki[5]->wysokosc_GENERALNA;
                if(Wezelki[5]->lewa != NULL) // 10 WEZEL
                {
                    Wezelki[10] = Wezelki[5]->lewa; pusty[10] = false; dane[10] = Wezelki[10]->wartosc; wysokosc_wezla[10] = Wezelki[10]->wysokosc; wysokosc_polozenia[10] = Wezelki[10]->wysokosc_GENERALNA;
                    if(Wezelki[10]->lewa != NULL) // 20 WEZEL
                    {
                        Wezelki[20] = Wezelki[10]->lewa; pusty[20] = false; dane[20] = Wezelki[20]->wartosc; wysokosc_wezla[20] = Wezelki[20]->wysokosc; wysokosc_polozenia[20] = Wezelki[20]->wysokosc_GENERALNA;
                    }
                    if(Wezelki[10]->prawa != NULL) // 21 WEZEL
                    {
                        Wezelki[21] = Wezelki[10]->prawa; pusty[21] = false; dane[21] = Wezelki[21]->wartosc; wysokosc_wezla[21] = Wezelki[21]->wysokosc; wysokosc_polozenia[21] = Wezelki[21]->wysokosc_GENERALNA;
                    }
                }
                if(Wezelki[5]->prawa != NULL) // 11 WEZEL
                {
                    Wezelki[11] = Wezelki[5]->prawa; pusty[11] = false; dane[11] = Wezelki[11]->wartosc; wysokosc_wezla[11] = Wezelki[11]->wysokosc; wysokosc_polozenia[11] = Wezelki[11]->wysokosc_GENERALNA;
                    if(Wezelki[11]->lewa != NULL) // 22 WEZEL
                    {
                        Wezelki[22] = Wezelki[11]->lewa; pusty[22] = false; dane[22] = Wezelki[22]->wartosc; wysokosc_wezla[22] = Wezelki[22]->wysokosc; wysokosc_polozenia[22] = Wezelki[22]->wysokosc_GENERALNA;
                    }
                    if(Wezelki[11]->prawa != NULL) // 23 WEZEL
                    {
                        Wezelki[23] = Wezelki[11]->prawa; pusty[23] = false; dane[23] = Wezelki[23]->wartosc; wysokosc_wezla[23] = Wezelki[23]->wysokosc; wysokosc_polozenia[23] = Wezelki[23]->wysokosc_GENERALNA;
                    }
                }
            }

        }

        if(p->prawa != NULL) // 3 WEZEL
        {
            Wezelki[3] = p->prawa; pusty[3] = false; dane[3] = Wezelki[3]->wartosc; wysokosc_wezla[3] = Wezelki[3]->wysokosc; wysokosc_polozenia[3] = Wezelki[3]->wysokosc_GENERALNA;
            if(Wezelki[3]->lewa != NULL) // 6 WEZEL
            {
                Wezelki[6] = Wezelki[3]->lewa; pusty[6] = false; dane[6] = Wezelki[6]->wartosc; wysokosc_wezla[6] = Wezelki[6]->wysokosc; wysokosc_polozenia[6] = Wezelki[6]->wysokosc_GENERALNA;
                if(Wezelki[6]->lewa != NULL) //12 WEZEL
                {
                    Wezelki[12] = Wezelki[6]->lewa; pusty[12] = false; dane[12] = Wezelki[12]->wartosc; wysokosc_wezla[12] = Wezelki[12]->wysokosc; wysokosc_polozenia[12] = Wezelki[12]->wysokosc_GENERALNA;
                    if(Wezelki[12]->lewa != NULL) //24 WEZEL
                    {
                        Wezelki[24] = Wezelki[12]->lewa; pusty[24] = false; dane[24] = Wezelki[24]->wartosc; wysokosc_wezla[24] = Wezelki[24]->wysokosc; wysokosc_polozenia[24] = Wezelki[24]->wysokosc_GENERALNA;
                    }
                    if(Wezelki[12]->prawa != NULL) //25 WEZEL
                    {
                        Wezelki[25] = Wezelki[12]->prawa; pusty[25] = false; dane[25] = Wezelki[25]->wartosc; wysokosc_wezla[25] = Wezelki[25]->wysokosc; wysokosc_polozenia[25] = Wezelki[25]->wysokosc_GENERALNA;
                    }
                }
                 if(Wezelki[6]->prawa != NULL) //13 WEZEL
                {
                    Wezelki[13] = Wezelki[6]->prawa; pusty[13] = false; dane[13] = Wezelki[13]->wartosc; wysokosc_wezla[13] = Wezelki[13]->wysokosc; wysokosc_polozenia[13] = Wezelki[13]->wysokosc_GENERALNA;
                    if(Wezelki[13]->lewa != NULL) //26 WEZEL
                    {
                        Wezelki[26] = Wezelki[13]->lewa; pusty[26] = false; dane[26] = Wezelki[26]->wartosc; wysokosc_wezla[26] = Wezelki[26]->wysokosc; wysokosc_polozenia[26] = Wezelki[26]->wysokosc_GENERALNA;
                    }
                    if(Wezelki[13]->prawa != NULL) //27 WEZEL
                    {
                        Wezelki[27] = Wezelki[13]->prawa; pusty[27] = false; dane[27] = Wezelki[27]->wartosc; wysokosc_wezla[27] = Wezelki[27]->wysokosc; wysokosc_polozenia[27] = Wezelki[27]->wysokosc_GENERALNA;
                    }
                }
            }
            if(Wezelki[3]->prawa != NULL) // 7 WEZEL
            {
                Wezelki[7] = Wezelki[3]->prawa; pusty[7] = false; dane[7] = Wezelki[7]->wartosc; wysokosc_wezla[7] = Wezelki[7]->wysokosc; wysokosc_polozenia[7] = Wezelki[7]->wysokosc_GENERALNA;
                if(Wezelki[7]->lewa != NULL) // 14 WEZEL
                {
                    Wezelki[14] = Wezelki[7]->lewa; pusty[14] = false; dane[14] = Wezelki[14]->wartosc; wysokosc_wezla[14] = Wezelki[14]->wysokosc; wysokosc_polozenia[14] = Wezelki[14]->wysokosc_GENERALNA;
                    if(Wezelki[14]->lewa != NULL) // 28 WEZEL
                    {
                        Wezelki[28] = Wezelki[14]->lewa; pusty[28] = false; dane[28] = Wezelki[28]->wartosc; wysokosc_wezla[28] = Wezelki[28]->wysokosc; wysokosc_polozenia[28] = Wezelki[28]->wysokosc_GENERALNA;
                    }
                    if(Wezelki[14]->prawa != NULL) // 29 WEZEL
                    {
                        Wezelki[29] = Wezelki[14]->prawa; pusty[29] = false; dane[29] = Wezelki[29]->wartosc; wysokosc_wezla[29] = Wezelki[29]->wysokosc; wysokosc_polozenia[29] = Wezelki[29]->wysokosc_GENERALNA;
                    }
                }
                if(Wezelki[7]->prawa != NULL) // 15 WEZEL
                {
                    Wezelki[15] = Wezelki[7]->prawa; pusty[15] = false; dane[15] = Wezelki[15]->wartosc; wysokosc_wezla[15] = Wezelki[15]->wysokosc; wysokosc_polozenia[15] = Wezelki[15]->wysokosc_GENERALNA;
                     if(Wezelki[15]->lewa != NULL) // 30 WEZEL
                    {
                            Wezelki[30] = Wezelki[15]->lewa; pusty[30] = false; dane[30] = Wezelki[30]->wartosc; wysokosc_wezla[30] = Wezelki[30]->wysokosc; wysokosc_polozenia[30] = Wezelki[30]->wysokosc_GENERALNA;
                    }
                     if(Wezelki[15]->prawa != NULL) // 31 WEZEL
                    {
                            Wezelki[31] = Wezelki[15]->prawa; pusty[31] = false; dane[31] = Wezelki[31]->wartosc; wysokosc_wezla[31] = Wezelki[31]->wysokosc; wysokosc_polozenia[31] = Wezelki[31]->wysokosc_GENERALNA;
                    }
                }
            }
        }

    }


system("CLS");
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
//wyswietlenie drzewa
ustaw_kursor(64,1); if (pusty[1]==true) cout<<"_"; else {cout<<dane[1]<<":"<<wysokosc_wezla[1]<<":"<<wysokosc_polozenia[1];}
ustaw_kursor(29,4); if (pusty[2]==true) cout<<"_"; else {cout<<dane[2]<<":"<<wysokosc_wezla[2]<<":"<<wysokosc_polozenia[2];}
ustaw_kursor(102,4); if (pusty[3]==true) cout<<"_"; else {cout<<dane[3]<<":"<<wysokosc_wezla[3]<<":"<<wysokosc_polozenia[3];}
ustaw_kursor(13,6); if (pusty[4]==true) cout<<"_"; else {cout<<dane[4]<<":"<<wysokosc_wezla[4]<<":"<<wysokosc_polozenia[4];}
ustaw_kursor(45,6); if (pusty[5]==true) cout<<"_"; else {cout<<dane[5]<<":"<<wysokosc_wezla[5]<<":"<<wysokosc_polozenia[5];}
ustaw_kursor(87,6); if (pusty[6]==true) cout<<"_"; else {cout<<dane[6]<<":"<<wysokosc_wezla[6]<<":"<<wysokosc_polozenia[6];}
ustaw_kursor(119,6); if (pusty[7]==true) cout<<"_"; else {cout<<dane[7]<<":"<<wysokosc_wezla[7]<<":"<<wysokosc_polozenia[7];}
ustaw_kursor(5,8); if (pusty[8]==true) cout<<"_"; else {cout<<dane[8]<<":"<<wysokosc_wezla[8]<<":"<<wysokosc_polozenia[8];}
ustaw_kursor(21,8); if (pusty[9]==true) cout<<"_"; else {cout<<dane[9]<<":"<<wysokosc_wezla[9]<<":"<<wysokosc_polozenia[9];}
ustaw_kursor(37,8); if (pusty[10]==true) cout<<"_"; else {cout<<dane[10]<<":"<<wysokosc_wezla[10]<<":"<<wysokosc_polozenia[10];}
ustaw_kursor(53,8); if (pusty[11]==true) cout<<"_"; else {cout<<dane[11]<<":"<<wysokosc_wezla[11]<<":"<<wysokosc_polozenia[11];}
ustaw_kursor(79,8); if (pusty[12]==true) cout<<"_"; else {cout<<dane[12]<<":"<<wysokosc_wezla[12]<<":"<<wysokosc_polozenia[12];}
ustaw_kursor(95,8); if (pusty[13]==true) cout<<"_"; else {cout<<dane[13]<<":"<<wysokosc_wezla[13]<<":"<<wysokosc_polozenia[13];}
ustaw_kursor(111,8); if (pusty[14]==true) cout<<"_"; else {cout<<dane[14]<<":"<<wysokosc_wezla[14]<<":"<<wysokosc_polozenia[14];}
ustaw_kursor(127,8); if (pusty[15]==true) cout<<"_"; else {cout<<dane[15]<<":"<<wysokosc_wezla[15]<<":"<<wysokosc_polozenia[15];}
ustaw_kursor(1,10); if (pusty[16]==true) cout<<"_"; else {cout<<dane[16]<<":"<<wysokosc_wezla[16]<<":"<<wysokosc_polozenia[16];}
ustaw_kursor(9,10); if (pusty[17]==true) cout<<"_"; else {cout<<dane[17]<<":"<<wysokosc_wezla[17]<<":"<<wysokosc_polozenia[17];}
ustaw_kursor(17,10); if (pusty[18]==true) cout<<"_"; else {cout<<dane[18]<<":"<<wysokosc_wezla[18]<<":"<<wysokosc_polozenia[18];}
ustaw_kursor(25,10); if (pusty[19]==true) cout<<"_"; else {cout<<dane[19]<<":"<<wysokosc_wezla[19]<<":"<<wysokosc_polozenia[19];}
ustaw_kursor(33,10); if (pusty[20]==true) cout<<"_"; else {cout<<dane[20]<<":"<<wysokosc_wezla[20]<<":"<<wysokosc_polozenia[20];}
ustaw_kursor(41,10); if (pusty[21]==true) cout<<"_"; else {cout<<dane[21]<<":"<<wysokosc_wezla[21]<<":"<<wysokosc_polozenia[21];}
ustaw_kursor(49,10); if (pusty[22]==true) cout<<"_"; else {cout<<dane[22]<<":"<<wysokosc_wezla[22]<<":"<<wysokosc_polozenia[22];}
ustaw_kursor(57,10); if (pusty[23]==true) cout<<"_"; else {cout<<dane[23]<<":"<<wysokosc_wezla[23]<<":"<<wysokosc_polozenia[23];}
ustaw_kursor(75,10); if (pusty[24]==true) cout<<"_"; else {cout<<dane[24]<<":"<<wysokosc_wezla[24]<<":"<<wysokosc_polozenia[24];}
ustaw_kursor(83,10); if (pusty[25]==true) cout<<"_"; else {cout<<dane[25]<<":"<<wysokosc_wezla[25]<<":"<<wysokosc_polozenia[25];}
ustaw_kursor(91,10); if (pusty[26]==true) cout<<"_"; else {cout<<dane[26]<<":"<<wysokosc_wezla[26]<<":"<<wysokosc_polozenia[26];}
ustaw_kursor(99,10); if (pusty[27]==true) cout<<"_"; else {cout<<dane[27]<<":"<<wysokosc_wezla[27]<<":"<<wysokosc_polozenia[27];}
ustaw_kursor(107,10); if (pusty[28]==true) cout<<"_"; else {cout<<dane[28]<<":"<<wysokosc_wezla[28]<<":"<<wysokosc_polozenia[28];}
ustaw_kursor(115,10); if (pusty[29]==true) cout<<"_"; else {cout<<dane[29]<<":"<<wysokosc_wezla[29]<<":"<<wysokosc_polozenia[29];}
ustaw_kursor(123,10); if (pusty[30]==true) cout<<"_"; else {cout<<dane[30]<<":"<<wysokosc_wezla[30]<<":"<<wysokosc_polozenia[30];}
ustaw_kursor(131,10); if (pusty[31]==true) cout<<"_"; else {cout<<dane[31]<<":"<<wysokosc_wezla[31]<<":"<<wysokosc_polozenia[31];}
cout<<endl<<endl<<endl;

SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);

}
