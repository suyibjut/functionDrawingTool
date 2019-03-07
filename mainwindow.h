#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialogaddfuntion.h"
#include "dialogdraw.h"

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
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();
/*
    void on_action_triggered();
*/
private:
    Ui::MainWindow *ui;
    DialogAddFuntion *dialog;  //添加私有成员
    DialogDraw *draw;  //添加私有成员
public:
    void refresh_table1(void);
    void refresh_table2(void);
};

#endif // MAINWINDOW_H
