/**
* ENSICAEN
* 6 Boulevard Marechal Juin
* F-14050 Caen Cedex
*
* This file is owned by ENSICAEN students.
* No portion of this document may be reproduced, copied
* or revised without written premission of the authors
*/

/**
* @author ELHIMDI Yasmine <yasmine.elhimdi@ecole.ensicaen.fr>
* @author PARMENTIER Laurent <laurent.parmentier@ecole.ensicaen.fr, laubosslink@society-lbl.com>
* @date 11-12-2014
*/

#include <iostream>
#include <fstream>
#include <set>


int main(int argc, char* argv[])
{
  char c_courant;

  std::ifstream fichier(argv[1], std::ios::in);

  std::set<char> t;
  std::set<char>::iterator it;

  if(fichier)
  {

    while(!fichier.eof()) {
      fichier.get(c_courant); // <=> fichier >> c_courant;
      t.insert(c_courant);
    }

    fichier.close();
  } else
  {
    std::cerr << "Impossible d'ouvrir le fichier" << std::endl;
    return 1;
  }

  // nombre de caractere différent
  std::cout << "il y a " << t.size() << " caracteres différents" << std::endl;

  // affichage caractere présent dans le fichier
  for(it=t.begin(); it!=t.end(); it++)
    std::cout << *it;

  return 0;
}
