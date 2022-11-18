#ifndef SOMMET_H
#define SOMMET_H

#include <vector>
#include <iostream>
#include "Antenne.h"

using std::vector;
using std::ostream;
using std::string;

template <class T>
class Sommet {
private:
	int d_id;
	T d_valeur;
	vector<Sommet<T>*> d_voisins;
	int d_couleur;
	bool d_isColored;
	string d_label;
public:
	Sommet(int id, string label, T valeur);

	void addVoisin(Sommet<T>& voisin);
	
	int getId() const;
	T getValeur() const;
	vector<Sommet<T>*> getVoisins() const;
	Sommet<T>* getVoisin(int i) const;
	int getCouleur() const;
	int getDegre() const;
	string getLabel() const;
	bool isVoisin(const Sommet<T>& voisin) const;
	bool isColored() const;

	void setValeur(T& valeur);
	void setCouleur(int couleur);

	bool operator==(const Sommet<T>& sommet) const;
	bool operator!=(const Sommet<T>& sommet) const;
};

template <class T>
ostream& operator<<(ostream& os, const Sommet<T>& sommet);

#include "Sommet.cpp" // Important pour le template

#endif // !SOMMET_H