#ifndef PRZESZKODA_GORA_HH
#define PRZESZKODA_GORA_HH

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
        /**
         * @brief Metoda tworzy plaskowyz i zapisuje go do pliku 
         */
        bool TworzPlaskowyz();

        Wektor3D TranDoUklGlobalnego(const Wektor3D &Wierzch) const;
        void ZmienPolozenie(Wektor3D Translacja) {Polozenie = Translacja;}
        void ZmienOrientacje(double Obrot) {Orientacja = Obrot;}
        void UstawNazwe_Wzorcowy(std::string NazwaWzorca) {Nazwa_BrylaWzorcowa = NazwaWzorca;}
        void UstawNazwe_Roboczy(unsigned int NrGory);

};

#endif