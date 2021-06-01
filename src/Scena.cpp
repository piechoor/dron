#include "Scena.hh"

using namespace std;

/**
 * Konstruktor sceny inicjujacy wszystkie drony
 * oraz lacze do gnuplota.
 */
Scena::Scena() {
    NrAktywnegoDrona = 0;
    LiczbaObiektow = LICZBA_OBIEKTOW_STARTOWYCH;
    for (unsigned int i = 0; i < LICZBA_DRONOW; ++i)
        TabDronow[i].InicjujDrona(i);
    this->InicjujLacze();

    // Dodawanie wstepnych elementow powierzchni:
    // shared_ptr<Gora> Gora1(new Gora());
    // Przeszkody.push_back(Gora1);
}

/**
 * Metoda inicjujaca lacze do gnuplota. Dodaje nazwy plikow
 * potrzebnych do narysowania sceny i obslugi przelotow dronow
 * i wyznaczenia trasy ich przelotow.
 * Ustawia rowniez zakresy widoku osi i widok na scene.
 */
void Scena::InicjujLacze() {
    Lacze.Inicjalizuj();  // Tutaj startuje gnuplot.

    Lacze.DodajNazwePliku("bryly_wzorcowe/plaszczyzna.dat");

    Lacze.DodajNazwePliku("dat/trasa_przelotu.dat");
    
    Lacze.DodajNazwePliku("dat/PlikRoboczy_Dron0_Korpus.dat");
    Lacze.DodajNazwePliku("dat/PlikRoboczy_Dron0_Rotor1.dat"); 
    Lacze.DodajNazwePliku("dat/PlikRoboczy_Dron0_Rotor2.dat");
    Lacze.DodajNazwePliku("dat/PlikRoboczy_Dron0_Rotor3.dat");
    Lacze.DodajNazwePliku("dat/PlikRoboczy_Dron0_Rotor4.dat");

    Lacze.DodajNazwePliku("dat/PlikRoboczy_Dron1_Korpus.dat");
    Lacze.DodajNazwePliku("dat/PlikRoboczy_Dron1_Rotor1.dat");
    Lacze.DodajNazwePliku("dat/PlikRoboczy_Dron1_Rotor2.dat");
    Lacze.DodajNazwePliku("dat/PlikRoboczy_Dron1_Rotor3.dat");
    Lacze.DodajNazwePliku("dat/PlikRoboczy_Dron1_Rotor4.dat");

    Lacze.ZmienTrybRys(PzG::TR_3D);

    Lacze.UstawZakresX(0, 200);
    Lacze.UstawZakresY(0, 200);
    Lacze.UstawZakresZ(0, 290);

    Lacze.UstawRotacjeXZ(64,65); // Tutaj ustawiany jest widok
}

void Scena::DodajPrzeszkode_Gora(Wektor3D Skala, Wektor3D Polozenie, double Orientacja) {
    shared_ptr<Gora> NowaGora(new Gora(LiczbaObiektow));
    Polozenie[2] += 0.5 * Skala[2]; // Dostosowanie wysokosci gory tak aby po skalowaniu
                                    // znajdowala sie na plaszczyznie powierzchni

    NowaGora->UstawSkale(Skala[0], Skala[1], Skala[2]);
    NowaGora->ZmienPolozenie(Polozenie);
    NowaGora->ZmienOrientacje(Orientacja);

    NowaGora->TworzGore();

    std::string Tymcz = NowaGora->PobierzNazwe_Robocza();
    const char *PlikRoboczy = Tymcz.c_str();

    Lacze.DodajNazwePliku(PlikRoboczy);

    Przeszkody.push_back(NowaGora);
}

/**
 * Metoda zmieniajaca polozenie dronow na ich startowe pozycje
 * okreslone za pomoca stalych sympolicznych.
 * 
 * @retval true - udalo sie zmienic polozenie dronow
 * @retval false - operacja nie powiodla sie
 */
bool Scena::UstawDrony() {
    Wektor3D PolozenieDrona1(POCZ_WSP_X_DRON1, POCZ_WSP_Y_DRON1, POCZ_WYSOKOSC_DRONA);
    Wektor3D PolozenieDrona2(POCZ_WSP_X_DRON2, POCZ_WSP_Y_DRON2, POCZ_WYSOKOSC_DRONA);

    TabDronow[0].ZmienPolozenie(PolozenieDrona1);
    if(!TabDronow[0].OblicziZapisz_WspGlb_Drona()) return false;

    TabDronow[1].ZmienPolozenie(PolozenieDrona2);
    if(!TabDronow[1].OblicziZapisz_WspGlb_Drona()) return false;

    return true;
}

/**
 * Metoda tworzaca sciezke przelotu drona zgodnie z parametrami podanymi
 * jako argumenty jej wywolania. Zapisuje ta sciezkie do pliku i wyswietla
 * ja na scenie.
 * 
 * @param[in] Dlugosc - dlugosc trasy przelotu drona
 * @param[in] Kat  - kat o ktory obroci sie dron
 * 
 * @retval true - poprawnie udalo sie zrealizowac wyznaczenie trasy lotu drona
 * @retval false - operacja ta nie powiodla sie
 */
bool Scena::RysujSciezkeLotu(double Dlugosc, double Kat) {
    ofstream trasa_przelotu("dat/trasa_przelotu.dat");
        if (!trasa_przelotu.is_open()) {
        cerr << endl << " Blad otwarcia do zapisu pliku: " << "dat/trasa_przelotu.dat"
            << endl << endl;
        return false;
    }

    double Kat_obr = Kat * M_PI / 180; // Zamiana kata w stopniach na radiany

    Wektor3D WspTrasy;
    WspTrasy = TabDronow[NrAktywnegoDrona].ZwrocWsp();
    Wektor3D WekKierunkowy(cos(Kat_obr)*Dlugosc,sin(Kat_obr)*Dlugosc,0); // Utowrzenie wektora kierunkowego

    trasa_przelotu << WspTrasy << endl;
    
    WspTrasy[2] += BEZPIECZNA_WYSOKOSC;

    trasa_przelotu << WspTrasy << endl;

    WspTrasy = WspTrasy + WekKierunkowy;

    trasa_przelotu << WspTrasy << endl;

    WspTrasy[2] -= BEZPIECZNA_WYSOKOSC;

    trasa_przelotu << WspTrasy << endl;

    this->RysujScene();

    return true;
}

/**
 * Metoda usuwajaca sciezke lotu i rysujaca scene bez niej.
 * 
 * @retval true - udalo sie usunac sciezke lotu
 * @retval false - operacja ta nie powiodla sie
 */
bool Scena::ZerujSciezkeLotu() {
    ofstream trasa_przelotu("dat/trasa_przelotu.dat");
        if (!trasa_przelotu.is_open()) {
        cerr << endl << " Blad otwarcia do zapisu pliku: " << "dat/trasa_przelotu.dat"
            << endl << endl;
        return false;
    }
    trasa_przelotu << endl;

    this->RysujScene();

    return true;
}