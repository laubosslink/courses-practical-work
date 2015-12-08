#ifndef INCLUDED_H_HOTE
#define INCLUDED_H_HOTE

#include <string>
#include <map>
#include <utility>
#include <ostream>

class hote
{
private:
  std::string nom;
  std::map<std::string, hote*> voisins;
  std::map<std::string, std::pair<std::string, int>> routage;
public:
  static int nbr_msg_rip;

  hote(std::string);

  std::string getNom();

  void ajoutVoisin(hote*);

  void retirerVoisin(hote*);

  bool voisinPresent(std::string);
  bool voisinPresent(hote*);

  hote* getVoisin(std::string);
  std::string getPasseur(std::string);

  void afficherVoisins();

  void afficherTableRoutage();

  void supprimerTableRoutage();

  bool routeVide();

  bool routePresente(std::string);

  int coutRoute(std::string);

  void receptionMessageRIP(hote*, std::string, int);

  void transmettreMessageRIP();

  void transmettreMessageRIP(std::string);

  void recevoirMessageIP(hote*, std::string);
};

#endif
