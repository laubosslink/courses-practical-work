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
#include <set>
#include <cstdlib>

int main()
{
  srand(time(NULL));

  std::set<int> t;
  std::set<int>::iterator it;

  int a;

  for(int i=0; i<20; i++)
  {
    a = rand()%50;
    t.insert(a);
  }

  // pourquoi il faut utiliser it!=t.end au lieu de it<t.end ?
  for(it=t.begin(); it!=t.end(); it++)
    std::cout << *it << std::endl;

  return 0;
}
