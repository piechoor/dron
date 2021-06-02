#include <iostream>

#include "Scena.hh"
#include "Menu.hh"

#include "lacze_do_gnuplota.hh"

int main()
{
  Scena LotDronow;
  if(!PrzetwarzajMenu(LotDronow)) {
    return -1;
    std::cout << "Blad dzialania programu" << std::endl;
  }

  return 0;
}
