#include <stdlib.h>
#include <iostream>
#include <hote.h>

int main()
{
  bool tests = true;

  /* Reseau:
   *   4
   * 2  \
   *  \  3
   *   1/ \
   *   ----5
   */

  hote m1("1");
  hote m2("2");
  hote m3("3");
  hote m4("4");
  hote m5("5");

  m1.ajoutVoisin(&m2);
  m1.ajoutVoisin(&m3);
  m1.ajoutVoisin(&m5);

  m2.ajoutVoisin(&m1);

  m3.ajoutVoisin(&m1);
  m3.ajoutVoisin(&m4);
  m3.ajoutVoisin(&m5);

  m4.ajoutVoisin(&m3);

  m5.ajoutVoisin(&m3);
  m5.ajoutVoisin(&m1);


  tests = tests && m1.routePresente(m1.getNom()) && m1.coutRoute(m1.getNom()) == 0;
  tests = tests && m1.routePresente(m2.getNom()) && m1.coutRoute(m2.getNom()) == 1;
  tests = tests && m1.routePresente(m4.getNom()) && m1.coutRoute(m4.getNom()) == 2;

  tests = tests && m4.routePresente(m5.getNom()) && m4.coutRoute(m5.getNom()) == 2;
  tests = tests && m4.routePresente(m2.getNom()) && m4.coutRoute(m2.getNom()) == 3;

  tests = tests && m2.routePresente(m3.getNom()) && m2.coutRoute(m3.getNom()) == 2;
  tests = tests && m2.routePresente(m4.getNom()) && m2.coutRoute(m4.getNom()) == 3;
  tests = tests && m2.routePresente(m5.getNom()) && m2.coutRoute(m5.getNom()) == 2;

#if DEBUG_AFFICHE == 1
  m2.recevoirMessageIP(&m4, "message m2 vers m4");
  m2.recevoirMessageIP(&m1, "message m2 vers m1");
  m2.recevoirMessageIP(&m2, "message m2 vers lui meme");

  m1.afficherTableRoutage();
  m2.afficherTableRoutage();
  m3.afficherTableRoutage();
  m4.afficherTableRoutage();
  m5.afficherTableRoutage();
#endif

  std::cout << std::endl << "Nombre de messages RIP : " << hote::nbr_msg_rip << std::endl;

	if(tests)
		std::cout << std::endl << "test_hote_home: \033[32mOK\033[0m\n" << std::endl;
	else
		std::cout << std::endl <<  "test_hote_home: \033[31mproblemes durant les tests\033[0m\n" << std::endl;

  return 0;
}
