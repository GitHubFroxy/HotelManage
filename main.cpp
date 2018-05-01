/***************************************************************
 *Copyright(c) 2014-2015 Company By LiQi
 *All rights reserved.
 *�ļ����ƣ�����������ļ�
 *��Ҫ�����������ݿ⣬���س��������ĸ������ò���
 *
 *��ǰ�汾��V1.0
 *���ߣ�Kelvin Li
 *�������ڣ�2014/12
 *˵�����Ƶ����ϵͳ��������
 *��Ȩ��creazylq���У�ת����ע��������������Ʒ������
 *Email��creazylq@163.com
******************************************************************/
#include <QApplication>
#include "app/myhelper.h"
#include "logindialog.h"
#include "app/Connection.h"
#include "app/myapp.h"

#include <QSqlQuery>
#include <qtextcodec.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //myHelper::SetGBK2312Code();
    myHelper::SetUTF8Code();
    myHelper::SetStyle("blue");//��ɫ���

    QTranslator translator;             //���������ַ�
    translator.load(":/image/qt_zh_CN.qm");
    a.installTranslator(&translator);


    LoginDialog login;


    if(!createConnection())
    {
        QTextCodec *codec = QTextCodec::codecForName("GBK");//�޸�������
        //�����ʵ��������
        //myHelper::ShowMessageBoxError(QObject::tr("���ݿ��ʧ�ܣ������Զ��ر�"));
        //myHelper::ShowMessageBoxError((QString::fromLocal8Bit("���ݿ��ʧ�ܣ������Զ��ر�")));
        myHelper::ShowMessageBoxError(codec->toUnicode("���ݿ��ʧ�ܣ������Զ��ر�"));
        return 1;
    }

    login.show();

//    closeConnection();
    return a.exec();
}
