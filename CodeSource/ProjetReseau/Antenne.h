#ifndef ANTENNE_H
#define ANTENNE_H

#include <QJsonObject>
#include "Point.h"

class Antenne
{
private:
	Point d_position;			// position de l'antenne en Lambert93
	double d_puissanceEmission; // en metre
	double d_frequence;
	std::string d_nom;

public:
	Antenne();
	Antenne(Point position, double puissanceEmission, double frequence, std::string nom);

	Point getPosition() const;
	double getPuissanceEmission() const;
	double getFrequence() const;
	std::string getNom() const;

	bool chevauchement(const Antenne &a) const;

	void setPosition(Point position);
	void setPuissanceEmission(double puissanceEmission);
	void setFrequence(double frequence);
	void setNom(std::string nom);

	std::string toString();

	QJsonObject toJson() const;

	// Affiche l'antenne sous la forme Nom, position, puissance d'emission, frequence sur le flot de sortie ost
	void affiche(std::ostream &ost) const;

	// Lit le point sous la forme Nom, position, puissance d'emission, frequence sur le flot d'entree ist
	void lit(std::istream &ist);
};

std::ostream &operator<<(std::ostream &ost, const Antenne &a);
std::istream &operator>>(std::istream &ist, Antenne &a);

#endif // !ANTENNE_H
