#pragma once
#ifndef SOMMET_CPP
#define SOMMET_CPP

#include "Sommet.h"

Sommet::Sommet(int id, string label, Antenne antenne) : d_id{id}, d_label{label}, d_antenne{antenne}, d_couleur{0} {}

void Sommet::addVoisin(Sommet &voisin)
{
	d_voisins.push_back(&voisin);
}

bool Sommet::isVoisin(const Sommet &voisin) const
{
	for (const Sommet *s : d_voisins)
	{
		if (*s == voisin)
		{
			return true;
		}
	}
	return false;
}

Antenne Sommet::getAntenne() const { return d_antenne; }

int Sommet::getId() const { return d_id; }

string Sommet::getLabel() const { return d_label; }

vector<Sommet *> Sommet::getVoisins() const { return d_voisins; }

Sommet *Sommet::getVoisin(int i) const
{
	if (i < d_voisins.size())
	{
		return d_voisins[i];
	}
	return nullptr;
}

int Sommet::getCouleur() const { return d_couleur; }

int Sommet::getDegre() const { return d_voisins.size(); }

void Sommet::setAntenne(Antenne &antenne) { d_antenne = antenne; }

void Sommet::setCouleur(int couleur) { d_couleur = couleur; }

QJsonObject Sommet::toJson() const
{
	QJsonObject json;
	json["id"] = d_id;
	json["label"] = QString::fromStdString(d_label);
	json["antenne"] = d_antenne.toJson();
	json["couleur"] = d_couleur;
	QJsonArray voisins;
	for (int i = 0; i < d_voisins.size(); i++)
		voisins.append(d_voisins[i]->getAntenne().getPosition().toJson());
	json["voisins"] = voisins;
	return json;
}

bool Sommet::operator==(const Sommet &sommet) const
{
	return d_id == sommet.d_id;
}

bool Sommet::operator!=(const Sommet &sommet) const
{
	return d_id != sommet.d_id;
}

ostream &operator<<(ostream &os, const Sommet &sommet)
{
	os << sommet;
	return os;
}

#endif // !SOMMET_CPP