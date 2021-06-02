#ifndef WEKTOR2x2_HH
#define WEKTOR2x2_HH

#include "Wektor.hh"

/**
 * @file Wektor3D.hh
 * 
 * Plik zawiera definicje klasy modelujacej
 * wektor 3D, ktory jest instancja szablonu wektor
 * o rozmiarze 3.
 */

/**
 * @brief Klasa modeluje pojecie wektora 3 wymiarowego
 * 
 * Klasa tworzy wektor o rozmiarze 3 jako instancje
 * szablonu wektora. Pozwala na podstawowe operacje na
 * tego typu wektorze. Liczy takze liczbe obiektow Wektor3d
 * aktualnych i ogolnie stworzonych.
 */
class Wektor3D : public Wektor<3> {
        /**
         * Pole przechowujace liczbe stworzonych wektorow
         */
        static int StworzonychWek;
        /**
         * Pole przechowujace liczbe usunietych wektorow
         */
        static int UsunietychWek;

    public:
        /**
         * Konstruktor korzystajacy z konstruktora klasy Wektor oraz inkrementujacy licznik
         * stworzonych wektorow 3D
         */
        Wektor3D() : Wektor<3>() {++StworzonychWek;} 

        /**
         * Konstruktor kapiujacy dla klasy Wektor3D, inkrementuje licznik
         * stworzonych wektorow 3D
         */
        //Wektor3D(const Wektor3D &Wek) : Wektor<3>(Wek) {(*this) = Wek; ++StworzonychWek;}

        /**
         * Kontruktor pobierajacy trzy parametry i przypisywujacy je do 
         * wspolrzednych wektora. Inkrementuje licznik stoworzonych wektorow 3D
         * 
         * @param[in] Wsp_x - parametr wspolrzednej x wektora
         * @param[in] Wsp_y - parametr wspolrzednej y wektora
         * @param[in] Wsp_z - parametr wspolrzednej z wektora
         */
        Wektor3D(double Wsp_x, double Wsp_y, double Wsp_z) : Wektor<3>()
            {(*this)[0] = Wsp_x; (*this)[1] = Wsp_y; (*this)[2] = Wsp_z; ++StworzonychWek;}

        Wektor3D(const Wektor<3> &Wek) : Wektor<3>(Wek) {++StworzonychWek;} // Konstruktor kopiujacy

        /**
         * Destruktor wektora 3D, inkrementuje licznik usunietych wektorow 3D
         */
        ~Wektor3D()  { ++UsunietychWek; }

        /**
         * Metoda pobierajacy trzy parametry i przypisywujacy je do wspolrzednych wektora.
         * 
         * @param[in] wartosc_x - parametr wspolrzednej x wektora
         * @param[in] wartosc_y - parametr wspolrzednej y wektora
         * @param[in] wartosc_z - parametr wspolrzednej z wektora
         */
        void UstawWar(double wartosc_x, double wartosc_y, double wartosc_z)
            {(*this)[0] = wartosc_x; (*this)[1] = wartosc_y; (*this)[2] = wartosc_z;}
        

        /**
         * Metoda zwraca liczbe aktualnie istniejacych wektorow 3D
         * 
         * @retval liczba istniejacych wetorow 3D
         */
        static int PobierzLiczbeAktual() {return (StworzonychWek - UsunietychWek);}

        /**
         * Metoda zwraca liczbe stworzonych wektorow 3D 
         * 
         * @return liczba stworzonych wetorow 3D
         */
        static int PobierzLiczbeStworz() {return StworzonychWek;}
};

#endif