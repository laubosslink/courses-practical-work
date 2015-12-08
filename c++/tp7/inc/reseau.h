#ifndef INCLUDED_H_RESEAU
#define INCLUDED_H_RESEAU

#include <string>
#include <map>

#include <hote.h>

class reseau
{
private:
  std::map<std::string, hote*> hotes;
public:
  reseau();

  void ajoutHote(std::string, hote*);

  hote* getHote(std::string);

  void afficherHotes();

  void reinitTableRoutage();

  bool routesVide();

  void diffusionTableRoutage();

  static reseau creerReseauAleatoire(int, int);
};

#endif
