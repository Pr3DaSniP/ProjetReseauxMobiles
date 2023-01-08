#include "Point.h"

#define _USE_MATH_DEFINES
#include <math.h>

Point::Point() : d_latitude{0}, d_longitude{0}, d_lambert_lat{0}, d_lambert_lon{0} {}

Point::Point(double lat, double lon, bool lambert) {
    if (lambert) {
        d_lambert_lat = lat;
        d_lambert_lon = lon;
        convertToWGS84();
    }
    else {
        d_latitude = lat;
        d_longitude = lon;
        convertToLambert93();
    }
}

void Point::convertToLambert93() {
    // définition des constantes
    double c = 11754255.426096; //constante de la projection
    double e = 0.0818191910428158; //première exentricité de l'ellipsoïde
    double n = 0.725607765053267; //exposant de la projection
    double xs = 700000; //coordonnées en projection du pole
    double ys = 12655612.049876; //coordonnées en projection du pole

    // pré-calculs
    double lat_rad = d_latitude / 180 * M_PI; //latitude en rad
    double lat_iso = atanh(sin(lat_rad)) - e * atanh(e * sin(lat_rad)); //latitude isométrique

    //calcul
    d_lambert_lat = ((c * exp(-n * (lat_iso))) * sin(n * (d_longitude - 3) / 180 * M_PI) + xs);
    d_lambert_lon = (ys - (c * exp(-n * (lat_iso))) * cos(n * (d_longitude - 3) / 180 * M_PI));
}

void Point::convertToWGS84()
{
    // Definition des constantes
    double c = 11754255.426096;    // constante de la projection
    double e = 0.0818191910428158; // premi�re exentricit� de l'ellipso�de
    double n = 0.725607765053267;  // exposant de la projection
    double xs = 700000;            // coordonn�es en projection du pole
    double ys = 12655612.049876;   // coordonn�es en projection du pole

    // pr�-calcul
    double a = (log(c / (sqrt(pow((d_lambert_lat - xs), 2) + pow((d_lambert_lon - ys), 2)))) / n);

    // calcul
    d_longitude = ((atan(-(d_lambert_lat - xs) / (d_lambert_lon - ys))) / n + static_cast<double>(3) / 180 * M_PI) / M_PI * 180;
    d_latitude = asin(tanh((log(c / sqrt(pow((d_lambert_lat - xs), 2) + pow((d_lambert_lon - ys), 2))) / n) + e * atanh(e * (tanh(a + e * atanh(e * (tanh(a + e * atanh(e * (tanh(a + e * atanh(e * (tanh(a + e * atanh(e * (tanh(a + e * atanh(e * (tanh(a + e * atanh(e * sin(1)))))))))))))))))))))) / M_PI * 180;
}

double Point::getLatitude() { return d_latitude; }

double Point::getLongitude() { return d_longitude; }

double Point::getLambertLatitude() { return d_lambert_lat; }

// Coordonnee Y
double Point::getLambertLongitude() { return d_lambert_lon; }

void Point::setLatitude(double lat) { d_latitude = lat; }

void Point::setLongitude(double lon) { d_longitude = lon; }

void Point::setLambertLatitude(double lambert_lat) { d_lambert_lat = lambert_lat; }

void Point::setLambertLongitude(double lambert_lon) { d_lambert_lon = lambert_lon; }

double Point::distance(const Point &p) const
{
    double dx = p.d_lambert_lat - d_lambert_lat, dy = p.d_lambert_lon - d_lambert_lon;
    return std::sqrt(dx * dx + dy * dy);
}

std::string Point::toString() { return "(" + std::to_string(d_lambert_lat) + ", " + std::to_string(d_lambert_lon) + ")"; }

QJsonObject Point::toJson() const
{
    QJsonObject json;
    json["latitude"] = d_latitude;
    json["longitude"] = d_longitude;
    json["lambert_latitude"] = d_lambert_lat;
    json["lambert_longitude"] = d_lambert_lon;
    return json;
}

void Point::affiche(std::ostream &ost) const
{
    ost << "{" << d_lambert_lat << ", " << d_lambert_lon << "}";
}

void Point::lit(std::istream &ist)
{
    char ponctuation;
    double x, y;

    ist >> ponctuation >> x >> ponctuation >> y >> ponctuation;
    if (ist.good())
    {
        d_lambert_lat = x;
        d_lambert_lon = y;
    }
    convertToWGS84();
}

std::ostream &operator<<(std::ostream &ost, const Point &p)
{
    p.affiche(ost);
    return ost;
}

std::istream &operator>>(std::istream &ist, Point &p)
{
    p.lit(ist);
    return ist;
}
