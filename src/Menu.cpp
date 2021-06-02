#include "Menu.hh"

using namespace std;

/**
 * Glowna funkcja programu, realizuje przelot dronow na
 * podanej jako parametr scenie. Zwraca true lub false w 
 * zaleznosci czy wszystkie operacje powiodly sie.
 * 
 * @param[in] Sc - scena, na ktorej wykonujemy przelot dronow
 * 
 * @retval true - gdy wszystkie operacje powiodly sie
 * @retval false - ktoras z operacji nie zostala wykonana prawidlowo
 */
bool PrzetwarzajMenu(Scena &Sc) {
    char Wybor;
    double Kat_obr, Dlugosc_lotu;

    if(!Sc.UstawDrony()) return false;
    if(!Sc.ZerujSciezkeLotu()) return false;
    Sc.RysujScene();

    do {
        cout << "Twoj wybor, m - menu> " ; cin >> Wybor;
        switch (Wybor) {
        case 'm':
            WyswietlOpcje(Sc); break;
        case 'a':
            PrzetwWyborDrona(Sc); break;
        case 'p':
            cout << "Podaj kierunek lotu (kat w stopniach)> "; cin >> Kat_obr;
            cout << "                   Podaj dlugosc lotu> "; cin >> Dlugosc_lotu;
            if(!ZadajPrzelot(Sc, Kat_obr, Dlugosc_lotu)) return false;
            break;
        case 'd':
            if(!DodajElemPowierz(Sc)) return false;
            break;
        case 'u':
            UsunElemPowierz(Sc); break;
        case 'k': 
            break;
        default:
            cin.ignore(1000,'\n');
            cout << "Wprowadzono nieprawilowa opcje. Sprobuj jeszcze raz" << endl;
        }
     } while (Wybor != 'k');
    
    return true;
}

/**
 * Funkcja pomocnicza wyswietlajaca dostepne opcje menu.
 * Pokazuje rowniez wspolrzedne aktywnego drona oraz
 * aktualna i ogolna liczbe obiektow typu Wektor3D
 * 
 * @param[in] Sc - scena, na ktorej wykonujemy przelot dronow
 */
void WyswietlOpcje(Scena &Sc) {
    cout << "Polozenie Drona aktywnego (x,y):  ";
    Sc.PobierzAktywnegoDrona().WyswietlWsp();
    cout << endl << endl << "a - wybierz aktywnego drona" << endl
         << "p - zadaj parametry przelotu" << endl
         << "d - dodaj element powierzchni" << endl
         << "m - wyswietl menu" << endl << endl
         << "k - koniec dzialania programu" << endl << endl
         << "Aktualna liczba obiektow Wektor3D: " 
         << Wektor3D::PobierzLiczbeAktual() << endl
         << "  Laczna liczba obiektow Wektor3D: " 
         << Wektor3D::PobierzLiczbeStworz() << endl << endl;
}

/**
 * Funkcja przeprowadzajaca operacje wyboru aktywnego dorna na
 * scenie podanej jako parametr jej wywolania. Wyswietla
 * aktualne wspolrzedne polozenia dronow oraz podkreska aktywnego
 * drona. Dodatkowo pokazuje liczbe aktualnych i ogolnych obiektow Wektor3D
 * 
 * @param[in] Sc - scena, na ktorej wykonujemy przelot dronow
 */
void PrzetwWyborDrona(Scena &Sc) {
    unsigned int NrDrona = Sc.ZwrocNrAktywnegoDrona();

    cout << endl << "Wybor aktywnego drona" << endl << endl;
    Sc.WybierzDrona(1);
    cout << "1 - Polozenie (x,y): "; Sc.PobierzAktywnegoDrona().WyswietlWsp();
    if (NrDrona == 1) cout << "   <-- Dron aktywny" << endl;
    else  cout << endl;

    Sc.WybierzDrona(2);
    cout << "2 - Polozenie (x,y): "; Sc.PobierzAktywnegoDrona().WyswietlWsp();
    if (NrDrona == 2) cout << "   <-- Dron aktywny" << endl << endl;
    else  cout << endl;

    cout << "Wprowadz numer aktywnego drona> "; cin >> NrDrona;
    if (NrDrona <= LICZBA_DRONOW) Sc.WybierzDrona(NrDrona);
    else cout << "Wybrano nieprawidlowy numer drona" << endl;

    cout << endl << "Polozenie Drona aktywnego (x,y): "; 
    Sc.PobierzAktywnegoDrona().WyswietlWsp();

    cout << endl;

    cout << endl << "Aktualna liczba obiektow Wektor3D: " 
         << Wektor3D::PobierzLiczbeAktual() << endl
         << "  Laczna liczba obiektow Wektor3D: " 
         << Wektor3D::PobierzLiczbeStworz() << endl << endl;

}

/**
 * Funkcja przeprowadzajaca operacje przelotu aktywnego drona
 * na scenie przekazanej jako parametr wywolania owej funkcji.
 * Przelot drona realizowany jest w kierunku podanym jako kat 
 * oraz o odleglosc podana jako parametr wywolania.
 * Najpierw wyswietla sciezke lotu, wznosi drona na bezpieczna wysokosc,
 * wykonuje poziomy przelot, opuszcza drona na powierzchnie i usuwa trase
 * przelotu.
 * 
 * @param[in] Sc - scena, na ktorej wykonujemy przelot dronow
 * @param[in] Kierunek - kierunek wyrazony jako kat, w ktorym chcemy wykonac przelot 
 * @param[in] Dlugosc - dlugosc przelotu
 * 
 * @retval true - gdy wszystkie operacje powiodly sie
 * @retval false - ktoras z operacji nie zostala wykonana prawidlowo
 */
bool ZadajPrzelot(Scena &Sc, double Kierunek, double Dlugosc) {

    PzG::LaczeDoGNUPlota Lacze = Sc.ZwrocLacze();

    if(!Sc.RysujSciezkeLotu(Dlugosc, Kierunek + Sc.PobierzAktywnegoDrona().ZwrocOrientacje()))
        return false;
 
    cout << endl << endl << "Realizacja przelotu ..." << endl << endl;

    Sc.PobierzAktywnegoDrona().WykonajPionowyLot(BEZPIECZNA_WYSOKOSC, Lacze);
    Sc.PobierzAktywnegoDrona().ObrocDrona(Kierunek, Lacze);
    Sc.PobierzAktywnegoDrona().WykonajPoziomyLot(Dlugosc, Lacze);
    Sc.PobierzAktywnegoDrona().WykonajPionowyLot(-BEZPIECZNA_WYSOKOSC, Lacze);

    if(!Sc.ZerujSciezkeLotu()) return false;
    
    return true;
}

bool DodajElemPowierz(Scena &Sc) {
    int NrElem = 0;
    Wektor3D Skala;
    double Wsp_X, Wsp_Y, Orientacja;

    cout << "Wybierz rodzaj powierzchniowego elementu" << endl << endl
         << "   1 - Gora z ostrym sztytem" << endl
         << "   2 - Gora z grania" << endl
         << "   3 - Plaskowyz" << endl << endl
         << "Wprowadz numer typu elementu> ";
    cin >> NrElem; cin.ignore(1000,'\n');
    if (NrElem <1 || NrElem > 3) {
        cerr << "Wprowadzono nieprawidlowy numer elementu" << endl;
        return false;
    }
    cout << endl << endl << "Podaj scale wzdluz kolejnych osi OX, OY, OZ."
         << endl << "Wprowadz skale: OX OY OZ> ";
    cin >> Skala;
    cout << endl << "Podaj wspolrzedne srodka podstawy x,y." << endl
         << "Wprowadz wspolrzedne: x y> ";
    cin >> Wsp_X >> Wsp_Y;
    cout << endl << "Podaj kat obrotu elementu wokol osi OZ." << endl
         << "Wprowadz kat obrotu: > ";
    cin >> Orientacja;

    Wektor3D Polozenie(Wsp_X, Wsp_Y, 0);

    if (NrElem == 1) if(!Sc.DodajPrzeszkode_Gora(Skala, Polozenie, Orientacja)) return false;
    if (NrElem == 2) if(!Sc.DodajPrzeszkode_Gran(Skala, Polozenie, Orientacja)) return false;
    if (NrElem == 3) if(!Sc.DodajPrzeszkode_Plaskowyz(Skala, Polozenie, Orientacja)) return false;

    cout << endl << "Element zostal dodany do sceny." << endl << endl;
    Sc.RysujScene();

    return true;
}

void UsunElemPowierz(Scena &Sc) {
    
    Sc.UsunPrzeszkode();
}