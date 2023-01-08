#include "maille.h"

Maille::Maille()
    : d_center{Point(0, 0, false)}, d_largeur{0}, d_hauteur{0}, d_antenne{Antenne()}, d_antennePresente{false}
{
}

Maille::Maille(Point center, double largeur, double hauteur)
    : d_center{center}, d_largeur{largeur}, d_hauteur{hauteur}, d_antenne{Antenne()}, d_antennePresente{false}
{
}

void Maille::setAntenne(Antenne antenne)
{
    d_antenne = antenne;
    d_antennePresente = true;
}

void Maille::removeAntenne()
{
    d_antennePresente = false;
}

Antenne *Maille::getAntenne()
{
    return &d_antenne;
}

Point Maille::getCenter()
{
    return d_center;
}

string Maille::affiche()
{
    if (!d_antennePresente)
    {
        return "-";
    }
    else
    {
        return "X";
    }
}

vector<vector<Maille>> Maille::maillage(Point from, Point to, double largeur, double hauteur)
{
    vector<vector<Maille>> maillage;
    double startLat = from.getLatitude();
    double startLon = from.getLongitude();
    double endLat = to.getLatitude();
    double endLon = to.getLongitude();
    while (startLat > endLat)
    {
        vector<Maille> ligne;
        while (startLon < endLon)
        {
            ligne.push_back(Maille(Point(startLat, startLon, true), largeur, hauteur));
            startLon += 2 * largeur;
        }
        maillage.push_back(ligne);
        startLat -= 2 * hauteur;
        startLon = from.getLongitude();
    }
    return maillage;
}

double Maille::getHauteur()
{
    return d_hauteur;
}

double Maille::getLargeur()
{
    return d_largeur;
}
