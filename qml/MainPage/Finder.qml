import QtQuick 2.15
import QtQuick.Controls.Basic 2.15
import QtQuick.Effects
import Qt5Compat.GraphicalEffects

Item {
  id: finderContainer

  width: parent.width
  height: 70

  focus: true
  Keys.onReleased: {
    textField.forceActiveFocus()
  }

  MouseArea {
    anchors.fill: parent
    onClicked: {
      textField.forceActiveFocus()
    }
  }

  TextField {
    id: textField

    anchors.fill: parent

    focus: true

    color: "black"

    leftPadding: magnifyingGlass.width + 32

    font {
      family: "DIN Alternate"
      pixelSize: 19
      bold: true
    }

    property string placeholderTexts: "Знайти рецепт за назвою"

    background: Rectangle {
      id: finderBackground

      color: "white"

      width: finderContainer.width
      height: finderContainer.height

      radius: 8

      border.color: "#E0E0E0"

      Image {
        id: magnifyingGlass
        source: "qrc:/icons/decorative/finder_magnifying_glass.png"
        width: 50
        height: 50
        fillMode: Image.PreserveAspectFit

        anchors {
          left: finderBackground.left
          leftMargin: 16
          verticalCenter: finderBackground.verticalCenter
        }
      }

      Text {
        text: textField.placeholderTexts
        color: "#aaaaaa"
        visible: textField.text.length === 0

        font {
          family: "DIN Alternate"
          pixelSize: 19
          bold: true
        }
        anchors {

          left: magnifyingGlass.right
          leftMargin: 16

          verticalCenter: finderBackground.verticalCenter
        }
      }
    }
  }
}
