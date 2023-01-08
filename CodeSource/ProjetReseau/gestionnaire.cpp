#include "gestionnaire.h"

gestionnaire::gestionnaire(QObject *parent) : QObject(parent)
{
    d_graphe = new Graphe;
    d_nbSommets = d_graphe->getNbSommets();
    d_degre = d_graphe->getDegre();
}

void gestionnaire::setPath(const QString &path)
{
    if (d_path == path)
        return;

    // Remove les 8 premiers caractères (file:///)
    d_path = path.mid(8);

    loadGraphe();
}

void gestionnaire::setObj(QObject *obj)
{
    if (d_obj == obj)
        return;

    d_obj = obj;
}

void gestionnaire::makeGlouton()
{
    if (d_nbSommets > 0)
    {
        auto start = high_resolution_clock::now();
        d_graphe->glouton();
        auto finish = high_resolution_clock::now();
        auto tmps = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() / 1e+6;
        d_graphe->showColors();
        int nbCouleurs = d_graphe->calculeCouleurs();
        std::cout << "GLOUTON : " << nbCouleurs << std::endl;
        // Colorier les antennes des bonnes couleurs
        QMetaObject::invokeMethod(d_obj, "colorierAntennes",
                                  Q_ARG(QVariant, d_graphe->toJson()),
                                  Q_ARG(QVariant, "glouton"),
                                  Q_ARG(QVariant, QVariant::fromValue(tmps)));
    }
    else
    {
        std::cout << "Le graphe est vide." << std::endl;
    }
}

void gestionnaire::makeRS()
{
    if (d_nbSommets > 0)
    {
        double temperature = 0;
        int iterMax = 0;
        double coef = 0.99;

        if(d_nbSommets <= 30) {
            temperature = 100;
            iterMax = 1000;
        }
        else if(d_nbSommets > 30 && d_nbSommets <=100) {
            temperature = 2000;
            iterMax = 10000;
        }
        else if(d_nbSommets > 100 && d_nbSommets <= 500) {
            temperature = 3000;
            iterMax = 50000;
        }

        auto start = high_resolution_clock::now();
        d_graphe->recuitSimule(temperature, iterMax, coef);
        auto finish = high_resolution_clock::now();
        auto tmps = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() / 1e+6;
        d_graphe->showColors();
        int nbCouleurs = d_graphe->calculeCouleurs();
        std::cout << "RS : " << nbCouleurs << std::endl;
        QMetaObject::invokeMethod(d_obj, "colorierAntennes",
                                  Q_ARG(QVariant, d_graphe->toJson()),
                                  Q_ARG(QVariant, "recuit simulé"),
                                  Q_ARG(QVariant, QVariant::fromValue(tmps)));
    }
    else
    {
        std::cout << "Le graphe est vide." << std::endl;
    }
}

void gestionnaire::loadGraphe()
{
    vector<Sommet *> sommets;

    ifstream fichier(d_path.toStdString());
    if (fichier)
    {
        string ligne;
        int nbLigne = 0;
        while (getline(fichier, ligne))
        {
            nbLigne++;
            istringstream iss(ligne);

            if (nbLigne == 1)
            {
                continue;
            }

            string nom, lat, lon, puissance;
            getline(iss, nom, ';');
            getline(iss, lat, ';');
            getline(iss, lon, ';');
            getline(iss, puissance, ';');

            double latitude = std::stod(lat);
            double longitude = std::stod(lon);
            double puissanceEmission = std::stod(puissance);

            Point p = {latitude, longitude, true};
            Antenne a = {p, puissanceEmission, 0, nom};
            Sommet *s = new Sommet{nbLigne, a.getNom(), a};

            sommets.push_back(s);
        }

        // Construction de graphe de conflits
        for (unsigned int i = 0; i < sommets.size(); i++)
        {
            for (unsigned int j = i + 1; j < sommets.size(); j++)
            {
                if (sommets[i]->getAntenne().chevauchement(sommets[j]->getAntenne()))
                {
                    sommets[i]->addVoisin(*sommets[j]);
                    sommets[j]->addVoisin(*sommets[i]);
                }
            }
        }

        d_graphe = new Graphe{sommets};
        d_nbSommets = d_graphe->getNbSommets();
        d_degre = d_graphe->getDegre();
        QMetaObject::invokeMethod(d_obj, "loadGrapheQML", Q_ARG(QVariant, d_graphe->toJson()));
    }
}
