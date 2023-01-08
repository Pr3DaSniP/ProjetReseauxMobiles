import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 2.5

// Résultat de la coloration du graphe

Window {
    id: resultatWindow
    width: 400
    height: 400
    visible: false
    title: qsTr("Résultat de la coloration du graphe")

    property var resultatAlgorithm;
    property var nomAlgorithm;
    property var time;

    Rectangle {
        id: rectangle
        anchors.fill: parent
        color: "white"

        Column {
            // Titre de la fenêtre puis la ligne des boutons
            id: column
            anchors.fill: parent
            spacing: 10

            Text {
                id: titre
                anchors.centerIn: parent
                text: qsTr("Résultat de la coloration du graphe")
                font.bold: true
                font.pixelSize: 15
            }

            Text {
                id: text
                anchors.top: titre.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Algorithme utilisé : ") + nomAlgorithm
                font.pixelSize: 15
            }

            Text {
                id: text2
                anchors.top: text.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Nombre de couleurs utilisées : ") + resultatAlgorithm
                font.pixelSize: 15
            }

            Text {
                id: text3
                anchors.top: text2.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Temps d'exécution : ") + time + qsTr(" ms")
                font.pixelSize: 15
            }

            Row {
                id: row
                anchors.top: text3.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 10
                Button {
                    id: button
                    text: qsTr("Fermer")
                    onClicked: {
                        resultatWindow.visible = false
                    }
                }
            }
        }
    }
}
