import QtQuick 2.10
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

ApplicationWindow {
    id: root
    width: 596
    visible: true
    height: 326
    title: "Бандероль"
    minimumWidth: 386
    minimumHeight: 256

    function init(bind_ok,nick) {
        taChat.clear()
        updateTime()
        lNick.text = nick
        processInterface()

        if(bind_ok === false) { bindDialog.open() }
        else { nickDialog.open() }
    }

    Dialog {
        id: bindDialog
        modal: true
        standardButtons: Dialog.Ok

        x: (parent.width - width) / 2
        y: (parent.height - height) / 2

        title: "Ошибка сети"
        Label { text: "Ошибка привязки к порту" }

        onAccepted: Qt.quit()
        onRejected: Qt.quit()
    }

    Dialog {
        id: nickDialog
        modal: true
        standardButtons: Dialog.Ok

        x: (parent.width - width) / 2
        y: (parent.height - height) / 2

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
        tfMessage.clear()
    }

    signal generatedMessage(var nick,var message)

    function recieveMessage(nick,message) {
        var dt = new Date()
        taChat.append("<i>" + dt.toTimeString() + "</i> - <b>" + nick + "</b> " + message)
    }

    function updateTime() {
        var dt = new Date()
        lTime.text = dt.toTimeString();
    }

    function processInterface() {
        bSend.enabled = (tfMessage.text != "")
    }

    function getNick() {
        return lNick.text
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
        text: "Отправить"
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
        text: "Пользователь"
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
        text: ""
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 6
        anchors.right: bSend.left
        anchors.rightMargin: 6
        anchors.left: lNick.right
        anchors.leftMargin: 6
        placeholderText: "Сообщение для отправки"

        onTextChanged: processInterface()
        onAccepted: sendMessage()
    }

    Label {
        id: lTime
        y: 272
        height: 48
        text: "00:00:00"
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
