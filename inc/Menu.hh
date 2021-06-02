#ifndef MENU_HH
#define MENU_HH

#include <iostream>

#include "Scena.hh"
#include "Wektor3D.hh"

#define BEZPIECZNA_WYSOKOSC 80  // Wysokosc na jaka wznosi sie dron
                                // podczas lotu

/**
 * @file
 * 
 * Plik zawiera funkcje niezbedne do obslugi
 * programu realizujacego przelot dronow.
 */

/**
 * @brief Glowna funckja realizujaca przetwarzanie menu do obslugi drona
 */
bool PrzetwarzajMenu(Scena &Sc);

/**
 * @brief Funkcja pomocnicza wyswietlajaca opcje menu
 */
void WyswietlOpcje(Scena &Sc);

/**
 * @brief Funkcja pozwalajaca na wybor konkretnego drona 
 */
void PrzetwWyborDrona(Scena &Sc);

/**
 * @brief Funkcja realizujaca przelot aktywnego drona o zadane parametry
 */
bool ZadajPrzelot(Scena &Sc, double Kierunek, double Dlugosc);

bool DodajElemPowierz(Scena &Sc);

void UsunElemPowierz(Scena &Sc);


#endif
