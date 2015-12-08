#include <stdlib.h>
#include <iostream>
#include <hote.h>
#include <reseau.h>

int main()
{
  bool tests = true;

  hote m1("1");
  hote m2("2");
  hote m3("3");
  hote m4("4");
  hote m5("5");

  reseau r;

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

  r.ajoutHote(m1.getNom(), &m1);
  r.ajoutHote(m2.getNom(), &m2);
  r.ajoutHote(m3.getNom(), &m3);
  r.ajoutHote(m4.getNom(), &m4);
  r.ajoutHote(m5.getNom(), &m5);


#if DEBUG_AFFICHE == 1
  r.afficherHotes();
  r.diffusionTableRoutage();
#endif

  r.reinitTableRoutage();

  tests = tests && r.routesVide();

#if DEBUG_AFFICHE == 1
  std::cout << "Tables de routage après réinitialisation" << std::endl;

  r.getHote(m1.getNom())->afficherTableRoutage();
  r.getHote(m2.getNom())->afficherTableRoutage();
  r.getHote(m3.getNom())->afficherTableRoutage();
  r.getHote(m4.getNom())->afficherTableRoutage();
  r.getHote(m5.getNom())->afficherTableRoutage();
#endif

  std::cout << std::endl << "Nombre de messages RIP : " << hote::nbr_msg_rip << std::endl;

  if(tests)
    std::cout << std::endl << "test_reseau: \033[32mOK\033[0m\n" << std::endl;
  else
    std::cout << std::endl <<  "test_reseau: \033[31mproblemes durant les tests\033[0m\n" << std::endl;




  return 0;
}
