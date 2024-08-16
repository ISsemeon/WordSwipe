import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 800
    height: 600
    title: "WordSwipe"

    // Root layout
    Rectangle {
        anchors.fill: parent

        // ListView to show folders
        ListView {
            id: folderListView
            anchors.fill: parent
            model: dataController.foldersModel
            delegate: Item {
                width: folderListView.width
                height: 50

                Rectangle {
                    width: parent.width
                    height: 50
                    color: "lightgrey"
                    border.color: "black"

                    Text {
                        anchors.centerIn: parent
                        text: model.name !== undefined ? model.name : "Default Name"
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            // Handle folder click event
                            dataController.selectFolder(model.index)
                        }
                    }
                }
            }
        }

        Button {
            text: "Add Folder"
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                dataController.addFolder("New Folder")
            }
        }
    }
}
