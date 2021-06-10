#ifndef PRZESZKODA_GORA_HH
#define PRZESZKODA_GORA_HH

/**
 * @file Przeszkoda_gora.hh
 * 
 * Plik zawiera definicje klasy reprezentujacej
 * jedna z przeszkod - gore.
 */

#include "BrylaGeometryczna.hh"
#include "ObiektSceny.hh"
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
class Gora : public ObiektSceny {
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
        /**
         * Podstawowy konstruktor gory.
         */
        Gora() {}

        /**
         * Konstrutor parametryczny tworzacy nazwe robocza pliku.
         */
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

        /**
         * Wsywietla wspolrzedna X i Y przeszkody w formacie (X, Y)
         */
        virtual void WyswietlWsp() const override { std::cout << "(" << Polozenie[0] << ", " << Polozenie[1] << ")";}

        /**
         * Zwraca nazwe obiektu.
         * 
         * @return const char* - wskaznik na lancuch znakow bedacych nazwa obiektu
         */
        virtual const char* Nazwa() const override {return "Gora z ostrym szczytem";}

        /**
         * @brief Sprawdza kolizje gory z dronem podanym jako parametr wywolania.
         */
        virtual bool SprKolizje(const Wektor3D &Polozenie, double Promien) override;

        /**
         * @brief Usuwa gore ze sceny i jako obiekt. 
         */
        ~Gora();

    private:
        /**
         * @brief Metoda usuwajaca gore.
         */
        bool UsunGore();

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