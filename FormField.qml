import QtQuick 2.0
import QtQuick.Controls 2.0

Rectangle {
    id: formFieldRoot
    width: parent.width
    height: 50
    property string text: "default"
    property string fieldText: "NULL"
    property color _color: "white"
    color: _color
    Column{
        Text {
            id: name
            height: 15
            text: formFieldRoot.text
            width: formFieldRoot.width
            font.pointSize: 12

        }


        TextField{
            id: field
            height: 30
            width: formFieldRoot.width
            text: formFieldRoot.fieldText
            font.pointSize: 10
        }
    }



}
