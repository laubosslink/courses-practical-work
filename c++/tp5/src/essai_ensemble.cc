#include <ios>                             // 
#include <iostream>                        //  Fichier essai_ensemble.cc
#include <iomanip>                         //
#include <Ensemble.h>
using namespace std;

int main(int argc, char * argv[]){
  Ensemble<double> e = ensembleVide<double>();
  Ensemble<double> f = ensembleVide<double>();
  Ensemble<double> g = ensembleVide<double>();
  for (int i = 1; i <= 10 ; i++) e.ajoute(i);
  for (int i = 5; i <= 20 ; i++) f.ajoute(i);
  for (int i = 14; i < 20 ; i++) g.ajoute(i);
  
  cout << setiosflags(ios_base::boolalpha);                // <iomanip>
  // Alternative :  cout.setf(ios_base::boolalpha);        // <ios>
  cout << e.contient(5) << endl;
  cout << f.contient(5) << endl;
  cout << g.contient(5) << endl;   
  cout << "e = " << e << endl;
  cout << "f = " << f << endl;
  cout << "g = " << g << endl;
  cout << " e U f = " << (e + f) << endl;
  cout << " e inter f = " << (e & f) << endl;
  cout << " e - f = " << (e - f) << endl;
  cout << " e inter g = " << (e & g) << endl;
  cout << " e diffSym f = " << (e ^ f) << endl;
  cout << " e diffSym g = " << (e ^ g) << endl;
  cout << " e - e = " << (e - e) << endl;
  cout << " e - {40.0} = " << (e - singleton<double>(40.0)) << endl;
  cout << " e U {40} U {50} = " << e + singleton(40.0) + singleton(50.0) << endl; 
  cout << endl;
  cout << " e = " << e << endl;
  cout << " f = " << f << endl;
  cout << " (e U f) - f " << (e + f) - f << endl;
  cout << " (e U f) - f == e ?   " << (((e + f) - f) == e) << endl;
  cout << " En effet, car e inter f = " << (e & f) << endl;
  cout << endl;
  cout << " e == e U {} ? " << ((e + Ensemble<double>()) == e) << endl;
// @todo provoque une erreur compilation
/*  cout << " e - {5} < e ? " << ((e - Ensemble<double>(5.0)) < e) << endl; */ 

  Ensemble<bool> a,b;  
  a.ajoute(true);
  b.ajoute(false);
  cout << endl;
  cout << " a = " << a << endl;
  cout << " b = " << b << endl;
  cout << " a + b = " << (a + b) << endl;
  cout << " a + b - {true} = " << ((a + b) - singleton(true)) << endl; 
  return 0;
}
