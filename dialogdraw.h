#ifndef DIALOGDRAW_H
#define DIALOGDRAW_H

#include <QDialog>

namespace Ui {
class DialogDraw;
}

class DialogDraw : public QDialog
{
    Q_OBJECT

public:
    explicit DialogDraw(QWidget *parent = 0);
    ~DialogDraw();

private slots:
    void on_checkBox_stateChanged(int arg1);
//    void mouseMoved(QMouseEvent *event);

private:
    Ui::DialogDraw *ui;
public:
    void refresh_graph(void);
};

#endif // DIALOGDRAW_H
