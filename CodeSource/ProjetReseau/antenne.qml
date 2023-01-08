import QtQuick 2.0
import QtLocation 5.6
import QtPositioning 5.6
import QtQuick.Controls 2.5

MapQuickItem {
    id: antenne
    clip: true
    anchorPoint.x: icon.width * 0.5
    anchorPoint.y: icon.height * 0.8
    sourceItem: Image {
        id: icon
        source: "qrc:/marker.png"
        sourceSize.width: 60
        sourceSize.height: 60
    }

    property var id;
    property var frequence;
    property var puissance;
    property var name;
    property var color;

    ToolTip {
        id: toolTip
        text: textAntenneToolTip()
        delay: 250
        visible: mouseA.containsMouse
    }

    MouseArea {
        id: mouseA
        anchors.fill: parent
        hoverEnabled: true
    }

    function textAntenneToolTip() {
        var str = "L'antenne " + name + " à comme puissance " + puissance;
        if(color !== undefined) {
            str += ", et à comme couleur " + color + ".";
        } else {
            str += ".";
        }
        return  str;
    }
}
