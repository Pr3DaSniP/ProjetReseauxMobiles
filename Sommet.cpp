#pragma once
#ifndef SOMMET_CPP
#define SOMMET_CPP

#include "Sommet.h"

template <class T>
Sommet<T>::Sommet(int id, string label, T valeur) : d_id{ id }, d_label{ label }, d_valeur { valeur }, d_couleur{ 0 }, d_isColored{ false } {}

template <class T>
void Sommet<T>::addVoisin(Sommet<T>& voisin) {
	d_voisins.push_back(&voisin);
}

template <class T>
bool Sommet<T>::isVoisin(const Sommet<T>& voisin) const {
	for (const Sommet* s : d_voisins) {
		if (*s == voisin) {
			return true;
		}
	}
	return false;
}

template <class T>
bool Sommet<T>::isColored() const {
	return d_isColored;
}

template <class T>
T Sommet<T>::getValeur() const { return d_valeur; }

template <class T>
int Sommet<T>::getId() const { return d_id; }

template <class T>
vector<Sommet<T>*> Sommet<T>::getVoisins() const { return d_voisins; }

template <class T>
Sommet<T>* Sommet<T>::getVoisin(int i) const {
	if (i < d_voisins.size()) {
		return d_voisins[i];
	}
	return nullptr;
}

template <class T>
int Sommet<T>::getCouleur() const { return d_couleur; }

template <class T>
int Sommet<T>::getDegre() const { return d_voisins.size(); }

template <class T>
string Sommet<T>::getLabel() const { return d_label; }

template <class T>
void Sommet<T>::setValeur(T& valeur) { d_valeur = valeur; }

template <class T>
void Sommet<T>::setCouleur(int couleur) { d_couleur = couleur; d_isColored = true; }

template <class T>
bool Sommet<T>::operator==(const Sommet<T>& sommet) const {
	return d_id == sommet.d_id;
}

template <class T>
bool Sommet<T>::operator!=(const Sommet<T>& sommet) const {
	return d_id != sommet.d_id;
}

template <class T>
ostream& operator<<(ostream& os, const Sommet<T>& sommet) {
	os << sommet.getValeur();
	return os;
}

#endif // !SOMMET_CPP