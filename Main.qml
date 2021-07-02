import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.0
 import QtQml 2.12
Rectangle {
    id: _root
    visible: true
    property color _rootColor: "white"
    color: _rootColor
    Component.onDestruction: {
        VideoStreamer.disconnectFromserver();
    }

    Rectangle{
        id: windowTop
        width: parent.width
        height: parent.height/5

        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.bottomMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10

        color: _root._rootColor
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
        anchors.verticalCenterOffset: -31

        anchors.top:  windowTop.bottom
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
        color: _root._rootColor

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
            color: "red"
        }

        Button{
            text: "Connect";
            onClicked: {
                VideoStreamer.connectToServer();
            }
            background: Rectangle {
                border.color: "black"
                color: "#f7d76a"
            }
            anchors.top: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 10
            height: 40
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
        id: streamer
        target: VideoStreamer

    }

    Connections{
        target: liveImageProvider
        onImageChanged:{
            opencvImage.framespersecond++
            opencvImage.reload()
        }
    }
}
