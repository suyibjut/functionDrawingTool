#ifndef FUNCTION1_Htr
#define FUNCTION1_H
#include <QString>
#include <QAbstractItemModel>
#include <QDebug>

class function1 //: public QAbstractItemModel
{
//    Q_OBJECT

private:
    QString expression;
    QString line_color;
    QString line_type;

public:
//    explicit function1(QObject *parent = nullptr);
    explicit function1(void);
/*
    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
*/

public:
    void get_expression(QString str, QString color, QString type);
    QString read_expression(void);
    QString read_line_color(void);
    QString read_line_type(void);
    //检查合法输入
    bool check_input(QString str);
    QString replace_x(QString str, double n);
    double calculate_function(double x);
};

#endif // FUNCTION1_H
