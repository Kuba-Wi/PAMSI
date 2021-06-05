import QtQuick.Controls 2.12
import QtQuick 2.12
import TicTacModel 0.1

ApplicationWindow {
    width: 640
    height: 550
    visible: true
    title: qsTr("Tic Tac Toe")
    property bool fieldEnabled: true
    property var field_size: 30

    TableView {
        id: tic_tac_view
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 50
        columnSpacing: 1
        rowSpacing: 1

        model: TicTacModel {
            id: tic_tac_model
            onGameOver: fieldEnabled = false;
            onMakeNextMove: next_move();
        }

        delegate: Button {
            id: field
            implicitWidth: field_size
            implicitHeight: field_size
            text: model.mark
            onClicked: {
                model.mark = text;
            }
            enabled: fieldEnabled
        }
    }

    Button {
        id: button_new_game
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: tic_tac_view.bottom
        anchors.topMargin: 50
        text: "New game"
        onClicked: {
            fieldEnabled = true;
            tic_tac_model.new_game(parseInt(text_size.text, 10), parseInt(text_marks.text, 10));
            tic_tac_view.height = field_size * tic_tac_model.rowCount()
            tic_tac_view.width = field_size * tic_tac_model.columnCount()
        }
    }

    TextField {
        id: text_size
        anchors.top: button_new_game.bottom
        anchors.topMargin: 20
        anchors.right: parent.horizontalCenter
        anchors.rightMargin: 10
    }
    
    TextField {
        id: text_marks
        anchors.top: button_new_game.bottom
        anchors.topMargin: 20
        anchors.left: parent.horizontalCenter
        anchors.leftMargin: 10
    }
}
