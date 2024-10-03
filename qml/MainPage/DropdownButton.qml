import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Basic 2.15
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects

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

    horizontalAlignment: Text.AlignLeft
    verticalAlignment: Text.AlignVCenter

    color: "white"

    anchors {
      left: parent.left
      leftMargin: 20
    }
  }

  background: Rectangle {
    id: receiptDropDownBackground
    color: "#6b80ef"

    anchors.fill: parent

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
    property bool isInCategoryList: false

    property string selectedCategoryName: ""
    property string lastCategoryName: ""

    background: Rectangle {
      id: popupContainer

      width: parent.width
      height: parent.height

      color: "transparent"
    }

    // close nationality when popup exited
    MouseArea {
      onExited: {
        nationalityColumn.x = -1000
      }
    }
    Rectangle {
      id: categoryColumnBackground

      radius: 7

      width: receiptDropDown.width + 40
      height: categoryModel.rowCount * 50

      color: "#f0f0f0"

      x: receiptDropDownBackground.x + 14
      y: receiptDropDownBackground.y + receiptDropDownBackground.height

      Column {
        id: categoryColumn

        width: categoryColumnBackground.width
        height: childrenRect.height

        Repeater {
          model: categoryModel

          delegate: Rectangle {
            id: dropdownColumnBackground

            width: categoryColumnBackground.width
            height: 50

            MouseArea {
              id: categoryHoverArea

              anchors.fill: parent

              hoverEnabled: true

              onEntered: {
                parent.color = "#f6f7f8"

                popup.selectedCategoryName = model.categoryName

                if (popup.selectedCategoryName !== popup.lastCategoryName) {
                  nationalityModel.clearNationalities()
                  popup.lastCategoryName = popup.selectedCategoryName
                }

                nationalityModel.fetchNationality(model.categoryName)

                nationalityColumn.x = categoryColumn.x + categoryColumn.width

                nationalityColumn.y = dropdownColumnBackground.y
              }

              onExited: {
                parent.color = "white"

                if (!popup.isInNationalityList) {
                  nationalityModel.clearNationalities()
                }
              }

              onClicked: {
                nationalityColumn.x = -1000
                nationalityModel.clearNationalities()
                popup.close()
              }
            }

            Row {
              id: categoryRow
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

      Rectangle {
        id: nationalityСolumnBackground

        width: receiptDropDown.width + 40
        height: nationalityModel.rowCount * 50

        color: "#f0f0f0"

        radius: receiptDropDownBackground.radius

        Column {
          id: nationalityColumn

          width: nationalityСolumnBackground.width
          height: childrenRect.height

          y: categoryColumn.y + categoryColumn.height

          Repeater {
            model: nationalityModel

            delegate: Rectangle {
              id: nationalityColumnBackground

              width: nationalityСolumnBackground.width

              height: 50

              MouseArea {
                id: nationalityHoverArea

                anchors.fill: parent

                hoverEnabled: true

                onEntered: {
                  popup.isInNationalityList = true
                  parent.color = "#f6f7f8"

                  dishNameModel.fetchDishName(popup.selectedCategoryName,
                                              model.nationality)

                  dishNameColumn.x = nationalityColumn.x + nationalityColumn.width

                  dishNameColumn.y = nationalityColumnBackground.y + nationalityColumn.y
                }

                onExited: {
                  popup.isInNationalityList = false
                  parent.color = "white"

                  if (!popup.isInCategoryList) {
                    dishNameModel.clearDishNames()
                  }
                }

                onClicked: {
                  nationalityColumn.x = -1000
                  popup.close()

                  dishNameModel.clearDishNames()
                }
              }

              Row {

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

      Rectangle {
        id: dishNameСolumnBackground

        width: receiptDropDown.width + 40
        height: dishNameModel.rowCount * 50

        color: "#f0f0f0"

        radius: receiptDropDownBackground.radius

        Column {
          id: dishNameColumn

          width: dishNameСolumnBackground.width
          height: childrenRect.height

          // y: nationalityColumn.y + nationalityColumn.height + nationalityColumnBackground.y
          Repeater {
            model: dishNameModel

            delegate: Rectangle {
              id: columnBackground

              width: dishNameСolumnBackground.width

              height: 50

              MouseArea {
                id: dishNameHoverArea

                anchors.fill: parent

                hoverEnabled: true

                onEntered: {
                  popup.isInCategoryList = true
                  parent.color = "#f6f7f8"
                }

                onExited: {
                  popup.isInCategoryList = false
                  parent.color = "white"
                }

                onClicked: {
                  dishNameColumn.x = -1000
                  popup.close()
                }
              }

              Row {
                anchors.fill: parent
                anchors.margins: 10

                anchors.verticalCenter: columnBackground.verticalCenter

                Text {
                  text: model.dishName
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
}
