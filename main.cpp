#include <Wezel.h>
using namespace std;

int main()
{
    Wezel *korzen = NULL; //korzen nie wskazuje na zaden obiekt
    int liczba;
    int wybor;
    do
    {
        WYSWIETL_DRZEWO(korzen);
    cout<<"------------------------------------------------------------"<<endl;
    cout<<"   EMULATOR DRZEWA AVL "<<endl;
    cout<<"------------------------------------------------------------"<<endl;
    cout<<"1. ADD (dodaje element do drzewa)"<<endl;
    cout<<"2. DELETE (usuwa element w drzewie)"<<endl;
    cout<<"3. WYS. INORDER (pokazuje drzewo na zasadzie INORDER)"<<endl;
    cout<<"4. WYS. PREORDER (pokazuje drzewo na zasadzie PREORDER)"<<endl;
    cout<<"5. WYS. POSTORDER (pokazuje drzewo na zasadzie POSTORDER)"<<endl;
    cout<<"6. EXIT (zakonczy ten program)"<<endl;
    cout<<"------------------------------------------------------------"<<endl;
    cout<<"   WYBOR: ";
    cin>>wybor;
    cout<<endl;

    switch(wybor)
    {
        case 1:
             DODAJ(korzen);  WYSWIETL_DRZEWO(korzen); break;
        case 2:
            {
            cout<<"Jaka liczbe chcesz usunac: ";
            cin>>liczba;
            Wezel *znajd = znajdz(korzen,liczba);
            if(znajd !=NULL)
            {
                znajd = USUN(korzen,znajd);
            }

            else
            {
               cout<<"Nie ma takiej liczby w drzewie!"; Sleep(4000);
            }

            }
             break;
        case 3: wyswietl_INORDER(korzen); Sleep(20000); break;
        case 4: wyswietl_PREORDER(korzen); Sleep(20000); break;
        case 5: wyswietl_POSTORDER(korzen); Sleep(20000); break;
        default:
            ; break;
    }

    }while (wybor!=6);
    UWOLNIJ(korzen);
    return 0;
}


/*
---------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------
Autor: Michal Rogala
Data: 12.03.2018
Tytul: Drzewo AVL

Program testowany z przykladow:
https://stackoverflow.com/questions/3955680/how-to-check-if-my-avl-tree-implementation-is-correct

-> wszystkie przeszly pozytywnie

Kolejne testy polegaly na wpisywaniu liczb w ten program i w Drzewo AVL ONLINE i porownywanie dzialania

-> nienapotkano bledow w dzialaniu chodz algorytm w pewnych sytuacjach byl inny jak
na przyklad szukanie najmniejszej wartosc w prawym poddrzewie usuwajacego itd.

Komentarz: Uwazam ze korzystanie z aktualizacji wysokosci GENERALNEJ i wysokokosci (balansu) jest zbyt
            duza zeby algorytm ten podlegal pod zlozonosc rowna logn(2)


            Strony z ktorych korzystalem przy pisaniu i bardzo pomogly wyobrazic sobie algorytm:

            -> http://eduinf.waw.pl/inf/alg/001_search/0119.php
            -> http://www.algolist.net/Data_structures/Binary_search_tree/Removal
            -> stackoverflow
            -> youtube (masa wyjasnien itd)

            ----------------------------------------------------------------------------
            ----------------------------------------------------------------------------
            */
