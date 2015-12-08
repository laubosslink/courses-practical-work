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

#include <utility>
#include <iostream>
#include <string>

int main()
{
  std::pair<int, int> p1;
  std::pair<int, int> p2;


  /* @todo utiliser <int, int> partout ? */
  std::pair<int, float> p1f;
  std::pair<int, float> p2f;

  std::pair<std::string, int> p1s;
  std::pair<std::string, int> p2s;

  p1 = std::make_pair(1, 10);
  p2 = std::make_pair(2, 1);

  std::cout << "(1,10) < (2,1) : " << ((p1<p2) ? "True" : "False") << std::endl;

  p1 = std::make_pair(0, 0);
  p2 = std::make_pair(0, 10);

  std::cout << "(0,0) < (0,10) : " << ((p1<p2) ? "True" : "False") << std::endl;

  p1 = std::make_pair(0, 0);
  p2 = std::make_pair(0, 0);

  std::cout << "(0,0) < (0,0) : " << ((p1<p2) ? "True" : "False") << std::endl;

  p1f = std::make_pair(1, 8.5);
  p2f = std::make_pair(1, 9.0);

  std::cout << "(1,8.5) < (1,9) : " << ((p1f<p2f) ? "True" : "False") << std::endl;


  p1 = std::make_pair(0, 0);
  p2 = std::make_pair(0, 1);

  std::cout << "(0,0) != (0,1) : " << ((p1!=p2) ? "True" : "False") << std::endl;


  p1 = std::make_pair(0, 5);
  p2 = std::make_pair(0, 5);

  std::cout << "(0,5) > (0,5) : " << ((p1>p2) ? "True" : "False") << std::endl;


  p1 = std::make_pair(0, 5);
  p2 = std::make_pair(0, 5);

  std::cout << "(0,5) < (0,5) : " << ((p1<p2) ? "True" : "False") << std::endl;


  p1 = std::make_pair(0, 5);
  p2 = std::make_pair(0, 5);

  std::cout << "(0,5) == (0,5) : " << ((p1==p2) ? "True" : "False") << std::endl;


  p1s = std::make_pair("pomme", 10);
  p2s = std::make_pair("tomate", 40);

  std::cout << "(pomme,10) > (tomage,40) : " << ((p1>p2) ? "True" : "False") << std::endl;

  return 0;
}
