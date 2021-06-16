#ifndef SCENA_HH
#define SCENA_HH

#include <fstream>
#include <memory> //dla shared_ptr

#include "BrylaGeometryczna.hh"
#include "Prostopadloscian.hh"
#include "Wektor3D.hh"
#include "Macierz3x3.hh"

#include "ObiektSceny.hh"
#include "Dron.hh"
#include "lacze_do_gnuplota.hh"
#include "Przeszkoda_gora.hh"
#include "Przeszkoda_gran.hh"
#include "Przeszkoda_plaskowyz.hh"

#define LICZBA_DRONOW 2
#define POCZ_WYSOKOSC_DRONA 8

#define POCZ_WSP_X_DRON1 20
#define POCZ_WSP_Y_DRON1 20
#define POCZ_WSP_X_DRON2 60
#define POCZ_WSP_Y_DRON2 60

#define BEZPIECZNA_WYSOKOSC 100
#define BEZPIECZNA_ODLEGLOSC 30

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
         * Lista wskaznikow na drony znajdujacych sie na scenie
         */
        std::list<std::shared_ptr<Dron>> TabDronow;
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
        std::list<std::shared_ptr<ObiektSceny>> Przeszkody;
        
        /**
         * Liczba przeszkod na scenie
         */
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
        Dron& PobierzAktywnegoDrona() {if (NrAktywnegoDrona == 0) return *TabDronow.front();
                                       else return *TabDronow.back(); }

        std::shared_ptr<Dron> PobierzWskAktywnegoDrona() {
            std::list<std::shared_ptr<Dron>>::iterator iter = TabDronow.begin();
            advance(iter, NrAktywnegoDrona);
            return *iter;
         }

        /**
         * Metoda zmieniajaca nnumer aktywnego drona.
         * 
         * @param[in] wybor - Numer drona, ktory ma byc aktywny.
         */
        void WybierzDrona(unsigned int wybor) {NrAktywnegoDrona = (wybor-1);}

        void Dodaj_Drona(const  Wektor3D &Polozenie);

        /**
         * @brief Metoda dodaje na scene gore w zadanym formacie
         */
        bool DodajPrzeszkode_Gora(const Wektor3D &Skala, Wektor3D Polozenie, double Orientacja);

        /**
         * @brief Metoda dodaje na scene gran w zadanym formacie
         */
        bool DodajPrzeszkode_Gran(const Wektor3D &Skala, Wektor3D Polozenie, double Orientacja);
        
        /**
         * @brief Metoda dodaje na scene plaskowyz w zadanym formacie
         */
        bool DodajPrzeszkode_Plaskowyz(const Wektor3D &Skala, Wektor3D Polozenie, double Orientacja);

        /**
         * @brief Pozwala na wybranie i usuniecie przeszkody ze sceny
         */
        bool UsunPrzeszkode(); 
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
         * @brief Metoda rysuje na scenie sciezke lotu drona 
         * zgodnie z zadanymi parametrami
         */
        bool RysujSciezkeLotu(Wektor3D WspTrasy, double Dlugosc, double Kat);

        /**
         * @brief Metoda usuwajaca sciezke przelotu drona ze sceny
         */
        bool ZerujSciezkeLotu();
        
        bool SprMozliwosciLadowania(const Wektor3D &SrodekDrona, double PromienDrona, const std::shared_ptr<Dron> &Dron) const;

        bool PrzelotDrona(double Kierunek, double Dlugosc);

    private:
        /**
         * @brief Metoda prywatna inicjujaca lacze do gnuplota.
         */
        void InicjujLacze();
};

#endif