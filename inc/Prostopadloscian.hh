#ifndef PROSTOPADLOSCIAN_HH
#define PROSTOPADLOSCIAN_HH

#include <iostream>
#include <fstream>

#include "Wektor.hh"
#include "Macierz.hh"
#include "Wektor3D.hh"
#include "Macierz3x3.hh"
#include "BrylaGeometryczna.hh"

/**
 *  @brief Definicja klasy prostopadloscian. 
 * 
 *  Klasa prostopadloscian modeluje prostopadloscian skladjacy sie z 8 wierzcholkow wyrazonych 
 *  jako wektory 3D. Pozwala wykonywac operacje umozliwiajace obrot, translacje, zapis do pliku 
 *  oraz sprawdzenie stani prostopadloscianu.
 */
class Prostopadloscian : public Bryla {
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
         * @return - wierzcholek w ukladzie rodzica 
         */
        Wektor3D TranDoUklRodzica(const Wektor3D &Wierzch) const {
            Macierz3x3 MacRotacji; UstawRotacjeZ(MacRotacji, Orientacja);
            return MacRotacji * Wierzch + Polozenie;
        }

        /**
         * Ustawia nazwe pliku wzorcowego na taka podana jako parametr
         * 
         * @param[in] NazwaWzorca - nazwa pliku wzorcowego graniastopslupa
         */
        void UstawNazwe_Wzorcowy(std::string NazwaWzorca) {Nazwa_BrylaWzorcowa = NazwaWzorca;}

        /**
         * @brief Tworzy i ustawia nazwe pliku roboczego dla prostopadloscianu.
         */
        void UstawNazwe_Roboczy(unsigned int NrDrona);

        /**
         * Zmienia polozenie bryly o podany jako parametr wektor.
         * 
         * @param[in] Translacja - wektor na jaki zmieniamy polozenie bryly
         */
        void ZmienPolozenie(Wektor3D Translacja) {Polozenie = Translacja;}
};


#endif
