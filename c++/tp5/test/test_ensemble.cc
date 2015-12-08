#include <stdlib.h>
#include <iostream>

#include <Ensemble.h>
#include <EnsembleImage.h>

int main()
{
	bool tests = true;

	Ensemble<int>* e = new Ensemble<int>(5);

#if DEBUG_AFFICHE == 1
  std::cout << "Ensemble : " << *e << std::endl;
#endif

	/**
	 * Test du singleton
	 */

	Ensemble<double> ensemble_singleton = singleton<double>(5.5);
	tests = tests && ensemble_singleton.contient(5.5);

#if DEBUG_AFFICHE == 1
	std::cout << "Singleton {5.5} <=> " << ensemble_singleton << std::endl;
#endif

	/**
	 * Test de l'ensemble vide
	 */
	Ensemble<double> ensemble_vide = ensembleVide<double>();
	tests = tests && ensemble_vide.estVide() == true;

#if DEBUG_AFFICHE == 1
	std::cout << "ensembleVide() {} <=> " << ensemble_vide << std::endl;
#endif

	/**
	 * Test de l'ajout
	 */

	Ensemble<double> ensemble_a = ensembleVide<double>();
	Ensemble<double> ensemble_b = ensembleVide<double>();
	Ensemble<double> ensemble_c = ensembleVide<double>();

	ensemble_a.ajoute(1.1);
	ensemble_a.ajoute(2.1);
	ensemble_a.ajoute(3.4);

	ensemble_b.ajoute(1.1);
	ensemble_b.ajoute(2.1);
	ensemble_b.ajoute(3.4);

	ensemble_c.ajoute(3.4);

	tests = tests && ensemble_a.contient(1.1);
	tests = tests && ensemble_a.contient(2.1);
	tests = tests && ensemble_a.contient(3.4);

	/**
	 * Test de l'inclusion
	 */
	//Ensemble<double>& ensemble_a_ref = ensemble_a;
	tests = tests && ensemble_c.estInclusDans(ensemble_a);

#if DEBUG_AFFICHE == 1
	std::cout << "Ensemble a {1.1, 2.1, 3.4} <=> " << ensemble_a << std::endl;
#endif


	/**
	 * Test de l'ensemble contient un autre
	 */

	tests = tests && (egale(ensemble_a, ensemble_b) == true);
	tests = tests && (egale(ensemble_a, ensemble_c) == false);

	/**
	 * Test de l'ajout d'un ensemble dans un ensemble
	 */
	Ensemble<double> ensemble_e = singleton<double>(5.0);
	Ensemble<double> ensemble_d = ensembleVide<double>();
	ensemble_d.ajoute(6.4);

	ensemble_d.ajouteDans(ensemble_e);

	tests = tests && ensemble_e.contient(6.4);
	tests = tests && ensemble_e.contient(5.0);


#if DEBUG_AFFICHE == 1
	std::cout << "Ensemble b {1.1, 2.1, 3.4} <=> " << ensemble_b << std::endl;
	std::cout << "Ensemble c {3.4} <=> " << ensemble_c << std::endl;

	std::cout << "Ensemble d {6.4} <=> " << ensemble_e << std::endl;
	std::cout << "Ensemble e (ajout de d dans e) {5.0, 6.4} <=> " << ensemble_e << std::endl;
#endif

	/**
	 * Test de l'opérateur ==
	 */
	tests = tests && (ensemble_a == ensemble_b);


	/**
	 * Test de la reunion
	 */

	Ensemble<double> ensemble_f = ensembleVide<double>();
	ensemble_f.ajoute(0.5);

	Ensemble<double> ensemble_reunie = reunion<double>(ensemble_a, ensemble_f);

	tests = tests && ensemble_reunie.contient(0.5);
	tests = tests && ensemble_reunie.contient(1.1);
	tests = tests && ensemble_reunie.contient(2.1);
	tests = tests && ensemble_reunie.contient(3.4);

#if DEBUG_AFFICHE == 1
	std::cout << "Ensemble Reunion de l'ensemble_a et ensemble f {0.5, 1.1, 2.1, 3.4} <=> " << ensemble_reunie << std::endl;
#endif

	/**
	 * Test de l'opérateur + et |
	 */
	ensemble_reunie = ensemble_a + ensemble_f;
	tests = tests && ensemble_reunie.contient(0.5);
	tests = tests && ensemble_reunie.contient(1.1);
	tests = tests && ensemble_reunie.contient(2.1);
	tests = tests && ensemble_reunie.contient(3.4);

	ensemble_reunie = ensemble_a | ensemble_f;
	tests = tests && ensemble_reunie.contient(0.5);
	tests = tests && ensemble_reunie.contient(1.1);
	tests = tests && ensemble_reunie.contient(2.1);
	tests = tests && ensemble_reunie.contient(3.4);


	/**
	 * Test de retire
	 */
	 Ensemble<double> ensemble_g = ensembleVide<double>();
	 ensemble_g.ajoute(0.5);
	 ensemble_g.ajoute(1.5);
	 ensemble_g.ajoute(2.5);
	 ensemble_g.ajoute(3.5);

	 ensemble_g.retire(2.5);

	 tests = tests && !ensemble_g.contient(2.5);

	/**
	 * Test de retireDe
	 */
	Ensemble<double> ensemble_h = ensembleVide<double>();
	ensemble_h.ajoute(1.5);
	ensemble_h.ajoute(3.5);

	ensemble_h.retireDe(ensemble_g);

	tests = tests && !ensemble_g.contient(1.5);
	tests = tests && !ensemble_g.contient(3.5);
	tests = tests && ensemble_g.contient(0.5);

	/**
	 * Test de la difference et difference symetrique
	 */

	Ensemble<double> ensemble_i = ensembleVide<double>();
	ensemble_i.ajoute(1.1);
	ensemble_i.ajoute(2.1);
	ensemble_i.ajoute(0.5);

	Ensemble<double> ensemble_difference = difference<double>(ensemble_a, ensemble_i);
	Ensemble<double> ensemble_diff_symetrique = diffSymetrique<double>(ensemble_a, ensemble_i);

	tests = tests && !ensemble_difference.contient(1.1);
	tests = tests && !ensemble_difference.contient(2.1);
	tests = tests && ensemble_difference.contient(3.4);

	tests = tests && !ensemble_diff_symetrique.contient(1.1);
	tests = tests && !ensemble_diff_symetrique.contient(2.1);
	tests = tests && ensemble_diff_symetrique.contient(3.4);
	tests = tests && ensemble_diff_symetrique.contient(0.5);

	/**
	 * Test de l'intersection
	 */

	Ensemble<double> ensemble_j = ensembleVide<double>();
	ensemble_j.ajoute(1.1);
	ensemble_j.ajoute(2.1);
	ensemble_j.ajoute(0.5);

	ensemble_i = ensembleVide<double>();
	ensemble_i.ajoute(1.1);
	ensemble_i.ajoute(2.1);
	ensemble_i.ajoute(0.5);


	Ensemble<double> ensemble_intersection = intersection<double>(ensemble_a, ensemble_j);

	tests = tests && ensemble_intersection.contient(1.1);
	tests = tests && ensemble_intersection.contient(2.1);
	tests = tests && !ensemble_intersection.contient(0.5);

	ensemble_intersection = ensemble_a & ensemble_i;

	tests = tests && ensemble_intersection.contient(1.1);
	tests = tests && ensemble_intersection.contient(2.1);
	tests = tests && !ensemble_intersection.contient(0.5);

	/* Partie 3, test d'une fonction affine */

	Affine<double> affine(2, 3);
  Ensemble<double> ie = imageEnsemble<double>(affine, ensemble_intersection);

	tests = tests && ie.contient(5.2);
	tests = tests && !ie.contient(5.1);

	if(tests)
		std::cout << "essai_ensemble: \033[32mOK\033[0m\n" << std::endl;
	else
		std::cout << "essai_ensemble: \033[31mproblemes durant les tests\033[0m\n" << std::endl;

	exit(0);
}
