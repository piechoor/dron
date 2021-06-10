#ifndef OBIEKTSCENY_HH
#define OBIEKTSCENY_HH

#include <memory>

#include "BrylaGeometryczna.hh"

/**
 * @file ObiektSceny.hh
 * 
 * Plik zawiera definicje klasy reprezentujacej
 * bryle geometryczna znajdujaca sie na scenie.
 */

/**
 * @brief Klasa definiuje pojecie obiektu sceny.
 * 
 * Klasa definiuje podstawowe pojecie obiektu sceny, czyli
 * specyficznej bryly, ktora znajduje sie na scenie
 */
class ObiektSceny : public Bryla {

    public:
        /**
         * Metoda sprawdzajaca czy dron podany jako parametr jej wywolania
         * koliduje z bryla, ktora jest obiektem.
         */
        virtual bool SprKolizje(const Wektor3D &Polozenie, double Promien);
        
};

#endif