#ifndef GESTIONNAIRE_H
#define GESTIONNAIRE_H

#include <QObject>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include "Graphe.h"
#include "Sommet.h"
#include "Antenne.h"
#include "Point.h"

#include <QVariant>

#include <chrono>

using std::ifstream;
using std::istringstream;
using std::vector;
using std::chrono::high_resolution_clock;

class gestionnaire : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString path WRITE setPath)
public:
    gestionnaire(QObject *parent = 0);

    Q_INVOKABLE void setPath(const QString &path);

    Q_INVOKABLE void makeGlouton();

    Q_INVOKABLE void makeRS();

    void setObj(QObject *obj);

private:
    void loadGraphe();

    Graphe *d_graphe;
    int d_nbSommets;
    int d_degre;
    QObject *d_obj;
    QString d_path;
};

#endif // GESTIONNAIRE_H
