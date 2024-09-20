import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Basic 2.15
import QtQuick.Layouts

Rectangle {
  id: grayBackground

  height: 76
  width: parent.width

  color: "#555555"

  Button {
    id: receiptDropDown
    width: 254
    height: 55

    onClicked: {

      popup.open()
      qmlHandler.fetchCategories()
    }

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

        model: qmlHandler.categoryModel

        delegate: Row {
          spacing: 10

          Image {
            id: dropDownIcon

            source: "qrc:/icons/categories/" + model.iconName

            width: 30
            height: 30

            fillMode: Image.PreserveAspectFit
          }

          Text {
            text: model.categoryName
            font {
              family: "DIN Alternate"
              pixelSize: 23
              bold: true
            }
            color: "black"
          }
          MouseArea {
            anchors.fill: parent
            onClicked: popup.close()
          }
        }
      }
    }
  }

  Text {
    id: klopotenkoTittleWord

    text: "Smart"
    color: "#6e9fec" // color from "line" word in hotline site

    font {

      pixelSize: 30

      bold: true
    }

    anchors {
      horizontalCenter: grayBackground.horizontalCenter

      top: receiptDropDown.top
    }
  }

  Text {
    id: cookBookTittleWord

    text: "<span style='color:#ffa726;'>cook</span><span style='color:#6e9fec;'>book</span>"

    textFormat: Text.RichText

    font {

      pixelSize: 30

      bold: true
    }

    anchors {
      horizontalCenter: grayBackground.horizontalCenter

      bottom: grayBackground.bottom
      bottomMargin: 4
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
