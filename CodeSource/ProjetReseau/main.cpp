#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QGeoCoordinate>
#include <QQmlComponent>
#include <QQuickStyle>

#include <QJsonObject>
#include <QQmlContext>

#include "gestionnaire.h"
#include "Sommet.h"
#include "Graphe.h"
#include "maille.h"
#include <vector>

using namespace std;

void mailleToQML(QObject *object, vector<vector<Maille>> m, Point from, Point to)
{
    QGeoCoordinate fromQML = QGeoCoordinate(from.getLatitude(), from.getLongitude());
    QGeoCoordinate toQML = QGeoCoordinate(to.getLatitude(), to.getLongitude());

    double largeur = m[0][0].getLargeur();
    double hauteur = m[0][0].getHauteur();

    QMetaObject::invokeMethod(object, "maillage",
                              Q_ARG(QVariant, QVariant::fromValue(fromQML)),
                              Q_ARG(QVariant, QVariant::fromValue(toQML)),
                              Q_ARG(QVariant, QVariant::fromValue(largeur)),
                              Q_ARG(QVariant, QVariant::fromValue(hauteur)));
}

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    QQuickStyle::setStyle("Material");
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QQmlComponent compo(&engine, url);
    QObject *obj = compo.create();

    gestionnaire *gen = new gestionnaire();
    gen->setObj(obj);
    engine.rootContext()->setContextProperty("gestionnaire", gen);

    Point from(47.79492422118306, 7.2622273477610975, false);
    Point to(47.70439892452686, 7.429003827996382, false);

    double hauteur = 0.0028; // 280m
    double largeur = 0.004;  // 400m

    vector<vector<Maille>> m = Maille::maillage(from, to, largeur, hauteur);

    mailleToQML(obj, m, from, to);

    return app.exec();
}
