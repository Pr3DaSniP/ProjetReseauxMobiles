#ifndef MAILLE_H
#define MAILLE_H

#include <QObject>
#include <vector>
#include "Point.h"
#include "Antenne.h"

using std::string;
using std::vector;

class Maille
{
private:
    Point d_center;
    double d_largeur;
    double d_hauteur;
    Antenne d_antenne;
    bool d_antennePresente;

public:
    Maille();

    Maille(
        Point center,
        double largeur,
        double hauteur);

    void setAntenne(Antenne antenne);

    void removeAntenne();

    Antenne *getAntenne();

    Point getCenter();

    string affiche();

    double getHauteur();

    double getLargeur();

    static vector<vector<Maille>> maillage(Point from, Point to, double largeur, double hauteur);
};

#endif // MAILLE_H
