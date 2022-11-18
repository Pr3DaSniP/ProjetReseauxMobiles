#ifndef GRAPHE_H
#define GRAPHE_H

#include <vector>
#include "Sommet.h"

using std::vector;


template <class T>
class Graphe {
private:
	vector<T> d_sommets;
	vector<int> d_couleurs;

	int trouveCouleurMinimal(int id);

	void trierCroissantSommets();
	
	void trierDecroissantSommets();

public:
	Graphe(vector<T> sommets);

	vector<T> getSommets();

	int getNbSommets() const;

	int getDegre() const;

	void showEdges() const;

	bool isGrapheColored() const;

	void colorierGraphe();

	void showColors() const;
};

#include "Graphe.cpp" // Important pour le template

#endif // !GRAPHE_H