#ifndef MAILLE_H
#define MAILLE_H

#include "Antenne.h"
#include "Point.h"

#include <iostream>
#include <vector>
using std::vector;
using std::cout;
using std::endl;

class Maille {
private:
	int d_id;
	Point d_centre;
	Antenne* d_antenne;
	bool d_estVide;
	vector<Maille*> d_voisins;
	vector<Point> d_coins;
	int d_taille;
	bool d_estDessine;
public:
	Maille(int id, Point centre, int taille);

	int getId() const;
	
	Point getCentre() const;

	Antenne* getAntenne() const;

	bool estVide() const;

	bool estDessine() const;

	vector<Maille*> getVoisins() const;

	vector<Point> getCoins() const;

	void setId(int id);

	void setAntenne(Antenne* antenne);

	void setEstDesinne(bool estDessine);

	void addVoisin(Maille* voisin);

	void affiche() const;
};

#endif // !MAILLE_H
