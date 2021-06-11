import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.0

Window {
    visible: true
    title: qsTr("Hello World")

    Rectangle{
        id: windowTop
        width: parent.width
        anchors.top: parent.top
        anchors.bottom: imageRect.top
        Text {
            id: appName
            text: qsTr("Derma App")
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            font.family: "Helvetica"
            font.pointSize: 27
            color: "black"
        }
    }

    Rectangle{
        id: imageRect
        width: parent.width - 20;
        height: width
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        Image{
            id: opencvImage
            anchors.fill: parent
            property bool counter: false
            property int framespersecond: 0
            source: "image://live/image"
            cache: false
            function reload(){
                counter = !counter
                source = "image://live/image?id=" + counter
            }
        }
        Text {
            id: fps
            text: qsTr("0")
            anchors.top: parent.top
            anchors.right: parent.right
            font.family: "Helvetica"
            font.pointSize: 24
            color: "green"
        }

        Timer {
            interval: 1000; running: true; repeat: true
            onTriggered: {
                fps.text = opencvImage.framespersecond
                opencvImage.framespersecond = 0
            }
        }
    }

    Connections{
        target: liveImageProvider
        onImageChanged:{
            opencvImage.framespersecond++
            opencvImage.reload()
        }
    }
}
