#ifndef GRAPHE_H
#define GRAPHE_H

#include <QJsonObject>
#include <QJsonArray>

#include <vector>
#include <list>
#include "Sommet.h"
#include "time.h"

using std::vector;

class Graphe
{
private:
	vector<Sommet *> d_sommets;
	vector<int> d_couleurs;
	int d_fitness;

	int trouveCouleurMinimal(int id);

	void trierCroissantSommetsParDegre();

	void trierDecroissantSommetsParDegre();

public:
	Graphe();

	Graphe(vector<Sommet *> sommets);

	vector<Sommet *> getSommets();

	int getNbSommets() const;

	int getDegre() const;

	void showEdges() const;

	void glouton();

	int getFitness();

	void setFitness(int fitness);

	int calculeCouleurs();

	void showColors() const;

	void calulateFitness();

	void randomInitialisation();

    void recuitSimule(double temperatureInitiale, int nombreIterations, double coef);

	QJsonObject toJson() const;
};

#endif // !GRAPHE_H
