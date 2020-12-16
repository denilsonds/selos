#include "principal.h"
#include "ui_principal.h"

#define caminho "C:\\Users\\Pro\\Documents\\Projetos\\Selos\\carros.sqlite"
Principal::Principal(QWidget *parent): QMainWindow(parent)
  , ui(new Ui::Principal)
{
    ui->setupUi(this);
    cores << "Branco" << "Preto" << "Azul" << "Vermelho" << "Verde" << "Amarelo" << "Outra";
    marcas << "Fiat" << "Chevrolet" << "Audi" << "BMW" << "Citroen" << "Ford" << "Kia" << "Outra";
    ui->cbCor->addItems(cores);
    ui->cbMarca->addItems(marcas);
    banco = QSqlDatabase::addDatabase("QSQLITE");
    banco.setDatabaseName(caminho);
    if(banco.open())
        qDebug("Banco conectado.");
    //        QMessageBox::information(this,"Aviso.","Banco conectado.");
    else
        qDebug("Banco não conectado.");
    //        QMessageBox::warning(this,"Aviso.","Banco não conectado.");
    preencheTabela();
}

Principal::~Principal()
{
    delete ui;
}

void Principal::apagarForm()
{
    ui->leAM->clear();
    ui->lePlaca->clear();
    ui->cbCor->setCurrentIndex(0);
    ui->cbMarca->setCurrentIndex(0);
}

void Principal::on_pbSalvar_clicked()
{
    QSqlQuery insertCarro("INSERT INTO carros (AnoModelo, Marca, Cor, Placa) VALUES('"+ui->leAM->text()+"','"+ui->cbMarca->currentText()+"','"+ui->cbCor->currentText()+"','"+ui->lePlaca->text()+"')");
    qDebug() << "insert: " << insertCarro.lastQuery();
    if(insertCarro.numRowsAffected() > 0){
        QMessageBox::information(this,"Aviso.","Carro cadastrado com sucesso.");
        apagarForm();
        preencheTabela();
    }
    else
        QMessageBox::warning(this,"Aviso.","ERRO AO SALVAR:\n" + insertCarro.lastError().text());
}

void Principal::preencheTabela(){
    ui->twPrincipal->setRowCount(0);
    QSqlQuery preencherTabela("Select * from carros");
    int linha = 0;
    while(preencherTabela.next()){
        ui->twPrincipal->setRowCount(ui->twPrincipal->rowCount()+1);
        for(int i = 0; i < 4; i++)
            setTabela(preencherTabela.value(i).toString(),linha,i);
        linha++;
    }
}

void Principal::setTabela(QString valor, int linha, int col)
{
    QTableWidgetItem* item = new QTableWidgetItem();
    item->setFlags(Qt::NoItemFlags | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    item->setText(valor);
    ui->twPrincipal->setItem(linha,col,item);
}
