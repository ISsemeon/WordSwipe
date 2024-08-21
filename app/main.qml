import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs
import Qt.labs.platform

ApplicationWindow {
    visible: true
    width: 450
    height: 800
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
                            font.pixelSize: 16
                            font.bold: true
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
    id: moduleDetailsPage
    Item {
        width: parent.width
        height: parent.height

       ListView {
    id: cardListView
    width: parent.width
    height: parent.height - 50
    model: dataController.selectedModule ? dataController.selectedModule.cardsModel : null
    delegate: Item {
        width: cardListView.width
        height: 120

        Rectangle {
            width: parent.width
            height: 120
            color: "lightgray"
            border.color: "black"
            radius: 5

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 10

                TextField {
                    id: questionField
                    text: model.question
                    font.pixelSize: 18
                    color: "black"
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    onTextChanged: model.question = questionField.text
                }

                TextField {
                    id: answerField
                    text: model.answer
                    font.pixelSize: 16
                    color: "black"
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    onTextChanged: model.answer = answerField.text
                }
            }
        }
    }
}

        Button {
            text: "Add Card"
            width: parent.width
            height: 50
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                dataController.selectedModule.addCard("New Question", "New Answer")
            }
        }
    }
}

    Component {
        id: folderDetailsPage
        Item {
            width: parent.width
            height: parent.height

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
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    cellWidth: (parent.width - 20) / 2
                    cellHeight: (parent.height - 80) / 3
                    model: dataController.selectedFolder ? dataController.selectedFolder.modulesModel : null
                    clip: true

                    delegate: Item {
                        width: modulesGridView.cellWidth
                        height: modulesGridView.cellHeight

                        Rectangle {
                            width: parent.width - 5
                            height: parent.height - 5
                            radius: 5
                            border.color: "black"
                            border.width: 2

                            // Эффект тени
                            Rectangle {
                                width: parent.width
                                height: parent.height
                                color: "black"
                                radius: 5
                                opacity: 0.4
                                anchors.left: parent.left
                                anchors.top: parent.top
                                anchors.leftMargin: 3
                                anchors.topMargin: 3
                                z: -1
                            }

                            // Эффект матового стекла
                            Rectangle {
                                anchors.fill: moduleDel
                                anchors.margins: 5
                                color: "black"  // Белый фон для имитации стеклянного эффекта
                                radius: 5
                                border.color: "black"
                                opacity: 0.1  // Настройка степени матовости
                                z:1
                            }

                            // Основной контент
                            Rectangle {
                                id: moduleDel
                                width: parent.width
                                height: parent.height
                                color: model.color
                                border.color: "black"
                                border.width: 2
                                radius: 5

                                // Текст
                                Text {
                                    id: textItem
                                    anchors.fill: parent
                                    anchors.margins: 10
                                    text: model.name
                                    font.pixelSize: 0
                                    font.bold: true
                                    horizontalAlignment: Text.AlignHCenter
                                    verticalAlignment: Text.AlignVCenter
                                    elide: Text.ElideRight
                                    wrapMode: Text.Wrap
                                    // Вычисление динамического размера шрифта
                                    onTextChanged: {
                                        var maxFontSize = 24;
                                        var minFontSize = 10;
                                        var fontSizeStep = 2;

                                        textItem.font.pixelSize = maxFontSize;
                                        var lines = textMetrics.lineCount;

                                        while (lines > 3 && textItem.font.pixelSize > minFontSize) {
                                            textItem.font.pixelSize -= fontSizeStep;
                                            lines = textMetrics.lineCount;
                                        }
                                    }
                                }

                                TextMetrics {
                                    id: textMetrics
                                    font: textItem.font
                                    text: textItem.text
                                }

                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: {
                                        onClicked: {
                                            dataController.selectModule(index);
                                            stackView.push(moduleDetailsPage);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                RowLayout {
                    spacing: 20
                    Layout.alignment: Qt.AlignBottom
                    Layout.fillWidth: true

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

                    ColumnLayout {
                        spacing: 10

                        Rectangle {
                            id: colorPreview
                            width: 50
                            height: 50
                            color: moduleColorInput.text !== "" ? moduleColorInput.text : "lightgray"
                            border.color: "black"
                            radius: 5

                            MouseArea {
                                anchors.fill: parent
                                onClicked: colorDialog.open()
                            }
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
                    moduleColorInput.text = colorDialog.color.toString();
                    colorPreview.color = colorDialog.color;
                }
            }

            TextField {
                id: moduleColorInput
                visible: false
            }
        }
    }
}
