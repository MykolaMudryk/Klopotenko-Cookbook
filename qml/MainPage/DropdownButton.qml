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

    modal: true
    focus: true

    parent: Overlay.overlay

    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

    x: receiptDropDown.x
    y: receiptDropDown.y + receiptDropDown.height

    background: Rectangle {
      id: categoryListviewBackground

      width: receiptDropDown.width + 40
      implicitHeight: qmlHandler.categoryModel.rowCount * 50

      color: "#f0f0f0"

      radius: receiptDropDownBackground.radius

      ListView {
        id: categoryListview

        width: categoryListviewBackground.width
        implicitHeight: contentHeight

        model: qmlHandler.categoryModel

        delegate: Rectangle {
          id: dropdownColumnBackground

          width: categoryListviewBackground.width

          height: 50

          MouseArea {
            id: categoryHoverArea

            anchors.fill: parent

            hoverEnabled: true

            onEntered: {
              parent.color = "#f6f7f8"
              qmlHandler.fetchNationality(model.categoryName)
            }

            onExited: parent.color = "white"

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

      Rectangle {
        id: nationalityListviewBackground

        width: parent.width
        implicitHeight: qmlHandler.nationalityModel.rowCount * 50

        color: "#f0f0f0"

        radius: receiptDropDownBackground.radius

        ListView {
          id: nationalityListview

          width: nationalityListviewBackground.width
          implicitHeight: contentHeight

          x: categoryListview.x + categoryListview.width
          y: categoryListview.y + categoryListview.height

          model: qmlHandler.nationalityModel

          delegate: Rectangle {
            id: nationalityColumnBackground

            width: popup.width

            height: 50

            MouseArea {
              id: nationalityHoverArea

              anchors.fill: parent

              hoverEnabled: true

              onEntered: parent.color = "#f6f7f8"

              onExited: parent.color = "white"

              onClicked: popup.close()
            }

            Row {
              spacing: 17

              anchors.fill: parent
              anchors.margins: 10

              anchors.verticalCenter: nationalityColumnBackground.verticalCenter

              Text {
                text: model.nationality
                font {
                  family: "DIN Alternate"
                  pixelSize: 23
                  bold: true
                }
                color: "black"
              }
            }
          }
        }
      }
    }
  }
}
