#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QPixmap>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../projekt/synagogy.db");

    if(db.open())
    {
        qDebug() << "Databaze byla pripojena";
    }else
    {
        qDebug() << "Databaze nebyla pripojena";
    }

    ui->comboBox->clear();
    //ui->comboBox->addItem("");
    ui->comboBox->addItems(hledat_synagogy());

    ui->comboBox_2->clear();
  //  ui->comboBox_2->addItem(""); odstaněním této řádky uživatel uvidí ihned po klikntí 1. synagogu v nabídce

}

MainWindow::~MainWindow()
{
    delete ui;
}

QStringList MainWindow::hledat_synagogy()
{
    QSqlQuery *zobr_kraj = new QSqlQuery;
    QString prikaz="SELECT nazev_kraje FROM Kraje";
    zobr_kraj->prepare(prikaz);
    zobr_kraj->exec();
    QStringList synagogyy;
    while (zobr_kraj->next()) {
        QString synagoga=zobr_kraj->value(0).toString();
        synagogyy.append(synagoga);
    }
    return synagogyy;
}


void MainWindow::on_pushButton_clicked()
{
     ui->comboBox_2->clear();
     ui->comboBox_2->addItems(zobrazit_podrobnosti());

}

QStringList MainWindow::zobrazit_podrobnosti()
{
    QString synagoga_hledana=ui->comboBox->currentText();
    QSqlQuery *zobr_synagoga = new QSqlQuery;
    QString prikaz="SELECT nazev FROM synagogy JOIN Kraje ON synagogy.Kraj_ID=Kraje.Kraj_ID WHERE nazev_kraje = '"+synagoga_hledana+"'";
    zobr_synagoga->prepare(prikaz);
    zobr_synagoga->exec();
    QStringList synagogyyy;
    while (zobr_synagoga->next()) {
        QString synagoga=zobr_synagoga->value(0).toString();
        synagogyyy.append(synagoga);
    }
    return synagogyyy;
}
void MainWindow::on_pushButton_2_clicked()
{
    ui->textBrowser->clear();
    QSqlQuery *hl = new QSqlQuery;

    QString kraj_hledana=ui->comboBox_2->currentText();

    QString hledej_1="SELECT nazev FROM synagogy  WHERE nazev = '"+kraj_hledana+"'";
    QString hledej_2="SELECT nazev_kraje FROM Kraje JOIN synagogy ON synagogy.Kraj_ID=Kraje.Kraj_ID WHERE nazev = '"+kraj_hledana+"'";
    QString hledej_3="SELECT rok_zalozeni FROM synagogy WHERE nazev =  '"+kraj_hledana+"'";
    QString hledej_4="SELECT zajimavosti FROM synagogy WHERE nazev =  '"+kraj_hledana+"'";
    QString hledej_5="SELECT zemepisna_sirka FROM synagogy WHERE nazev = '"+kraj_hledana+"'";
    QString hledej_6="SELECT zemepisna_delka FROM synagogy WHERE nazev = '"+kraj_hledana+"'";
    QString hledej_7="SELECT mesto FROM synagogy WHERE nazev = '"+kraj_hledana+"'";

    QString hledej_8="SELECT synagoga_ID FROM synagogy WHERE nazev ='"+kraj_hledana+"'";

    hl->prepare(hledej_8);
    hl->exec();
    hl->first();
    QString id=hl->value(0).toString();

    hl->prepare(hledej_1);
    hl->exec();
    hl->first();
    QString nazev=hl->value(0).toString();

    hl->prepare(hledej_2);
    hl->exec();
    hl->first();
    QString nazevk=hl->value(0).toString();

    hl->prepare(hledej_3);
    hl->exec();
    hl->first();
    QString rok=hl->value(0).toString();

    hl->prepare(hledej_4);
    hl->exec();
    hl->first();
    QString zajimavost=hl->value(0).toString();

    hl->prepare(hledej_5);
    hl->exec();
    hl->first();
    QString sirka=hl->value(0).toString();

    hl->prepare(hledej_6);
    hl->exec();
    hl->first();
    QString delka=hl->value(0).toString();

    hl->prepare(hledej_7);
    hl->exec();
    hl->first();
    QString mesto=hl->value(0).toString();


    QString zobrazit="Název synagogy:  "+nazev+"\n"
            "\n"
                    "Město:                   "+mesto+"\n"
            "\n"
                    "Kraj:                      "+nazevk+"\n"
            "\n"
                    "Rok výstavby:       "+rok+"\n"
            "\n"
                    "Zajímavost:\n"
            "\n"
                    ""+zajimavost+"\n"
            "\n"
                    "Zem. šířka:        "+sirka+"\n"
            "\n"
                    "Zem. délka:       "+delka+"\n";

    ui->textBrowser->setText(zobrazit);


    QPixmap pix("../projekt/foto/"+id+".jpg");

    int v=ui->obrazek->width();
    int s=ui->obrazek->height();
    ui->obrazek->setPixmap(pix.scaled(v,s,Qt::KeepAspectRatio));

// ui->comboBox_2->clear();
}

