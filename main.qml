import QtQuick 2.15
import QtQuick.Window 2.15
import QtCharts 2.15
import QtQuick.Dialogs 1.0
import QtQuick.Controls 2.15
import textfile 1.0
import QtQuick.Controls.Material 2.15

ApplicationWindow {
    id:window
    width: 640
    height: 480
    visible: true
    title: qsTr("BarChart")

    Material.theme: Material.Dark

    TextFile {
        id:textFile
    }

    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        folder: shortcuts.home
        nameFilters: [ "Text files (*.txt)" ]
        onAccepted: textFile.fileName = fileUrl
    }

    ProgressBar {
        id: progressBar
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: selectFileBtn.top
        value: textFile.progress
    }

    ChartView {
        id:barChartView
        anchors.top: parent.top
        anchors.bottom: progressBar.top
        anchors.right: parent.right
        anchors.left: parent.left
        legend.visible: false
        antialiasing: true
        BarSeries {
            labelsVisible: true
            labelsAngle: 270
            axisX: BarCategoryAxis { categories: textFile.topWords }
            axisY: ValueAxis{ max:textFile.maxValue}
            BarSet {values: textFile.topValues}
        }
    }

    ItemDelegate {
        id:selectFileBtn
        text: "выбрать файл"
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        onClicked: fileDialog.visible = true
    }
}
