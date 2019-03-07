#ifndef FUNCTION2_H
#define FUNCTION2_H

#include <QAbstractItemModel>

class function2 //: public QAbstractItemModel
{
//    Q_OBJECT

private:
    QString expression1;
    QString expression2;
    QString line_color;
    QString line_type;

public:
//    explicit function2(QObject *parent = nullptr);
    explicit function2(void);
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
    void get_expression(QString str1, QString str2,QString color, QString type);
    QString read_expression1(void);
    QString read_expression2(void);
    QString read_line_color(void);
    QString read_line_type(void);
    bool check_input(QString str1, QString str2);
    QString replace_t(QString str, double n);
    double calculate_function(int n, double x);
};

#endif // FUNCTION2_H
