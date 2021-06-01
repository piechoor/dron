#ifndef BRYLA_GEOMETRYCZNA_HH
#define BRYLA_GEOMETRYCZNA_HH

#include <string>
#include "Wektor3D.hh"
#include <fstream>

/**
 * @file BrylaGeometryczna.hh
 * 
 * Plik zawiera definicje klasy reprezentujacej
 * podstawowa bryle geometryczna.
 */

/**
 * @brief Klasa definiuje pojecie bryly geometrycznej.
 * 
 * Klasa definiuje podstawowe pojecie bryly geometrycznej i
 * elementarne operacje, ktore mozna na niej wykonywac.
 */
class Bryla {
    protected:
        /**
         * Wektor przechowujacy skale figury w osiach x,y i z
         */
        Wektor3D Skala;
        /**
         * Kontener na nazwe pliku przechowujacego wspolrzedne bryly wzorcowej
         */
        std::string Nazwa_BrylaWzorcowa;
        /**
         * Kontener na nazwe pliku przechowujacego wspolrzedne bryly finalnej
         */
        std::string Nazwa_BrylaRobocza;
    public:
        /**
         * @brief Skaluje pobrany jako parametr punkt i zwraca go
         */
        const Wektor3D Skaluj(const Wektor3D &Wierzch) const;

        /**
         * Metooda klasy bryla zwracajaca nazwe bryly wzorcowej
         * 
         * @retval Nazwa bryly wzorcowej
         */
        std::string PobierzNazwe_Wzorcowa() const {return Nazwa_BrylaWzorcowa;}

        /**
         * Metooda klasy bryla zwracajaca nazwe bryly finalnej
         * 
         * @retval Nazwa bryly finalnej
         */
        std::string PobierzNazwe_Robocza() const {return Nazwa_BrylaRobocza;}

        /**
         * Ustawia skale bryly zgonie z podanymi parametrami.
         * 
         * @param[in] Skala_X - stopien skalowania w osi X
         * @param[in] Skala_Y - stopien skalowania w osi Y
         * @param[in] Skala_Z - stopien skalowania w osi Z
         */
        void UstawSkale(double Skala_X, double Skala_Y, double Skala_Z)
            {Skala[0] = Skala_X; Skala[1] = Skala_Y; Skala[2] = Skala_Z;}
};

#endif
