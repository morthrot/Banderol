import QtQuick 2.9
import QtQuick.Controls 2.2

ApplicationWindow {
    id: root
    width: 506
    visible: true
    height: 304
    title: "Бандероль"

    signal generatedMessage(var nick, var message)

    function recieveMessage(nick,message) {
        taChat.text = taChat.text + nick + " " + message
    }

    Button {
        id: bSend
        x: 418
        y: 270
        text: qsTr("Отправить")
        onClicked: generatedMessage(tNick.text,tfMessage.text)
    }

    TextArea {
        id: taChat
        x: 8
        y: 8
        width: 490
        height: 256
        text: qsTr("")
        placeholderText: "Текст чата"
        wrapMode: Text.WordWrap
    }

    TextField {
        id: tfMessage
        x: 156
        y: 270
        width: 256
        height: 24
        text: qsTr("")
        placeholderText: "Введите текст для отправки"
    }

    Text {
        id: tTime
        x: 8
        y: 275
        text: qsTr("00:00:00")
        font.pixelSize: 12
    }

    Text {
        id: tNick
        y: 275
        text: qsTr("Пользователь")
        anchors.left: parent.left
        anchors.leftMargin: 64
        font.bold: true
        font.pixelSize: 12
    }
}
