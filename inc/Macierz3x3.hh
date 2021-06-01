#ifndef MACIERZ3x3_HH
#define MACIERZ3x3_HH

/**
 *  @file
 *  @brief Modeluje pojecie Macierzy 3x3
 * 
 *  Zawiera specyfikacje szablonu macierzy na macierz wymiaru 3x3 oraz
 *  funkcje potrzebne do obslugi macierzy rotacji wsrod osi x, y i z.
 */

#include "Macierz.hh"

typedef Macierz<3> Macierz3x3;

/**
 * @brief Ustawia macierz rotacji dla osi X
 * 
 * Funkcja ustawia macierz rotacji dla osi X zgodnie z podanym
 * katem jako parametr.
 */
void UstawRotacjeX(Macierz3x3 &Mac, double Kat_rot);

/**
 * @brief Ustawia macierz rotacji dla osi Y
 * 
 * Funkcja ustawia macierz rotacji dla osi Y zgodnie z podanym
 * katem jako parametr.
 */
void UstawRotacjeY(Macierz3x3 &Mac, double Kat_rot);

/**
 * @brief Ustawia macierz rotacji dla osi Z
 * 
 * Funkcja ustawia macierz rotacji dla osi Z zgodnie z podanym
 * katem jako parametr.
 */
void UstawRotacjeZ(Macierz3x3 &Mac, double Kat_rot);



#endif