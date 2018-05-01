/***************************************************************
 *Copyright(c) 2014-2015 Company By LiQi
 *All rights reserved.
 *�ļ����ƣ����ݿ�Ĵ����ļ�
 *��Ҫ�������������ݿ⣬���ݱ�
 *
 *��ǰ�汾��V1.0
 *���ߣ�Kelvin Li
 *�������ڣ�2014/12
 *˵����Email:creazylq@163.com
*****************************************************************/
#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlError>

/*
 *�������ܣ����������ﲢ����
 *˵�����˺������Խ����������ݿ⣬�����Ӳ��ϣ��������Ĵ�����ʾ
*/
static bool createConnection()
{
    QSqlDatabase db;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        db = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        //db = QSqlDatabase::addDatabase("QMYSQL"); //����һ�����ݿ�
        db = QSqlDatabase::addDatabase("QSQLITE"); //����һ�����ݿ� �������ݿ���������ϵͳ��û�ж�Ӧ�����ݿ�

    }

    db.setHostName("localhost");                            //���ص�ַ����ҪԶ�����ӣ�������Ӧ�ĵ�ַ��
//    db.setPort(3306);                                       //���ö˿ں�
    db.setDatabaseName("SmartHome.db");                            //�������ݿ������
    db.setUserName("root");                                 //�����û�����
    db.setPassword("123456");                               //��������
    if(!db.open())
    {
        qCritical("Can't open database: %s(%s)",
                  db.lastError().text().toLocal8Bit().data(),
                  qt_error_string().toLocal8Bit().data());

        return false;
    }

#if 0
   QSqlQuery query;
   /***************************�� ��  �� ****************************
    *�û��˺š��û��������û����롢�û����ͣ�����Ա/�ۻ�Ա��
   */
   query.exec(QObject::tr("create table UserInfo (UserId vchar(4) primary key not null,"
                          "UserName vchar(10),UserPwd vchar(10),UserType vchar(20))"));
   query.exec(QObject::tr("insert into UserInfo values ('1001','admin','admin','����Ա')"));
   query.exec(QObject::tr("insert into UserInfo values ('1002','С��','admin','�ۻ�Ա')"));


   /*
    *��Ʒ����
    *����š���Ʒ���롢�������
   */
   query.exec(QObject::tr("create table Store (StoreId vchar(8) PRIMARY KEY NOT NULL,"
                          "StoreName vchar(10) NOT NULL,"
                          "StoryNum Int(4) NOT NULL CHECK(StoryNum>=0))"));

   /**********************�� Ա �� �� Ϣ ��********************/
   query.exec(QObject::tr("create table Member(MemberId NUMERIC(9) PRIMARY KEY"
                          "CONSTRAINT C1 CHECK(MemberId BETWEEN 80000000 AND 99999999),"
                          "MemberName vchar(10),MemberPhone vchar(11) NOT NULL,"
                          "MemberAddress vchar(100),MemberClass vchar(10),"
                          "MemberGrade vchar(20) ,MemberCost vchar(20),"
                          "MemberRegister vchar(20),MemberBirthday vchar(20),"
                          "MemberEmail vchar(20),CurrentTime vchar(30),"
                          "MemberRemark vchar(500))"));
   query.exec(QObject::tr("insert into Member values (80000000,'���','15383463513',"
                          "'ɽ��ʡ̫ԭ�м��ƺ��̫ԭ��ҵѧԺ','��ͨ��','300','350',"
                          "'2014-08-20','1992-01-01','Zhang@163.com','','')"));
   query.exec(QObject::tr("insert into Member values (80000001,'����','15383465641',"
                          "'ɽ��ʡ̫ԭ�м��ƺ��̫ԭ��ҵѧԺ','���','3000','10000',"
                          "'2014-06-20','1992-11-24','creazylq@163.com','','')"));
   query.exec(QObject::tr("insert into Member values (80000002,'�����','15388511234',"
                          "'ɽ��ʡ̫ԭ�м��ƺ��̫ԭ��ҵѧԺ','��ͨ��','440','500',"
                          "'2013-06-20','1991-1-4','zhangzj@163.com','','')"));
   query.exec(QObject::tr("insert into Member values (80000003,'÷��','15388513945',"
                          "'ɽ��ʡ̫ԭ�м��ƺ��̫ԭ��ҵѧԺ','���','1000','1200',"
                          "'2011-04-12','1992-4-12','meixiang@163.com','','')"));
   query.exec(QObject::tr("insert into Member values (80000004,'�����','15388513920',"
                          "'ɽ��ʡ̫ԭ�м��ƺ��̫ԭ��ҵѧԺ','��ͨ��','500','700',"
                          "'2001-06-20','1991-3-2','maendong@163.com','','')"));
   query.exec(QObject::tr("insert into Member values (80000005,'������','15388510110',"
                          "'ɽ��ʡ̫ԭ�м��ƺ��̫ԭ��ҵѧԺ','��ͨ��','500','700',"
                          "'2014-09-10','1991-8-2','guzhongxin@163.com','','')"));

   /**********************�� Ʒ �� Ϣ ��********************************
    *��Ʒ��š�����(���)����Ʒ���ơ������̺�(���)����Ʒ���͡��۸񣨲���<0��
   */
   query.exec(QObject::tr("CREATE TABLE GoodsInfo(GoodsId vchar(8) PRIMARY KEY NOT NULL,"
                          "StoreId vchar(8) NOT NULL,GoodsName vchar(10)NOT NULL,"
                          "SupplyId vchar(8) NOT NULL,GoodsType vchar(10)NOT NULL,"
                          "GoodsPrice int(4) NOT NULL CHECK (GoodsPrice >0),"
                          "FOREIGN KEY(StoreId) REFERENCES Store(StoreId),"
                          "FOREIGN KEY(SupplyId) REFERENCES Supply(SupplyId))"));

   /**********************�� �� �� ��***********************************
    *������ID����������ַ���绰
   */
   query.exec(QObject::tr("create table Supply(SupplyID vchar(8)PRIMARY KEY NOT NULL,"
                          "SupplyName vchar(10)NOT NULL,SupplyAdress vchar(50)NOT NULL,"
                          "SupplyPhone vchar(11) NOT NULL)"));

   /***********************�������̱�******************************
    *�����̱�š���������ַ���绰
   */
   query.exec(QObject::tr("create table Product(ProductId vchar(8)PRIMARY KEY NOT NULL,"
                          "ProductName vchar(40)NOT NULL,"
                          "ProductAddress vchar(40),ProductPhone vchar(20))"));


   /**************************��Ʒ��ɫ��*******************************
    *��ɫ��š�����
   */
   query.exec(QObject::tr("create table Color(ColorId vchar(4) PRIMARY KEY NOT NULL,"
                          "ColorKind vchar(10))"));
   query.exec(QObject::tr("insert into Color values ('01','͸��')"));
   query.exec(QObject::tr("insert into Color values ('02','��ɫ')"));
   query.exec(QObject::tr("insert into Color values ('03','��ɫ')"));
   query.exec(QObject::tr("insert into Color values ('04','��ɫ')"));
   query.exec(QObject::tr("insert into Color values ('05','��ɫ')"));
   query.exec(QObject::tr("insert into Color values ('06','��ɫ')"));
   query.exec(QObject::tr("insert into Color values ('07','��ɫ')"));
   query.exec(QObject::tr("insert into Color values ('08','��ɫ')"));

   /**********************��Ʒ����*********************
    *��Ʒ����š�����
   */
   query.exec(QObject::tr("CREATE TABLE G_Type(TypeId int PRIMARY KEY NOT NULL,"
                          "TypeName vchar(10))"));
   query.exec(QObject::tr("insert into G_Type values (1,'�ջ���')"));

   /******************************�� �� ��**********************************
    *�ۿ۱�š��ۿ�����
   */
   query.exec(QObject::tr("create table Discount(DiscountId int PRIMARY KEY,"
                          "DiscountName vchar(4))"));
#endif
    return true;
}

static bool closeConnection()
{
    QSqlDatabase::database().close();
    return 1;
}

#endif // CONNECTION_H
