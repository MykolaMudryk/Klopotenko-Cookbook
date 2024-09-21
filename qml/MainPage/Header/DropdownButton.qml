import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Basic 2.15
import QtQuick.Layouts

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
      id: popupBackground
      width: parent.width + 40
      height: parent.height

      color: "white"

      radius: receiptDropDownBackground.radius
    }

    ListView {
      id: listview

      width: parent.width
      height: parent.height

      model: qmlHandler.categoryModel

      delegate: Rectangle {
        id: dropdownColumnBackground

        width: popup.width

        height: 50

        MouseArea {
          id: hoverArea

          anchors.fill: parent

          hoverEnabled: true

          onEntered: parent.color = "#f6f7f8"

          onExited: parent.color = "transparent"

          onClicked: popup.close()
        }

        Row {
          spacing: 17

          anchors.fill: parent
          anchors.margins: 10

          anchors.verticalCenter: dropdownColumnBackground.verticalCenter

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

            anchors.verticalCenter: dropDownIcon.verticalCenter
            color: "black"
          }
        }
      }
    }
  }
}
