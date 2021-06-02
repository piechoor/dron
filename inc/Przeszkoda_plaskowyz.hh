#ifndef PRZESZKODA_PLASKOWYZ_HH
#define PRZESZKODA_PLASKOWYZ_HH

/**
 * @file Przeszkoda_plaskowyz.hh
 * 
 * Plik zawiera definicje klasy reprezentujacej
 * jedna z przeszkod - plaskowyz.
 */

#include "BrylaGeometryczna.hh"
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
class Plaskowyz : public Bryla {
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
        Plaskowyz() {}
        Plaskowyz(unsigned int NrPlaskowyza);
        /**
         * @brief Metoda tworzy plaskowyz i zapisuje go do pliku 
         */
        bool TworzPlaskowyz();

        Wektor3D TranDoUklGlobalnego(const Wektor3D &Wierzch) const;
        void ZmienPolozenie(Wektor3D Translacja) {Polozenie = Translacja;}
        void ZmienOrientacje(double Obrot) {Orientacja = Obrot;}

        virtual void WyswietlWsp() const override { std::cout << "(" << Polozenie[0] << ", " << Polozenie[1] << ")";}
        
        virtual const char* Nazwa() const override {return "Plaskowyz";}

        ~Plaskowyz();
    private:
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
         * @param[in] NazwaRobocza - nazwa pliku roboczego gory
         */
        void UstawNazwe_Roboczy(std::string NazwaRobocza) {Nazwa_BrylaRobocza = NazwaRobocza;}

};

#endif