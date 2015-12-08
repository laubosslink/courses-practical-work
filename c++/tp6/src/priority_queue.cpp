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
#include <queue>
#include <vector>

template <typename T>
std::priority_queue<T, std::vector<T>, std::greater<T>> trier(std::vector<T> v)
{
  std::priority_queue<int, std::vector<T>, std::greater<T>> q; // ne pas écrire q()
  std::vector<int>::iterator it;

  for(it=v.begin(); it<v.end(); it++)
    q.push(*it);

  return q;
}

int main()
{
  std::vector<int> v;
  v.push_back(1);
  v.push_back(15);
  v.push_back(16);
  v.push_back(3);
  v.push_back(9);
  v.push_back(25);
  v.push_back(35);
  v.push_back(98);
  v.push_back(101);
  v.push_back(56);
  v.push_back(0);
  v.push_back(-5);

  std::priority_queue<int, std::vector<int>, std::greater<int>> qt = trier<int>(v);

  while(!qt.empty())
  {
    std::cout << qt.top() << " < ";
    qt.pop();
  }

  return 0;
}
