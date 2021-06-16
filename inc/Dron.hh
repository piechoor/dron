#ifndef DRON_HH
#define DRON_HH

#include "Wektor3D.hh"
#include "ObiektSceny.hh"
#include "Prostopadloscian.hh"
#include "Graniastoslup6.hh"
#include "lacze_do_gnuplota.hh"
#include <fstream>
#include <unistd.h>
#include <cmath>
#include <iostream>

#define ILOSC_WIERZ_LINII_TWORZACEJ 4
#define KROK_LOTU_DRONA 1
#define KROK_OBROTU_DRONA 1
#define KROK_OBROTU_ROTORA 10
#define CZAS_KROKU 25000
#define WZORZEC_KORPUS "bryly_wzorcowe/szescian.dat"
#define WZORZEC_ROTOR "bryly_wzorcowe/graniastoslup6.dat"
#define LICZBA_ROTOROW 4
#define PROMIEN_ROTORA 5

#define SKALA_KORPUSU_DRONA_X 10
#define SKALA_KORPUSU_DRONA_Y 10
#define SKALA_KORPUSU_DRONA_Z 15
#define SKALA_WIRNIKA_DRONA_X 10
#define SKALA_WIRNIKA_DRONA_Y 10
#define SKALA_WIRNIKA_DRONA_Z 10

/**
 * @file
 * 
 * Plik zawiera definicje klasy dron,
 * modeluje ona obiekt skladajacy sie z 4
 * rotorow i korpusu.
 */

/**
 * @brief Klasa modeluje przemieszczalnego drona
 * 
 * Klasa dron tworzy drona skladajacego sie z 5 bryl geometrycznych.
 * pozwala na zmiane wspolrzednych tych figur w danych ukladach wspolrzenych
 * tak aby mozliwe bylo rysowanie animacji lotu drona.
 */
class Dron : public ObiektSceny {
    private:
        /**
         * Wektor reprezentujacy polozenie graniastoslupa w przestrzeni
         */
        Wektor3D Polozenie;
        /**
         * Kat reprezentujacy obrocenie graniastoslupa w przestrzeni
         */
        double Orientacja;
        /**
         * Prostopadloscian sluzacy jako korpus drona
         */
        Prostopadloscian Korpus;
        /**
         * Tablica graniastoslupow sluzacych jako rotory drona
         */
        Graniastoslup6 Rotor[LICZBA_ROTOROW];

    public:
        /**
         * @brief Inicjuje drona i tworzy pliki na jego wierzcholki zgodnie z podanym numerem
         */
        void InicjujDrona(unsigned int NrDrona);

        /**
         * Metoda zmieniajaca wspolrzedne wierzcholka tak, aby byl
         * on wyrazony w ukladzie wspolrzednych rodzica
         * 
         * @param[in]  Wierzch - wierzcholek, ktory transformujemy do ukladu rodzica
         * @return - wierzcholek w ukladzie rodzica 
         */
        Wektor3D TranDoUklRodzica(const Wektor3D &Wierzch) const {
            Macierz3x3 MacRotacji; UstawRotacjeZ(MacRotacji, Orientacja);
            return MacRotacji * Wierzch + Polozenie;
        }

        /**
         * @brief Przeprowadza operacje pionowego przelotu drona
         */
        bool WykonajPionowyLot(double Wysokosc, PzG::LaczeDoGNUPlota &Lacze);

        /**
         * @brief Przeprowadza operacje poziomego przelotu drona
         */
        bool WykonajPoziomyLot(double DlugoscLotu, PzG::LaczeDoGNUPlota &Lacze);
        
        /**
         * @brief Przeprowadza opercje obrotu drona o zadany kat
         */
        bool ObrocDrona(double Obrot, PzG::LaczeDoGNUPlota &Lacze);

        /**
         * Wyswietla wspolrzene x i y drona na standardowym wyjsciu.
         * Format: "WSP_X WSPY"
         */
        void WyswietlWsp() const { std::cout << (*this).Polozenie[0] << " " << (*this).Polozenie[1];}

        /**
         * Zwraca aktualne wspolrzedne drona zapisane jako wektor rozmiaru 3.
         * 
         * @return Wektor3D - polozenie drona
         */
        Wektor3D ZwrocWsp() const { return Polozenie; };

        /**
         * Metoda zwracajaca orientacje drona w przestrzeni
         * 
         * @return Orientacja drona
         */
        double ZwrocOrientacje() const { return Orientacja; }

        /**
         * @brief Oblicza i zaposuje wspolrzedne drona w ukladzie globalnym
         */
        bool OblicziZapisz_WspGlb_Drona() const;

        /**
         * Zmienia polozenie drona zgodnie z wektorem3D podanym jako argument wywolania.
         * 
         * @param[in] Translacja - pozadanie polozenie drona
         */
        void ZmienPolozenie(Wektor3D Translacja) {Polozenie = Translacja;}

        /**
         * @brief Oblicza i zwraca promien drona
         */
        double ZwrocPromien() {return 2*PROMIEN_ROTORA + 0.5*SKALA_WIRNIKA_DRONA_X;}

        /**
         * Zwraca nazwe obiektu.
         * 
         * @return const char* - wskaznik na lancuch znakow bedacych nazwa obiektu
         */
        virtual const char* Nazwa() const override {return "Dron";}

        /**
         * @brief Sprawdza czy nie wystepuje kolizja miedzy dronami
         */
        virtual bool SprKolizje(const Wektor3D &Polozenie, double Promien) override;

    private:
        /**
         * @brief Oblicza i zapisuje wspolrzedne drona w ukladzie globalnym
         */
        bool OblicziZapisz_WspGlb_Korpusu() const;
        /**
         * @brief Oblicza i zapisuje do pliku wspolrzedne globalne rotora 
         * podanego jako parametr wywolania 
         */
        bool OblicziZapisz_WspGlb_Rotora(const Graniastoslup6 &Rotor) const;

        /**
         * @brief Ustawia korpus i rotory drona wzgledem siebie
         */
        void UstawElementyDrona();

        /**
         * @brief Obraca wszystkie rotory o zadany kat
         */
        void ObrocRotory(double Kat_obr);
};

#endif