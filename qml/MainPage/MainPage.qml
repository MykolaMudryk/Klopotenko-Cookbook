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

    DropdownButton {
      id: dropdownReceiptButton
    }
    AddReceiptButton {
      id: addReceiptButton
    }

    Finder {
      id: finderLine

      anchors {
        top: header.bottom
        topMargin: 17

        left: dropdownReceiptButton.left

        right: addReceiptButton.right
      }

      BreadCrumbNavigation {
        id: breadCrumbNavigation

        anchors {
          top: finderLine.bottom
          topMargin: 13

          left: finderLine.left
        }

        CurrentRecipe {
          id: currentRecipe
        }

        FilterPanel {
          id: filterPanel

          anchors {
            top: currentRecipe.bottom // встановлюємо анкор до нижньої частини `currentRecipe`
            topMargin: 25 // задаємо відступ від нижньої частини

            left: currentRecipe.left
          }
        }
      }
    }
  }
}
