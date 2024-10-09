import QtQuick 2.15
import QtQuick.Effects
import QtQuick.Controls.Basic 2.15

Item {
  id: filterPanelContainer

  MultiEffect {
    source: filterPanelBackground
    anchors.fill: filterPanelBackground
    shadowBlur: 0.10
    shadowColor: 'black'
    shadowEnabled: true
    shadowVerticalOffset: 0
    shadowHorizontalOffset: 0
  }
  Rectangle {
    id: filterPanelBackground

    property int rectHeight: 350
    property int rectWidth: 254
    property int shadowSize: 10
    width: rectWidth
    height: rectHeight
    color: "white"
    radius: 5

    Image {
      id: filterIcon
      source: "qrc:icons/decorative/filter.png"

      width: 60
      height: 60

      fillMode: Image.PreserveAspectFit

      anchors {
        left: filterPanelBackground.left
        top: filterPanelBackground.top
      }

      Text {
        id: filterText
        text: qsTr("Фільтри")

        font {
          family: "DIN Alternate"

          pixelSize: 23
          bold: true
        }

        anchors {
          left: filterIcon.left
          leftMargin: 53

          verticalCenter: filterIcon.verticalCenter
        }
      }
    }

    Rectangle {
      id: categoryColumnBackground

      width: 254
      height: 40
      color: "white"

      anchors {
        top: filterPanelBackground.top
        topMargin: 60
      }

      Button {
        id: categoryFilter
        width: 254
        height: 40

        onClicked: {

          menuCategoryModel.fetchCategories()
        }

        Connections {
          target: menuCategoryModel
          function onCategoryForFilter() {
            categoryListContainer.isOpen = !categoryListContainer.isOpen

            console.log("menuCategoryModel.rowCount:", menuCategoryModel.rowCount(),
                        "Clicked. isAnimating:",
                        categoryListContainer.isAnimating)

            console.log("isOpen змінено на:", categoryListContainer.isOpen)
            console.log("Поточна висота:", categoryListContainer.height)
          }
        }

        contentItem: Text {
          id: categoryDropDownText
          text: "Категорії страв"
          font {
            family: "DIN Alternate"
            pixelSize: 20
            bold: true
          }
          color: "black"
          anchors {
            left: parent.left
            leftMargin: 8
            verticalCenter: parent.verticalCenter
          }
        }

        background: Rectangle {
          id: categoryDropDownBackground
          color: "white"
          anchors.fill: parent

          Rectangle {
            id: topLine
            height: 1
            color: "lightgray"

            anchors {
              top: parent.top
              left: parent.left
              right: parent.right
            }
          }

          Image {
            id: filterArrowIcon
            source: "qrc:icons/decorative/filter_arrow.png"
            width: 30
            height: 30
            fillMode: Image.PreserveAspectFit

            anchors {
              right: parent.right
              rightMargin: 16
              verticalCenter: parent.verticalCenter
            }

            RotationAnimation {
              id: arrowRotation

              target: filterArrowIcon
              from: 0
              to: 180
              duration: 200
            }
          }
        }

        Rectangle {
          id: categoryListContainer
          property bool isFetching: false
          property bool isAnimating: false

          property bool isOpen: false

          width: filterPanelBackground.width
          height: isOpen ? menuCategoryModel.rowCount() * 40 : 0

          color: "white"
          radius: filterPanelBackground.radius
          anchors {
            top: categoryDropDownBackground.bottom
          }

          Rectangle {
            id: bottomLine
            height: 1
            color: "lightgray"

            anchors {
              top: categoryListContainer.bottom
              left: parent.left
              right: parent.right
            }
          }

          Behavior on height {
            SmoothedAnimation {
              id: heightChanged
              duration: 200
              easing.type: Easing.InOutQuad
            }
          }

          onIsOpenChanged: {
            if (isOpen) {
              arrowRotation.from = 0
              arrowRotation.to = 180
            } else {
              arrowRotation.from = 180
              arrowRotation.to = 0
            }

            arrowRotation.start()
          }

          Column {
            id: categoryColumn
            width: parent.width
            height: childrenRect.height

            Repeater {
              model: categoryListContainer.height > 0 ? menuCategoryModel : null
              delegate: Rectangle {
                id: dropdownColumnBackground
                width: parent.width
                implicitHeight: 40

                color: "transparent"
                Row {
                  spacing: 14
                  anchors.fill: parent
                  anchors.margins: 10

                  CheckBox {
                    id: categoryCheckBox
                    checked: false
                    height: 20
                  }

                  Text {
                    id: categoryText
                    text: model.categoryName
                    font {
                      family: "DIN Alternate"
                      pixelSize: 18
                      bold: true
                    }
                    color: "black"
                    anchors.verticalCenter: categoryCheckBox.verticalCenter
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}
