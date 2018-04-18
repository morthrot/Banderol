import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3

ApplicationWindow {
    id: root
    width: 596
    visible: true
    height: 326
    title: "Бандероль"

    function init(bind_ok,nick) {
        taChat.clear()
        updateTime()
        lNick.text = nick

        if(bind_ok === false) {
            bindDialog.open()
        }

        nickDialog.open()
    }

    Dialog {
        id: bindDialog

        title: "Ошибка сети"
        Label { text: "Ошибка привязки к порту" }

        onAccepted: Qt.quit()
    }

    Dialog {
        id: nickDialog

        title: "Вход"
        ColumnLayout {
            spacing: 20
            anchors.fill: parent
            Label {
                elide: Label.ElideRight
                text: "Введите погоняло:"
                Layout.fillWidth: true
            }
            TextField {
                id: dialog_nick
                text: lNick.text
                focus: true
                Layout.fillWidth: true
            }
        }

        onAccepted: lNick.text = dialog_nick.text
    }

    function sendMessage() {
        generatedMessage(lNick.text,tfMessage.text)
        tfMessage.text = ""
    }

    signal generatedMessage(var nick,var message)

    function recieveMessage(nick,message) {
        var dt = new Date()
        taChat.append(dt.toTimeString() + " <b>" + nick + "</b> " + message)
    }

    function updateTime() {
        var dt = new Date()
        lTime.text = dt.toTimeString();
    }

    Timer {
        interval: 1000
        running: true
        repeat: true

        onTriggered: updateTime()
    }

    Button {
        id: bSend
        x: 458
        y: 272
        width: 128
        height: 48
        text: qsTr("Отправить")
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 6
        anchors.right: parent.right
        anchors.rightMargin: 10
        onClicked: sendMessage()
    }

    Label {
        id: lNick
        y: 272
        height: 48
        text: qsTr("Пользователь")
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 6
        anchors.left: lTime.right
        anchors.leftMargin: 6
        font.bold: true
        verticalAlignment: Text.AlignVCenter
    }

    TextField {
        id: tfMessage
        y: 272
        height: 48
        text: qsTr("")
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 6
        anchors.right: bSend.left
        anchors.rightMargin: 6
        anchors.left: lNick.right
        anchors.leftMargin: 6
        placeholderText: "Сообщение для отправки"

        onAccepted: sendMessage()
    }

    Label {
        id: lTime
        y: 272
        height: 48
        text: qsTr("00:00:00")
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 6
        anchors.left: parent.left
        anchors.leftMargin: 10
        verticalAlignment: Text.AlignVCenter
    }

    ScrollView {
        id: svChat
        anchors.bottom: tfMessage.top
        anchors.bottomMargin: 6
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10

        TextArea {
            id: taChat
            textFormat: Text.RichText
            wrapMode: Text.WordWrap
            readOnly: true
        }
    }
}




