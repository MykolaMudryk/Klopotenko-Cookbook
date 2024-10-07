import QtQuick 2.15

Image {
  id: houseIcon

  source: "qrc:/icons/decorative/breadcrumb_house.png"

  width: 45
  height: 45

  fillMode: Image.PreserveAspectFit

  Row {
    id: breadCrumbRow

    anchors {

      verticalCenter: houseIcon.verticalCenter

      left: parent.right
      leftMargin: 10
    }

    Text {
      text: breadCrumb.breadCrumbRow
      color: "black"

      font {
        family: "DIN Alternate"
        pixelSize: 16
        bold: true
      }
    }
  }
}
