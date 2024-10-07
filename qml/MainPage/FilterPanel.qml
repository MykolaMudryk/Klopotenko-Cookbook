import QtQuick 2.15
import QtQuick.Effects

Item {

  MultiEffect {
    source: filterPanelContainer
    anchors.fill: filterPanelContainer
    //autoPaddingEnabled: true
    shadowBlur: 0.10
    shadowColor: 'black'
    shadowEnabled: true
    shadowVerticalOffset: 0
    shadowHorizontalOffset: 0
  }
  Rectangle {
    id: filterPanelContainer

    property int rectHeight: 220
    property int rectWidth: 254
    property int shadowSize: 10
    width: rectWidth
    height: rectHeight
    color: "white"

    Image {
      id: filterIcon
      source: "qrc:icons/decorative/filter.png"

      width: 60
      height: 60

      fillMode: Image.PreserveAspectFit

      anchors {
        left: filterPanelContainer.left
        top: filterPanelContainer.top
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
  }
}
