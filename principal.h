#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class Principal; }
QT_END_NAMESPACE

class Principal : public QMainWindow
{
    Q_OBJECT

public:
    QStringList cores;
    QStringList marcas;
    void apagarForm();
    QSqlDatabase banco;
    Principal(QWidget *parent = nullptr);
    ~Principal();

private slots:
    void on_pbSalvar_clicked();

private:
    void preencheTabela();
    void setTabela(QString valor, int linha, int col);
    Ui::Principal *ui;
};
#endif // PRINCIPAL_H
