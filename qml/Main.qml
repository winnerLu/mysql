import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
ApplicationWindow {
    id: root
    visible: true
    width: 800
    height: 600
    title: "MySQL Database Connection"
    property string resultText: ""

    Button{
        id: connectDatabase
        width: 80
        height: 40
        anchors.top: parent.top
        anchors.left: parent.left
        text: qsTr("Connect")
        onClicked: {
            inputConnectInfo.visible=true;
        }
    }
    Button{
        id: test
        width: 80
        height: 40
        anchors.top: parent.top
        anchors.left: connectDatabase.right
        text: qsTr("Test")
        onClicked: {
            databaseManager.deleteToTableTrajectory(2);
        }
    }
    Switch{
        id: connect
        anchors.right: parent.right
        text: qsTr("Connect")
        onClicked: {
            if(connect.visualPosition>0.5){
                inputConnectInfo.visible=true;
            }else{
                databaseManager.disconnectDatabase()
                closedPopup.visible=true;
            }

        }
    }

    Popup{
        id: inputConnectInfo
        width: 250
        height: 180
        anchors.centerIn: parent
        visible: false

        GridLayout{
            columns: 2

            Text {
                id: txtHostName
                text: qsTr("Host Name")
            }
            TextField {
                id: hostNameInput
                placeholderText: "Host Name"
                text: qsTr("localhost")
            }

            Text {
                id: txtPort
                text: qsTr("Port")
            }
            TextField {
                id: portInput
                placeholderText: "Port"
                text: qsTr("3306")
            }

            Text {
                id: txtDatabaseName
                text: qsTr("DatabaseName")
            }
            TextField {
                id: dbNameInput
                placeholderText: "Database Name"
                text: qsTr("track")
            }

            Text {
                id: txtUserName
                text: qsTr("User Name")
            }
            TextField {
                id: userNameInput
                placeholderText: "User Name"
                text: qsTr("root")
            }

            Text {
                id: txtPassword
                text: qsTr("Password")
            }
            TextField {
                id: passwordInput
                placeholderText: "Password"
                echoMode: TextInput.Password
                text: "123456"
            }

            Button{
                id: cancelInput
                width: 80
                height: 40
                text: "取消"
                onClicked: {
                    inputConnectInfo.visible=false;
                }
            }

            Button{
                id: confirmInput
                width: 80
                height: 40
                text: "确认"
                onClicked: {
                    databaseManager.connectToDatabase(hostNameInput.text,
                                                      parseInt(portInput.text),
                                                      dbNameInput.text,
                                                      userNameInput.text,
                                                      passwordInput.text);
                    inputConnectInfo.visible=false;
                }
            }
        }
    }

    // 显示连接结果的弹窗
    Popup {
        id: resultPopup
        visible: false
        width: 200
        height: 100
        topInset: 0
        bottomInset: 0
        leftInset: 0
        rightInset: 0
        topPadding: 0
        bottomPadding: 0
        leftPadding: 0
        rightPadding: 0
        anchors.centerIn: parent
        modal: true
        background: Rectangle{
            color: "lightblue"
        }

        Rectangle {
            anchors.fill: parent
            color: "lightblue"

            Text {
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment:Text.AlignVCenter
                text: resultText
                wrapMode: Text.WordWrap
            }
        }

        Rectangle{
            id: rectExit
            width: 10
            height: 10
            anchors.right: parent.right
            anchors.top: parent.top
            color: "white"
            Text{
                id: txtExit
                anchors.centerIn: parent
                text: qsTr("X")
                color: "black"
            }

            MouseArea{
                anchors.fill: parent
                hoverEnabled: true
                onEntered: {
                    rectExit.color="red";
                    txtExit.color="white";
                }
                onExited: {
                    rectExit.color="white";
                    txtExit.color="black";
                }
                onPressed: {
                    rectExit.color=Qt.lighter("red");
                }

                onClicked: {
                    resultPopup.visible=false;
                }
            }
        }
    }
    Popup{
        id: closedPopup
        visible: false
        width: 200
        height: 100
        topPadding: 0
        bottomPadding: 0
        leftPadding: 0
        rightPadding: 0
        anchors.centerIn: parent
        modal: true
        background: Rectangle{
            color: "lightblue"
        }
        Rectangle {
            anchors.fill: parent
            color: "lightblue"

            Text {
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment:Text.AlignVCenter
                text: qsTr("Closed!")
                wrapMode: Text.WordWrap
            }
        }
        Rectangle{
            id: rectExit2
            width: 10
            height: 10
            anchors.right: parent.right
            anchors.top: parent.top
            color: "white"
            Text{
                id: txtExit2
                anchors.centerIn: parent
                text: qsTr("X")
                color: "black"
            }

            MouseArea{
                anchors.fill: parent
                hoverEnabled: true
                onEntered: {
                    rectExit2.color="red";
                    txtExit2.color="white";
                }
                onExited: {
                    rectExit2.color="white";
                    txtExit2.color="black";
                }
                onPressed: {
                    rectExit2.color=Qt.lighter("red");
                }

                onClicked: {
                    closedPopup.visible=false;
                }
            }
        }
    }

    // 在连接结果发生变化时更新弹窗内容
    Connections {
        target: databaseManager
        function onConnectionResult(success, errorMessage) {//槽函数
                resultPopup.visible = true;
                resultText = success ? "连接成功" : "连接失败：" + errorMessage;
            }
    }

    TableWidget{
        id: tableView
        y: root.height/2
        horHearderAlias: ["student_id", "student_name", "class_id"]
        //initDataAlias: [{"student_id":"","student_name":"","class_id":""}]
    }

    Connections{
        target: databaseManager
        function onInitTableWidgetData(m_modelData){
            tableView.table_modelAlias.loadData(m_modelData);
        }
    }

    Button{
        id: btnQuery
        width: 100
        height: 50
        anchors.left: tableView.right
        anchors.leftMargin: 10
        anchors.top: tableView.top
        text: qsTr("Query")

        onClicked: {
            console.log("btnQuery.Clicked!");
            databaseManager.queryTable();
        }
    }

    Button{
        id: btnInsert
        width: 100
        height: 50
        anchors.left: btnQuery.right
        anchors.leftMargin: 10
        anchors.top: tableView.top
        text: qsTr("Insert")

        onClicked: {
            console.log("btnInsert.Clicked!");
            insertInfo.visible=true;
        }
    }

    Popup{
        id: insertInfo
        width: 230
        height: 120
        anchors.centerIn: parent
        closePolicy: Popup.CloseOnEscape
        visible: false
        focus: true

        GridLayout{
            columns: 2

            Text {
                id: txtStudentID
                text: qsTr("Student ID")
            }
            TextField {
                id: studentIDInput
                placeholderText: "Student ID"
            }

            Text {
                id: txtStudentName
                text: qsTr("Student Name")
            }
            TextField {
                id: studentNameInput
                placeholderText: "Student Name"
            }

            Text {
                id: txtClassID
                text: qsTr("Class ID")
            }
            TextField {
                id: classIDInput
                placeholderText: "Class ID"
            }

            Button{
                id: cancelInsertInput
                width: 80
                height: 40
                text: "取消"
                onClicked: {
                    studentIDInput.text="";
                    studentNameInput.text="";
                    classIDInput.text="";
                    insertInfo.close()
                }
            }

            Button{
                id: confirmInsertInput
                width: 80
                height: 40
                text: "确认"
                onClicked: {
                    databaseManager.insertToDatabase(parseInt(studentIDInput.text),
                                                      studentNameInput.text,
                                                      classIDInput.text,
                                                      );
                    databaseManager.queryTable();
                    insertInfo.visible=false;
                }
            }
        }
    }

    Button{
        id: btnDelete
        width: 100
        height: 50
        anchors.left: btnQuery.left
        anchors.topMargin: 10
        anchors.top: btnQuery.bottom
        text: qsTr("Delete")

        onClicked: {
            console.log("btnDelete.Clicked!");
            deleteInfo.visible=true;
        }
    }

    Popup{
        id: deleteInfo
        width: 230
        height: 100
        anchors.centerIn: parent
        closePolicy: Popup.CloseOnEscape
        visible: false
        focus: true

        GridLayout{
            columns: 2

            Text {
                id: txtStudentIDDelete
                text: qsTr("Student ID")
            }
            TextField {
                id: studentIDDeleteInput
                placeholderText: "Student ID"
            }

            Button{
                id: cancelDeleteInput
                width: 80
                height: 40
                text: "取消"
                onClicked: {
                    txtStudentIDDelete.text="";
                    deleteInfo.close()
                }
            }

            Button{
                id: confirmDeleteInput
                width: 80
                height: 40
                text: "确认"
                onClicked: {
                    databaseManager.deleteToDatabase(parseInt(studentIDDeleteInput.text));
                    databaseManager.queryTable();
                    deleteInfo.visible=false;
                }
            }
        }
    }

    Button{
        id: btnModify
        width: 100
        height: 50
        anchors.left: btnDelete.right
        anchors.leftMargin: 10
        anchors.top: btnDelete.top
        text: qsTr("Modify")

        onClicked: {
            console.log("btnModify.Clicked!");
            modifyInfo.visible=true;
        }
    }

    Popup{
        id: modifyInfo
        width: 230
        height: 120
        anchors.centerIn: parent
        closePolicy: Popup.CloseOnEscape
        visible: false
        focus: true

        GridLayout{
            columns: 2

            Text {
                id: txtStudentIDModify
                text: qsTr("Student ID")
            }
            TextField {
                id: studentIDInputModify
                placeholderText: "Student ID"
            }

            Text {
                id: txtStudentNameModify
                text: qsTr("Student Name")
            }
            TextField {
                id: studentNameInputModify
                placeholderText: "Student Name"
            }

            Text {
                id: txtClassIDModify
                text: qsTr("Class ID")
            }
            TextField {
                id: classIDInputModify
                placeholderText: "Class ID"
            }

            Button{
                id: cancelInsertInputModify
                width: 80
                height: 40
                text: "取消"
                onClicked: {
                    studentIDInputModify.text="";
                    studentNameInputModify.text="";
                    classIDInputModify.text="";
                    modifyInfo.close()
                }
            }

            Button{
                id: confirmInsertInputModify
                width: 80
                height: 40
                text: "确认"
                onClicked: {
                    databaseManager.modifyToDatabase(parseInt(studentIDInputModify.text),
                                                      studentNameInputModify.text,
                                                      classIDInputModify.text,
                                                      );
                    databaseManager.queryTable();
                    modifyInfo.visible=false;
                }
            }
        }
    }

    GridLayout{
        columns: 2
        width: 300
        height: 110
        anchors.left: btnQuery.left
        anchors.top: btnDelete.bottom
        anchors.topMargin: 10
        Button{
            id: queryFromStudentID
            width: 80
            height: 40
            text: qsTr("按ID查询")
            onClicked: {

            }
        }

        TextField {
            id: studentIDInputQuery
            placeholderText: "Student ID"
        }

        Button{
            id: queryFromStudentName
            width: 80
            height: 40
            text: qsTr("按名字查询")
            onClicked: {

            }
        }

        TextField {
            id: studentNameInputQuery
            placeholderText: "Student Name"
        }
    }

}
