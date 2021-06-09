#ifndef PRZESZKODA_GRAN_HH
#define PRZESZKODA_GRAN_HH

/**
 * @file Przeszkoda_gran.hh
 * 
 * Plik zawiera definicje klasy reprezentujacej
 * jedna z przeszkod - gran.
 */

#include "BrylaGeometryczna.hh"
#include "ObiektSceny.hh"
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
class Gran : public ObiektSceny {
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
        /**
         * Podstawowy konstruktor grani.
         */
        Gran() {}

        /**
         * Konstrutor parametryczny tworzacy nazwe robocza pliku.
         */
        Gran(unsigned int NrGrani);

        /**
         * @brief Metoda tworzy gran i zapisuje ja do pliku 
         */
        bool TworzGran();

        /**
         * @brief Metoda transferuje wierzcholek do ukladu globalnego
         */
        Wektor3D TranDoUklGlobalnego(const Wektor3D &Wierzch) const;

        /**
         * Zmienia polozenie grani o podany jako parametr wektor.
         * 
         * @param[in] Translacja - wektor na jaki zmieniamy polozenie grani
         */
        void ZmienPolozenie(Wektor3D Translacja) {Polozenie = Translacja;}

        /**
         * Zmienia orientacje grani o podany jako parametr wektor.
         * 
         * @param[in] Obrot - kat o jaki rotujemy gran
         */
        void ZmienOrientacje(double Obrot) {Orientacja = Obrot;}

        /**
         * Wsywietla wspolrzedna X i Y przeszkody w formacie (X, Y)
         */
        virtual void WyswietlWsp() const override { std::cout << "(" << Polozenie[0] << ", " << Polozenie[1] << ")";}

        /**
         * Zwraca nazwe obiektu.
         * 
         * @return const char* - wskaznik na lancuch znakow bedacych nazwa obiektu
         */
        virtual const char* Nazwa() const override {return "Gora z grania";}
        
        /**
         * @brief Usuwa gran ze sceny i jako obiekt. 
         */
        ~Gran();
    private:
        /**
         * @brief Metoda usuwajaca gran.
         */
        bool UsunGran();
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