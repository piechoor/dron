#include <iostream>

#include "Scena.hh"
#include "Menu.hh"

#include "Przeszkoda_gora.hh"
#include "Wektor3D.hh"
#include "lacze_do_gnuplota.hh"
#include <iostream>

int main()
{
  Scena LotDronow;
  if(!PrzetwarzajMenu(LotDronow)) {
    return -1;
    std::cout << "Blad dzialania programu" << std::endl;
  }

  // PzG::LaczeDoGNUPlota Lacze;
  // Gora *Gora1 = new Gora();
  // Gora1->UstawNazwe_Wzorcowy("bryly_wzorcowe/szescian.dat");
  // Gora1->UstawNazwe_Roboczy("dat/PlikRoboczy_Gora1.dat");
  // Gora1->UstawSkale(5,5,5);
  // Wektor3D Transl(2,2,-2); double kat = 45;
  // Gora1->ZmienPolozenie(Transl);
  // Gora1->ZmienOrientacje(kat);
  // Gora1->TworzGore();

  // Lacze.Inicjalizuj();
  // Lacze.DodajNazwePliku("dat/PlikRoboczy_Gora1.dat");
  // Lacze.ZmienTrybRys(PzG::TR_3D);
  // Lacze.UstawZakresX(-10, 10);
  // Lacze.UstawZakresY(-10, 10);
  // Lacze.UstawZakresZ(-10, 10);
  // Lacze.UstawRotacjeXZ(64,65);


  // Lacze.Rysuj();
  // std::cin.ignore(1000,'\n');

  // delete Gora1;
  // Lacze.Rysuj();
  // std::cin.ignore(1000,'\n');

  return 0;
}
