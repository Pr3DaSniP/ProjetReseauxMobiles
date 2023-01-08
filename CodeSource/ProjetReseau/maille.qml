import QtQuick 2.0
import QtLocation 5.9
import QtPositioning 5.8
import QtQuick.Controls 2.5

MapPolygon {
    opacity: 0.5
    property var coordinate: {
        latitude: 5
        longitude : 0
    }
    property var id;

    clip: true

    MouseArea {
        anchors.fill: parent
        onClicked: {
            console.log("My id : " + id)
            console.log("My coords are (lat/lon) : " + coordinate.latitude + " " + coordinate.longitude);
        }
    }
}
