#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>

class QSqlTableModel;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    QStringList hledat_synagogy();
    QStringList zobrazit_podrobnosti();

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();


private:
    Ui::MainWindow *ui;
    QSqlDatabase db;

    QSqlQueryModel *model=new QSqlQueryModel();

};

#endif // MAINWINDOW_H
