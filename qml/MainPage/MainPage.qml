import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15
import QtQuick.Controls.Basic

ApplicationWindow {
  id: mainPage
  visible: true

  width: Screen.width
  height: Screen.height

  color: "white"

  Header {
    id: header
    anchors {
      top: parent.top
      left: parent.left
      right: parent.right
    }
  }
}
