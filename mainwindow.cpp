#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "conn.h"
#include <QtSql>
#include <QtDebug>
#include <QtGui>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QTableView>
#include <QDebug>
#include "delegat.h"
//#include <QSqlTableModel>
//#include <QSqlRelationalTableModel>
#include <QtCore/QFile>
 #include <QtCore/QTextStream>


MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //loadTextFile();
    ui->stackedWidget->setCurrentIndex(1);

    createConnection();


    model= new QSqlQueryModel (this);
    //model->setTable("books");
   // model->setEditStrategy(QSqlTableModel::OnManualSubmit);
   // model->select();
    model->setQuery("SELECT * FROM books");
    ui->tableView->setItemDelegate(new delegat(ui->tableView));


    model->setHeaderData(0, Qt::Horizontal, tr("Id"));
    model->setHeaderData(1, Qt::Horizontal, tr("Title"));
    model->setHeaderData(2, Qt::Horizontal, tr("Author"));
    model->setHeaderData(3, Qt::Horizontal, tr("Genre"));
    model->setHeaderData(4, Qt::Horizontal, tr("Year"));
    model->setHeaderData(5, Qt::Horizontal, tr("Rating"));
    model->setHeaderData(6, Qt::Horizontal, tr("Text"));


    this->ui->tableView->setModel(model);


}






MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{
    bool author=false,title=false,genre=false,rating=false,year=false,first=true, texts=false;
    QString result="SELECT * FROM books WHERE ";


    if ((this->ui->lineEdit_4->text())!="") author=true;
    if ((this->ui->lineEdit->text())!="") title=true;
    if ((this->ui->lineEdit_3->text())!="") genre=true;
    if ((this->ui->lineEdit_5->text())!="") rating=true;
    if ((this->ui->lineEdit_2->text())!="") year=true;
    if ((this->ui->lineEdit_6->text())!="") texts=false;

    if (author)
    {
        if (!first)
        {
            result+=" AND ";
        }
        result+=" author='";
        result+=this->ui->lineEdit_4->text();
        result+="'";
        first=false;

    }
    if (title)
    {
        if (!first)
        {
            result+=" AND ";
        }
        result+=" title='";
        result+=this->ui->lineEdit->text();
        result+="'";
        first=false;
    }
    if (genre)
    {
        if (!first)
        {
            result+=" AND ";
        }
        result+=" genre='";
        result+=this->ui->lineEdit_3->text();
        result+="'";
        first=false;
    }
    if (year)
    {
        if (!first)
        {
            result+=" AND ";
        }
        result+=" year='";
        result+=this->ui->lineEdit_2->text();
        result+="'";
        first=false;
    }
    if (rating)
    {
        if (!first)
        {
            result+=" AND ";
        }
        result+=" rating='";
        result+=this->ui->lineEdit_5->text();
        result+="'";
        first=false;
    }



   model->setQuery("SELECT * FROM books");

    QSqlQuery query;
    query.exec(result);
    model->setQuery(query);

    model->setHeaderData(0, Qt::Horizontal, tr("Id"));
    model->setHeaderData(1, Qt::Horizontal, tr("Title"));
    model->setHeaderData(2, Qt::Horizontal, tr("Author"));
    model->setHeaderData(3, Qt::Horizontal, tr("Genre"));
    model->setHeaderData(4, Qt::Horizontal, tr("Year"));
    model->setHeaderData(5, Qt::Horizontal, tr("Rating"));
    model->setHeaderData(6, Qt::Horizontal, tr("Text"));


    this->ui->tableView->setModel(model);
}

void MainWindow::on_pushButton_clicked(bool checked)
{
}

void MainWindow::on_pushButton_pressed()
{
}

void MainWindow::on_pushButton_4_clicked()
{

//    model->setTable("books");
//    model->select();

    model->setQuery("SELECT * FROM books");

    model->setHeaderData(0, Qt::Horizontal, tr("Id"));
    model->setHeaderData(1, Qt::Horizontal, tr("Title"));
    model->setHeaderData(2, Qt::Horizontal, tr("Author"));
    model->setHeaderData(3, Qt::Horizontal, tr("Genre"));
    model->setHeaderData(4, Qt::Horizontal, tr("Year"));
    model->setHeaderData(5, Qt::Horizontal, tr("Rating"));
    model->setHeaderData(6, Qt::Horizontal, tr("Text"));


    this->ui->tableView->setModel(model);
}

void MainWindow::on_pushButton_3_clicked()
{

    //    "insert into books values('Var and Peace', 'Tolstoy', 'Novel',1879,3)"
    QString result="insert into books values ('";
    result+=ui->lineEdit->text();
    result+="', '";
    result+=ui->lineEdit_4->text();
    result+="', '";
    result+=ui->lineEdit_3->text();
    result+="', '";
    result+=ui->lineEdit_2->text();
    result+="', '";
    result+=ui->lineEdit_5->text();
    result+="')";

    QSqlQuery query;
    query.exec(result);
    model->setQuery(query);
    model->setQuery("SELECT * FROM books");


    model->setHeaderData(0, Qt::Horizontal, tr("Id"));
    model->setHeaderData(1, Qt::Horizontal, tr("Title"));
    model->setHeaderData(2, Qt::Horizontal, tr("Author"));
    model->setHeaderData(3, Qt::Horizontal, tr("Genre"));
    model->setHeaderData(4, Qt::Horizontal, tr("Year"));
    model->setHeaderData(5, Qt::Horizontal, tr("Rating"));
    model->setHeaderData(6, Qt::Horizontal, tr("Text"));
    this->ui->tableView->setModel(model);
}

void MainWindow::on_pushButton_2_clicked()
{
//   int count=ui->tableView->selectionModel()->selectedRows().count();
  // QSqlTableModel *model= new QSqlTableModel (this);
//   for (int i=0;i<count;i++)
//       model->removeRow(ui->tableView->selectionModel()->selectedRows().at( i).row(),QModelIndex());
   // model->removeRow(2,QModelIndex());
    //ui->tableView->selectionModel()->selectedRows().at(i).row()

    //model->removeRow(ui->tableView->selectionModel()->selectedRows(),1,QModelIndex());
QString del="",result="";



//QString asd="";
    //asd=ui->tableView->data(ui->tableView->selectionModel()->selectedRows())


   del+=model->data(ui->tableView->selectionModel()->currentIndex()).toString();
    result+="delete from books where id="+del;
   QSqlQuery query;
   query.exec(result);

   model->setQuery(query);
   model->submit();
//   model->setTable("books");
//   model->select();

   model->setQuery("SELECT * FROM books");

   model->setHeaderData(0, Qt::Horizontal, tr("Id"));
   model->setHeaderData(1, Qt::Horizontal, tr("Title"));
   model->setHeaderData(2, Qt::Horizontal, tr("Author"));
   model->setHeaderData(3, Qt::Horizontal, tr("Genre"));
   model->setHeaderData(4, Qt::Horizontal, tr("Year"));
   model->setHeaderData(5, Qt::Horizontal, tr("Rating"));
   model->setHeaderData(6, Qt::Horizontal, tr("Text"));
   this->ui->tableView->setModel(model);
}

void MainWindow::on_pushButton_5_clicked()
{
QString result="SELECT * FROM books WHERE ";
                result+="id LIKE '%";
               result+=ui->lineEdit_6->text();
               result+="%' OR title LIKE '%";
               result+=ui->lineEdit_6->text();
               result+="%' OR author LIKE '%";
               result+=ui->lineEdit_6->text();
               result+="%' OR genre LIKE '%";
               result+=ui->lineEdit_6->text();
               result+="%' OR year LIKE '%";
               result+=ui->lineEdit_6->text();
               result+="%' OR rating LIKE '%";
               result+=ui->lineEdit_6->text();
               result+="%'";

QSqlQuery query;
query.exec(result);
model->setQuery(query);

model->setHeaderData(0, Qt::Horizontal, tr("Id"));
model->setHeaderData(1, Qt::Horizontal, tr("Title"));
model->setHeaderData(2, Qt::Horizontal, tr("Author"));
model->setHeaderData(3, Qt::Horizontal, tr("Genre"));
model->setHeaderData(4, Qt::Horizontal, tr("Year"));
model->setHeaderData(5, Qt::Horizontal, tr("Rating"));
model->setHeaderData(6, Qt::Horizontal, tr("Text"));


this->ui->tableView->setModel(model);


}

void MainWindow::on_lineEdit_7_textChanged(QString res)
{

    if (ui->checkBox->checkState()==Qt::Checked)
    {
    QString result="SELECT * FROM books WHERE ";
                    result+="id LIKE '%";
                   result+=res;
                   result+="%' OR title LIKE '%";
                   result+=res;
                   result+="%' OR author LIKE '%";
                   result+=res;
                   result+="%' OR genre LIKE '%";
                   result+=res;
                   result+="%' OR year LIKE '%";
                   result+=res;
                   result+="%' OR rating LIKE '%";
                   result+=res;
                   result+="%'";

    QSqlQuery query;
    query.exec(result);
    model->setQuery(query);

    model->setHeaderData(0, Qt::Horizontal, tr("Id"));
    model->setHeaderData(1, Qt::Horizontal, tr("Title"));
    model->setHeaderData(2, Qt::Horizontal, tr("Author"));
    model->setHeaderData(3, Qt::Horizontal, tr("Genre"));
    model->setHeaderData(4, Qt::Horizontal, tr("Year"));
    model->setHeaderData(5, Qt::Horizontal, tr("Rating"));
    model->setHeaderData(6, Qt::Horizontal, tr("Text"));


    this->ui->tableView->setModel(model);
}
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    ui->stackedWidget->setCurrentIndex(0);

    //!!!!!!
//   QFile inputFile("C:/in.txt");
//    inputFile.open(QIODevice::ReadOnly);

//    QTextStream in(&inputFile);
   QString line;// = in.readAll();
//    inputFile.close();
//    ui->textEdit->


    int row=index.row();
    line = model->record(row).value("Text").toString();
    ui->textEdit->setPlainText(line);
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor, 1);

}
