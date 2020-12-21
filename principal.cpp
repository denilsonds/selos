#include "principal.h"
#include "ui_principal.h"

#define caminho "C:\\Users\\Pro\\Documents\\Projetos\\Selos\\carros.sqlite"

Principal::Principal(QWidget *parent): QMainWindow(parent)
  , ui(new Ui::Principal)
{
    ui->setupUi(this);
    cores << "Branco" << "Preto" << "Azul" << "Vermelho" << "Verde" << "Amarelo" << "Outra";
    ui->cbCor->addItems(cores);
    ui->cbMarca->addItems(marcas);
    banco = QSqlDatabase::addDatabase("QSQLITE");
    banco.setDatabaseName(caminho);
    if(banco.open())
        qDebug("Banco conectado.");
    else
        qDebug("Banco não conectado.");
    QRegExp re("^[a-zA-Z]{3}[0-9][A-Za-z0-9][0-9]{2}$");
    QRegExpValidator *validator = new QRegExpValidator(re, this);
    ui->lePlaca->setValidator(validator);
    desabilitaCampos();
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
    QSqlQuery insertCarro("INSERT INTO carros (Tipo, AnoModelo, Marca, Cor, Placa) VALUES('"+ui->cbTipo->currentText()+"','"+ui->leAM->text()+"','"+ui->cbMarca->currentText()+"','"+ui->cbCor->currentText()+"','"+ui->lePlaca->text()+"')");
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
        for(int i = 0; i < 6; i++)
            setTabela(preencherTabela.value(i).toString(),linha,i);
        linha++;
    }
    ColunsAlternativecolor();
}

void Principal::setTabela(QString valor, int linha, int col)
{
    QTableWidgetItem* item = new QTableWidgetItem();
    item->setFlags(Qt::NoItemFlags | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    item->setText(valor);
    ui->twPrincipal->setItem(linha,col,item);
}

void Principal::desabilitaCampos(){
    ui->leAM->setDisabled(true);
    ui->lePlaca->setDisabled(true);
    ui->cbCor->setDisabled(true);
    ui->cbMarca->setDisabled(true);
}

void Principal::abilitaCampos(){
    for(int i = 0;i > 8; i++)
        ui->cbMarca->removeItem(i);
    ui->leAM->setEnabled(true);
    ui->lePlaca->setEnabled(true);
    ui->cbCor->setEnabled(true);
    ui->cbMarca->setEnabled(true);
}

void Principal::on_cbTipo_currentTextChanged(const QString & arg1)
{
    if(ui->cbTipo->currentText() == "Selecione"){
        apagarForm();
        desabilitaCampos();
    }
    else if(ui->cbTipo->currentText() == "Carro"){
        apagarForm();
        abilitaCampos();
        marcas.clear();
        marcas << "Selecione" << "Fiat" << "Chevrolet" << "Audi" << "BMW" << "Citroen" << "Ford" << "Kia" << "Outra";
        ui->cbMarca->addItems(marcas);
    }
    else if(ui->cbTipo->currentText() == "Moto"){
        apagarForm();
        abilitaCampos();
        marcas.clear();
        marcas << "Selecione" << "Honda" << "Yamaha" << "Suzuki" << "Dafra" << "Shineray" << "Kasawaki" << "Kasinki" << "Outra";
        ui->cbMarca->addItems(marcas);
    }
}

void Principal::ColunsAlternativecolor()
{
    for(double i = 0 ; i< ui->twPrincipal->columnCount(); i++){
        QStringList cor,cor2;
        double j;
        j = i/2;
        cor.append(QString::number(j,'f',2));
        cor2.append(cor.join("|").split("."));
        if (cor2.at(1)=="00")
            for(double l = 0 ; l< ui->twPrincipal->rowCount(); l++)
                ui->twPrincipal->item(l,i)->setBackgroundColor(QColor(172, 255, 127, 120));
    }
}

