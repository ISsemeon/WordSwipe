import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs
import Qt.labs.platform

ApplicationWindow {
    visible: true
    width: 600
    height: 400
    title: "WordSwipe"

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: mainPage
    }

    Component {
        id: mainPage
        Item {
            width: parent.width
            height: parent.height

            GridView {
                id: gridView
                width: parent.width
                height: parent.height - 50
                cellWidth: width / 2
                cellHeight: height / 3
                model: dataController.foldersModel
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
                            text: model.name
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                dataController.selectFolder(index)
                                stackView.push(folderDetailsPage)
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
                onClicked: stackView.push(addFolderPage)
            }
        }
    }

    Component {
        id: addFolderPage
        Item {
            width: parent.width
            height: parent.height

            Rectangle {
                width: parent.width
                height: parent.height
                color: "white"
                border.color: "black"
                radius: 10

                ColumnLayout {
                    spacing: 20
                    anchors.margins: 20

                    TextField {
                        id: folderNameInput
                        Layout.fillWidth: true
                        placeholderText: "Enter folder name"
                        text: dataController.newFolderName
                        onTextChanged: dataController.setNewFolderName(text)
                    }

                    RowLayout {
                        spacing: 20

                        Button {
                            text: "Add"
                            width: (parent.width - 40) / 2
                            onClicked: {
                                dataController.addFolder(folderNameInput.text)
                                stackView.pop()
                            }
                        }

                        Button {
                            text: "Cancel"
                            width: (parent.width - 40) / 2
                            onClicked: stackView.pop()
                        }
                    }
                }
            }
        }
    }

    Component {
        id: folderDetailsPage
        Item {
            anchors.fill: parent

            ColumnLayout {
                anchors.fill: parent
                spacing: 20
                anchors.margins: 20

                Text {
                    id: selectedFolderName
                    text: dataController.selectedFolder ? dataController.selectedFolder.name : "No Folder Selected"
                    font.pixelSize: 24
                    Layout.alignment: Qt.AlignHCenter
                }

                GridView {
                    id: modulesGridView
                    width: parent.width
                    height: parent.height - 100
                    cellWidth: (parent.width - 40) / 2
                    cellHeight: (parent.height - 120) / 3
                    model: dataController.selectedFolder ? dataController.selectedFolder.modulesModel : null
                    delegate: Item {
                        width: modulesGridView.cellWidth
                        height: modulesGridView.cellHeight

                        Rectangle {
                            width: modulesGridView.cellWidth
                            height: modulesGridView.cellHeight
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
                                    // Обновляем выбранный модуль в dataController
                                    dataController.selectModule(index);
                                }
                            }
                        }
                    }
                }

                RowLayout {
                    spacing: 20

                    Button {
                        text: "Add New Module"
                        width: (parent.width - 40) / 2
                        onClicked: stackView.push(addModulePage)
                    }

                    Button {
                        text: "Close"
                        width: (parent.width - 40) / 2
                        onClicked: stackView.pop()
                    }
                }
            }
        }
    }

    Component {
        id: addModulePage
        Item {
            width: parent.width
            height: parent.height

            Rectangle {
                width: parent.width
                height: parent.height
                color: "white"
                border.color: "black"
                radius: 10

                ColumnLayout {
                    spacing: 20
                    anchors.margins: 20

                    TextField {
                        id: moduleNameInput
                        Layout.fillWidth: true
                        placeholderText: "Enter module name"
                    }

                    RowLayout {
                        spacing: 10

                        Rectangle {
                            id: colorPreview
                            width: 50
                            height: 50
                            color: moduleColorInput.text != "" ? moduleColorInput.text : "lightgray"
                            border.color: "black"
                            radius: 5
                        }

                        Button {
                            text: "Choose Color"
                            Layout.fillWidth: true
                            onClicked: colorDialog.open()
                        }
                    }

                    RowLayout {
                        spacing: 20

                        Button {
                            text: "Add"
                            width: (parent.width - 40) / 2
                            onClicked: {
                                dataController.addModuleToSelectedFolder(moduleNameInput.text, moduleColorInput.text)
                                stackView.pop()
                            }
                        }

                        Button {
                            text: "Cancel"
                            width: (parent.width - 40) / 2
                            onClicked: stackView.pop()
                        }
                    }
                }
            }

            ColorDialog {
                id: colorDialog
                onAccepted: {
                    moduleColorInput.text = colorDialog.color.toString();  // Преобразуем QColor в строку
                    colorPreview.color = colorDialog.color;  // Устанавливаем цвет в preview
                }
            }

            TextField {
                id: moduleColorInput
                visible: false  // Скрыт, так как теперь используется диалог выбора цвета
            }
        }
    }

}
