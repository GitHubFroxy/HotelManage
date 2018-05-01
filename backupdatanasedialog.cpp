/***************************************************************
 *Copyright(c) 2014-2015 Company By LiQi
 *All rights reserved.
 *�ļ����ƣ����ݿⱸ���ļ�
 *��Ҫ�������ṩ�û��������ݿ⹦��
 *
 *��ǰ�汾��V1.0
 *���ߣ�Kelvin Li
 *�������ڣ�2014/12
 *˵�����Ƶ����ϵͳ���ݿⱸ��
 *��Ȩ��creazylq���У�ת����ע��������������Ʒ������
 *Email��creazylq@163.com
******************************************************************/
#include "backupdatanasedialog.h"
#include "ui_backupdatanasedialog.h"

#include "app/myhelper.h"
#include "app/myapp.h"
#include <QProcess>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

BackupDatanaseDialog::BackupDatanaseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BackupDatanaseDialog)
{
    ui->setupUi(this);
    this->InitForm();
}

BackupDatanaseDialog::~BackupDatanaseDialog()
{
    delete ui;
}

void BackupDatanaseDialog::InitForm()
{
    ui->labelBackInfo->setText(QString::fromLocal8Bit(" "));//��ʼ��������ʾ��Ϣ
    ui->pbnOk->setToolTip(QString::fromLocal8Bit("ȷ�ϱ���"));

    ui->progressBar->setRange(0,5000 - 1);
    ui->progressBar->setValue(0);
}

/*
 *�������ܣ��������ݿ�
*/
void BackupDatanaseDialog::on_pbnOk_clicked()
{
    QString pathname = ui->lineEdit->text();
    QString Cmd = QString("mysqldump.exe --add-drop-table -u%1 -p%2 hotel").arg("root","123456");
    QString Path = QString("%1").arg(pathname);
    QProcess *poc=new QProcess;
    poc->setStandardOutputFile(Path);
    poc->start(Cmd);

    for(int i = 0;i<5000;i++)
    {
        ui->labelBackInfo->setText(QString::fromLocal8Bit("���ڱ��ݡ���"));
        for(int j = 0;j<2000;j++)
        {
            ui->progressBar->setValue(i);
        }
        ui->labelBackInfo->setText(QString::fromLocal8Bit("�������"));

        ui->pbnOk->setToolTip(QString::fromLocal8Bit("�Ѿ��������"));
    }

    QString currentname = Myapp::CurrentUserName;
    qDebug() <<QString::fromLocal8Bit("�������ݿ�:")<<currentname;
    myHelper::MyLoginBlog("logblog",QString::fromLocal8Bit("�������ݿ�"),QString::fromLocal8Bit("����ȫ������"),currentname);

}

/*
 *��ȡ��ǰҪ�������ݿ��Ŀ¼
*/
void BackupDatanaseDialog::on_pbnSearch_clicked()
{
    QString defaultname = "back_hotel.sql";
    //ѡ��·��
    QString filename = QFileDialog::getSaveFileName(this,QString::fromLocal8Bit("�������ݿ�"),"",
                                                    tr("*sql;; *txt;;"));
    if(filename.isEmpty())
    {
        filename = defaultname;
    }
    ui->lineEdit->setText(filename);

}

void BackupDatanaseDialog::on_lineEdit_textChanged(const QString &arg1)
{
    ui->progressBar->setValue(0);
    ui->pbnOk->setToolTip(QString::fromLocal8Bit(""));
}
