#include "widget.h"
#include "ui_widget.h"
#include "personadialog.h"

#include <QMessageBox>
#include <QFile>
#include <QTextStream>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    f = -1;
    QStringList titulos;
    setWindowTitle("Lista de cosas");
    ui->tableWidget->setColumnCount(4);
    titulos << "Nombre or Name" << "Fecha or Date" << "Prioridad or Priority" << "Tipo or Type";
    ui->tableWidget->setHorizontalHeaderLabels(titulos);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_agregar_clicked()
{
    //funcion para ejecutar personadialog primero y definimos como padre a widget
    int res, fila;
    QString nombre,prioridad,tipo,fecha;
    PersonaDialog pd(this);
    pd.setWindowTitle("Agregar Cosas");
    res = pd.exec();
    if(res == QDialog::Rejected)
        return;
    nombre = pd.nombre();
    fecha = pd.fecha();
    prioridad = pd.prioridad();
    tipo = pd.tipo();
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    fila = ui->tableWidget->rowCount() -1;
    ui->tableWidget->setItem(fila, NOMBRE,new QTableWidgetItem(nombre));
    ui->tableWidget->setItem(fila, FECHA,new QTableWidgetItem((fecha)));
    ui->tableWidget->setItem(fila, PRIORIDAD,new QTableWidgetItem(prioridad));
    ui->tableWidget->setItem(fila, TIPO,new QTableWidgetItem(tipo));

    //La aplicación guardará automaticamente la nueva tarea
       QMessageBox mensajeBox;
               QString fileName = "Lista.csv";
                   if (fileName.isEmpty()) {
                       return;
                   }

                   QFile file(fileName);
                   if (!file.open(QIODevice::WriteOnly |   QFile::Text)) {
                       QMessageBox::information(this, tr("No se puede abrir el archivo"),
                       file.errorString());
                       return;
                   }

                   QTextStream out(&file);
                   int rowCount = ui->tableWidget->rowCount();
                   int colCount = ui->tableWidget->columnCount();

                   for (int i = 0; i < rowCount; i++) {

                       for (int j = 0; j < colCount; j++) {
                           if (j > 0) {
                               out << ";";
                           }
                           QTableWidgetItem* item = ui->tableWidget->item(i,j);
                           out << item->data(Qt::DisplayRole).toString();
                       }
                       out << "\n";
                   }
                   mensajeBox.setText(tr("Se guardó en el archivo:") + fileName);
                   mensajeBox.exec();



}


void Widget::on_Borrar_clicked()
{
 ui->tableWidget->removeRow(f);
}

void Widget::on_tableWidget_itemClicked(QTableWidgetItem *item)
{
    f = item->row();
}
