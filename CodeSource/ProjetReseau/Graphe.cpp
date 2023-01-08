#ifndef GRAPHE_CPP
#define GRAPHE_CPP

#include "Graphe.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <cmath>
using std::cout;
using std::endl;
using std::iota;

Graphe::Graphe() : d_fitness{-1}
{
}

Graphe::Graphe(vector<Sommet *> sommets) : d_sommets{sommets}, d_fitness{-1}
{
	for (int i = 0; i < getDegre(); i++)
	{
		d_couleurs.push_back(i + 1);
	}
}

vector<Sommet *> Graphe::getSommets() { return d_sommets; }

int Graphe::getNbSommets() const { return d_sommets.size(); }

int Graphe::getDegre() const
{
	int max = 0;
    for (unsigned int i = 0; i < d_sommets.size(); i++)
	{
		int degre = d_sommets[i]->getDegre();
		if (degre > max)
		{
			max = degre;
		}
	}
	return max + 1;
}

void Graphe::showEdges() const
{
	for (Sommet *sommet : d_sommets)
	{
		cout << sommet->getLabel() << " : ";
		for (Sommet *voisin : sommet->getVoisins())
		{
			cout << voisin->getLabel() << " ";
		}
		cout << endl;
	}
}

void Graphe::showColors() const
{
	for (Sommet *sommet : d_sommets)
	{
		cout << sommet->getLabel() << " : " << sommet->getCouleur() << endl;
	}
}

int Graphe::calculeCouleurs()
{
	vector<int> couleursDifferentes;
    for (unsigned int i = 0; i < d_sommets.size(); i++)
	{
		int couleur = d_sommets[i]->getCouleur();
		if (std::find(couleursDifferentes.begin(), couleursDifferentes.end(), couleur) == couleursDifferentes.end())
		{
			couleursDifferentes.push_back(couleur);
		}
	}
	return couleursDifferentes.size();
}

int Graphe::trouveCouleurMinimal(int id)
{
	vector<int> couleursDisponibles = d_couleurs;
	for (Sommet *voisin : d_sommets[id]->getVoisins())
	{
		int couleur = voisin->getCouleur();
		couleursDisponibles.erase(std::remove(couleursDisponibles.begin(), couleursDisponibles.end(), couleur), couleursDisponibles.end());
	}
	return couleursDisponibles[0];
}

void Graphe::trierCroissantSommetsParDegre()
{
	sort(d_sommets.begin(), d_sommets.end(), [](Sommet *a, Sommet *b)
		 { return a->getDegre() < b->getDegre(); });
}

void Graphe::trierDecroissantSommetsParDegre()
{
	sort(d_sommets.begin(), d_sommets.end(), [](Sommet *a, Sommet *b)
		 { return a->getDegre() > b->getDegre(); });
}

void Graphe::glouton()
{
	trierDecroissantSommetsParDegre();
    for (unsigned int i = 0; i < d_sommets.size(); i++)
	{
		d_sommets[i]->setCouleur(trouveCouleurMinimal(i));
	}
}

void Graphe::calulateFitness()
{
	if (d_fitness == -1)
	{
		for (Sommet *sommet : d_sommets)
		{
			for (Sommet *voisin : sommet->getVoisins())
			{
				if (sommet->getCouleur() == voisin->getCouleur())
				{
					d_fitness++;
				}
			}
		}
	}
}

int Graphe::getFitness()
{
	if (d_fitness == -1)
	{
		calulateFitness();
	}
	return d_fitness;
}

void Graphe::setFitness(int fitness)
{
	d_fitness = fitness;
}

void Graphe::randomInitialisation()
{
	for (Sommet *sommet : d_sommets)
	{
		sommet->setCouleur(d_couleurs[rand() % d_couleurs.size()]);
	}
}

void Graphe::recuitSimule(double temperatureInitiale, int nombreIterations, double coef)
{
    srand(time(NULL));
	// G�n�re une solution initiale au hasard
	randomInitialisation();
	Graphe *meilleureSolution = this; // La meilleure solution est la solution actuelle au d�but

	double temperature = temperatureInitiale;

	for (int i = 0; i < nombreIterations; i++)
	{
		// G�n�re une nouvelle solution en changeant la couleur d'un sommet au hasard
		Graphe nouvelleSolution = *this;
		int sommetIndex = rand() % nouvelleSolution.getNbSommets();
		Sommet *sommet = nouvelleSolution.getSommets()[sommetIndex];
		sommet->setCouleur(nouvelleSolution.trouveCouleurMinimal(sommetIndex));

		// Calcule la diff�rence de fitness entre la nouvelle solution et la solution actuelle
		int differenceFitness = nouvelleSolution.getFitness() - getFitness();

		if (differenceFitness < 0 || (float)rand() / RAND_MAX < exp(-differenceFitness / temperature))
		{
			*this = nouvelleSolution; // Accepte la nouvelle solution
		}

		if (getFitness() < meilleureSolution->getFitness())
		{
			meilleureSolution = this; // Mise � jour de la meilleure solution
		}

		// Refroidit la temp�rature
        temperature *= coef;
	}

    *this = *meilleureSolution; // La solution actuelle devient la meilleure solution trouvée
}

QJsonObject Graphe::toJson() const
{
	QJsonObject json;
	QJsonArray sommets;
	for (Sommet *sommet : d_sommets)
	{
		sommets.append(sommet->toJson());
	}
	json["sommets"] = sommets;
	return json;
}

#endif // !GRAPHE_CPP
