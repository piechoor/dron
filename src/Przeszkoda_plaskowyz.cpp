#include "Przeszkoda_plaskowyz.hh"

using namespace std;

Plaskowyz::Plaskowyz(unsigned int NrPlaskowyza) {
    UstawNazwe_Wzorcowy(WZORZEC_PLASKOWYZA);
    ostringstream StrWyj;
    StrWyj << "dat/PlikRoboczy_Gora" << NrPlaskowyza << ".dat";
    UstawNazwe_Roboczy(StrWyj.str());
}

/**
 * Metoda przeksztalca wzorcowy szescian na gore
 * stanowiaca jedna z przeszkod. Plaskowyz ten jest rowniez skalowany,
 * obracany i translowany zgodnie z wartosciami jego pol.
 * 
 * @retval true - operacja tworzenia plaskowyza powiodla sie
 * @retval false - opracja nie powiodla sie
 */
bool Plaskowyz::TworzPlaskowyz() {
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

            Wierzch[0] *= 2;
            Wierzch[1] *= 2;

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
Wektor3D Plaskowyz::TranDoUklGlobalnego(const Wektor3D &Wierzch) const {
    Macierz3x3 MacRotacji; 
    UstawRotacjeZ(MacRotacji, Orientacja);
    return MacRotacji * Wierzch + Polozenie;
}

bool Plaskowyz::UsunPlaskowyz() {
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
Plaskowyz::~Plaskowyz() {
    if (!UsunPlaskowyz()) {
        cerr << "Blad destrukcji plaskowyza" << endl;
        exit(0);
    }
}
