import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Basic 2.15
import QtQuick.Layouts

Image {
  id: addReceiptIcon

  source: "qrc:icons/decorative/plusAddReceipt.png"

  width: 80
  height: 75

  anchors {
    verticalCenter: parent.verticalCenter

    right: parent.right
    rightMargin: 30
  }

  MouseArea {
    anchors.fill: parent
    onClicked: {

      // виклик функції для додвання рецепту
    }
  }
}
