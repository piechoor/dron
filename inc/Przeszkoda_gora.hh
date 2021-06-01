#ifndef PRZESZKODA_GORA_HH
#define PRZESZKODA_GORA_HH

/**
 * @file Przeszkoda_gora.hh
 * 
 * Plik zawiera definicje klasy reprezentujacej
 * jedna z przeszkod - gore.
 */

#include "BrylaGeometryczna.hh"
#include "Wektor3D.hh"
#include "Macierz3x3.hh"
#include <string>

#define WZORZEC_GORY "bryly_wzorcowe/szescian.dat"

/**
 * @brief Klasa modeluje bryle w formie gory.
 * 
 * Klasa definiuje gore - jedna z trzech podstawowych
 * przeszkod prezentowanych na scenie.
 */
class Gora : public Bryla {
    private:
        /**
         * Polozenie gory w przestrzeni
         */
        Wektor3D Polozenie;
        /**
         * Orientacja gory w przestrzeni
         */
        double Orientacja;
    public:
        Gora() {std::cout << "Stworzono gore bez numeru!" << std::endl;}
        Gora(unsigned int NrGory);
        /**
         * @brief Metoda tworzy gore i zapisuje ja do pliku 
         */
        bool TworzGore();

        /**
         * @brief Metoda transferuje wierzcholek do ukladu globalnego
         */
        Wektor3D TranDoUklGlobalnego(const Wektor3D &Wierzch) const;

        /**
         * Zmienia polozenie gory o podany jako parametr wektor.
         * 
         * @param[in] Translacja - wektor na jaki zmieniamy polozenie gory
         */
        void ZmienPolozenie(Wektor3D Translacja) {Polozenie = Translacja;}

        /**
         * Zmienia orientacje gory o podany jako parametr wektor.
         * 
         * @param[in] Obrot - kat o jaki rotujemy gore
         */
        void ZmienOrientacje(double Obrot) {Orientacja = Obrot;}

        bool UsunGore();

        ~Gora();

    private:
        /**
         * Ustawia nazwe pliku wzorcowego na taka podana jako parametr
         * 
         * @param[in] NazwaWzorca - nazwa pliku wzorcowego graniastopslupa
         */
        void UstawNazwe_Wzorcowy(std::string NazwaWzorca) {Nazwa_BrylaWzorcowa = NazwaWzorca;}

        /**
         * Ustawia nazwe pliku roboczego na taka podana jako parametr
         * 
         * @param[in] NazwaRobocza - nazwa pliku roboczego gory
         */
        void UstawNazwe_Roboczy(std::string NazwaRobocza) {Nazwa_BrylaRobocza = NazwaRobocza;}


};

#endif