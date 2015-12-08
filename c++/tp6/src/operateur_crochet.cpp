#include <iostream>
#include <map>

int main()
{
  std::map<int, double> tab;
  tab[10] = 5.0;
  tab[5] = 2.5;

  if(tab[0] == 0)
  {
    std::cout << tab[0] << std::endl;
    std::cout << tab.size() << std::endl;
  }
}
