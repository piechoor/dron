#include "Scena.hh"

using namespace std;

/**
 * Konstruktor sceny inicjujacy wszystkie drony
 * oraz lacze do gnuplota.
 */
Scena::Scena() {
    NrAktywnegoDrona = 0;
    LiczbaObiektow = 0;

    Wektor3D PolozenieDrona1(POCZ_WSP_X_DRON1, POCZ_WSP_Y_DRON1, POCZ_WYSOKOSC_DRONA);
    Wektor3D PolozenieDrona2(POCZ_WSP_X_DRON2, POCZ_WSP_Y_DRON2, POCZ_WYSOKOSC_DRONA);

    Dodaj_Drona(PolozenieDrona1);
    Dodaj_Drona(PolozenieDrona2);

    this->InicjujLacze();

    Wektor3D Pol(30,150,0), Sk(20,20,150);
    double testOrient = 45;
    DodajPrzeszkode_Gora(Sk, Pol, testOrient);

    Pol = {170, 120, 0}; Sk = {30,60,80}; testOrient = 15;
    DodajPrzeszkode_Gora(Sk, Pol, testOrient);

    Pol = {100, 180, 0}; Sk = {30,80,130}; testOrient = 95;
    DodajPrzeszkode_Gran(Sk, Pol, testOrient);

    Pol = {150, 30, 0}; Sk = {15,15,20}; testOrient = 70;
    DodajPrzeszkode_Plaskowyz(Sk, Pol, testOrient);
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

/**
 * Metoda dodajaca na scene przeszkode w formie gory.
 * Pozwala uzytkownikowi na skalowanie przeszkody, jej
 * tanslacje oraz obrot wokol osi Z. Przeszkoda jest alokowana
 * dynamicznie za pomoca listy wskaznikow wspoldzielonych.
 * 
 * @param[in] Skala - wektor reprezentujacy czynniki skalujace przeszkode wokol 3 osi
 * @param[in] Polozenie - pozadane polozenie przeszkody na scenie
 * @param[in] Orientacja - kat obrotu przeszkody wokol osi Z
 * 
 * @retval true - dodanie przeszkody powiodlo sie
 * @retval false - nastapil blad podczas dodawania przeszkody
 */
bool Scena::DodajPrzeszkode_Gora(const Wektor3D &Skala, Wektor3D Polozenie, double Orientacja) {
    shared_ptr<Gora> NowaGora(new Gora(LiczbaObiektow));
    Polozenie[2] += 0.5 * Skala[2]; // Dostosowanie wysokosci grani tak aby po skalowaniu
                                    // znajdowala sie na plaszczyznie powierzchni

    NowaGora->UstawSkale(Skala);
    NowaGora->ZmienPolozenie(Polozenie);
    NowaGora->ZmienOrientacje(Orientacja);

    if (!NowaGora->TworzGore()) return false;

    std::string Tymcz = NowaGora->PobierzNazwe_Robocza();
    const char *PlikRoboczy = Tymcz.c_str();

    Lacze.DodajNazwePliku(PlikRoboczy);

    Przeszkody.push_back(NowaGora);
    LiczbaObiektow++;

    return true;
}

/**
 * Metoda dodajaca na scene drona, zeskalowanego zgodnie ze stalymi
 * symbolicznymi umieszczonymi w naglowku "Dron.hh"
 * Parametrem wywolania metody jest Wektor3D, ktory
 * pozwala na polozenie drona w konktretnym miejscu na scenie
 * 
 * @param[in] Polozenie - pozadane polozenie przeszkody na scenie
 */
void Scena::Dodaj_Drona(const Wektor3D &Polozenie) {
    shared_ptr<Dron> NowyDron(new Dron);

    NowyDron->ZmienPolozenie(Polozenie);
    NowyDron->InicjujDrona(LiczbaObiektow);

    TabDronow.push_back(NowyDron);
    Przeszkody.push_back(NowyDron);

    LiczbaObiektow++;
}

/**
 * Metoda dodajaca na scene przeszkode w formie grani.
 * Pozwala uzytkownikowi na skalowanie przeszkody, jej
 * tanslacje oraz obrot wokol osi Z. Przeszkoda jest alokowana
 * dynamicznie za pomoca listy wskaznikow wspoldzielonych.
 * 
 * @param[in] Skala - wektor reprezentujacy czynniki skalujace przeszkode wokol 3 osi
 * @param[in] Polozenie - pozadane polozenie przeszkody na scenie
 * @param[in] Orientacja - kat obrotu przeszkody wokol osi Z
 * 
 * @retval true - dodanie przeszkody powiodlo sie
 * @retval false - nastapil blad podczas dodawania przeszkody
 */
bool Scena::DodajPrzeszkode_Gran(const Wektor3D &Skala, Wektor3D Polozenie, double Orientacja) {
    shared_ptr<Gran> NowaGran(new Gran(LiczbaObiektow));
    Polozenie[2] += 0.5 * Skala[2]; // Dostosowanie wysokosci plaskowyza tak aby po skalowaniu
                                    // znajdowala sie na plaszczyznie powierzchni

    NowaGran->UstawSkale(Skala);
    NowaGran->ZmienPolozenie(Polozenie);
    NowaGran->ZmienOrientacje(Orientacja);

    if (!NowaGran->TworzGran()) return false;

    std::string Tymcz = NowaGran->PobierzNazwe_Robocza();
    const char *PlikRoboczy = Tymcz.c_str();

    Lacze.DodajNazwePliku(PlikRoboczy);

    Przeszkody.push_back(NowaGran);
    LiczbaObiektow++;

    return true;
}

/**
 * Metoda dodajaca na scene przeszkode w formie plaskowyza.
 * Pozwala uzytkownikowi na skalowanie przeszkody, jej
 * tanslacje oraz obrot wokol osi Z. Przeszkoda jest alokowana
 * dynamicznie za pomoca listy wskaznikow wspoldzielonych.
 * 
 * @param[in] Skala - wektor reprezentujacy czynniki skalujace przeszkode wokol 3 osi
 * @param[in] Polozenie - pozadane polozenie przeszkody na scenie
 * @param[in] Orientacja - kat obrotu przeszkody wokol osi Z
 * 
 * @retval true - dodanie przeszkody powiodlo sie
 * @retval false - nastapil blad podczas dodawania przeszkody
 */
bool Scena::DodajPrzeszkode_Plaskowyz(const Wektor3D &Skala, Wektor3D Polozenie, double Orientacja) {
    shared_ptr<Plaskowyz> NowyPlaskowyz(new Plaskowyz(LiczbaObiektow));

    Polozenie[2] += 0.5 * Skala[2]; // Dostosowanie wysokosci gory tak aby po skalowaniu
                                    // znajdowala sie na plaszczyznie powierzchni

    NowyPlaskowyz->UstawSkale(Skala);
    NowyPlaskowyz->ZmienPolozenie(Polozenie);
    NowyPlaskowyz->ZmienOrientacje(Orientacja);

    if (!NowyPlaskowyz->TworzPlaskowyz()) return false;

    std::string Tymcz = NowyPlaskowyz->PobierzNazwe_Robocza();
    const char *PlikRoboczy = Tymcz.c_str();

    Lacze.DodajNazwePliku(PlikRoboczy);

    Przeszkody.push_back(NowyPlaskowyz);
    LiczbaObiektow++;

    return true;
}

/**
 * Pozwala uzytkownikowi na usuniecie wybranej przeszkody ze sceny.
 * Uzytkownik ma mozliwosc wyboru przeszkody z listy.
 * Jezeli wybranie zostany numer bryly nieznajdujacej sie na scenie
 * albo nie ma na niej juz zadnych usuwalnych elementow 
 * funkcja zakonczy swoje dzialanie i zwroci false.
 * 
 * @return true - prawidlowe usuniecie wybranej przeszkody ze sceny
 * @return false - brak elementow na scenie badz wybrano nieprawdlowy
 * indeks bryly do usuniecia
 */
bool Scena::UsunPrzeszkode() {
    unsigned int NumerElem = 1;
    std::list<std::shared_ptr<ObiektSceny>>::iterator iter = Przeszkody.begin();
    
    if (LiczbaObiektow == 0) {
        cout << "Brak elementow na scenie" << endl;
        return false;
    }

    cout << endl << "Wybierz element powierzchni do usuniecia:" << endl;
    for (const shared_ptr<ObiektSceny> &Wsk : Przeszkody) {
        cout << NumerElem << ". ";
        Wsk->WyswietlWsp();
        cout << " " << Wsk->Nazwa() << endl;
        NumerElem++;
    }
    cout << endl << "Podaj numer elementu> ";
    cin >> NumerElem;
    
    if (NumerElem < 1 || NumerElem > LiczbaObiektow) {
        cerr << "Podano nieprawidlowy numer elementu" << endl;
        return false;
    }

    advance(iter, NumerElem - 1);
    Przeszkody.erase(iter);

    cout << endl << endl << "Element zostal usuniety." << endl << endl
         << "Aktualna liczba obiektow Wektor3D: " 
         << Wektor3D::PobierzLiczbeAktual() << endl
         << "  Laczna liczba obiektow Wektor3D: " 
         << Wektor3D::PobierzLiczbeStworz() << endl << endl;
         
    --LiczbaObiektow;

    RysujScene();
    return true;
}



/**
 * Metoda tworzaca sciezke przelotu drona zgodnie z parametrami podanymi
 * jako argumenty jej wywolania. Zapisuje ta sciezkie do pliku i wyswietla
 * ja na scenie.
 * 
 * @param[in] WspTrasy - wspolrzedna poczatka trasy
 * @param[in] Dlugosc - dlugosc trasy przelotu drona
 * @param[in] Kat  - kat o ktory obroci sie dron
 * 
 * @retval true - poprawnie udalo sie zrealizowac wyznaczenie trasy lotu drona
 * @retval false - operacja ta nie powiodla sie
 */
bool Scena::RysujSciezkeLotu(Wektor3D WspTrasy, double Dlugosc, double Kat) {
    ofstream trasa_przelotu("dat/trasa_przelotu.dat");
        if (!trasa_przelotu.is_open()) {
        cerr << endl << " Blad otwarcia do zapisu pliku: " << "dat/trasa_przelotu.dat"
            << endl << endl;
        return false;
    }

    double Kat_obr = Kat * M_PI / 180; // Zamiana kata w stopniach na radiany

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

/**
 * Sprawdza mozliwosc ladowania drona na scenie, tzn sprawdza czy
 * aktywny dron nie przecina obrysu zadnej z przeszkod (oprocz siebie).
 * Jezeli ladowisko jest niedostepne wyswietla komunikat o rodzaju przeszkody.
 * 
 * @param[in] SrodekDrona - wspolrzedne srodka aktywnego drona
 * @param[in] PromienDrona - promien aktywnego drona
 * @param[in] Dron - wskaznik wspoldzielony na drona
 * 
 * @retval true - ladowanie jest mozlie
 * @retval false - na ladowisku jest przeszkoda
 */
bool Scena::SprMozliwosciLadowania(const Wektor3D &SrodekDrona,
                                   double PromienDrona,
                                   const shared_ptr<Dron> &Dron) const {

    for (const shared_ptr<ObiektSceny> &Ob : Przeszkody) {
        if (Ob == Dron) continue;
        if (Ob->SprKolizje(SrodekDrona, PromienDrona)) {
            cout << endl << "Ladowisko niedostepne!" << endl;
            cout << "Wykryto element powierzchni typu: \"" 
                 << Ob->Nazwa() << "\"." << endl << endl;
            return false;
        }
    }
    
    return true;
} 

/**
 * Metoda realizujaca przelot drona o zadane parametry na scenie.
 * 
 * Najpierw wyswietla sciezke lotu, wznosi drona na bezpieczna wysokosc,
 * wykonuje poziomy przelot, sprawdza czy dostepne jest ladowisko i laduje jezeli
 * tak, a jezeli nie to do skutku leci dalej na bezpieczna odleglosc i aktualizuje
 * sciezke przelotu drona. Nastepnie opuszcza drona na powierzchnie i usuwa trase przelotu.
 * 
 * @param[in] Kierunek - kat w ktorym dron ma sie przemiescic
 * @param[in] Dlugosc - dlugosc o jaka dron ma sie przemiescic
 * 
 * @retval true - udany przelot drona
 * @retval false - operacja nie powiodla sie
 */
bool Scena::PrzelotDrona(double Kierunek, double Dlugosc) {

    Wektor3D PolPoczDrona = PobierzAktywnegoDrona().ZwrocWsp();
    double OrientacjaDrona = PobierzAktywnegoDrona().ZwrocOrientacje();

    if(!RysujSciezkeLotu(PolPoczDrona, Dlugosc, Kierunek + OrientacjaDrona))
        return false;
    cout << endl << "Rysuje zaplanowana sciezke lotu ..." << endl;
    cout << endl << endl << "Realizacja przelotu ..." << endl << endl;

    PobierzAktywnegoDrona().WykonajPionowyLot(BEZPIECZNA_WYSOKOSC, Lacze);
    PobierzAktywnegoDrona().ObrocDrona(Kierunek, Lacze);
    PobierzAktywnegoDrona().WykonajPoziomyLot(Dlugosc, Lacze);

    while(!SprMozliwosciLadowania(PobierzAktywnegoDrona().ZwrocWsp(),
                              PobierzAktywnegoDrona().ZwrocPromien(),
                              PobierzWskAktywnegoDrona())) {
        cout << "Lot zostal wydluzony." << endl 
             << "Poszukiwanie wolnego ladowiska." << endl << endl;
        Dlugosc += BEZPIECZNA_ODLEGLOSC;
        if(!ZerujSciezkeLotu()) return false;
        if(!RysujSciezkeLotu(PolPoczDrona, Dlugosc, Kierunek + OrientacjaDrona))
            return false;
        PobierzAktywnegoDrona().WykonajPoziomyLot(BEZPIECZNA_ODLEGLOSC, Lacze);
    }

    cout << "Ladowisko dostepne." << endl << "Rozpoczecie procedury ladowania." << endl;

    PobierzAktywnegoDrona().WykonajPionowyLot(-BEZPIECZNA_WYSOKOSC, Lacze);
    
    cout << endl << endl << "Dron wyladowal ..." << endl << endl;

    if(!ZerujSciezkeLotu()) return false;
    
    return true;
}