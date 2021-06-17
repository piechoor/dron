#include "Przeszkoda_gran.hh"

using namespace std;

/**
 * Konstruktor parametryczny grani, tworzacy plik
 * roboczy bryly zgodnie z numerem podanym jako parametr.
 * 
 * @param[in] NrGrani - numer wykorzystywany w tworzeniu nazwy pliku roboczego 
 */
Gran::Gran(unsigned int NrGrani) {
    UstawNazwe_Wzorcowy(WZORZEC_GRANI);
    ostringstream StrWyj;
    StrWyj << "dat/PlikRoboczy_Gran" << NrGrani << ".dat";
    UstawNazwe_Roboczy(StrWyj.str());
}

/**
 * Metoda sprawdza, czy zachodzi kolizja miedzy dronem reprezentowanym jako
 * okrag a obiektem klasy.
 * 
 * @param[in] Polozenie - polozenie srodka okregu
 * @param[in] Promien - promien okregu
 * 
 * @retval true - wystapila kolizja drona z grania
 * @retval false - nie wystepuje kolizja
 */
bool Gran::SprKolizje(const Wektor3D &Polozenie, double Promien) {

    Wektor3D PolDrona = Polozenie, PolPrzeszkody = this->Polozenie;
    PolDrona[2] = 0;
    PolPrzeszkody[2] = 0;

    //Wyznaczenie wektora w ukladzie lokalnym wskazujacego na jeden z wierzcholkow
    Wektor3D WekPomoc(0.5*this->Skala[0], 0.5*this->Skala[1],0);
    Macierz3x3 MacObr; UstawRotacjeZ(MacObr, this->Orientacja);

    //Wyznaczenie wektorow wskazujacych na 4 wierzcholki w ukladzie globalnym
    Wektor3D WskNaWierz = MacObr * WekPomoc + PolPrzeszkody;

    //Wyznaczenie polowy przekatnej przeszkody
    double PolPrzek = WskNaWierz.Modul(PolPrzeszkody);

    //Odleglosc srodkow drona i przeszkody
    double OdlSrodkow = PolDrona.Modul(PolPrzeszkody);

    if (Promien + PolPrzek > OdlSrodkow)
        return true;

    return false;
}

/**
 * Metoda przeksztalca wzorcowy szescian na gore
 * stanowiaca jedna z przeszkod. Gran ta jest rowniez skalowana,
 * obracana i translowana zgodnie z wartosciami jej pol.
 * 
 * @retval true - operacja tworzenia grani powiodla sie
 * @retval false - opracja nie powiodla sie
 */
bool Gran::TworzGran() {
    ifstream Plik_BrylaWzorcowa(this->PobierzNazwe_Wzorcowa());
     if (!Plik_BrylaWzorcowa.is_open()) {
     cerr << endl << " Blad otwarcia do odczytu pliku: " << this->PobierzNazwe_Wzorcowa() 
          << endl << endl;
     return false;
     }
     ofstream Plik_BrylaWynikowa(this->PobierzNazwe_Robocza());
     if (!Plik_BrylaWynikowa.is_open()) {
     cerr << endl << " Blad otwarcia do zapisu pliku: " << this->PobierzNazwe_Robocza() 
          << endl << endl;
     return false;
     }
    Wektor3D Wierzch;
    
    for (unsigned int Ind_krawedz = 0; Ind_krawedz < 5; ++Ind_krawedz) {
        for (unsigned int Ind_wierz = 0; Ind_wierz < 4; ++Ind_wierz) {
            Plik_BrylaWzorcowa >> Wierzch;
            if (Plik_BrylaWzorcowa.fail()) return false;

            if (Wierzch[2] == 0.5) Wierzch[0] = 0;
            //if (Wierzch[0] == 0.5) Wierzch[0] = 0; Tworzy pionowa sciane na jednym ze zboczy grani

            Wierzch = this->Skaluj(Wierzch);
            Wierzch = this->TranDoUklGlobalnego(Wierzch);

            Plik_BrylaWynikowa << Wierzch << endl;
            if (Plik_BrylaWynikowa.fail()) return false;
        }
        Plik_BrylaWynikowa << endl;
    }
    return !Plik_BrylaWynikowa.fail();
}

/**
 * Metoda zmieniajaca wspolrzedne wierzcholka tak, aby byl
 * on wyrazony w ukladzie wspolrzednym globalnym
 * 
 * @param[in] Wierzch - wierzcholek, ktory transformujemy do ukladu globalnego
 * @return - wierzcholek w ukladzie globalnym
 */
Wektor3D Gran::TranDoUklGlobalnego(const Wektor3D &Wierzch) const {
    Macierz3x3 MacRotacji; 
    UstawRotacjeZ(MacRotacji, Orientacja);
    return MacRotacji * Wierzch + Polozenie;
}

/**
 * Metoda usuwajaca gran ze sceny. Czysci ona plik roboczy bryly
 * przez co nie jest ona wiecej rysowana na scenie.
 * 
 * @retval true - powodzenie w usunieciu bryly
 * @retval false - nie udalo sie otworzyc pliku roboczego bryly
 */
bool Gran::UsunGran() {
    ofstream Plik_BrylaWynikowa(this->PobierzNazwe_Robocza());
    if (!Plik_BrylaWynikowa.is_open()) {
        cerr << endl << " Blad otwarcia do zapisu pliku: " << this->PobierzNazwe_Robocza() 
            << endl << endl;
        return false;
        }
    else Plik_BrylaWynikowa << endl;
    return true;
}

/**
 * Destruktor - usuwa wszystkie dane z pliku
 * roboczego obiektu gora, tak aby gnuplot nie
 * rysowal go na scenie.
 */
Gran::~Gran() {
    if (!UsunGran()) {
        cerr << "Blad destrukcji grani" << endl;
        exit(0);
    }
}
