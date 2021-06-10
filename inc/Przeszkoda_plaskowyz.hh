#ifndef PRZESZKODA_PLASKOWYZ_HH
#define PRZESZKODA_PLASKOWYZ_HH

/**
 * @file Przeszkoda_plaskowyz.hh
 * 
 * Plik zawiera definicje klasy reprezentujacej
 * jedna z przeszkod - plaskowyz.
 */

#include "BrylaGeometryczna.hh"
#include "ObiektSceny.hh"
#include "Wektor3D.hh"
#include "Macierz3x3.hh"
#include <string>

#define WZORZEC_PLASKOWYZA "bryly_wzorcowe/szescian.dat"

/**
 * @brief Klasa modeluje bryle w formie plaskowyza.
 * 
 * Klasa definiuje plaskowyz - jedna z trzech podstawowych
 * przeszkod prezentowanych na scenie.
 */
class Plaskowyz : public ObiektSceny {
    private:
        /**
         * Polozenie plaskowyza w przestrzeni
         */
        Wektor3D Polozenie;
        /**
         * Orientacja plaskowyza w przestrzeni
         */
        double Orientacja;
    public:
        /**
         * Podstawowy konstruktor plaskowyza.
         */
        Plaskowyz() {}

        /**
         * Konstrutor parametryczny tworzacy nazwe robocza pliku.
         */
        Plaskowyz(unsigned int NrPlaskowyza);

        /**
         * @brief Metoda tworzy plaskowyz i zapisuje go do pliku 
         */
        bool TworzPlaskowyz();

        /**
         * @brief Metoda transferuje wierzcholek do ukladu globalnego
         */
        Wektor3D TranDoUklGlobalnego(const Wektor3D &Wierzch) const;

        /**
         * Zmienia polozenie plaskowyza o podany jako parametr wektor.
         * 
         * @param[in] Translacja - wektor na jaki zmieniamy polozenie plaskowyza
         */
        void ZmienPolozenie(Wektor3D Translacja) {Polozenie = Translacja;}

        /**
         * Zmienia orientacje plaskowyza o podany jako parametr wektor.
         * 
         * @param[in] Obrot - kat o jaki rotujemy plaskowyz
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
        virtual const char* Nazwa() const override {return "Plaskowyz";}

        virtual bool SprKolizje(std::shared_ptr<Dron> DronKol) override;

        /**
         * @brief Usuwa plaskowyz ze sceny i jako obiekt. 
         */
        ~Plaskowyz();
    private:
        /**
         * @brief Metoda usuwajaca plaskowyz.
         */
        bool UsunPlaskowyz();
        
        /**
         * Ustawia nazwe pliku wzorcowego na taka podana jako parametr
         * 
         * @param[in] NazwaWzorca - nazwa pliku wzorcowego graniastopslupa
         */
        void UstawNazwe_Wzorcowy(std::string NazwaWzorca) {Nazwa_BrylaWzorcowa = NazwaWzorca;}

        /**
         * Ustawia nazwe pliku roboczego na taka podana jako parametr
         * 
         * @param[in] NazwaRobocza - nazwa pliku roboczego plaskowyza
         */
        void UstawNazwe_Roboczy(std::string NazwaRobocza) {Nazwa_BrylaRobocza = NazwaRobocza;}

};

#endif