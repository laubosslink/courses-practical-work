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
#include <vector>
#include <cstdlib>

int main()
{
  srand(time(NULL));

  std::vector<int> t;
  std::vector<int>::iterator it;

  int a, capacite=t.capacity();

  for(int i=0; i<3000; i++)
  {
    a = rand()%50;
    t.push_back(a);

    if(t.capacity() != capacite)
    {
      capacite=t.capacity();
      std::cout << "Nouvelle capacite de " << capacite << " lors de l'ajout numero " << i << std::endl;
    }
  }

  // On déduit que la capacite double lorsqu'on ajoute le dernier element de sa capacite courrante

  return 0;
}
