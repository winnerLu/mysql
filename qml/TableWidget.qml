import QtQuick
import QtQuick.Controls
import TableModel

//自定义QtQuick 2中的TableView
Item {
    id: control
    implicitHeight: 300
    implicitWidth: 500

    property int verHeaderHeight: 30
    property int verHeaderWidth: 30
    property int horHeaderHeight: 30
    property color scrollBarColor: "#3e3e42"
    property variant columnWidthArr: [100,100,100,100,100,100,100,100,100,100,100,100]
    property color headerColor: "#252526"
    property color tableViewColor: "#252526"
    property color txtColor: "white"
    property color backgroundColor: "#808080"
    property alias horHearderAlias: table_model.horHeader
    property alias initDataAlias: table_model.initData
    property alias table_modelAlias: table_model

    TableModel{
        id: table_model
        horHeader: ["id","name","age","note"]
//        initData: [
//            {"id":1,"name":"zhangsan","age":20,"note":"********"},
//            {"id":2,"name":"lisi","age":21,"note":"********"},
//            {"id":3,"name":"wangwu","age":22,"note":"********"},
//            {"id":4,"name":"zhaoliu","age":23,"note":"********"}
//        ]
    }

    //表格内容（不包含表头）
    TableView{
        id: table_view
        anchors{
            fill: parent
            leftMargin: control.verHeaderWidth
            topMargin: control.horHeaderHeight+1
        }

        clip: true
        boundsBehavior: Flickable.StopAtBounds
        columnSpacing: 1
        rowSpacing: 1
        //此属性可以包含一个函数，该函数返回模型中每行的行高
        rowHeightProvider: function (row) {
            return control.verHeaderHeight;
        }
        //此属性可以保存一个函数，该函数返回模型中每个列的列宽
        columnWidthProvider: function (column) {
            return control.columnWidthArr[column];
        }
        ScrollBar.vertical: CusScrollBar {
            handleNormalColor: scrollBarColor
        }

        ScrollBar.horizontal: CusScrollBar {
            handleNormalColor: scrollBarColor
        }
        //model是在C++中定义的，和QtC++是类似的
        model: table_model
        delegate: Rectangle{
            color: tableViewColor
            Text {
                id: txt_table_model
                anchors.fill: parent
                text: model.value
                elide: Text.ElideRight
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                color: txtColor
            }
        }
        Component.onCompleted: console.log(model.value);
    }

    //横项表头
    Item{
        id: header_horizontal
        anchors{
            left: parent.left
            right: parent.right
            leftMargin: control.verHeaderWidth
        }
        height: control.horHeaderHeight
        z: 2
        //暂存鼠标拖动的位置
        property int posXTemp: 0
        MouseArea{
            anchors.fill: parent
            onPressed: {
                header_horizontal.posXTemp=mouseX;
            }
            onPositionChanged: {//按住表头可拖动表格向左右移动
                if(table_view.contentX+(header_horizontal.posXTemp-mouseX)>0){//contentX=0时不可再向右拖动
                    table_view.contentX+=(header_horizontal.posXTemp-mouseX);
                }else{
                    table_view.contentX=0;
                }
                header_horizontal.posXTemp=mouseX;
            }
        }
        Row {
            id: header_horizontal_row
            anchors.fill: parent
            leftPadding: -table_view.contentX
            clip: true
            spacing: 0

            Repeater {
                model: table_view.columns > 0 ? table_view.columns : 0

                Rectangle {
                    id: header_horizontal_item
                    width: table_view.columnWidthProvider(index)+table_view.columnSpacing
                    height: control.horHeaderHeight
                    color: headerColor

                    Text {
                        anchors.centerIn: parent
                        text: table_model.headerData(index, Qt.Horizontal)
                        color: txtColor
                    }
                    Rectangle{
                        width: 1
                        height: parent.height
                        anchors.right: parent.right
                        color: backgroundColor
                        opacity: 1
                    }
                    MouseArea{
                        width: 3
                        height: parent.height
                        anchors.right: parent.right
                        cursorShape: Qt.SplitHCursor
                        onPressed: header_horizontal.posXTemp=mouseX;
                        onPositionChanged: {
                            if((header_horizontal_item.width-(header_horizontal.posXTemp-mouseX))>10){
                                header_horizontal_item.width-=(header_horizontal.posXTemp-mouseX);
                            }else{
                                header_horizontal_item.width=10;
                            }
                            header_horizontal.posXTemp=mouseX;
                            control.columnWidthArr[index]=(header_horizontal_item.width-table_view.columnSpacing);
                            //刷新布局，这样宽度才会改变
                            table_view.forceLayout();
                        }
                    }
                }
            }
        }
    }
    Rectangle{
        z: 2
        width: control.verHeaderWidth
        height: control.verHeaderHeight
        color: control.headerColor
        anchors.top: parent.top
        anchors.left: header_verical.left
        anchors.topMargin: 0
    }

    //竖向表头
    Column {
        id: header_verical
        anchors{
            top: parent.top
            bottom: parent.bottom
            topMargin: control.horHeaderHeight+1
        }
        topPadding: -table_view.contentY
        z: 2
        clip: true
        spacing: 1
        Repeater {
            model: table_view.rows > 0 ? table_view.rows : 0
            Rectangle {
                width: control.verHeaderWidth
                height: table_view.rowHeightProvider(index)
                color: headerColor
                Text {
                    anchors.centerIn: parent
                    text: index
                    color: txtColor
                }
            }
        }
    }
}
