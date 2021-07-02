import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.0
import QtQuick.Scene3D 2.0
import QtQuick.Extras 1.4
import QtQuick.Controls 2.12
import QtQml 2.12
import QtQuick.Layouts 1.12
import "./" as MyComponents

ApplicationWindow{
    title: qsTr("Home Page")
    visible: true

    height: 732
    width: 422
    property color bannerColor: "#fbeba1"

    Rectangle{
        id: _root
        anchors.fill: parent

        Rectangle{
            id: banner
            width: parent.width
            height: parent.height / 15
            color: bannerColor

            Button{
                id: backBtn
                text: "<"
                font.pointSize: 10
                width: 40
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.top: parent.top
                anchors.topMargin: 10
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                background: Rectangle {
                    border.color: "black"
                    color: "#f7d76a"
                }

                onClicked: {
                    stack.pop()
                }

            }
        }

        Rectangle{
            id: pageArea
            width: parent.width
            height: (parent.height*13)/15
            anchors.top: banner.bottom
            anchors.bottom: footer.top
            color: "light yellow"

            StackView {
                id: stack
                initialItem: mainView
                anchors.fill: parent
                clip: false
            }

            Component {
               id: mainView

               Column {
                   spacing: 40

                   Text{
                       text: "Derma App"
                       anchors.horizontalCenter: parent.horizontalCenter
                       font.family: "Helvetica"
                       font.pointSize: 30
                       color: "black"
                   }

                   Button {
                       text: "Add Patient"
                       anchors.horizontalCenter: parent.horizontalCenter
                       onClicked: stack.push(addPatientPage)
                       background: Rectangle {
                           border.color: "black"
                           color: "#f7d76a"
                       }
                   }
                   Button {
                       text: "Search"
                       anchors.horizontalCenter: parent.horizontalCenter
                       background: Rectangle {
                           border.color: "black"
                           color: "#f7d76a"
                       }
//                       enabled: stack.depth > 1
//                       onClicked: stack.pop()
                   }
                   Button {
                       anchors.horizontalCenter: parent.horizontalCenter
                       background: Rectangle {
                           border.color: "black"
                           color: "#f7d76a"
                       }
                       text: "Camera"
                       onClicked: stack.push(camera)
                   }
               }
           }

            Component{
                id: addPatientPage

                Rectangle{
                    id: addPatientPageRect
                    Component.onCompleted:{
                        anchors.left = parent.left
                        anchors.right = parent.right
                        anchors.leftMargin = 40
                        anchors.rightMargin = 40
                    }

                    width: parent.width
                    height: parent.height
                    property color addPatientPageColor: "light yellow"
                    color: addPatientPageColor

                    Column{
                        spacing: 20

                        Rectangle{
                            width: heading.width
                            height: heading.height/2
                            color: addPatientPageColor
                        }

                        Text{
                            id: heading
                            text: "Patient Information"
                            font.family: "Helvetica"
                            font.pointSize: 20
                            color: "black"
                            height: 20
                            width: addPatientPageRect.width-80
                        }

                        Rectangle{
                            width: heading.width
                            height: heading.height
                            color: addPatientPageColor
                        }


                        MyComponents.FormField{
                            id: field1
                            _color: addPatientPageColor
                            text: "Name"
                            fieldText: ""
                        }

                        MyComponents.FormField{
                            id: field2
                            text: "Address"
                            _color: addPatientPageColor
                            fieldText: ""
                        }
                    }
                }



            }

            Component{
                id: camera
                MyComponents.Main{
                    _rootColor: "light yellow"
                }
            }

        }

        Rectangle{
            id: footer
            width: parent.width
            anchors.bottom: _root.bottom
            height: parent.height / 15
            color: bannerColor
        }
    }

}

/*##^##
Designer {
    D{i:0;height:732;width:422}
}
##^##*/
