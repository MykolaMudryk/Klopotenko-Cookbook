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
      id: receiptDropDownText

      text: "Список рецептів"

      font.family: "DIN Alternate"

      font.pixelSize: 25
      font.bold: true

      horizontalAlignment: Text.AlignHCenter
      verticalAlignment: Text.AlignVCenter

      color: "white"

      anchors {
        right: parent.right
        rightMargin: 20
      }
    }

    background: Rectangle {
      id: receiptDropDownBackground
      color: "#6b80ef"

      radius: 7

      Image {
        id: customArrowIcon

        source: "qrc:icons/decorative/dropdownIcon.png"

        width: 30
        height: 30

        fillMode: Image.PreserveAspectFit

        anchors {
          right: parent.right
          rightMargin: 16

          top: parent.top
          topMargin: 15
        }
      }
    }

    Popup {
      id: popup

      width: receiptDropDown.width
      height: 300

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

        model: ListModel {

          ListElement {
            icon: "qrc:icons/categories/main.png"
            text: "Перші страви"
          }

          ListElement {
            icon: "qrc:icons/categories/starters.png"
            text: "Другі страви"
          }

          ListElement {
            icon: "qrc:icons/categories/salad.png"
            text: "Салати"
          }

          ListElement {
            icon: "qrc:icons/categories/snack.png"
            text: "Закуски"
          }

          ListElement {
            icon: "qrc:icons/categories/dessert.png"
            text: "Десерти"
          }
        }

        delegate: ItemDelegate {
          id: dropdownElementsStyle

          contentItem: Row {
            spacing: 10

            Image {
              source: model.icon
              width: 30
              height: 30
              fillMode: Image.PreserveAspectFit
            }

            Text {
              text: model.text
              font {
                family: "DIN Alternate"
                pixelSize: 23
                bold: true
              }
              color: "black"
              anchors.verticalCenter: parent.verticalCenter
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
    id: klopotenkoTittleWord

    text: "Klopotenko's"
    color: "#6e9fec" // color from "line" word in hotline site

    font {

      pixelSize: 27

      bold: true
    }

    anchors {
      horizontalCenter: parent.horizontalCenter

      top: receiptDropDown.top
    }
  }

  Text {
    id: smartTittleWord

    text: "Smart"
    color: "#ffa726"

    font {

      pixelSize: 27

      bold: true
    }

    anchors {
      horizontalCenter: grayBackground.horizontalCenter

      bottom: grayBackground.bottom
      bottomMargin: 6

      horizontalCenterOffset: -63
    }
  }

  Text {
    id: cookBookTittleWord

    text: "cookbook"
    color: "#6e9fec"

    font {

      pixelSize: 27

      bold: true
    }

    anchors {
      horizontalCenter: grayBackground.horizontalCenter

      bottom: grayBackground.bottom
      bottomMargin: 6

      horizontalCenterOffset: +50
    }
  }

  Image {
    id: addReceiptIcon

    source: "qrc:icons/decorative/plusAddReceipt.png"

    width: 80
    height: 75

    anchors {
      verticalCenter: grayBackground.verticalCenter

      right: grayBackground.right
      rightMargin: 150
    }

    MouseArea {
      anchors.fill: parent
      onClicked: {

        // виклик функції для додвання рецепту
      }
    }
  }
}
