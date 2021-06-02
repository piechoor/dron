#include "Przeszkoda_gora.hh"

using namespace std;


Gora::Gora(unsigned int NrGory) {
    UstawNazwe_Wzorcowy(WZORZEC_GORY);
    ostringstream StrWyj;
    StrWyj << "dat/PlikRoboczy_Gora" << NrGory << ".dat";
    UstawNazwe_Roboczy(StrWyj.str());
}

/**
 * Metoda przeksztalca wzorcowy szescian na gore
 * stanowiaca jedna z przeszkod. Gora ta jest rowniez skalowana,
 * obracana i translowana zgodnie z wartosciami jej pol.
 * 
 * @retval true - operacja tworzenia gory powiodla sie
 * @retval false - opracja nie powiodla sie
 */
bool Gora::TworzGore() {
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

            if (Wierzch[2] > -0.5 && Wierzch[2] < 0.5) {
                Wierzch[0] /= 2; Wierzch[1] /= 2;
            }
            else if (Wierzch[2] == 0.5) {
                Wierzch[0] =0;  Wierzch[1] =0;
            }

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
Wektor3D Gora::TranDoUklGlobalnego(const Wektor3D &Wierzch) const {
    Macierz3x3 MacRotacji; 
    UstawRotacjeZ(MacRotacji, Orientacja);
    return MacRotacji * Wierzch + Polozenie;
}


bool Gora::UsunGore() {
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
Gora::~Gora() {
    if (!UsunGore()) {
        cerr << "Blad destrukcji gory" << endl;
        exit(0);
    }
}