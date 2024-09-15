import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Basic 2.15

Rectangle {
  id: grayBackground

  height: 76
  width: parent.width

  color: "#555555"

  Button {
    id: receiptDropDown
    width: 254
    height: 55

    onClicked: popup.open()

    anchors {
      left: parent.left
      leftMargin: 25
      verticalCenter: parent.verticalCenter
    }

    contentItem: Text {
      text: "Список рецептів"

      font.family: "DIN Alternate"

      font.pixelSize: 20
      font.bold: true

      horizontalAlignment: Text.AlignHCenter
      verticalAlignment: Text.AlignVCenter

      color: "white"

      anchors.centerIn: parent
    }

    background: Rectangle {
      id: receiptDropDownBackground
      color: "#2e77da"

      radius: 7

      Image {
        id: customArrowIcon

        source: "qrc:/custom_arrow_down.png"

        width: 12
        height: 12

        fillMode: Image.PreserveAspectFit

        anchors.right: parent.right
        anchors.rightMargin: 20
      }
    }

    Popup {
      id: popup

      width: receiptDropDown.width
      height: 200

      modal: true
      focus: true

      parent: Overlay.overlay

      closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

      x: receiptDropDown.x
      y: receiptDropDown.y + receiptDropDown.height

      background: Rectangle {

        width: parent.width + 40
        height: parent.height

        color: "white"

        radius: receiptDropDownBackground.radius
      }

      ListView {

        width: parent.width
        height: parent.height

        model: ["Перше", "Друге", "Салати", "Закуски"]

        delegate: ItemDelegate {
          id: dropdownElementsStyle

          contentItem: Text {
            text: modelData

            font {

              family: "DIN Alternate"
              pixelSize: 18
              bold: true
            }

            color: "black"

            anchors {
              left: parent.left
              leftMargin: 46
            }
          }

          onClicked: {
            popup.close()
          }
        }
      }
    }
  }

  Text {
    id: menuTittle

    text: "Klopotenko's Smart cookbook"
    color: "white"

    font.pixelSize: 20

    anchors.horizontalCenter: parent.horizontalCenter
  }

  Image {
    id: addReceiptIcon

    source: " " // додати іконку плюсика з фотошопу

    width: 30
    height: 30

    anchors.rightMargin: 25

    MouseArea {
      anchors.fill: parent
      onClicked: {

        // виклик функції для додвання рецепту
      }
    }
  }
}
