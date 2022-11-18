#pragma once
#ifndef GRAPHE_CPP
#define GRAPHE_CPP

#include "Graphe.h"

#include <algorithm>
#include <iostream>
using std::cout;
using std::endl;

template <class T>
Graphe<T>::Graphe(vector<T> sommets) :
	d_sommets{ sommets }
{
	for (int i = 0; i < getDegre(); i++) {
		d_couleurs.push_back(i + 1);
	}
}

template <class T>
vector<T> Graphe<T>::getSommets() { return d_sommets; }

template <class T>
int Graphe<T>::getNbSommets() const { return d_sommets.size(); }

template <class T>
int	 Graphe<T>::getDegre() const {
	int max = 0;
	for (int i = 0; i < d_sommets.size(); i++) {
		int degre = d_sommets[i]->getDegre();
		if (degre > max) {
			max = degre;
		}
	}
	return max + 1;
}

template <class T>
void Graphe<T>::showEdges() const {
	for (auto sommet : d_sommets) {
		cout << sommet->getLabel() << " : ";
		for (auto voisin : sommet->getVoisins()) {
			cout << voisin->getLabel() << " ";
		}
		cout << endl;
	}
}

template <class T>
void Graphe<T>::showColors() const {
	for (auto sommet : d_sommets) {
		cout << sommet->getLabel() << " : " << sommet->getCouleur() << endl;
	}
}

template <class T>
bool Graphe<T>::isGrapheColored() const {
	for (auto sommet : d_sommets) {
		if (!sommet->isColored()) {
			return false;
		}
	}
	return true;
}

template <class T>
int Graphe<T>::trouveCouleurMinimal(int id) {
	vector<int> couleursDisponibles = d_couleurs;
	for (auto voisin : d_sommets[id]->getVoisins()) {
		if (voisin->isColored()) {
			int couleur = voisin->getCouleur();
			couleursDisponibles.erase(std::remove(couleursDisponibles.begin(), couleursDisponibles.end(), couleur), couleursDisponibles.end());
		}
	}
	return couleursDisponibles[0];
}

template <class T>
void Graphe<T>::trierCroissantSommets() {
	sort(d_sommets.begin(), d_sommets.end(), [](auto a, auto b) {
		return a->getDegre() < b->getDegre();
	});
}

template <class T>
void Graphe<T>::trierDecroissantSommets() {
	sort(d_sommets.begin(), d_sommets.end(), [](auto a, auto b) {
		return a->getDegre() > b->getDegre();
	});
}

template <class T>
void Graphe<T>::colorierGraphe() {
	trierDecroissantSommets();
	
	for (int i = 0; i < d_sommets.size(); i++) {
		d_sommets[i]->setCouleur(trouveCouleurMinimal(i));
	}
	
}

#endif // !GRAPHE_CPP