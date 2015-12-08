#include <map>
#include <string>
#include <iostream>

#include <hote.h>
#include <reseau.h>

reseau::reseau()
{
  hotes = std::map<std::string, hote*>();
}

void reseau::ajoutHote(std::string nom, hote* h)
{
  hotes[nom] = h;
}

hote* reseau::getHote(std::string nom)
{
  std::map<std::string, hote*>::iterator it;

  for(it=hotes.begin(); it!=hotes.end(); it++)
    if(nom == it->first)
      return it->second;

  return nullptr;
}

void reseau::afficherHotes()
{
  std::map<std::string, hote*>::iterator it;

  if(hotes.empty())
  {
    std::cout << "aucun hote" << std::endl;
    return;
  }

  std::cout << "Hotes: " << std::endl;

  for(it=hotes.begin(); it!=hotes.end(); it++)
  {
    std::cout << "* " << it->first << ", liens (voisins):" << std::endl;
    it->second->afficherVoisins();
    it->second->afficherTableRoutage();
    std::cout << std::endl;
  }
}

void reseau::reinitTableRoutage()
{
  if(hotes.empty())
    return;

  std::map<std::string, hote*>::iterator it;
  for(it=hotes.begin(); it!=hotes.end(); it++)
  {
    it->second->supprimerTableRoutage();
  }
}

bool reseau::routesVide()
{
  std::map<std::string, hote*>::iterator it;

  for(it=hotes.begin(); it!=hotes.end(); it++)
  {
    if(!it->second->routeVide())
      return false;
  }
  return true;

}

void reseau::diffusionTableRoutage()
{
  std::map<std::string, hote*>::iterator it;

  if(hotes.empty())
    return;

  for(it=hotes.begin(); it!=hotes.end(); it++)
  {
    it->second->transmettreMessageRIP();
  }
}

reseau reseau::creerReseauAleatoire(int nbr_hotes, int nbr_liaisons)
{
  reseau r;

  for(int i=1; i<=nbr_hotes; i++)
  {
    hote h(std::to_string(i)); // stoi ?

    r.ajoutHote(h.getNom(), &h);
  }

  // @todo les liaisons

  return r;
}
