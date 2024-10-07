import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15
import QtQuick.Controls.Basic

Text {
  id: currentRecipe

  text: "Суп з крупою та томатом"

  font {
    family: "DIN Alternate"
    pixelSize: 23
    bold: true
  }

  anchors {
    top: parent.bottom
    topMargin: 20

    left: parent.left
  }
}
