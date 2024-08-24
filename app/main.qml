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

    ListModel {
        id: colorPresets
        ListElement { color: "lightblue" }
        ListElement { color: "lightgreen" }
        ListElement { color: "lightcoral" }
        ListElement { color: "lightgoldenrodyellow" }
        ListElement { color: "lightpink" }
        ListElement { color: "lightsalmon" }
        ListElement { color: "lightseagreen" }
        ListElement { color: "lightsteelblue" }
        ListElement { color: "lightyellow" }
        ListElement { color: "lavender" }
    }

    QtObject {
        id: appStyle
    }

    Component {
        id: mainPage
        Item {
            width: parent.width
            height: parent.height

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 20

                Button {
                    text: "New Folder"
                    onClicked: stackView.push(addFolderPage)
                    Layout.preferredHeight: 50
                    Layout.fillWidth: true
                }

                GridView {
                    id: gridView
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    cellWidth: (parent.width) / 2
                    cellHeight: (parent.height) / 3

                    model: dataController.foldersModel

                    delegate: Item {
                        width: gridView.cellWidth
                        height: gridView.cellHeight

                        Rectangle {
                            width: gridView.cellWidth - 5
                            height: gridView.cellHeight -5
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
                width: parent.width
                height: parent.height
                color: "white"
                border.color: "black"
                border.width: 1
                radius: 10
                anchors.margins: 10

                ColumnLayout {
                    spacing: 20
                    anchors.fill: parent

                    TextField {
                        id: folderNameInput
                        Layout.fillWidth: true
                        Layout.preferredHeight: 90
                        placeholderText: "Enter folder name"
                        text: dataController.newFolderName
                        onTextChanged: dataController.setNewFolderName(text)
                    }

                    RowLayout {
                        spacing: 20
                        Layout.fillWidth: true

                        Button {
                            text: "Add New"
                            Layout.preferredHeight: 50
                            Layout.fillWidth: true
                            onClicked: {
                                dataController.addFolder(folderNameInput.text)
                                stackView.pop()
                            }
                        }
                        Button {
                            text: "Import "
                            Layout.preferredHeight: 50
                            Layout.fillWidth: true
                            onClicked:
                            {
                                importFolderDialog.open();
                            }
                        }

                        Button {
                            text: "Cancel"
                            Layout.preferredHeight: 50
                            Layout.fillWidth: true
                            onClicked: stackView.pop()
                        }

                        FileDialog {
                            id: importFolderDialog
                            title: "Import File"
                            nameFilters: ["JSON Files (*.json)"]
                            onAccepted: {
                                var filePath = importFolderDialog.file.toString(); // Преобразуйте в строку
                                // Удалите префикс "file://" из пути
                                if (filePath.startsWith("file://")) {
                                    filePath = filePath.substring(7);
                                }
                                dataController.importFolder(filePath);
                                stackView.pop();
                            }
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

            ColumnLayout {
                anchors.fill: parent
                spacing: 20
                anchors.margins: 20

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
                        text: "Delete"
                        Layout.preferredHeight: 50
                        Layout.fillWidth: true
                        onClicked: {
                            dataController.deleteSelectedModule()
                            stackView.pop()
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
                        text: "Export"
                        Layout.preferredHeight: 50
                        Layout.fillWidth: true
                        onClicked: {exportModuleDialog.open()}
                    }


                    FolderDialog {
                        id: exportModuleDialog
                        title: "Select Folder"
                        onAccepted: {
                            var folderPath = folder.toString().replace("file:///", ""); // Удаление префикса

                            if (dataController.selectedFolder) {
                                var folderName = dataController.selectedFolder.name;
                                var currentDate = Qt.formatDateTime(new Date(), "yyyy-MM-dd_HH-mm-ss");
                                var fullPath =  "/" + folderPath + "/" + "Module_" +folderName + "_" + currentDate + ".json";

                                console.log(fullPath)

                                dataController.exportSelectedModule(fullPath);
                            } else {
                                console.log("No folder selected for export.");
                            }
                        }

                        onRejected: {
                            console.log("Select folder dialog was cancelled");
                        }
                    }
                }

                ListView {
                    id: cardListView
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    layoutDirection: Qt.TopToBottom
                    spacing: 5
                    clip: true
                    model: dataController.selectedModule ? dataController.selectedModule.cardsModel : null

                    delegate: Item {
                        width: cardListView.width
                        height: 120

                        Rectangle {
                            width: parent.width
                            height: 120
                            color: "lightgray"
                            border.color: "black"
                            border.width: 2
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
                                    onTextChanged: {
                                        model.question = questionField.text
                                    }
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
                spacing: 10
                anchors.margins: 10

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
                    Layout.fillWidth: true

                    Button {
                        text: "Export Folder"
                        Layout.preferredHeight: 50
                        Layout.fillWidth: true
                        onClicked:
                        {
                            exportFolderDialog.open();
                        }
                    }
                    Button {
                        text: "Import Module"
                        Layout.preferredHeight: 50
                        Layout.fillWidth: true
                        onClicked: {importModuleDialog.open()}
                    }

                    FileDialog {
                        id: importModuleDialog
                        title: "Import File"
                        nameFilters: ["JSON Files (*.json)"]
                        onAccepted: {
                            var filePath = importModuleDialog.file.toString(); // Преобразуйте в строку
                            // Удалите префикс "file://" из пути
                            if (filePath.startsWith("file://")) {
                                filePath = filePath.substring(7);
                            }
                            dataController.importModule(filePath);
                        }
                    }

                    Button {
                        text: "Delete"
                        Layout.preferredHeight: 50
                        Layout.fillWidth: true
                        onClicked: {
                            dataController.deleteSelectedFolder()
                            stackView.pop()
                        }
                    }

                    FolderDialog {
                        id: exportFolderDialog
                        title: "Select Folder"
                        onAccepted: {
                            var folderPath = folder.toString().replace("file:///", ""); // Удаление префикса

                            if (dataController.selectedFolder) {
                                var folderName = dataController.selectedFolder.name;
                                var currentDate = Qt.formatDateTime(new Date(), "yyyy-MM-dd_HH-mm-ss");
                                var fullPath =   "/" + folderPath + "/" + "Folder_" +folderName + "_" + currentDate + ".json";
                                dataController.exportSelectedFolder(fullPath);
                            } else {
                                console.log("No folder selected for export.");
                            }
                        }

                        onRejected: {
                            console.log("Select folder dialog was cancelled");
                        }
                    }
                }

                GridView {
                    id: modulesGridView
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    cellWidth: (parent.width) / 2
                    cellHeight: (parent.height) / 3
                    model: dataController.selectedFolder ? dataController.selectedFolder.modulesModel : null
                    clip: true

                    delegate: Item {
                        width: modulesGridView.cellWidth
                        height: modulesGridView.cellHeight

                        Rectangle {
                            width: modulesGridView.cellWidth - 5
                            height: modulesGridView.cellHeight - 5
                            radius: 5
                            border.color: "black"
                            border.width: 2

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

                            Rectangle {
                                anchors.fill: parent
                                anchors.margins: 5
                                color: "white"
                                radius: 5
                                border.color: "black"
                                opacity: 0.1
                            }

                            Rectangle {
                                id: moduleContent
                                anchors.fill: parent
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
            anchors.fill: parent

            Rectangle {
                id: modBG
                anchors.fill: parent
                color: "white"
                border.color: "black"
                border.width: 1
                radius: 10
                anchors.margins: 10

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 10

                    TextField {
                        id: moduleNameInput
                        Layout.fillWidth: true
                        Layout.preferredHeight: 50
                        placeholderText: "Enter module name"
                    }

                    GridView {
                        id: colorGridView
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        model: colorPresets
                        cellWidth: 100
                        cellHeight: 100


                        delegate: Rectangle {
                            width: colorGridView.cellWidth - 5
                            height: colorGridView.cellHeight - 5
                            color: model.color
                            border.color: "black"
                            border.width: 2

                            radius: width / 2

                            MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    modBG.color = model.color
                                }
                            }
                        }
                    }

                    RowLayout {
                        spacing: 20
                        Layout.fillWidth: true

                        Button {
                            text: "Add"
                            Layout.preferredHeight: 50
                            Layout.fillWidth: true
                            onClicked: {
                                dataController.addModuleToSelectedFolder(moduleNameInput.text, modBG.color)
                                stackView.pop()
                            }
                        }

                        Button {
                            text: "Cancel"
                            Layout.preferredHeight: 50
                            Layout.fillWidth: true
                            onClicked: stackView.pop()
                        }
                    }

                    Item {
                        Layout.fillHeight: true
                    }
                }
            }

        }
    }
    QtObject
    {
        id: guiController

    }

}
