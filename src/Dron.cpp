#include "Dron.hh"

using namespace std;

/**
 * Skaluje korpus i rotory drona wedlug stalych symbolicznych.
 * Ustawia nazwy plikow wzorcowych i roboczych dla kazdego elementu drona.
 * Ustawia elementy drona wzgledem siebie.
 * 
 * @param[in] NrDrona - parametr potrzebny do nadania nazw plikow
 * przechowujacych informacje o polozeniu drona
 */
void Dron::InicjujDrona(unsigned int NrDrona) {
     Wektor3D SkalaDrona(SKALA_KORPUSU_DRONA_X,SKALA_KORPUSU_DRONA_Y,SKALA_KORPUSU_DRONA_Z),
              SkalaWirnika(SKALA_WIRNIKA_DRONA_X,SKALA_WIRNIKA_DRONA_Y,SKALA_WIRNIKA_DRONA_Z);
     Korpus.UstawSkale(SkalaDrona);
     Korpus.UstawNazwe_Wzorcowy(WZORZEC_KORPUS);
     Korpus.UstawNazwe_Roboczy(NrDrona);

     for (unsigned int i = 0; i < LICZBA_ROTOROW; ++i) {
          Rotor[i].UstawSkale(SkalaWirnika);
          Rotor[i].UstawNazwe_Wzorcowy(WZORZEC_ROTOR);
          Rotor[i].UstawNazwe_Roboczy(NrDrona, i);
     }

     this->UstawElementyDrona();
     this->OblicziZapisz_WspGlb_Drona();
}

/**
 * Metoda sprawdzajaca czy nie zachodzi kolizja miedzy
 * obiektem klasy a dronem podanym jako parametr wywolania metody.
 * 
 * @param[in] Polozenie - polozenie srodka okregu
 * @param[in] Promien - promien okregu
 * 
 * @retval true - zachodzi kolizja miedzy dronami
 * @retval false - nie zachodzi kolizja
 */
bool Dron::SprKolizje(const Wektor3D &Polozenie, double Promien) {
     double R = this->ZwrocPromien();

     Wektor3D Pol = this->ZwrocWsp();

     if (Pol.Modul(Polozenie) < R+Promien)
          return true;
     else
          return false;
}

/**
 * Oblicza i zapisuje wspolrzeedne globalne wszytskich elementow drona.
 * 
 * @retval true jezeli operacja zapisu sie udala
 * @retval false jezeli operacja zapisu sie nie powiodla
 */
bool Dron::OblicziZapisz_WspGlb_Drona() const {
     if(!OblicziZapisz_WspGlb_Korpusu()) return false;

     for (int i = 0; i <4; ++i) {
          if(!OblicziZapisz_WspGlb_Rotora(Rotor[i])) return false;
     }
     return true;
}

/**
 * Oblicza i zapisuje wspolrzedne globalne korpusu drona wyrazonego
 * poprzez prostopadloscian.
 * 
 * @retval true jezeli operacja zapisu sie udala
 * @retval false jezeli operacja zapisu sie nie powiodla
 */
bool Dron::OblicziZapisz_WspGlb_Korpusu() const{

     ifstream Plik_BrylaWzorcowa(Korpus.PobierzNazwe_Wzorcowa());
     if (!Plik_BrylaWzorcowa.is_open()) {
     cerr << endl << " Blad otwarcia do odczytu pliku: " << Korpus.PobierzNazwe_Wzorcowa() 
          << endl << endl;
     return false;
     }

     ofstream Plik_BrylaWynikowa(Korpus.PobierzNazwe_Robocza());
     if (!Plik_BrylaWynikowa.is_open()) {
     cerr << endl << " Blad otwarcia do zapisu pliku: " << Korpus.PobierzNazwe_Robocza() 
          << endl << endl;
     return false;
     }

     Wektor3D Wierzch;

     Plik_BrylaWzorcowa >> Wierzch;
     while (!Plik_BrylaWzorcowa.fail()) {

     for (unsigned int IloscWierzcholkow = 0; IloscWierzcholkow < ILOSC_WIERZ_LINII_TWORZACEJ;
          ++IloscWierzcholkow) 
     {
          Wierzch = Korpus.Skaluj(Wierzch);
          Wierzch = Korpus.TranDoUklRodzica(Wierzch);
          Wierzch = this->TranDoUklRodzica(Wierzch);

          Plik_BrylaWynikowa << Wierzch << endl;
          Plik_BrylaWzorcowa >> Wierzch;
     }

     Plik_BrylaWynikowa << endl;
     }
     return !Plik_BrylaWynikowa.fail();
}

/**
 * Oblicza i zapisuje wspolrzedne globalne rotora drona podanego
 * jako prarametr metody, wyrazonego poprzez prostopadloscian.
 * 
 * @param[in] Rotor - rotor, ktory poddajemy transformacji
 * 
 * @retval true jezeli operacja zapisu sie udala
 * @retval false jezeli operacja zapisu sie nie powiodla
 */
bool Dron::OblicziZapisz_WspGlb_Rotora(const Graniastoslup6 &Rotor) const{

     ifstream Plik_BrylaWzorcowa(Rotor.PobierzNazwe_Wzorcowa());
     if (!Plik_BrylaWzorcowa.is_open()) {
     cerr << endl << " Blad otwarcia do odczytu pliku: " << Rotor.PobierzNazwe_Wzorcowa() 
          << endl << endl;
     return false;
     }

     ofstream Plik_BrylaWynikowa(Rotor.PobierzNazwe_Robocza());
     if (!Plik_BrylaWynikowa.is_open()) {
     cerr << endl << " Blad otwarcia do zapisu pliku: " << Rotor.PobierzNazwe_Robocza() 
          << endl << endl;
     return false;
     }

     Wektor3D Wierzch;

     Plik_BrylaWzorcowa >> Wierzch;

     while (!Plik_BrylaWzorcowa.fail()) {
     for (unsigned int IloscWierzcholkow = 0; IloscWierzcholkow < ILOSC_WIERZ_LINII_TWORZACEJ;
          ++IloscWierzcholkow) 
     {
          Wierzch = Rotor.Skaluj(Wierzch);
          Wierzch = Rotor.TranDoUklRodzica(Wierzch);
          Wierzch = this->TranDoUklRodzica(Wierzch);

          Plik_BrylaWynikowa << Wierzch << endl;
          Plik_BrylaWzorcowa >> Wierzch;
     }

     Plik_BrylaWynikowa << endl;
     }
     return !Plik_BrylaWynikowa.fail();
}

/**
 * Wykonuje pionowy lot drona o wysokosc zadana jako parametr wywolania metody.
 * Tworzy rowniez animacje lotu z wykorzystaniem lacza podanego jako parametr.
 * 
 * @param[in] Wysokosc - wysokosc na jaka wzniesc ma sie dron. Jezeli bedzie ujemna dron bedzie opadal.
 * @param[in] Lacze - lacze dzieki ktoremu dokonujemy animacji lotu drona
 * 
 * @retval true - wykonano prawidlowy przelot
 * @retval false - operacja nie powiodla sie
 */
bool Dron::WykonajPionowyLot(double Wysokosc, PzG::LaczeDoGNUPlota &Lacze) {
     double PrzeleconyDystans = 0;

     if (Wysokosc >= 0) {
          while (PrzeleconyDystans < Wysokosc) {
               Polozenie[2] += KROK_LOTU_DRONA;
               PrzeleconyDystans += KROK_LOTU_DRONA;
               ObrocRotory(KROK_OBROTU_ROTORA);
               OblicziZapisz_WspGlb_Drona();
               usleep(CZAS_KROKU);
               if(!Lacze.Rysuj()) return false;
          }
     }
     else {
          while (PrzeleconyDystans > Wysokosc) {
               Polozenie[2] -= KROK_LOTU_DRONA;
               PrzeleconyDystans -= KROK_LOTU_DRONA;
               ObrocRotory(KROK_OBROTU_ROTORA);
               OblicziZapisz_WspGlb_Drona();
               usleep(CZAS_KROKU);
               if(!Lacze.Rysuj()) return false;
          }
     }
     return true;
}

/**
 * Wykonuje poziomy lot drona o dlugosci zadanej jako parametr wywolania metody.
 * Tworzy rowniez animacje lotu z wykorzystaniem lacza podanego jako parametr.
 * 
 * @param[in] DlugoscLotu - dlugosc trasy jaka przeleciec ma dron
 * @param[in] Lacze - lacze dzieki ktoremu dokonujemy animacji lotu drona
 * 
 * @retval true - wykonano prawidlowy przelot
 * @retval false - operacja nie powiodla sie
 */
bool Dron::WykonajPoziomyLot(double DlugoscLotu, PzG::LaczeDoGNUPlota &Lacze) {
     Wektor3D PolozeniePoczatkowe = Polozenie;
     double Kat_rot = Orientacja * M_PI / 180; // Zamiana kata w stopniach na radiany

     Wektor3D WekKierunkowy(cos(Kat_rot),sin(Kat_rot),0); // Utowrzenie wektora kierunkowego

     if (DlugoscLotu >= 0) {
          while (PolozeniePoczatkowe.Modul(Polozenie) <= DlugoscLotu) {
               Polozenie = Polozenie + WekKierunkowy;
               ObrocRotory(KROK_OBROTU_ROTORA);
               OblicziZapisz_WspGlb_Drona();
               usleep(CZAS_KROKU);
               if(!Lacze.Rysuj()) return false;
          }
     }
     else {
          cerr << "Podano nieprawidlowa dlugosc lotu poziomego, powinna byc ona dodatnia!" 
               << endl << "Dron nie wykonal przelotu poziomego." << endl << endl;
          return false;
     }
     return true;
}

/**
 * Wykonuje obrot drona o zadany kat podany jako parametr wywolania.
 * Tworzy rowniez animacje obrotu z wykorzystaniem lacza podanego jako parametr.
 * 
 * @param[in] Obrot - dlugosc trasy jaka przeleciec ma dron
 * @param[in] Lacze - lacze dzieki ktoremu dokonujemy animacji lotu drona
 * 
 * @retval true - wykonano prawidlowy obrot
 * @retval false - operacja nie powiodla sie
 */
bool Dron::ObrocDrona(double Obrot, PzG::LaczeDoGNUPlota &Lacze) {
     double MiaraObrocenia = 0;

     while (MiaraObrocenia < Obrot) {
          Orientacja += KROK_OBROTU_DRONA;
          MiaraObrocenia += KROK_OBROTU_DRONA;
          ObrocRotory(KROK_OBROTU_ROTORA);
          OblicziZapisz_WspGlb_Drona();
          usleep(CZAS_KROKU);
          if(!Lacze.Rysuj()) return false;
     }
     while (MiaraObrocenia > Obrot) {
          Orientacja -= KROK_OBROTU_DRONA;
          MiaraObrocenia -= KROK_OBROTU_DRONA;
          ObrocRotory(KROK_OBROTU_ROTORA);
          OblicziZapisz_WspGlb_Drona();
          usleep(CZAS_KROKU);
          if(!Lacze.Rysuj()) return false;
     }
     return true;
}

/**
 * Metoda ustawiajaca elementy drona wzgledem siebie.
 * transluje ona rotory drona, tak aby byly ustawione prawidlowo.
 * Wykorzystuje stale symboliczne.
 */
void Dron::UstawElementyDrona() {

     Wektor3D TranslacjaRotor1(PROMIEN_ROTORA,PROMIEN_ROTORA,PROMIEN_ROTORA);
     Wektor3D TranslacjaRotor2(-PROMIEN_ROTORA,PROMIEN_ROTORA,PROMIEN_ROTORA);
     Wektor3D TranslacjaRotor3(-PROMIEN_ROTORA,-PROMIEN_ROTORA,PROMIEN_ROTORA);
     Wektor3D TranslacjaRotor4(PROMIEN_ROTORA,-PROMIEN_ROTORA,PROMIEN_ROTORA);

     Rotor[0].ZmienPolozenie(TranslacjaRotor1);
     Rotor[1].ZmienPolozenie(TranslacjaRotor2);
     Rotor[2].ZmienPolozenie(TranslacjaRotor3);
     Rotor[3].ZmienPolozenie(TranslacjaRotor4);
}

/**
 * Obraca rotory o zadany kat podany jako parametr wywolania.
 * Rotory obracaja sie tak, ze naprzecciwlegle odbracaja sie w
 * jedna strone, a drugie naprzeciwlegle w druga.
 * 
 * @param[in] Kat_obr - kat obrotu, o ktory obrocic sie maja rotory.
 */
void Dron::ObrocRotory(double Kat_obr) {
     Rotor[0].ZmienOrientacje(Kat_obr);
     Rotor[1].ZmienOrientacje(-Kat_obr);
     Rotor[2].ZmienOrientacje(Kat_obr);
     Rotor[3].ZmienOrientacje(-Kat_obr);
}