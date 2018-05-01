#include "promanage.h"
#include "ui_promanage.h"
#include <QDateTime>
#include "app/Connection.h"

ProManage::ProManage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProManage)
{
    ui->setupUi(this);
    this->initForm();
}

ProManage::~ProManage()
{
    delete ui;
}

void ProManage::initForm()
{
    //mythread.SetCurrentTime(ui->Datetimelabel);
    /***************����һ����ʱ����������ʾϵͳ��ǰ��ʱ��*************/
    timer = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(showtimeslot()));
    timer->start(1000);

    QueryModel = new QSqlQueryModel(this);
    //��ʼ������������п�
    ColumnNames[0] = QString::fromLocal8Bit("������");
    ColumnNames[1] = QString::fromLocal8Bit("��������");
    ColumnNames[2] = QString::fromLocal8Bit("����۸�");
    ColumnNames[3] = QString::fromLocal8Bit("����״̬");
    ColumnNames[4] = QString::fromLocal8Bit("��ע");

    ColumnWidths[0] = 80;
    ColumnWidths[1] = 120;
    ColumnWidths[2] = 120;
    ColumnWidths[3] = 120;
    ColumnWidths[4] = 200;

    //mysql = new MysqlApi(this);//ʵ�������ݿ���������Ա��Ժ����
    //mysql->SetControl(ui->tableView,ui->labInfo,ui->btnFirst,ui->btnPre,ui->btnNext,ui->btnLast);
    //mysql->BindData("Room","RoomId","dec",10,ColumnNames,ColumnWidths);
    BindHotelInfo("Room",ui->tableView,ColumnNames,ColumnWidths);

    this->connect(ui->tableView,SIGNAL(clicked(QModelIndex)),SLOT(showCurrentRoomNo()));
    roomstate = "";
    roomtypename = "";
    roomlayer = "";
}

/*
 *�������ܣ�ʵ�����ݰ�
 *������������ݱ�����tableview�����������п��
 *�����������
 *����ֵ����
*/
void ProManage::MyBindTable(QString tableName, QTableView *tableView, QString columnNames[], int columnWidths[])
{
    TableView = tableView;
    QString sql = "SELECT * FROM " + tableName;
    QueryModel->setQuery(sql);
    TableView->setModel(QueryModel);

    //���������б��⡢�п��
    for (int i = 0;i<TableView->model()->columnCount();i++)
    {
        QueryModel->setHeaderData(i,Qt::Horizontal,columnNames[i]);     //�����б���
        TableView->setColumnWidth(i,columnWidths[i]);                   //�����п�
    }

    TableView->horizontalHeader()->setHighlightSections(false);         //�����ͷʱ���Ա�ͷ����
    TableView->setSelectionMode(QAbstractItemView::ContiguousSelection);//ѡ��ģʽΪ����ѡ��
    TableView->setSelectionBehavior(QAbstractItemView::SelectRows);     //ѡ������
    TableView->setStyleSheet( "QTableView::item:hover{background-color:rgb(92,188,227,200)}"
                              "QTableView::item:selected{background-color:#1B89A1}");
}

/*
 *�������ܣ����ͷ���Ϣ��ʾ��tableview��
 *˵������ʾ�ͷ���Ϣʱ�õ����ű���Ҫ��������
*/
void ProManage::BindHotelInfo(QString tableName, QTableView *tableView, QString columnNames[], int columnWidths[])
{
    TableView = tableView;
    QString sql = "SELECT RoomNo,Typename,TypePrice,RoomState,RoomRemark FROM " + tableName+
            ",RoomType where room.RoomTypeId=roomtype.RoomTypeId;";

    QueryModel->setQuery(sql);
    TableView->setModel(QueryModel);

    //���������б��⡢�п��
    for (int i = 0;i<TableView->model()->columnCount();i++)
    {
        QueryModel->setHeaderData(i,Qt::Horizontal,columnNames[i]);     //�����б���
        TableView->setColumnWidth(i,columnWidths[i]);                   //�����п�
    }

    TableView->horizontalHeader()->setHighlightSections(false);         //�����ͷʱ���Ա�ͷ����
    TableView->setSelectionMode(QAbstractItemView::ContiguousSelection);//ѡ��ģʽΪ����ѡ��
    TableView->setSelectionBehavior(QAbstractItemView::SelectRows);     //ѡ������
    TableView->setStyleSheet( "QTableView::item:hover{background-color:rgb(92,188,227,200)}"
                              "QTableView::item:selected{background-color:#1B89A1}");
}

/*
 *�������ܣ�������  ������
 *������������������������������ʽ(�������)�����������������
 *˵��������ʱ�����Ӧ�Ĳ���
*/
void ProManage::BindDataSelect(QString tableName,QTableView *tableView, QString orderColumn, QString orderType, QString where, QString columnNames[], int columnWidths[])
{
    TableView = tableView;
    QString sql = "SELECT RoomNo,Typename,TypePrice,RoomState,RoomRemark FROM " + tableName+
            ",RoomType where room.RoomTypeId=roomtype.RoomTypeId"+" "+where+" order by "+orderColumn+" "+orderType+";";
    qDebug() <<sql;
    QueryModel->setQuery(sql);
    TableView->setModel(QueryModel);

    //���������б��⡢�п��
    for (int i=0;i<TableView->model()->columnCount();i++){
        QueryModel->setHeaderData(i,Qt::Horizontal,columnNames[i]);//�����б���
        TableView->setColumnWidth(i,columnWidths[i]);//�����п�
    }


    TableView->horizontalHeader()->setHighlightSections(false);//�����ͷʱ���Ա�ͷ����
    TableView->setSelectionMode(QAbstractItemView::SingleSelection);//ѡ��ģʽΪ����ѡ��
    TableView->setSelectionBehavior(QAbstractItemView::SelectRows);//ѡ������
    TableView->setStyleSheet( "QTableView::item:hover{background-color:rgb(92,188,227,200)}"
                              "QTableView::item:selected{background-color:#1B89A1}");
}

/*
 *�������ܣ���ʾϵͳʱ��
*/
void ProManage::showtimeslot()
{
    ui->Datetimelabel->setText(QDateTime::currentDateTime().toString(tr("yyyy-MM-dd\ndddd HH:mm")));
}

/*
 *�������ܣ���ʾ��ǰ������
*/
void ProManage::showCurrentRoomNo()
{
    QSqlQueryModel userMode(ui->tableView);
    QString sql = "SELECT RoomNo,Typename,TypePrice,RoomState,RoomRemark FROM Room,RoomType where "
            "room.RoomTypeId = roomtype.RoomTypeId";
    qDebug() <<sql;
    userMode.setQuery(QString(sql));
    int Row = ui->tableView->currentIndex().row();
    QSqlRecord record = userMode.record(Row);
    ui->labelRoomNo->setText(record.value(0).toString());
}

/*
 *�������ܣ����������͸ı�ʱ����Ӧ�����Ҳ�ı�
 *˵������ǰ���������е��˼䣬˫�˼䣬�����׼䣬��ͳ�׼�
*/
void ProManage::on_comboBoxRoomType_activated(const QString &arg1)
{
    qDebug() <<QString::fromLocal8Bit("��ʾ")<<arg1<<QString::fromLocal8Bit("��Ϣ");
    QString sql = "and Typename='"+arg1+"'";
    if(arg1 == QString::fromLocal8Bit("���з���"))
    {
        sql = "";
    }
    roomtypename = sql;

    if(ui->checkBox->isChecked() == true)
    {

        sql += roomstate;
    }
    if(ui->checkBox_2->isChecked() == true)
    {

        sql += roomlayer;
    }
    BindDataSelect("Room",ui->tableView,"RoomNo","asc",sql,ColumnNames,ColumnWidths);
}

/*
 *�������ܣ�������¥��仯ʱ���ı���Ӧ�����
*/
void ProManage::on_comboBoxRoomfloor_activated(const QString &arg1)
{
    qDebug() <<QString::fromLocal8Bit("��ʾ")<<arg1<<QString::fromLocal8Bit("������Ϣ");
    QString sql = " ";
    if(arg1 == QString::fromLocal8Bit("1��"))
    {
        sql+= " and RoomNo like '1__'";
    }
    else if(arg1 == QString::fromLocal8Bit("2��"))
    {
        sql+=" and RoomNo like '2__'";
    }
    else if(arg1 == QString::fromLocal8Bit("3��"))
    {
        sql+=" and RoomNo like '3__'";
    }
    else if(arg1 == QString::fromLocal8Bit("4��"))
    {
        sql+=" and RoomNo like '4__'";
    }
    else if(arg1 == QString::fromLocal8Bit("5��"))
    {
        sql+=" and RoomNo like '5__'";
    }
    else if(arg1 == QString::fromLocal8Bit("6��"))
    {
        sql+=" and RoomNo like '6__'";
    }
    else if(arg1 == QString::fromLocal8Bit("7��"))
    {
        sql+=" and RoomNo like '7__'";
    }
    else if(arg1 == QString::fromLocal8Bit("8��"))
    {
        sql+=" and RoomNo like '8__'";
    }
    else if(arg1 == QString::fromLocal8Bit("9��"))
    {
        sql+=" and RoomNo like '9__'";
    }
    else if(arg1 == QString::fromLocal8Bit("10��"))
    {
        sql+=" and RoomNo like '1___'";
    }
    roomlayer = sql;

    if(ui->checkBox->isChecked() == true)
    {

        sql += roomstate;
    }
    if(ui->checkBox_3->isChecked() == true)
    {

        sql += roomtypename;
    }

    BindDataSelect("Room",ui->tableView,"RoomNo","asc",sql,ColumnNames,ColumnWidths);
}

/*
 *�������ܣ������� ״̬�仯ʱ���ı���Ӧ�����
*/
void ProManage::on_comboBoxRoomStatus_activated(const QString &arg1)
{
    qDebug() <<QString::fromLocal8Bit("��ʾ")<<arg1<<QString::fromLocal8Bit("������Ϣ");
    QString sql = " ";
    if(arg1 == QString::fromLocal8Bit("���޷�̬"))
    {
        sql +="";
    }
    else if(arg1 == QString::fromLocal8Bit("�޿շ�"))
    {
        sql +=" and RoomState = '";
        sql +=QString::fromLocal8Bit("��");//�����ַ��������� ֻ�ֿܷ�д
        sql +="'";
    }
    else if(arg1 == QString::fromLocal8Bit("��ס�ͷ�"))
    {
//        sql +=" and RoomState = '��'";
        sql +=" and RoomState = '";
        sql +=QString::fromLocal8Bit("��");//�����ַ��������� ֻ�ֿܷ�д
        sql +="'";
    }
    else if(arg1 == QString::fromLocal8Bit("�ޱ�����"))
    {
//        sql +=" and RoomState = '����'";
        sql +=" and RoomState = '";
        sql +=QString::fromLocal8Bit("����");//�����ַ��������� ֻ�ֿܷ�д
        sql +="'";
    }
    else if(arg1 == QString::fromLocal8Bit("��ά�޷�"))
    {
//        sql +=" and RoomState = 'ά��'";
        sql +=" and RoomState = '";
        sql +=QString::fromLocal8Bit("ά��");//�����ַ��������� ֻ�ֿܷ�д
        sql +="'";
    }
    roomstate = sql;
    if(ui->checkBox_2->isChecked() == true)
    {

        sql += roomlayer;
    }
    if(ui->checkBox_3->isChecked() == true)
    {

        sql += roomtypename;
    }
    BindDataSelect("Room",ui->tableView,"RoomNo","asc",sql,ColumnNames,ColumnWidths);
}
