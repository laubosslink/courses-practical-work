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
#include <map>
#include <string>

int main()
{

  std::map<std::string, int> ages;
  std::map<std::string, int>::iterator it;

  ages["Laurent"] = 22;
  ages["Yasmine"] = 21;

  for(it=ages.begin(); it!=ages.end(); it++)
    std::cout << "ages[" << it->first << "] = " << it->second << std::endl;

  return 0;
}
