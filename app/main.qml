import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 600
    height: 400
    title: "WordSwipe"

    GridView {
        id: gridView
        width: parent.width
        height: parent.height - 50
        cellWidth: width / 2
        cellHeight: height / 3
        model: dataController.foldersModel // Используем FolderModel
        delegate: Item {
            width: gridView.cellWidth
            height: gridView.cellHeight

            Rectangle {
                width: gridView.cellWidth
                height: gridView.cellHeight
                color: "lightgray"
                border.color: "black"
                radius: 5
                Text {
                    anchors.centerIn: parent
                    text: model.name // Используем роль "name" из FolderModel
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        dataController.selectFolder(index);
                        folderDetailsDialog.open();
                    }
                }
            }
        }
    }

    Button {
        text: "Add New Folder"
        width: parent.width
        height: 50
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        onClicked: addFolderDialog.open()
    }

    Dialog {
        id: addFolderDialog
        title: "Add New Folder"
        width: parent.width
        height: parent.height
        modal: true

        Column {
            anchors.fill: parent
            spacing: 20
            padding: 20

            TextField {
                id: folderNameInput
                width: parent.width - 40
                placeholderText: "Enter folder name"
                text: dataController.newFolderName
                onTextChanged: dataController.setNewFolderName(text)
            }

            Row {
                spacing: 10
                width: parent.width - 40

                Button {
                    text: "Add"
                    width: (parent.width - 60) / 2
                    onClicked: {
                        dataController.addFolder(folderNameInput.text)
                        addFolderDialog.close()
                    }
                }

                Button {
                    text: "Cancel"
                    width: (parent.width - 60) / 2
                    onClicked: addFolderDialog.close()
                }
            }
        }
    }

    Dialog {
        id: folderDetailsDialog
        title: "Folder Details"
        width: parent.width
        height: parent.height
        modal: true

        Column {
            anchors.fill: parent
            spacing: 20
            padding: 20

            GridView {
                id: moduleGridView
                width: parent.width
                height: parent.height - 100
                cellWidth: (parent.width - 40) / 2
                cellHeight: (parent.height - 120) / 3
                model: dataController.selectedFolder ? dataController.selectedFolder.modulesModel : null
                delegate: Item {
                    width: moduleGridView.cellWidth
                    height: moduleGridView.cellHeight

                    Rectangle {
                        width: moduleGridView.cellWidth
                        height: moduleGridView.cellHeight
                        color: model.color
                        border.color: "black"
                        radius: 5
                        Text {
                            anchors.centerIn: parent
                            text: model.name
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                // Handle module selection
                            }
                        }
                    }
                }
            }

            Button {
                text: "Add New Module"
                width: parent.width
                height: 50
                onClicked: addModuleDialog.open()
            }

            Button {
                text: "Close"
                width: parent.width
                height: 50
                onClicked: folderDetailsDialog.close()
            }
        }
    }

    Dialog {
        id: addModuleDialog
        title: "Add New Module"
        width: parent.width
        height: parent.height
        modal: true

        Column {
            anchors.fill: parent
            spacing: 20
            padding: 20

            TextField {
                id: moduleNameInput
                width: parent.width - 40
                placeholderText: "Enter module name"
            }

            TextField {
                id: moduleColorInput
                width: parent.width - 40
                placeholderText: "Enter module color"
            }

            Row {
                spacing: 10
                width: parent.width - 40

                Button {
                    text: "Add"
                    width: (parent.width - 60) / 2
                    onClicked: {
                        dataController.addModuleToSelectedFolder(moduleNameInput.text, moduleColorInput.text)
                        addModuleDialog.close()
                    }
                }

                Button {
                    text: "Cancel"
                    width: (parent.width - 60) / 2
                    onClicked: addModuleDialog.close()
                }
            }
        }
    }
}
