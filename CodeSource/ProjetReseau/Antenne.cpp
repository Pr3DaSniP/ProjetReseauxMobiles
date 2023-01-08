#include "Antenne.h"

Antenne::Antenne() : d_position{Point()}, d_puissanceEmission{0}, d_frequence{0}, d_nom{""} {}

Antenne::Antenne(Point position, double puissanceEmission, double frequence, std::string nom) : d_position{position}, d_puissanceEmission{puissanceEmission}, d_frequence{frequence}, d_nom{nom}
{
}

Point Antenne::getPosition() const { return d_position; }

double Antenne::getPuissanceEmission() const { return d_puissanceEmission; }

double Antenne::getFrequence() const { return d_frequence; }

std::string Antenne::getNom() const { return d_nom; }

bool Antenne::chevauchement(const Antenne &a) const
{
	return d_position.distance(a.getPosition()) - (d_puissanceEmission + a.getPuissanceEmission()) <= 0;
}

void Antenne::setPosition(Point position) { d_position = position; }

void Antenne::setPuissanceEmission(double puissanceEmission) { d_puissanceEmission = puissanceEmission; }

void Antenne::setFrequence(double frequence) { d_frequence = frequence; }

void Antenne::setNom(std::string nom) { d_nom = nom; }

std::string Antenne::toString()
{
	return "(" + d_nom + ", " + d_position.toString() + ", " + std::to_string(d_puissanceEmission) + ", " + std::to_string(d_frequence) + ")";
}

QJsonObject Antenne::toJson() const
{
	QJsonObject json;
	json["nom"] = QString::fromStdString(d_nom);
	json["position"] = d_position.toJson();
	json["puissanceEmission"] = d_puissanceEmission;
	json["frequence"] = d_frequence;
	return json;
}

void Antenne::affiche(std::ostream &ost) const
{
	ost << "(" << d_nom << ", " << d_position << ", " << d_puissanceEmission << ", " << d_frequence << ")";
}

void Antenne::lit(std::istream &ist)
{
	char ponctuation;
	std::string nom;
	Point position;
	double puissanceEmission, frequence;

	ist >> ponctuation >> nom >> ponctuation >> position >> ponctuation >> puissanceEmission >> ponctuation >> frequence >> ponctuation;
	if (ist.good())
	{
		d_nom = nom;
		d_position = position;
		d_puissanceEmission = puissanceEmission;
		d_frequence = frequence;
	}
}

std::ostream &operator<<(std::ostream &ost, const Antenne &a)
{
	a.affiche(ost);
	return ost;
}

std::istream &operator>>(std::istream &ist, Antenne &a)
{
	a.lit(ist);
	return ist;
}