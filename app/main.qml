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

    Component
    {
        id: mainPage
        Item
        {
            width: parent.width
            height: parent.height

            ColumnLayout
            {
                anchors.fill: parent
                anchors.margins: 20

                Button
                {
                    text: "New Folder"
                    width: parent.width
                    onClicked: stackView.push(addFolderPage)
                    Layout.preferredHeight: 50
                    Layout.fillWidth: true
                }


                GridView {
                    id: gridView
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    cellWidth: (parent.width ) / 2
                    cellHeight: (parent.height ) / 3

                    model: dataController.foldersModel

                    delegate: Item {
                        width: gridView.cellWidth
                        height: gridView.cellHeight

                        Rectangle {
                            width: gridView.cellWidth
                            height: gridView.cellHeight
                            color: "lightgray"
                            border.color: "black"
                            border.width: 2
                            radius: 5
                            Text {
                                id: moduleText2
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

                                    moduleText2.font.pixelSize = maxFontSize;
                                    var lines = textMetrics2.lineCount;

                                    while (lines > 3 && moduleText2.font.pixelSize > minFontSize) {
                                        moduleText2.font.pixelSize -= fontSizeStep;
                                        lines = textMetrics2.lineCount;
                                    }
                                }
                            }
                            TextMetrics {
                                id: textMetrics2
                                font: moduleText2.font
                                text: moduleText2.text
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

            }

        }
    }

    Component {
        id: addFolderPage
        Item {
            width: parent.width
            height: parent.height

            Rectangle {
                anchors.fill: parent
                color: "white"
                border.color: "black"
                radius: 10
                anchors.margins: 10

                ColumnLayout {
                    spacing: 20
                    anchors.fill: parent
                    anchors.margins: 10

                    RowLayout {
                        spacing: 20
                        Layout.fillWidth: true


                        Button {
                            text: "Add New"

                            Layout.fillWidth: true
                            Layout.preferredHeight: 50
                            onClicked: {
                                dataController.addFolder(folderNameInput.text)
                                stackView.pop()
                            }
                        }

                        Button {
                            text: "Cancel"
                            Layout.fillWidth: true
                            Layout.preferredHeight: 50
                            onClicked: stackView.pop()
                        }
                    }

                    TextField {
                        id: folderNameInput
                        Layout.fillWidth: true
                        Layout.preferredHeight: 90
                        placeholderText: "Enter folder name"
                        text: dataController.newFolderName
                        onTextChanged: dataController.setNewFolderName(text)
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

            ColumnLayout
            {
                anchors.fill: parent
                anchors.margins: 10
                RowLayout {
                    spacing: 20
                    Layout.fillWidth: true

                    Button {
                        text: "Add"
                        Layout.preferredHeight: 50
                        Layout.fillWidth: true
                        onClicked: {
                            dataController.selectedModule.addCard("", "")
                        }
                    }
                    Button {
                        text: "Study"
                        Layout.preferredHeight: 50
                        Layout.fillWidth: true
                        onClicked: {}
                    }
                    Button {
                        text: "Back"
                        Layout.preferredHeight: 50
                        Layout.fillWidth: true
                        onClicked: stackView.pop()
                    }
                }
                RowLayout {
                    spacing: 20
                    Layout.fillWidth: true
                    Button {
                        text: "Import"
                        Layout.preferredHeight: 50
                        Layout.fillWidth: true
                        onClicked: {}
                    }
                    Button {
                        text: "Export"
                        Layout.preferredHeight: 50
                        Layout.fillWidth: true
                        onClicked: {}
                    }
                }

                ListView {
                    id: cardListView
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    layoutDirection: Qt.TopToBottom
                    spacing: 5
                    clip:true
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
                                    placeholderText: qsTr("Word")
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
                                    placeholderText: qsTr("Translation")
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
                    id: folderNameText
                    text: dataController.selectedFolder ? dataController.selectedFolder.name : "No Folder Selected"
                    font.pixelSize: 26
                    font.bold: true
                    Layout.alignment: Qt.AlignHCenter
                }
                RowLayout {
                    Layout.fillWidth: true

                    Button {
                        text: "Add"
                        Layout.preferredHeight: 50
                        Layout.fillWidth: true
                        onClicked: stackView.push(addModulePage)
                    }
                    Button {
                        text: "Study"
                        Layout.preferredHeight: 50
                        Layout.fillWidth: true
                        onClicked:
                        {}
                    }
                    Button {
                        text: "Export"
                        Layout.preferredHeight: 50
                        Layout.fillWidth: true
                        onClicked:
                        {}
                    }
                    Button {
                        text: "Import"
                        Layout.preferredHeight: 50
                        Layout.fillWidth: true
                        onClicked:
                        {}
                    }

                    Button {
                        text: "Back"

                        Layout.preferredHeight: 50
                        Layout.fillWidth: true
                        onClicked: stackView.pop()
                    }
                }

                GridView {
                    id: modulesGridView
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    cellWidth: (parent.width ) / 2
                    cellHeight: (parent.height ) / 3
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
                                anchors.fill: parent
                                anchors.margins: 5
                                color: "white"
                                radius: 5
                                border.color: "black"
                                opacity: 0.1
                            }

                            // Основной контент
                            Rectangle {
                                id: moduleContent
                                width: parent.width
                                height: parent.height
                                color: model.color
                                border.color: "black"
                                border.width: 2
                                radius: 5

                                Text {
                                    id: moduleText
                                    anchors.fill: parent
                                    anchors.margins: 10
                                    text: model.name
                                    font.pixelSize: 0
                                    font.bold: true
                                    horizontalAlignment: Text.AlignHCenter
                                    verticalAlignment: Text.AlignVCenter
                                    elide: Text.ElideRight
                                    wrapMode: Text.Wrap

                                    onTextChanged: {
                                        var maxFontSize = 24;
                                        var minFontSize = 10;
                                        var fontSizeStep = 2;

                                        moduleText.font.pixelSize = maxFontSize;
                                        var lines = textMetrics.lineCount;

                                        while (lines > 3 && moduleText.font.pixelSize > minFontSize) {
                                            moduleText.font.pixelSize -= fontSizeStep;
                                            lines = textMetrics.lineCount;
                                        }
                                    }
                                }

                                TextMetrics {
                                    id: textMetrics
                                    font: moduleText.font
                                    text: moduleText.text
                                }

                                MouseArea {
                                    anchors.fill: parent
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
                        Layout.preferredHeight: 50
                        placeholderText: "Enter module name"
                    }



                    Rectangle {
                        id: colorPreview
                        width: 50
                        height: 50
                        color: moduleColorInput.text !== "" ? moduleColorInput.text : "lightgray"
                        border.color: "black"
                        radius: 5

                        MouseArea {
                            anchors.fill: colorPreview
                            onClicked: colorDialog.open()
                        }
                    }


                    RowLayout {
                        spacing: 20

                        Button {
                            text: "Add"
                            width: (parent.width - 40) / 2
                            onClicked: {
                                dataController.addModuleToSelectedFolder(moduleNameInput.text, colorPreview.color)
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
                onAccepted: colorPreview.color = colorDialog.selectedColor
            }

            TextField {
                id: moduleColorInput
                visible: false
                text: colorPreview.color
                onTextChanged: colorPreview.color = moduleColorInput.text
            }
        }
    }
}
