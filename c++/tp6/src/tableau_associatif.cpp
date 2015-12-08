#include <iostream>
#include <utility>
#include <map>

#include <iomanip>

typedef std::map<std::pair<int, int>, double> TA;

class Tableau : public TA
{
public:
  Tableau() : TA() {}

  double operator()(int ligne, int colonne)
  {
    std::pair<int, int> index = std::make_pair(ligne, colonne);

    TA::iterator it = find(index);

    if(it == end() && it->first != index)
      return 0;

    return (*this)[index];
  }

  void setValeur(int ligne, int colonne, double valeur)
  {
    std::pair<int, int> index = std::make_pair(ligne, colonne);
    (*this)[index] = valeur;
  }

  friend std::ostream & operator<<(std::ostream & out, TA t)
  {
    TA::iterator it;
    std::pair<int, int> index;

    /** @todo pas compris... determiner plus grande valeur colonne ?
     * une fois determiner on en fait quoi ?
     */
    

    /** left() et stw() ? */

    for(it=t.begin(); it!=t.end(); it++)
    {
      index = it->first;
      out << "pair[ " << index.first << "," << index.second << " ] = " << std::setprecision(2) << it->second << std::endl;
    }

    return out;
  }
};

int main()
{

  std::pair<int, int> p = std::make_pair(2,1);

  Tableau t;

  /** données qui ne devrait pas être crée */
  t(2,2);

  /** données qui sont crées */
  t[p] = 1.0/3;
  t.setValeur(2, 3, 1.0/9);

  /** vérification via l'affichage */
  std::cout << t;

  return 0;
}
