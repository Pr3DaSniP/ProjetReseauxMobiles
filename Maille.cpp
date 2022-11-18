#include "Maille.h"

Maille::Maille(int id, Point centre, int taille) 
: d_id{ id }, d_centre{ centre }, d_taille{ taille }, d_antenne{ nullptr }, d_estVide{ true }, d_estDessine{ false } {
	d_coins.push_back(Point(centre.getLatitude() - taille / 2, centre.getLongitude() - taille / 2));
	d_coins.push_back(Point(centre.getLatitude() + taille / 2, centre.getLongitude() - taille / 2));
	d_coins.push_back(Point(centre.getLatitude() + taille / 2, centre.getLongitude() + taille / 2));
	d_coins.push_back(Point(centre.getLatitude() - taille / 2, centre.getLongitude() + taille / 2));
}

int Maille::getId() const { return d_id; }

Point Maille::getCentre() const { return d_centre; }

Antenne* Maille::getAntenne() const { return d_antenne; }

bool Maille::estVide() const { return d_estVide; }

bool Maille::estDessine() const { return d_estDessine; }

vector<Maille*> Maille::getVoisins() const { return d_voisins; }

vector<Point> Maille::getCoins() const { return d_coins; }

void Maille::setId(int id) { d_id = id; }

void Maille::setAntenne(Antenne* antenne) { d_antenne = antenne; d_estVide = false; }

void Maille::addVoisin(Maille* voisin) { d_voisins.push_back(voisin); }

void Maille::setEstDesinne(bool estDessine) { d_estDessine = estDessine; }

void Maille::affiche() const {
	for (int i = 0; i < d_voisins.size(); ++i) {
		auto v = d_voisins[i];

		if (i == 4) {
			cout << getCentre() << " ";
		}
		
		if (v != nullptr) {
			cout << v->getCentre() << " ";
		}
		else {
			cout << "X ";
		}
		
		if (i == 2 || i == 4 || i == 7) {
			cout << endl;
		}
	}
}