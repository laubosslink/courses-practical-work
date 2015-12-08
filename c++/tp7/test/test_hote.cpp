#include <stdlib.h>
#include <iostream>
#include <hote.h>

int main()
{
  bool tests = true;

  hote m1("pc-lbl");
  hote m2("po-home");
  hote m3("ordi-lolo");

  /**
   * Obtention du nom
   */

#if DEBUG_AFFICHE == 1
  std::cout << "Nom de m1: " << m1.getNom() << std::endl;
  std::cout << "Nom de m2: " << m2.getNom() << std::endl;
  std::cout << "Nom de m3: " << m3.getNom() << std::endl;
  std::cout << std::endl;
#endif

  tests = tests && m1.getNom() == "pc-lbl";
  tests = tests && m2.getNom() == "po-home";
  tests = tests && m3.getNom() == "ordi-lolo";

  /**
   * Ajout d'un hote
   */

#if DEBUG_AFFICHE == 1
  std::cout << "Ajout du voisin m2 a m1" << std::endl;
#endif

  m1.ajoutVoisin(&m2);

  tests = tests && m1.voisinPresent(&m2);
  tests = tests && m1.routePresente(m2.getNom());

#if DEBUG_AFFICHE == 1
  std::cout << "Voisins de " << m1.getNom() << ":" << std::endl;
  m1.afficherVoisins();
  std::cout << std::endl;
#endif

  /**
   * retire un hote
   */

#if DEBUG_AFFICHE == 1
  std::cout << "Suppression du voisin m2 a m1" << std::endl;
#endif

  m1.retirerVoisin(&m2);

  tests = tests && !m1.voisinPresent(&m2);

#if DEBUG_AFFICHE == 1
  std::cout << "Voisins de " << m1.getNom() << ":" << std::endl;
  m1.afficherVoisins();
  std::cout << std::endl;
#endif

#if DEBUG_AFFICHE == 1
  std::cout << "Ajout de m2 et m3 à m1" << std::endl;
#endif

  /**
   * Affichage des voisins
   */
  m1.ajoutVoisin(&m2);
  m1.ajoutVoisin(&m3);


#if DEBUG_AFFICHE == 1
  std::cout << "Voisins de " << m1.getNom() << ":" << std::endl;
  m1.afficherVoisins();
  std::cout << std::endl;
#endif

  /**
   * Affichage de la table de routage
   */

#if DEBUG_AFFICHE == 1
  m1.afficherTableRoutage();
  std::cout << std::endl;
#endif

  /**
   * Verification des données dans la table de routage
   */
  tests = tests && m1.coutRoute(m1.getNom()) == 0;
  tests = tests && m1.routePresente(m2.getNom());
  tests = tests && m1.routePresente(m3.getNom());
  tests = tests && m1.coutRoute(m2.getNom()) == 1;
  tests = tests && m1.coutRoute(m3.getNom()) == 1;

  std::cout << "Nombre de messages RIP : " << hote::nbr_msg_rip << std::endl;

	if(tests)
		std::cout << std::endl << "test_hote: \033[32mOK\033[0m\n" << std::endl;
	else
		std::cout << std::endl <<  "test_hote: \033[31mproblemes durant les tests\033[0m\n" << std::endl;

  return 0;
}
