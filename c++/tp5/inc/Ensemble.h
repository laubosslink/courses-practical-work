#ifndef ENSEMBLE_INCLUDED_H
#define ENSEMBLE_INCLUDED_H

#include <iostream>
#include <ostream>

template <typename T> class Ensemble;

template <typename T>
std::ostream & operator<<(std::ostream &, const Ensemble<T> &);

template <typename T> class Ensemble {
private:
	class Noeud {
	private:
		T valeur;
		Noeud* suivant;
	public:
		Noeud(T valeur, Noeud* suivant=0): valeur(valeur), suivant(suivant){}
		T getValeur() { return valeur; }
		Noeud* getSuivant(){ return suivant; }
		void setSuivant(Noeud* suivant){ Noeud::suivant = suivant; }
	};

	Noeud* liste;
public:

	/** Partie 3 : iterator */
	class iterator {
	private:
		Noeud *courant;
	public:
		iterator(Ensemble<T> e) { courant = e.liste; }
		bool hasNext() { return courant->getSuivant() != nullptr; }
		void next() {
			if(!hasNext()) return;
			courant = courant->getSuivant();
		}
		T getCurrent() {
			return courant->getValeur();
		}
	};

	Ensemble(): liste(0){}
	Ensemble(T x){ liste = new Noeud(x); }
	~Ensemble(){};

	bool estVide() const { return liste == 0; }

	std::ostream & flush(std::ostream & out) const
	{
		if(estVide())
			return out << "{}";

		Noeud* courrant = liste;

		out << "{";

		do
		{
			out << courrant->getValeur();

			if(courrant->getSuivant() != nullptr)
				out << ", ";

		} while((courrant = courrant->getSuivant()) != nullptr);

		out << "}";
	}

	bool contient(T x) const
	{
		if(liste == nullptr)
			return false;

		Noeud* courant = liste;

		do
		{
			if(courant->getValeur() == x)
				return true;
		}while((courant = courant->getSuivant()) != nullptr);


		return false;
	}

	bool estInclusDans(const Ensemble & autre) const
	{
		if(autre.estVide()){
			return false;
		}

		if(estVide()){
			return true;
		}

		Noeud* courant = liste;
		do
		{
			if(!autre.contient(courant->getValeur()))
				return false;
		} while((courant = courant->getSuivant()) != nullptr);

		return true;
	}

	void ajoute(T x){
		if(estVide())
		{
			liste = new Noeud(x);
			return;
		}

		Noeud* e = new Noeud(x);
		Noeud* courant = liste;

		while(courant->getSuivant() != nullptr)
		{
			/* verifie unicite d'une valeur dans l'ensemble */
			if(courant->getValeur() == x)
				return;

			courant = courant->getSuivant();
		}

		courant->setSuivant(e);
	}

	void retire(T x)
	{
		if(estVide())
			return;

		Noeud* courant = liste;

		// cas on trouve sur le premier element
		if(liste->getValeur() == x)
		{
			liste = liste->getSuivant();
			delete courant;
			return;
		}

		// cas où la liste a un seul element, on s'arrête
		if(liste->getSuivant() == nullptr)
			return;

		Noeud* tmp = courant->getSuivant();

		do
		{
			if(tmp->getValeur() == x)
			{
				courant->setSuivant(tmp->getSuivant());
				delete tmp;
				return;
			}

			courant = courant->getSuivant();

		} while((tmp = tmp->getSuivant()) != nullptr);
	}

	void ajouteDans(Ensemble &e) const{
		if(estInclusDans(e))
			return;

		Noeud* courant = liste;
		do {
			e.ajoute(courant->getValeur());
		} while((courant = courant->getSuivant()) != nullptr);

	}

	void retireDe(Ensemble &e) const
	{
		if(estVide())
			return;

		Noeud* courant = liste;

		do
		{
			e.retire(courant->getValeur());
		} while((courant = courant->getSuivant()) != nullptr);
	}

	friend std::ostream & operator<<<>(std::ostream &, const Ensemble<T> &);
};

template <typename T>
std::ostream & operator<<(std::ostream & out, const Ensemble<T> & e)
{
	return e.flush(out);
}

template <typename T> Ensemble<T> singleton(T x)
{
	return Ensemble<T>(x);
}

template <typename T> Ensemble<T> ensembleVide()
{
	return Ensemble<T>();
}

template <typename T> bool egale(const Ensemble<T> & a, const Ensemble<T> & b)
{
	return (a.estInclusDans(b) && b.estInclusDans(a));
}

template <typename T> bool operator==(const Ensemble<T> & a, const Ensemble<T> & b)
{
	return egale<T>(a, b);
}

template <typename T> Ensemble<T> reunion(const Ensemble<T> & a, const Ensemble<T> & b)
{
	Ensemble<T> r = ensembleVide<T>(); // @todo utiliser le constructeur par recopie

	a.ajouteDans(r);
	b.ajouteDans(r);

	return r;
}

template <typename T> Ensemble<T> operator+(const Ensemble<T> & a, const Ensemble<T> & b)
{
	return reunion<T>(a, b);
}

template <typename T> Ensemble<T> operator|(const Ensemble<T> & a, const Ensemble<T> & b)
{
	return reunion<T>(a, b);
}

// A\B <=> A inter B
template <typename T> Ensemble<T> difference(const Ensemble<T> & a, const Ensemble<T> & b)
{
	Ensemble<T> d = ensembleVide<T>(); // @todo utiliser le constructeur par recopie

	a.ajouteDans(d);
	b.retireDe(d);

	return d;
}

template <typename T> Ensemble<T> operator-(const Ensemble<T> & a, const Ensemble<T> & b)
{
	return difference<T>(a, b);
}

// (A\B) U (B\A)
template <typename T> Ensemble<T> diffSymetrique(const Ensemble<T> & a, const Ensemble<T> & b)
{
	return reunion<T>(a - b, b - a);
}

template <typename T> Ensemble<T> operator^(const Ensemble<T> & a, const Ensemble<T> & b)
{
	return diffSymetrique<T>(a, b);
}

template <typename T> Ensemble<T> intersection(const Ensemble<T> & a, const Ensemble<T> & b)
{
	if(a.estInclusDans(b))
		return a; // @todo recopie, pas redonner le même élément !

	if(b.estInclusDans(a))
		return b; // @todo

	return reunion<T>(a, b)-diffSymetrique<T>(a, b);
}

template <typename T> Ensemble<T> operator&(const Ensemble<T> &a, const Ensemble<T> &b)
{
	return intersection<T>(a, b);
}


#endif
