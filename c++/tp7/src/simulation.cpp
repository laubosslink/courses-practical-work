#include <iostream>
#include <fstream>
#include <string>

#include <hote.h>
#include <reseau.h>

int main(int argc, char* argv[])
{
  if(argc != 5)
  {
    std::cout << "Vous devez passer 4 arguments : ./simulation reseau.txt source destination \"mon message\"" << std::endl;
    return 1;
  }

  char* file = argv[1];
  char* src  = argv[2];
  char* dest = argv[3];
  char* mess = argv[4];

  char c_courant;

  std::ifstream fichier(file, std::ios::in);

  // 1 construire le reseau
  reseau* r;
  std::string s1, s2;
  hote* h1;
  hote* h2;

  if(!fichier)
  {
    std::cout << "Impossible d'ouvrir le fichier" << std::endl;
    return 4;
  }

  r = new reseau();

  while(!fichier.eof())
  {
    fichier >> s1 >> s2;

    if(r->getHote(s1) == nullptr)
    {
      h1 = new hote(s1);
      r->ajoutHote(h1->getNom(), h1);
    } else
    {
      h1 = r->getHote(s1);
    }

    if(r->getHote(s2) == nullptr)
    {
      h2 = new hote(s2);
      r->ajoutHote(h2->getNom(), h2);
    } else
    {
      h2 = r->getHote(s2);
    }

    h1->ajoutVoisin(h2);
    h2->ajoutVoisin(h1);
  }

  fichier.close();

  int nRIP;

  // 2 afficher les tables de routages de tout les hotes
  r->afficherHotes();

  nRIP = hote::nbr_msg_rip;

  // 3 diffusion des tables de routage
  r->diffusionTableRoutage();

  // 4 afficher de nouveau les tables de routages de tous les hotes
  r->afficherHotes();

  nRIP = hote::nbr_msg_rip - nRIP;

  // 5 afficher le nombre de RIP echange (durant l'etape 3)
  std::cout << "Nombre de message rip echange lors de la diffusion : " << nRIP << std::endl;

  // 6 envoyer a l'hote dest le message IP contenant la chaine mess a destination de l'hote dest
  if(!r->getHote(src))
  {
    std::cout << "Source innexistante" << std:: endl;
    return 2;
  }

  if(!(r->getHote(dest)))
  {
    std::cout << "Destination innexistante" << std:: endl;
    return 3;
  }

  r->getHote(src)->recevoirMessageIP(r->getHote(dest), mess);

  return 0;
}
