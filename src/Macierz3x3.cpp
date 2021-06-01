#include "Macierz3x3.hh"

/**
 * Funkcja ustawia macierz rotacji dla osi X zgodnie z
 * katem podanym jako parametr.
 * 
 * @param Mac - Macierz, ktora zostanie ustawiona jako macierz rotacji
 * @param Kat_rot - Kat podany w stopniach, potrzebny do ustawienia macierzy
 * 
 * @pre Kat podany w stopniach
 * @post Macierz rotacji stworzona wedlug zadanego kata
 */
void UstawRotacjeX(Macierz3x3 &Mac, double Kat_rot) {
    Kat_rot *= M_PI / 180; // Zamiana stopni na radiany 
    Mac.UstawWar(1,1,cos(Kat_rot)); Mac.UstawWar(1,2,-sin(Kat_rot));
    Mac.UstawWar(2,1,sin(Kat_rot)); Mac.UstawWar(2,2,cos(Kat_rot));
}

/**
 * Funkcja ustawia macierz rotacji dla osi Y zgodnie z
 * katem podanym jako parametr.
 * 
 * @param Mac - Macierz, ktora zostanie ustawiona jako macierz rotacji
 * @param Kat_rot - Kat podany w stopniach, potrzebny do ustawienia macierzy 
 * 
 * @pre Kat podany w stopniach
 * @post Macierz rotacji stworzona wedlug zadanego kata
 */
void UstawRotacjeY(Macierz3x3 &Mac, double Kat_rot) {
    Kat_rot *= M_PI / 180; // Zamiana stopni na radiany 
    Mac.UstawWar(0,0,cos(Kat_rot)); Mac.UstawWar(0,2,sin(Kat_rot));
    Mac.UstawWar(2,0,-sin(Kat_rot)); Mac.UstawWar(2,2,cos(Kat_rot));
}

/**
 * Funkcja ustawia macierz rotacji dla osi Z zgodnie z
 * katem podanym jako parametr.
 * 
 * @param Mac - Macierz, ktora zostanie ustawiona jako macierz rotacji
 * @param Kat_rot - Kat podany w stopniach, potrzebny do ustawienia macierzy
 * 
 * @pre Kat podany w stopniach
 * @post Macierz rotacji stworzona wedlug zadanego kata
 */
void UstawRotacjeZ(Macierz3x3 &Mac, double Kat_rot) {
    Kat_rot *= M_PI / 180; // Zamiana stopni na radiany 
    Mac.UstawWar(0,0,cos(Kat_rot)); Mac.UstawWar(0,1,-sin(Kat_rot));
    Mac.UstawWar(1,0,sin(Kat_rot)); Mac.UstawWar(1,1,cos(Kat_rot));
}