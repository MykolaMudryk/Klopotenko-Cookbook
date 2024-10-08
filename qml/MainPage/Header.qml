import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Basic 2.15
import QtQuick.Layouts

Rectangle {
  id: grayBackground

  height: 76
  width: parent.width

  color: "#555555"

  Text {
    id: klopotenkoTittleWord

    text: "Smart"
    color: "#6e9fec" // color from "line" word in hotline site

    font {

      pixelSize: 30

      bold: true
    }

    anchors {
      horizontalCenter: grayBackground.horizontalCenter

      top: dropdownReceiptButton.top
    }
  }

  Text {
    id: cookBookTittleWord

    text: "<span style='color:#ffa726;'>cook</span><span style='color:#6e9fec;'>book</span>"

    textFormat: Text.RichText

    font {

      pixelSize: 30

      bold: true
    }

    anchors {
      horizontalCenter: grayBackground.horizontalCenter

      bottom: grayBackground.bottom
      bottomMargin: 4
    }
  }
}
