#ifndef SOMMET_H
#define SOMMET_H

#include <vector>
#include <iostream>
#include <QJsonObject>
#include <QJsonArray>
#include "Antenne.h"

using std::ostream;
using std::string;
using std::vector;

class Sommet
{
private:
	int d_id;
	Antenne d_antenne;
	vector<Sommet *> d_voisins;
	int d_couleur;
	string d_label;

public:
	Sommet(int id, string label, Antenne valeur);

	void addVoisin(Sommet &voisin);

	int getId() const;
	Antenne getAntenne() const;
	vector<Sommet *> getVoisins() const;
	Sommet *getVoisin(int i) const;
	string getLabel() const;
	int getCouleur() const;
	int getDegre() const;
	bool isVoisin(const Sommet &voisin) const;

	void setAntenne(Antenne &antenne);
	void setCouleur(int couleur);

	bool operator==(const Sommet &sommet) const;
	bool operator!=(const Sommet &sommet) const;

	QJsonObject toJson() const;
};

ostream &operator<<(ostream &os, const Sommet &sommet);

#endif // !SOMMET_H
