#ifndef GRANIASTOSLUP6_HH
#define GRANIASTOSLUP6_HH

#include "Wektor3D.hh"
#include "BrylaGeometryczna.hh"
#include "Macierz3x3.hh"

/**
 * @file Graniastoslup6.hh
 * 
 * Plik zawiera definicje klasy Graniastoslup6,
 * modelujacej graniastoslup prawidlowy, foremny o
 * podstawie 6 wierzcholkowej.
 */


/**
 * @brief Klasa modelujaca graniastoslup
 * 
 * Klasa modeluje graniastoslup o 6 wierzcholkach w podstawach.
 * Dziedziczy ona z klasy bryla.
 */
class Graniastoslup6 : public Bryla {
    protected:
        /**
         * Wektor reprezentujacy polozenie graniastoslupa w przestrzeni
         */
        Wektor3D Polozenie;
        /**
         * Kat reprezentujacy obrocenie graniastoslupa w przestrzeni
         */
        double Orientacja;
    public:
        /**
         * Metoda zmieniajaca wspolrzedne wierzcholka tak, aby byl
         * on wyrazony w ukladzie wspolrzednych rodzica
         * 
         * @param[in] Wierzch - wierzcholek, ktory transformujemy do ukladu rodzica
         * @retval - wierzcholek w ukladzie rodzica 
         */
        Wektor3D TranDoUklRodzica(const Wektor3D &Wierzch) const {
            Macierz3x3 MacRotacji; 
            UstawRotacjeZ(MacRotacji, Orientacja);
            return MacRotacji * Wierzch + Polozenie;
        }

        /**
         * Zmienia orientacje graniastoslupa. Dodaje kat podany jako
         * parametr do aktualnej orientacji.
         * 
         * @param[in] Kat_obr - kat, o ktory obracamy granistoslup
         */
        void ZmienOrientacje(double Kat_obr) {Orientacja += Kat_obr;}

        /**
         * Ustawia nazwe pliku wzorcowego na taka podana jako parametr
         * 
         * @param[in] NazwaWzorca - nazwa pliku wzorcowego graniastopslupa
         */
        void UstawNazwe_Wzorcowy(std::string NazwaWzorca) {Nazwa_BrylaWzorcowa = NazwaWzorca;}

        /**
         * @brief Tworzy i ustawia nazwe pliku roboczego dla granisatoslupa.
         */
        void UstawNazwe_Roboczy(unsigned int NrDrona, unsigned int NrRotora);

        /**
         * Zmienia polozenie bryly o podany jako parametr wektor.
         * 
         * @param[in] Translacja - wektor na jaki zmieniamy polozenie bryly
         */
        void ZmienPolozenie(Wektor3D Translacja) {Polozenie = Translacja;}
};

#endif