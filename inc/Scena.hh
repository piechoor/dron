#ifndef SCENA_HH
#define SCENA_HH

#include <fstream>
#include <memory> //dla shared_ptr

#include "BrylaGeometryczna.hh"
#include "Prostopadloscian.hh"
#include "Wektor3D.hh"
#include "Macierz3x3.hh"
#include "Dron.hh"
#include "lacze_do_gnuplota.hh"
#include "Przeszkoda_gora.hh"
#include "Przeszkoda_gran.hh"
#include "Przeszkoda_plaskowyz.hh"

#define LICZBA_DRONOW 2
#define POCZ_WYSOKOSC_DRONA 8
#define LICZBA_OBIEKTOW_STARTOWYCH 4

#define POCZ_WSP_X_DRON1 20
#define POCZ_WSP_Y_DRON1 20
#define POCZ_WSP_X_DRON2 60
#define POCZ_WSP_Y_DRON2 60

#define BEZPIECZNA_WYSOKOSC 80

/**
 *  @file
 *  @brief Modeluje klase scena
 * 
 *  Zostaje zdefiniowana klasa scena zawierajaca tablice dronow
 *  oraz lacze do GNU-plota
 */

/**
 * @brief Modeluje klase pozwalajaca na rysowanie przelotow dronow.
 * 
 * Klasa Scena zawiera podstawowe elementy do przeprowadzenia
 * lotow dronow oraz ich wyswietlania za pomoca programu gnuplot.
 */
class Scena {
    private:
        /**
         * Tablica dronow znajdujacych sie na scenie
         */
        Dron TabDronow[LICZBA_DRONOW];
        /**
         * Lacze do GNU-plota
         */
        PzG::LaczeDoGNUPlota Lacze;
        /**
         * Numer aktywnego drona na scenie
         */
        unsigned int NrAktywnegoDrona;
        /**
         * Lista przeszkod znajdujacych sie na scenie
         */
        std::list<std::shared_ptr<Bryla>> Przeszkody;

        unsigned int LiczbaObiektow;

    public:
        /**
         * @brief Konstruktor inicjujacy elementy sceny.
         */
        Scena();

        /**
         * Metoda zwracajaca aktywnego drona.
         * 
         * @return Zwraca referencje do drona zgodnie z numerem aktywnego drona.
         */
        Dron& PobierzAktywnegoDrona() {return TabDronow[NrAktywnegoDrona];}

        /**
         * Metoda zmieniajaca nnumer aktywnego drona.
         * 
         * @param[in] wybor - Numer drona, ktory ma byc aktywny.
         */
        void WybierzDrona(unsigned int wybor) {NrAktywnegoDrona = (wybor-1);}

        void DodajPrzeszkode_Gora(Wektor3D Skala, Wektor3D Polozenie, double Orientacja);
        void DodajPrzeszkode_Gran(Wektor3D Skala, Wektor3D Polozenie, double Orientacja);
        void DodajPrzeszkode_Plaskowyz(Wektor3D Skala, Wektor3D Polozenie, double Orientacja);

        /**
         * Metoda zwracajaca numer aktywnego drona
         * 
         * @return Numer aktywnego drona
         */
        unsigned int ZwrocNrAktywnegoDrona() const {return NrAktywnegoDrona + 1;}

        /**
         * Metoda zwraca referencje lacza do gnuplota bedacego elementem sceny.
         * 
         * @return Lacze do gnuplota sceny
         */
        const PzG::LaczeDoGNUPlota& ZwrocLacze() const {return (*this).Lacze;}

        /**
         * Metoda rysujaca scene z wykorzystaniem lacza do gnuplota bedacego
         * ekenentem sceny.
         */
        void RysujScene() {Lacze.Rysuj();}

        /**
         * @brief Metoda ustawiajaca drony w ich poczatkowych pozycjach na scenie
         */
        bool UstawDrony();

        /**
         * @brief Metoda rysuje na scenie sciezke lotu drona 
         * zgodnie z zadanymi parametrami
         */
        bool RysujSciezkeLotu(double Dlugosc, double Kat);

        /**
         * @brief Metoda usuwajaca sciezke przelotu drona ze sceny
         */
        bool ZerujSciezkeLotu();

    private:
        /**
         * @brief Metoda prywatna inicjujaca lacze do gnuplota.
         */
        void InicjujLacze();
};

#endif