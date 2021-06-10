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

bool Dron::SprKolizje(std::shared_ptr<Dron> DronKol) {
    //Wyznaczenie promienia i polozenia drona
    double R = DronKol->ZwrocPromien();
    Wektor3D PolDron = DronKol->ZwrocWsp();

    //Wyznaczenie wektora w ukladzie lokalnym wskazujacego na jeden z wierzcholkow
    Wektor3D WekPomoc(0.5*this->Skala[0], 0.5*this->Skala[1],0);
    Macierz3x3 MacObr; UstawRotacjeZ(MacObr, this->Orientacja);

    //Wyznaczenie wektorow wskazujacych na 4 wierzcholki w ukladzie globalnym
    Wektor3D WskNaWierz[4];
    WskNaWierz[0] = MacObr * WekPomoc + this->Polozenie; WekPomoc[0] *= (-1); //(X,Y)
    WskNaWierz[1] = MacObr * WekPomoc + this->Polozenie; WekPomoc[1] *= (-1); //(-X,Y)
    WskNaWierz[2] = MacObr * WekPomoc + this->Polozenie; WekPomoc[0] *= (-1); //(-X,-Y)
    WskNaWierz[3] = MacObr * WekPomoc + this->Polozenie;                     //(X,-Y)

    //Sprawdzenie czy w okregu wyznaczonym przez drona znajduje sie jakis wierzcholek
    //Zgodnie z nierownoscia (x-x0)^2+(y-y0)^2<=R^2
    for (unsigned int i = 0; i < 4; ++i) {
        if (pow((WskNaWierz[i][0]-PolDron[0]),2) + pow((WskNaWierz[i][1]-PolDron[1]),2) <= pow(R,2))
            return true;
    }
    //Sprawdzenie czy dron znajduje sie w przeszkodzie
    //Jest tak, gdy wszystkie wierzcholki przeszkody sa poza obrysem drona (sprawdzone wyzej)
    //i jezeli odleglosc srodka drona od srodka przeszkody jest mniejsza od polowy dlugosci krotszego boku
    double DlugoscBoku1 = WskNaWierz[0].Modul(WskNaWierz[1];
    double DlugoscBoku1 = WskNaWierz[0].Modul(WskNaWierz[3];
    double OdlSrodkow = PolDron.Modul(Polozenie);
    if (OdlSrodkow > DlugoscBoku1/2 || OdlSrodkow > DlugoscBoku2/2 )
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
