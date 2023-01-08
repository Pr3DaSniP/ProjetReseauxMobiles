#ifndef POINT_H
#define POINT_H

#include <string>
#include <iostream>

#include <QJsonObject>

class Point
{
private:
	double d_latitude;	// Latitude
	double d_longitude; // Longitude

	double d_lambert_lat; // Lambert latitude
	double d_lambert_lon; // Lambert longitude

	// https://georezo.net/forum/viewtopic.php?id=94465
	void convertToWGS84();
    void convertToLambert93();

public:
	Point();
    Point(double lat, double lon, bool lambert);

	// Coordonnee WGS84 X
	double getLatitude();

	// Coordonnee WGS84 Y
	double getLongitude();

	// Coordonnee Lambert X
	double getLambertLatitude();

	// Coordonnee Lambert Y
	double getLambertLongitude();

	void setLatitude(double lat);
	void setLongitude(double lon);

	void setLambertLatitude(double lat);
	void setLambertLongitude(double lon);

	double distance(const Point &p) const;

	QJsonObject toJson() const;

	// Affiche le point sous la forme (x,y) sur le flot de sortie ost
	void affiche(std::ostream &ost) const;

	// Lit le point sous la forme (x,y) sur le flot d'entree ist
	void lit(std::istream &ist);

	std::string toString();
};

std::ostream &operator<<(std::ostream &ost, const Point &p);
std::istream &operator>>(std::istream &ist, Point &p);

#endif // !POINT_H
