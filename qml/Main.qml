import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import QtQuick.Dialogs

ApplicationWindow {
    id: root
    width: 1200
    height: 760
    visible: true
    title: "Blockchain File Transfer"

    property bool darkTheme: true

    Material.theme: darkTheme ? Material.Dark : Material.Light
    Material.accent: darkTheme ? "#3ddc84" : "#0f766e"
    Material.foreground: darkTheme ? "#e5e7eb" : "#111827"
    Material.background: darkTheme ? "#0b0f14" : "#f8fafc"

    function showToast(message) {
        toastText.text = message
        toast.open()
    }

    Component.onCompleted: {
        appController.initializeDefault("127.0.0.1", 39150)
        appController.refresh()
    }

    Rectangle {
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0.0; color: darkTheme ? "#0b0f14" : "#f8fafc" }
            GradientStop { position: 1.0; color: darkTheme ? "#111827" : "#e2e8f0" }
        }
    }

    RowLayout {
        anchors.fill: parent
        spacing: 0

        Rectangle {
            Layout.preferredWidth: 260
            color: darkTheme ? "#0f172a" : "#ffffff"
            border.color: darkTheme ? "#1f2937" : "#e5e7eb"
            border.width: 1

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 20
                spacing: 16

                Text {
                    text: "Blockchain"
                    font.pixelSize: 24
                    font.bold: true
                    color: darkTheme ? "#e5e7eb" : "#111827"
                }

                Text {
                    text: appController.currentUserName.length > 0
                          ? "Пользователь: " + appController.currentUserName
                          : "Не авторизован"
                    font.pixelSize: 14
                    color: darkTheme ? "#9ca3af" : "#6b7280"
                }
                Text {
                    text: appController.currentUserAddress.length > 0
                          ? "Адрес: " + appController.currentUserAddress
                          : ""
                    font.pixelSize: 11
                    color: "#3ddc84"
                    wrapMode: Text.WrapAnywhere
                }

                Button { text: "Регистрация / Вход"; onClicked: stackView.push(loginPage) }
                Button { text: "Пользователи"; onClicked: stackView.push(usersPage) }
                Button { text: "Отправка файла"; onClicked: stackView.push(sendPage) }
                Button { text: "История"; onClicked: stackView.push(historyPage) }
                Button { text: "Блоки"; onClicked: stackView.push(blocksPage) }
                Button { text: "Проверка файла"; onClicked: stackView.push(verifyPage) }

                Item { Layout.fillHeight: true }

                RowLayout {
                    spacing: 8
                    Text { text: "Тема"; color: darkTheme ? "#9ca3af" : "#6b7280" }
                    Switch {
                        checked: darkTheme
                        onToggled: darkTheme = checked
                    }
                }
            }
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "transparent"

            StackView {
                id: stackView
                anchors.fill: parent
                initialItem: loginPage
                pushEnter: Transition {
                    NumberAnimation { property: "opacity"; from: 0.0; to: 1.0; duration: 160 }
                }
                pushExit: Transition {
                    NumberAnimation { property: "opacity"; from: 1.0; to: 0.0; duration: 160 }
                }
            }
        }
    }

    Component {
        id: loginPage
        Item {
            anchors.fill: parent
            ColumnLayout {
                anchors.centerIn: parent
                spacing: 16
                width: 480

                Text {
                    text: "Регистрация"
                    font.pixelSize: 22
                    font.bold: true
                    color: darkTheme ? "#e5e7eb" : "#111827"
                }

                TextField { id: regName; placeholderText: "Имя пользователя" }
                TextField { id: regHost; placeholderText: "Host"; text: "127.0.0.1" }
                TextField { id: regPort; placeholderText: "Port"; text: "39150"; inputMethodHints: Qt.ImhDigitsOnly }

                Button {
                    text: "Создать пользователя"
                    onClicked: {
                        var err = ""
                        if (!appController.registerUser(regName.text, regHost.text, parseInt(regPort.text), err)) {
                            showToast(err)
                        } else {
                            showToast("Пользователь создан")
                        }
                    }
                }

                Rectangle { height: 1; width: parent.width; color: darkTheme ? "#1f2937" : "#e5e7eb" }

                Text {
                    text: "Вход"
                    font.pixelSize: 22
                    font.bold: true
                    color: darkTheme ? "#e5e7eb" : "#111827"
                }

                TextField { id: loginAddress; placeholderText: "Адрес пользователя (hex)" }
                Button {
                    text: "Войти"
                    onClicked: {
                        var err = ""
                        if (!appController.loginByAddress(loginAddress.text, err)) {
                            showToast(err)
                        } else {
                            showToast("Вход выполнен")
                        }
                    }
                }
            }
        }
    }

    Component {
        id: usersPage
        Item {
            anchors.fill: parent
            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 24
                spacing: 12
                Text { text: "Пользователи"; font.pixelSize: 22; font.bold: true; color: darkTheme ? "#e5e7eb" : "#111827" }

                ListView {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    model: appController.users
                    delegate: Rectangle {
                        width: parent.width
                        height: 70
                        radius: 8
                        color: darkTheme ? "#111827" : "#ffffff"
                        border.color: darkTheme ? "#1f2937" : "#e5e7eb"
                        RowLayout {
                            anchors.fill: parent
                            anchors.margins: 12
                            Text { text: name; font.bold: true; color: darkTheme ? "#e5e7eb" : "#111827" }
                            Item { Layout.fillWidth: true }
                            Text { text: address; color: "#3ddc84"; font.pixelSize: 12 }
                            Text { text: host + ":" + port; color: darkTheme ? "#9ca3af" : "#6b7280" }
                        }
                    }
                }
            }
        }
    }

    Component {
        id: sendPage
        Item {
            anchors.fill: parent
            ColumnLayout {
                anchors.centerIn: parent
                spacing: 16
                width: 520
                Text { text: "Отправка файла"; font.pixelSize: 22; font.bold: true; color: darkTheme ? "#e5e7eb" : "#111827" }

                TextField { id: receiverAddress; placeholderText: "Адрес получателя (hex)" }
                TextField { id: filePath; placeholderText: "Путь к файлу"; readOnly: true }

                Button {
                    text: "Выбрать файл"
                    onClicked: fileDialog.open()
                }
                Button {
                    text: "Отправить"
                    onClicked: {
                        var err = ""
                        if (!appController.sendFile(receiverAddress.text, filePath.text, err)) {
                            showToast(err)
                        } else {
                            showToast("Файл отправлен")
                        }
                    }
                }
            }
            FileDialog {
                id: fileDialog
                title: "Выберите файл"
                fileMode: FileDialog.OpenFile
                onAccepted: filePath.text = fileDialog.selectedFile
            }
        }
    }

    Component {
        id: historyPage
        Item {
            anchors.fill: parent
            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 24
                spacing: 12
                Text { text: "История транзакций"; font.pixelSize: 22; font.bold: true; color: darkTheme ? "#e5e7eb" : "#111827" }
                ListView {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    model: appController.transactions
                    delegate: Rectangle {
                        width: parent.width
                        height: 92
                        radius: 8
                        color: darkTheme ? "#0f172a" : "#ffffff"
                        border.color: darkTheme ? "#1f2937" : "#e5e7eb"
                        ColumnLayout {
                            anchors.fill: parent
                            anchors.margins: 12
                            Text { text: fileName + " • " + fileSize + " bytes"; font.bold: true; color: darkTheme ? "#e5e7eb" : "#111827" }
                            Text { text: "Hash: " + fileHash; color: "#3ddc84"; font.pixelSize: 12 }
                            Text { text: "От: " + sender + " → " + receiver; color: darkTheme ? "#9ca3af" : "#6b7280"; font.pixelSize: 12 }
                            Text { text: "Блок: " + blockIndex; color: darkTheme ? "#9ca3af" : "#6b7280"; font.pixelSize: 12 }
                        }
                    }
                }
            }
        }
    }

    Component {
        id: blocksPage
        Item {
            anchors.fill: parent
            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 24
                spacing: 12
                Text { text: "Блоки"; font.pixelSize: 22; font.bold: true; color: darkTheme ? "#e5e7eb" : "#111827" }
                ListView {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    model: appController.blocks
                    delegate: Rectangle {
                        width: parent.width
                        height: 80
                        radius: 8
                        color: darkTheme ? "#0b0f14" : "#ffffff"
                        border.color: darkTheme ? "#1f2937" : "#e5e7eb"
                        ColumnLayout {
                            anchors.fill: parent
                            anchors.margins: 12
                            Text { text: "Hash: " + hash; color: "#3ddc84"; font.pixelSize: 12 }
                            Text { text: "Prev: " + prevHash; color: darkTheme ? "#9ca3af" : "#6b7280"; font.pixelSize: 12 }
                            Text { text: "Authority: " + authority; color: darkTheme ? "#9ca3af" : "#6b7280"; font.pixelSize: 12 }
                        }
                    }
                }
            }
        }
    }

    Component {
        id: verifyPage
        Item {
            anchors.fill: parent
            ColumnLayout {
                anchors.centerIn: parent
                spacing: 16
                width: 520
                Text { text: "Проверка файла"; font.pixelSize: 22; font.bold: true; color: darkTheme ? "#e5e7eb" : "#111827" }
                TextField { id: verifyPath; placeholderText: "Путь к файлу"; readOnly: true }
                Button { text: "Выбрать файл"; onClicked: verifyDialog.open() }
                Button {
                    text: "Проверить"
                    onClicked: {
                        var result = appController.verifyFile(verifyPath.text)
                        if (result.ok) {
                            showToast("Файл найден: " + result.fileName + " | Блок: " + result.blockIndex)
                        } else {
                            showToast(result.error)
                        }
                    }
                }
            }
            FileDialog {
                id: verifyDialog
                title: "Выберите файл"
                fileMode: FileDialog.OpenFile
                onAccepted: verifyPath.text = verifyDialog.selectedFile
            }
        }
    }

    Popup {
        id: toast
        x: (root.width - width) / 2
        y: root.height - height - 24
        width: Math.min(root.width - 32, 720)
        height: toastText.implicitHeight + 24
        modal: false
        focus: false
        closePolicy: Popup.NoAutoClose
        padding: 12

        background: Rectangle {
            radius: 10
            color: darkTheme ? "#111827" : "#111827"
            border.color: "#374151"
        }

        contentItem: Text {
            id: toastText
            color: "#f9fafb"
            wrapMode: Text.Wrap
        }

        Timer {
            id: toastTimer
            interval: 2400
            repeat: false
            onTriggered: toast.close()
        }

        onOpened: {
            appController.refresh()
            toastTimer.restart()
        }
    }

    Connections {
        target: appController
        function onNotification(message) {
            showToast(message)
        }
    }
}
