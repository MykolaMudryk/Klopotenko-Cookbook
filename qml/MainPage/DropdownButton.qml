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
    categoryModel.fetchCategories()
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

    closePolicy: Popup.CloseOnPressOutside

    property bool isInNationalityList: false

    x: receiptDropDown.x
    y: receiptDropDown.y + receiptDropDown.height

    background: Rectangle {
      id: popupContainer

      width: parent.width
      height: parent.height

      color: "transparent"
    }

    Rectangle {
      id: categoryListviewBackground

      width: receiptDropDown.width + 40
      implicitHeight: categoryModel.rowCount * 50

      radius: 7

      color: "#f0f0f0"

      ListView {
        id: categoryListview

        width: categoryListviewBackground.width
        implicitHeight: contentHeight

        model: categoryModel

        delegate: Rectangle {
          id: dropdownColumnBackground

          width: categoryListviewBackground.width

          height: 50

          property int hoveredCategoryX: 0

          MouseArea {
            id: categoryHoverArea

            anchors.fill: parent

            hoverEnabled: true

            property int hoveredCategoryY: 0

            onEntered: {
              parent.color = "#f6f7f8"

              nationalityModel.fetchNationality(model.categoryName)

              hoveredCategoryX = dropdownColumnBackground.x
              hoveredCategoryY = dropdownColumnBackground.y

              nationalityListview.x = hoveredCategoryX + categoryListview.x + categoryListview.width
              nationalityListview.y = hoveredCategoryY
            }

            onExited: {
              parent.color = "white"

              if (!popup.isInNationalityList) {
                nationalityModel.clearNationalities()
              }
            }

            onClicked: {
              nationalityListview.x = -1000
              nationalityModel.clearNationalities()
              popup.close()
            }
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

        width: receiptDropDown.width + 40
        implicitHeight: nationalityModel.rowCount * 50

        color: "#f0f0f0"

        radius: receiptDropDownBackground.radius

        ListView {
          id: nationalityListview

          width: nationalityListviewBackground.width
          implicitHeight: contentHeight

          x: categoryListview.x + categoryListview.width
          y: categoryListview.y + categoryListview.height

          model: nationalityModel

          delegate: Rectangle {
            id: nationalityColumnBackground

            width: nationalityListviewBackground.width

            height: 50

            MouseArea {
              id: nationalityHoverArea

              anchors.fill: parent

              hoverEnabled: true

              onEntered: {
                popup.isInNationalityList = true
                parent.color = "#f6f7f8"
              }

              onExited: {
                popup.isInNationalityList = false
                parent.color = "white"
              }

              onClicked: {
                nationalityListview.x = -1000
                popup.close()
              }
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
