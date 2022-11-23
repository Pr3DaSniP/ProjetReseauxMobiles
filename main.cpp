#include <iostream>

#include "Point.h"
#include "Antenne.h"
#include "Graphe.h"
#include "Sommet.h"
#include "Maille.h"

#include "graphics.h"
#include <time.h>

#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

void sleep(int milliseconds)
{
	clock_t time_end;
	time_end = clock() + milliseconds * CLOCKS_PER_SEC / 1000;
	while (clock() < time_end)
	{
	}
}

void trace(Graphe<Sommet<Antenne> *> g, bool rect)
{
	for (Sommet<Antenne> *s : g.getSommets())
	{
		Point p = s->getValeur().getPosition();

		// TODO: Redimensionner les coordonnées Lambert93 pour qu'elles soient dans la fenêtre graphique (800 x 600)
		// colorier le point en fonction de la couleur de l'antenne
		setcolor(s->getCouleur());
		fillellipse(p.getLambertLatitude(), p.getLambertLongitude(), 10, 10);

		setcolor(RED);
		if (rect)
		{
			rectangle(
				p.getLambertLatitude() - s->getValeur().getPuissanceEmission(),
				p.getLambertLongitude() - s->getValeur().getPuissanceEmission(),
				p.getLambertLatitude() + s->getValeur().getPuissanceEmission(),
				p.getLambertLongitude() + s->getValeur().getPuissanceEmission());
		}
		else
		{
			circle(p.getLambertLatitude(), p.getLambertLongitude(), s->getValeur().getPuissanceEmission());
		}
		setcolor(WHITE);

		// Afficher le Label du sommet
		stringstream ss;
		ss << s->getLabel();
		string label = ss.str();

		// Changer la taille de la police
		settextstyle(10, 0, 2);
		outtextxy(p.getLambertLatitude() + 8, p.getLambertLongitude() + 8, label.c_str());

		// Afficher les arcs du sommet vers ses voisins
		vector<Sommet<Antenne> *> voisins = s->getVoisins();
		for (Sommet<Antenne> *v : voisins)
		{
			Point p2 = v->getValeur().getPosition();
			line(p.getLambertLatitude(), p.getLambertLongitude(), p2.getLambertLatitude(), p2.getLambertLongitude());
		}
	}
}

void toGraphviz(Graphe<Sommet<Antenne> *> g)
{
	ofstream fichier("Antennes.gv", ios::out | ios::trunc);
	if (fichier)
	{
		fichier << "digraph G {" << endl;
		for (Sommet<Antenne> *s : g.getSommets())
		{
			fichier << s->getId() << " [label=\"" << s->getLabel() << "\"];" << endl;
		}
		for (Sommet<Antenne> *s : g.getSommets())
		{
			for (Sommet<Antenne> *v : s->getVoisins())
			{
				fichier << s->getId() << " -> " << v->getId() << ";" << endl;
			}
		}
		fichier << "}";
	}
}

void maillesEtVoisins(const vector<vector<Maille *>> &mailles)
{
	for (int i = 0; i < mailles.size(); ++i)
	{
		for (int j = 0; j < mailles[i].size(); ++j)
		{
			auto m = mailles[i][j];
			cout << "Maille " << m->getCentre() << " : ";
			for (auto v : m->getVoisins())
			{
				cout << v->getCentre() << " ";
			}
			cout << endl;
		}
	}
}

void afficheMailles(const vector<vector<Maille *>> &mailles)
{
	for (int i = 0; i < mailles.size(); ++i)
	{
		for (int j = 0; j < mailles[i].size(); ++j)
		{
			auto m = mailles[i][j];
			if (!m->estDessine())
			{
				cout << m->getCentre() << " ";
				m->setEstDesinne(true);
			}
		}
		cout << endl;
	}
}

void testGraphe1()
{
	// https://i.imgur.com/BN0meRQ.png
	Sommet<Antenne> *a = new Sommet<Antenne>{1, "A", {}};
	Sommet<Antenne> *b = new Sommet<Antenne>{2, "B", {}};
	Sommet<Antenne> *c = new Sommet<Antenne>{3, "C", {}};
	Sommet<Antenne> *d = new Sommet<Antenne>{4, "D", {}};
	Sommet<Antenne> *e = new Sommet<Antenne>{5, "E", {}};
	Sommet<Antenne> *f = new Sommet<Antenne>{6, "F", {}};
	Sommet<Antenne> *g = new Sommet<Antenne>{7, "G", {}};

	a->addVoisin(*b);

	b->addVoisin(*a);
	b->addVoisin(*c);
	b->addVoisin(*g);
	b->addVoisin(*f);

	c->addVoisin(*b);
	c->addVoisin(*d);
	c->addVoisin(*e);
	c->addVoisin(*f);

	d->addVoisin(*c);
	d->addVoisin(*e);

	e->addVoisin(*c);
	e->addVoisin(*d);

	f->addVoisin(*b);
	f->addVoisin(*c);

	g->addVoisin(*b);

	vector<Sommet<Antenne> *> sommets = {a, b, c, d, e, f, g};

	Graphe<Sommet<Antenne> *> g1 = {sommets};

	g1.colorierGraphe();

	g1.showColors();
}

void testGraphe2()
{
	// https://i.imgur.com/lqAL1rm.png
	Sommet<Antenne> *un = new Sommet<Antenne>{1, "1", {}};
	Sommet<Antenne> *deux = new Sommet<Antenne>{2, "2", {}};
	Sommet<Antenne> *trois = new Sommet<Antenne>{3, "3", {}};
	Sommet<Antenne> *quatre = new Sommet<Antenne>{4, "4", {}};
	Sommet<Antenne> *cinq = new Sommet<Antenne>{5, "5", {}};
	Sommet<Antenne> *six = new Sommet<Antenne>{6, "6", {}};
	Sommet<Antenne> *sept = new Sommet<Antenne>{7, "7", {}};

	un->addVoisin(*deux);
	un->addVoisin(*quatre);
	un->addVoisin(*trois);

	deux->addVoisin(*un);
	deux->addVoisin(*trois);
	deux->addVoisin(*quatre);
	deux->addVoisin(*cinq);
	deux->addVoisin(*six);

	trois->addVoisin(*un);
	trois->addVoisin(*deux);
	trois->addVoisin(*cinq);

	quatre->addVoisin(*un);
	quatre->addVoisin(*deux);
	quatre->addVoisin(*cinq);
	quatre->addVoisin(*sept);
	quatre->addVoisin(*six);

	cinq->addVoisin(*deux);
	cinq->addVoisin(*trois);
	cinq->addVoisin(*quatre);

	six->addVoisin(*deux);
	six->addVoisin(*quatre);
	six->addVoisin(*sept);

	sept->addVoisin(*quatre);
	sept->addVoisin(*six);

	vector<Sommet<Antenne> *> sommets = {un, deux, trois, quatre, cinq, six, sept};

	Graphe<Sommet<Antenne> *> g2 = {sommets};

	g2.colorierGraphe();

	g2.showColors();
}

void testGraphe3()
{
	// https://i.imgur.com/um2IkDE.png
	Sommet<Antenne> *un = new Sommet<Antenne>{1, "1", {}};
	Sommet<Antenne> *deux = new Sommet<Antenne>{2, "2", {}};
	Sommet<Antenne> *trois = new Sommet<Antenne>{3, "3", {}};
	Sommet<Antenne> *quatre = new Sommet<Antenne>{4, "4", {}};
	Sommet<Antenne> *cinq = new Sommet<Antenne>{5, "5", {}};
	Sommet<Antenne> *six = new Sommet<Antenne>{6, "6", {}};
	Sommet<Antenne> *sept = new Sommet<Antenne>{7, "7", {}};

	un->addVoisin(*deux);
	un->addVoisin(*quatre);
	un->addVoisin(*trois);

	deux->addVoisin(*un);
	deux->addVoisin(*trois);
	deux->addVoisin(*quatre);
	deux->addVoisin(*cinq);

	trois->addVoisin(*un);
	trois->addVoisin(*deux);
	trois->addVoisin(*cinq);
	trois->addVoisin(*six);
	trois->addVoisin(*quatre);

	quatre->addVoisin(*un);
	quatre->addVoisin(*deux);
	quatre->addVoisin(*trois);
	quatre->addVoisin(*six);

	cinq->addVoisin(*deux);
	cinq->addVoisin(*trois);
	cinq->addVoisin(*sept);

	six->addVoisin(*trois);
	six->addVoisin(*quatre);
	six->addVoisin(*sept);

	sept->addVoisin(*cinq);
	sept->addVoisin(*six);

	vector<Sommet<Antenne> *> sommets = {un, deux, trois, quatre, cinq, six, sept};

	Graphe<Sommet<Antenne> *> g3 = {sommets};

	g3.colorierGraphe();

	g3.showColors();
}

void testLectureFichier()
{
	vector<Sommet<Antenne> *> sommets;

	ifstream fichier("Antennes.txt");
	if (fichier)
	{
		string ligne;
		int nbLigne = 0;
		while (getline(fichier, ligne))
		{
			nbLigne++;
			istringstream iss(ligne);
			Point p;
			double puissanceEmission, frequence;
			string nom;
			iss >> p >> puissanceEmission >> frequence >> nom;

			Antenne a = {p, puissanceEmission, frequence, nom};

			Sommet<Antenne> *s = new Sommet<Antenne>{nbLigne, a.getNom(), a};

			sommets.push_back(s);
		}
	}

	Graphe<Sommet<Antenne> *> g = {sommets};

	g.showEdges();
}

void testMailles()
{
	const int NOMBRE_MAILLE = 5;

	vector<vector<Maille *>> mailles(NOMBRE_MAILLE, vector<Maille *>(NOMBRE_MAILLE));

	// Initialisation des mailles
	for (int i = 0; i < NOMBRE_MAILLE; i++)
	{
		for (int j = 0; j < NOMBRE_MAILLE; j++)
		{
			mailles[i][j] = new Maille{i, Point(i, j), 100};
		}
	}

	// Initialisation des voisins
	for (int i = 0; i < NOMBRE_MAILLE; i++)
	{
		for (int j = 0; j < NOMBRE_MAILLE; j++)
		{
			if (i > 0)
			{
				mailles[i][j]->addVoisin(mailles[i - 1][j]);
			}
			if (i < NOMBRE_MAILLE - 1)
			{
				mailles[i][j]->addVoisin(mailles[i + 1][j]);
			}
			if (j > 0)
			{
				mailles[i][j]->addVoisin(mailles[i][j - 1]);
			}
			if (j < NOMBRE_MAILLE - 1)
			{
				mailles[i][j]->addVoisin(mailles[i][j + 1]);
			}
		}
	}

	maillesEtVoisins(mailles);

	cout << endl
		 << endl;

	afficheMailles(mailles);
}

void testPoints()
{
	// 1617040.1 2338189.3 => 10 10
	Point p1(1617040.1, 2338189.3);
	cout << "(" << p1.getLambertLatitude() << ", " << p1.getLambertLongitude() << ")"
		 << " => " << p1.getLatitude() << " " << p1.getLongitude() << endl;

	// 1024725.72 6747856.18 => 47.750839 7.335888
	Point p2(1024725.72, 6747856.18);
	cout << "(" << p2.getLambertLatitude() << ", " << p2.getLambertLongitude() << ")"
		 << " => " << p2.getLatitude() << " " << p2.getLongitude() << endl;
}

void testComplet()
{
	vector<Sommet<Antenne> *> sommets;

	ifstream fichier("Antennes.txt");
	if (fichier)
	{
		string ligne;
		int nbLigne = 0;
		while (getline(fichier, ligne))
		{
			nbLigne++;
			istringstream iss(ligne);
			Point p;
			double puissanceEmission, frequence;
			string nom = "Antenne" + to_string(nbLigne);
			iss >> p >> puissanceEmission >> frequence;

			Antenne a = {p, puissanceEmission, frequence, nom};

			Sommet<Antenne> *s = new Sommet<Antenne>{nbLigne, a.getNom(), a};

			sommets.push_back(s);
		}
	}

	for (int i = 0; i < sommets.size(); i++)
	{
		for (int j = i + 1; j < sommets.size(); j++)
		{
			if (sommets[i]->getValeur().chevauchement(sommets[j]->getValeur()))
			{
				sommets[i]->addVoisin(*sommets[j]);
				sommets[j]->addVoisin(*sommets[i]);
			}
		}
	}

	Graphe<Sommet<Antenne> *> g = {sommets};

	g.colorierGraphe();

	trace(g, true);
}

void testAnimation()
{
	vector<Sommet<Antenne> *> sommets;

	ifstream fichier("AntennesV2.txt");
	if (fichier)
	{
		string ligne;
		int nbLigne = 0;
		while (getline(fichier, ligne))
		{
			nbLigne++;
			istringstream iss(ligne);
			Point p;
			double puissanceEmission, frequence;
			string nom = "Antenne" + to_string(nbLigne);
			iss >> p >> puissanceEmission >> frequence;

			Antenne a = {p, puissanceEmission, frequence, nom};

			Sommet<Antenne> *s = new Sommet<Antenne>{nbLigne, a.getNom(), a};

			sommets.push_back(s);
		}
	}

	for (int t = 0; t < 40; ++t)
	{
		cleardevice();

		// Augmenter la fréquence de chaque antenne
		for (Sommet<Antenne> *s : sommets)
		{

			// if(s->getVoisins().size() > 0) continue;

			Antenne a = s->getValeur();
			a.setPuissanceEmission(a.getPuissanceEmission() + 5);
			s->setValeur(a);
		}
		for (int i = 0; i < sommets.size(); i++)
		{
			for (int j = i + 1; j < sommets.size(); j++)
			{
				if (sommets[i]->getValeur().chevauchement(sommets[j]->getValeur()))
				{
					sommets[i]->addVoisin(*sommets[j]);
					sommets[j]->addVoisin(*sommets[i]);
				}
			}
		}

		Graphe<Sommet<Antenne> *> g = {sommets};

		g.colorierGraphe();

		trace(g, false);

		sleep(100);
	}
}

int main()
{
	opengraphsize(1200, 800);

	testAnimation();

	getch();

	closegraph();

	return 0;
}
