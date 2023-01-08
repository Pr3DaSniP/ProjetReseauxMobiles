import QtQuick 2.12
import QtQuick.Window 2.12
import QtLocation 5.12
import QtPositioning 5.8
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2

ApplicationWindow {
    id: window
    width: 1600
    height: 900
    visible: true
    title: qsTr("Outil d’optimisation des fréquences affectées à des antennes de téléphonie mobile")
    menuBar: MenuBar {
        id: menu
        Menu {
            title: "Fichier"
            MenuItem {
                text: "Importer"
                onTriggered: {
                    fileDialogImport.visible = true;
                }
            }
            MenuSeparator { }
            MenuItem {
                text: "Quitter"
                onTriggered: {
                    Qt.quit();
                }
            }
        }
        Menu {
            title: "Affichage"
            MenuItem {
                text: "Afficher les mailles"
                onTriggered: {
                    for(var i = 0; i < listMailles.length; i++) {
                        listMailles[i].opacity = 0.5;
                    }
                }
            }
            MenuItem {
                text: "Cacher les mailles"
                onTriggered: {
                    for(var i = 0; i < listMailles.length; i++) {
                        listMailles[i].opacity = 0;
                    }
                }
            }
            MenuSeparator { }
            MenuItem {
                text: "Afficher les antennes"
                onTriggered: {
                    for(var i = 0; i < listAntennes.length; i++) {
                        listAntennes[i].opacity = 1;
                    }
                    for(var j = 0; j < listRanges.length; j++) {
                        listRanges[j].opacity = 0.4;
                    }
                    for(var k = 0; k < listAretes.length; k++) {
                        listAretes[k].opacity = 1;
                    }
                }
            }
            MenuItem {
                text: "Cacher les antennes"
                onTriggered: {
                    for(var i = 0; i < listAntennes.length; i++) {
                        listAntennes[i].opacity = 0;
                    }
                    for(var j = 0; j < listRanges.length; j++) {
                        listRanges[j].opacity = 0;
                    }
                    for(var k = 0; k < listAretes.length; k++) {
                        listAretes[k].opacity = 0;
                    }
                }
            }
        }
        Menu {
            title: "Algorithme"
            MenuItem {
                text: "Glouton"
                onTriggered: {
                    gestionnaire.makeGlouton();
                }
            }
            MenuItem {
                text: "Recuit simulé"
                onTriggered: {
                    gestionnaire.makeRS();
                }
            }
        }
    }

    FileDialog {
        id: fileDialogImport
        title: "Veuillez choisir un fichier"
        folder: shortcuts.desktop
        nameFilters: "*.csv"
        onAccepted: {
            gestionnaire.setPath(fileDialogImport.fileUrl);
        }
        onRejected: {
            console.log("Canceled")
        }
    }

    property var listAntennes: []
    property var listMailles: []
    property var listRanges: []
    property var listAretes: []

    Plugin {
        id: mapPlugin
        name: "osm"

        PluginParameter {
            name: "osm.mapping.providersrepository.disabled"
            value: "true"
        }
        PluginParameter {
            name: "osm.mapping.providersrepository.address"
            value: "http://maps-redirect.qt.io/osm/5.6/"
        }
    }

    Map {
        id: map
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(47.746, 7.3384) // Mulhouse
        zoomLevel: 12.5
        gesture.enabled: true
    }

    // Fonction qui créer une antenne à partir de "name", "frequence", "puissance" et "coords"
    function createAntenne(name, frequence, puissance, coords) {
        var component = Qt.createComponent("qrc:/antenne.qml");
        var antenne = component.createObject(window);
        antenne.coordinate = QtPositioning.coordinate(coords.latitude, coords.longitude);
        antenne.id = "antenne_" + name;
        antenne.name = name;
        antenne.frequence = frequence;
        antenne.puissance = puissance;
        return antenne;
    }

    // Fonction qui créer un polygone "maille" à du centre "Centre" et de taille "hauteur" et "largeur"
    function createMaille(centre, hauteur, largeur, i, j) {
        var component = Qt.createComponent("qrc:/maille.qml");
        var HG = QtPositioning.coordinate(
            centre.latitude - hauteur,
            centre.longitude - largeur
        );
        var HD = QtPositioning.coordinate(
            centre.latitude - hauteur,
            centre.longitude + largeur
        );
        var BG = QtPositioning.coordinate(
            centre.latitude + hauteur,
            centre.longitude - largeur
        );
        var BD = QtPositioning.coordinate(
            centre.latitude + hauteur,
            centre.longitude + largeur
        );
        var poly = component.createObject(window);
        poly.id = "maille_" + i  + "_" + j;
        poly.coordinate = centre;
        poly.addCoordinate(HG);
        poly.addCoordinate(HD);
        poly.addCoordinate(BD);
        poly.addCoordinate(BG);
        poly.color = "transparent";
        return poly;
    }

    // Fonction qui créer une grille de maille à partir de "Start", jusqu'à "End" avec une taille de maille "hauteur" et "largeur"
    function maillage(Start, End, Largeur, Hauteur) {
        var StartLatitude = Start.latitude;
        var StartLongitude = Start.longitude;
        var EndLatitude = End.latitude;
        var EndLongitude = End.longitude;
        var hauteur = Hauteur;
        var largeur = Largeur;
        var i = 0, j = 0;
        while(StartLatitude > EndLatitude) {
            while(StartLongitude < EndLongitude) {
                var poly = createMaille(
                    QtPositioning.coordinate(StartLatitude, StartLongitude),
                    hauteur,
                    largeur,
                    j,
                    i
                );
                i++;
                // Décalage du centre de la maille suivante en fonction de la largeur
                StartLongitude += 2*largeur;
                listMailles.push(poly);
                map.addMapItem(poly);
            }
            i = 0;
            j++;
            // Décalage du centre de la maille suivante en fonction de la hauteur
            StartLatitude -= 2*hauteur;
            // Réinitialisation de la longitude
            StartLongitude = Start.longitude;
        }
    }

    // Fonction qui créer et ajoute une antenne à la liste des antennes
    function addAntenne(nom, frequence, puissance, coords) {
        var a = createAntenne(nom, frequence, puissance, QtPositioning.coordinate(coords.latitude, coords.longitude));

        var component = Qt.createComponent("qrc:/rangeAntenne.qml");
        var range = component.createObject(window);
        range.id = "range_" + nom;
        range.center = QtPositioning.coordinate(coords.latitude, coords.longitude);
        range.radius = puissance;
        range.color = "#" + Math.floor(Math.random()*16777215).toString(16);
        map.addMapItem(range);
        listRanges.push(range);
        
        listAntennes.push(a);
        map.addMapItem(a);
    }

    // Fonction qui dit si une maille est couverte par une antenne
    function squareIsCoveredByCircle(circle, square) {
        var distance = Math.sqrt(
            Math.pow(circle.center.latitude - square.coordinate.latitude, 2) +
            Math.pow(circle.center.longitude - square.coordinate.longitude, 2)
        );
        var radius = circle.radius / 80000; // C'est un chiffre magique choisi arbitrairement
        if(distance < radius) {
            return true;
        }
        return false;
    }

    // Colorie les mailles en fonction des antennes qui les couvrent
    function colorierMailles() {
        for(var i = 0; i < listMailles.length; i++) {
            var maille = listMailles[i];
            var couverte = false;
            for(var j = 0; j < listRanges.length; j++) {
                var range = listRanges[j];
                if(squareIsCoveredByCircle(range, maille)) {
                    couverte = true;
                    maille.color = range.color;
                    break;
                }
            }
            if(!couverte) {
                maille.color = "lightgrey";
            }
        }
    }

    // Fonction qui charge un graphe depuis un fichier JSON
    function loadGrapheQML(grapheJson) {
        nettoyer();
        for(var i = 0; i < grapheJson.sommets.length; i++) {
            var sommet = grapheJson.sommets[i];
            var id = sommet.id;
            var antenne = sommet.antenne
            var nom = antenne.nom;
            var position = antenne.position;

            var lat = position.latitude;
            var lon = position.longitude;

            var puissance = antenne.puissanceEmission;
            var frequence = antenne.frequence;

            var voisins = sommet.voisins;

            // Connecter l'antenne à ses voisins
            for(var j = 0; j < voisins.length; j++) {
                var component = Qt.createComponent("qrc:/arete.qml");
                var arete = component.createObject(window);
                arete.id = "arete_" + id + "_" + voisins[j];
                arete.addCoordinate(QtPositioning.coordinate(lat, lon));
                arete.addCoordinate(
                 QtPositioning.coordinate(voisins[j].latitude, voisins[j].longitude)
                );
                listAretes.push(arete);
                // map.addMapItem(arete);
            }
            addAntenne(nom, frequence, puissance, QtPositioning.coordinate(lat, lon));
        }
        colorierMailles();
    }

    function nettoyer() {
        for(var i = 0; i < listAntennes.length; i++) {
            map.removeMapItem(listAntennes[i]);
        }
        for(var j = 0; j < listAretes.length; j++) {
            map.removeMapItem(listAretes[j]);
        }
        for(var k = 0; k < listRanges.length; k++) {
            map.removeMapItem(listRanges[k]);
        }
        listAntennes = [];
        listAretes = [];
        listRanges = [];
    }

    // Fonction qui colorie les antennes de leur couleur de couverture
    function colorierAntennes(grapheJson, nomAlgorithm, time) {
        console.log(time);
        var couleurs = [];
        for(var i = 0; i < grapheJson.sommets.length; i++) {
            var sommet = grapheJson.sommets[i];
            couleurs.push(sommet.couleur);
        }
        // Supprimer les doublons de couleurs
        var couleursUniqueID = [];
        for(var j = 0; j < couleurs.length; j++) {
            if(couleursUniqueID.indexOf(couleurs[j]) === -1) {
                couleursUniqueID.push(couleurs[j]);
            }
        }
        // Créer une couleur par ID
        var couleursUnique = [];
        for(var k = 0; k < couleursUniqueID.length; k++) {
            couleursUnique.push("#" + Math.floor(Math.random()*16777215).toString(16));
        }
        // Colorier les antennes
        // Si l'antenne a la couleur "1", alors elle prend la couleur "couleursUnique[0]"
        for(var l = 0; l < grapheJson.sommets.length; l++) {
            var couleurAntenne = grapheJson.sommets[l].couleur - 1;
            var nomAntenne = grapheJson.sommets[l].antenne.nom;
            for(var m = 0; m < listAntennes.length; m++) {
                if(listAntennes[m].name === nomAntenne) {
                    listAntennes[m].color = couleursUnique[couleurAntenne];
                    listRanges[m].color = couleursUnique[couleurAntenne];
                }
            }
        }
        colorierMailles();

        showDialogRes(couleursUnique.length, nomAlgorithm, time);
    }

    function showDialogRes(resultatAlgorithm, nomAlgorithm, time) {
        var component = Qt.createComponent("qrc:/resultatDialog.qml");
        var dialog = component.createObject(window);
        dialog.resultatAlgorithm = resultatAlgorithm;
        dialog.nomAlgorithm = nomAlgorithm;
        dialog.time = time;
        dialog.visible = true;
    }
}
