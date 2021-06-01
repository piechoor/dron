#ifndef PRZESZKODA_GRAN_HH
#define PRZESZKODA_GRAN_HH

/**
 * @file Przeszkoda_gran.hh
 * 
 * Plik zawiera definicje klasy reprezentujacej
 * jedna z przeszkod - gran.
 */

#include "BrylaGeometryczna.hh"
#include "Wektor3D.hh"
#include "Macierz3x3.hh"
#include <string>

#define WZORZEC_GRANI "bryly_wzorcowe/szescian.dat"

/**
 * @brief Klasa modeluje bryle w formie grani.
 * 
 * Klasa definiuje gran - jedna z trzech podstawowych
 * przeszkod prezentowanych na scenie.
 */
class Gran : public Bryla {
    private:
        /**
         * Polozenie grani w przestrzeni
         */
        Wektor3D Polozenie;
        /**
         * Orientacja grani w przestrzeni
         */
        double Orientacja;
    public:
        Gran() {std::cout << "Stworzono gran bez numeru!" << std::endl;}
        Gran(unsigned int NrGrani);

        /**
         * @brief Metoda tworzy gran i zapisuje ja do pliku 
         */
        bool TworzGran();

        Wektor3D TranDoUklGlobalnego(const Wektor3D &Wierzch) const;
        void ZmienPolozenie(Wektor3D Translacja) {Polozenie = Translacja;}
        void ZmienOrientacje(double Obrot) {Orientacja = Obrot;}
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
         * @param[in] NazwaRobocza - nazwa pliku roboczego grani
         */
        void UstawNazwe_Roboczy(std::string NazwaRobocza) {Nazwa_BrylaRobocza = NazwaRobocza;}
};

#endif