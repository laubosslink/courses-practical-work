#include <string>
#include <map>
#include <utility>
#include <ostream>
#include <iostream>

#include <hote.h>

#define INFINI 16

int hote::nbr_msg_rip = 0;

hote::hote(std::string nom)
{
  hote::nom = nom;
  voisins = std::map<std::string, hote*>();
  routage = std::map<std::string, std::pair<std::string, int>>();
  routage[nom] = std::make_pair<std::string, int>("-", 0);
}

std::string hote::getNom()
{
  return nom;
}

void hote::ajoutVoisin(hote* h)
{
  voisins[h->getNom()] = h;
  routage[h->getNom()] = std::make_pair(nom, 1);
  transmettreMessageRIP();
}

void hote::retirerVoisin(hote* h)
{
  voisins.erase(h->getNom());
  routage.erase(h->getNom());
  transmettreMessageRIP();
}

bool hote::voisinPresent(std::string h)
{
  if(voisins.empty())
    return false;

  return (voisins.find(h) != voisins.end());
}

bool hote::voisinPresent(hote* h)
{
  return voisinPresent(h->getNom());
}

hote* hote::getVoisin(std::string nom)
{
  std::map<std::string, hote*>::iterator it;

  for(it=voisins.begin(); it!=voisins.end(); it++)
    if(nom == it->first)
      return it->second;

  return nullptr;
}

std::string hote::getPasseur(std::string destination)
{
  if(routage.empty())
    return "table routage vide";

  return routage.find(destination)->second.first;
}

void hote::afficherVoisins()
{
  std::map<std::string, hote*>::iterator it;

  if(voisins.empty())
  {
    std::cout << nom << ": pas de voisins" << std::endl;
    return;
  }

  for(it=voisins.begin(); it!=voisins.end(); it++)
    std::cout << "\t- " << it->first << std::endl;

}

void hote::afficherTableRoutage()
{
  std::map<std::string, std::pair<std::string, int>>::iterator it;

  if(routage.empty())
  {
    std::cout << nom << ": table de routage vide" << std::endl;
    return;
  }

  std::cout << "Table de routage de " << nom << ":" << std::endl;

  for(it=routage.begin(); it!=routage.end(); it++)
    std::cout << "- " << it->first << " (" << it->second.first << ", " << it->second.second << ") " << std::endl;

}

void hote::supprimerTableRoutage()
{
  routage.clear();
}

bool hote::routeVide()
{
  return routage.empty();
}

bool hote::routePresente(std::string h)
{
  if(routage.empty())
    return false;

  return (routage.find(h) != routage.end());
}

int hote::coutRoute(std::string h)
{
  if(!routePresente(h))
    return -1;

  return routage.find(h)->second.second;
}

void hote::receptionMessageRIP(hote* expediteur, std::string destinataire, int cout)
{
  // otpimisation: Si c'est un voisin, on a deja le cout minimum (split horizon ?).
  if(voisinPresent(destinataire))
    return;

  hote::nbr_msg_rip++;

  cout = (cout+1 < INFINI) ? cout+1 : INFINI;

  if(!routePresente(destinataire) && cout != INFINI)
  {
    routage[destinataire] = std::make_pair(expediteur->getNom(), cout);
    transmettreMessageRIP(destinataire);
  } else if(routePresente(destinataire) && coutRoute(destinataire) > cout)
  {
    routage[destinataire] = std::make_pair(expediteur->getNom(), cout);
    transmettreMessageRIP(destinataire);
  } /* else if(routePresente(destinataire) && routage[destinataire].first == expediteur->getNom()) // cas particulie : perte de connection d'une machine. Presque inutile ici.
  {
    routage[destinataire].second = cout;
    transmettreMessageRIP(destinataire);
  } */
}

void hote::transmettreMessageRIP()
{
  std::map<std::string, hote*>::iterator itv;
  std::map<std::string, std::pair<std::string, int>>::iterator itr;

  if(voisins.empty())
    return;

  for(itv=voisins.begin(); itv!=voisins.end(); itv++)
    for(itr=routage.begin(); itr!=routage.end(); itr++)
      itv->second->receptionMessageRIP(this, itr->first, itr->second.second);
}

void hote::transmettreMessageRIP(std::string h)
{
  std::map<std::string, hote*>::iterator itv;

  if(voisins.empty())
    return;

  // transmettre par message RIP la table de routage de l'hote passé en parametre
  // à chaque voisin

  int cout = coutRoute(h);

  for(itv=voisins.begin(); itv!=voisins.end(); itv++)
    itv->second->receptionMessageRIP(this, h, cout);
}


void hote::recevoirMessageIP(hote* dest, std::string msg)
{
  int cout = coutRoute(dest->getNom());

  // destination arrive
  if(cout == 0)
  {
    std::cout << " -> " << nom << " -> message: " << msg << std::endl;
  } else if(cout == 1) // destination voisin
  {
    std::cout << nom;
    getVoisin(dest->getNom())->recevoirMessageIP(dest, msg);
  } else if(cout >= INFINI || cout == -1) // destination trop loin
  {
    std::cout << "Pas de route connue" << std::endl;
  } else // transmisison
  {
    if(!routePresente(dest->getNom()))
    {
      std::cout << "Pas de route connue" << std::endl;
      return;
    }

    std::string passeur = getPasseur(dest->getNom());

    std::cout << nom << " -> ";

    getVoisin(passeur)->recevoirMessageIP(dest, msg);
  }
}
