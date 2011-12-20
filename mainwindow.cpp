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
#include <QSqlTableModel>
//#include <QSqlRelationalTableModel>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(1);
    createConnection();
    model= new QSqlTableModel (this);
    model->setTable("books");
    model->setEditStrategy(QSqlTableModel::OnRowChange);
    model->select();
//    model->setQuery("SELECT * FROM books");
    ui->tableView->setItemDelegate(new delegat(ui->tableView));


    model->setHeaderData(0, Qt::Horizontal, tr("Id"));
    model->setHeaderData(1, Qt::Horizontal, tr("Title"));
    model->setHeaderData(2, Qt::Horizontal, tr("Author"));
    model->setHeaderData(3, Qt::Horizontal, tr("Genre"));
    model->setHeaderData(4, Qt::Horizontal, tr("Year"));
    model->setHeaderData(5, Qt::Horizontal, tr("Rating"));


    this->ui->tableView->setModel(model);

}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    bool author=false,title=false,genre=false,rating=false,year=false,first=true;
    QString result="SELECT * FROM books WHERE ";


    if ((this->ui->lineEdit_4->text())!="") author=true;
    if ((this->ui->lineEdit->text())!="") title=true;
    if ((this->ui->lineEdit_3->text())!="") genre=true;
    if ((this->ui->lineEdit_5->text())!="") rating=true;
    if ((this->ui->lineEdit_2->text())!="") year=true;

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


   // model->setTable("books");
   // model->setEditStrategy(QSqlTableModel::OnManualSubmit);
   // model->select();
   //model->setQuery("SELECT * FROM books");

    QSqlQuery query;
    query.exec(result);
    model->setQuery(query);

    model->setHeaderData(0, Qt::Horizontal, tr("Id"));
    model->setHeaderData(1, Qt::Horizontal, tr("Title"));
    model->setHeaderData(2, Qt::Horizontal, tr("Author"));
    model->setHeaderData(3, Qt::Horizontal, tr("Genre"));
    model->setHeaderData(4, Qt::Horizontal, tr("Year"));
    model->setHeaderData(5, Qt::Horizontal, tr("Rating"));


    this->ui->tableView->setModel(model);
}

void MainWindow::on_pushButton_4_clicked()
{

//    model->setTable("books");
//    model->select();

 //   model->setTable("books");
 //   model->setEditStrategy(QSqlTableModel::OnManualSubmit);
 //   model->select();

    model->setQuery("SELECT * FROM books");

    model->setHeaderData(0, Qt::Horizontal, tr("Id"));
    model->setHeaderData(1, Qt::Horizontal, tr("Title"));
    model->setHeaderData(2, Qt::Horizontal, tr("Author"));
    model->setHeaderData(3, Qt::Horizontal, tr("Genre"));
    model->setHeaderData(4, Qt::Horizontal, tr("Year"));
    model->setHeaderData(5, Qt::Horizontal, tr("Rating"));


    this->ui->tableView->setModel(model);
}

void MainWindow::on_pushButton_3_clicked()
{

    //    "insert into books values('Var and Peace', 'Tolstoy', 'Novel',1879,3)"
    QString result="INSERT INTO books (Title, Author, Genre, Year, Rating) VALUES ('";
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

//            QMessageBox msgBox;
//              msgBox.setText(result);
//              msgBox.exec();

    QSqlQuery query;
//         query.exec("INSERT INTO books (Id, Title, Author, Genre, Year, Rating) VALUES (9, 'Thad Beaumont', 'Thad', 'Beaumont', 2500, 3)");

    query.exec(result);
//    model->setQuery(query);
//    model->submit();
    model->setQuery("SELECT * FROM books");

    //model->setTable("books");
    //model->setEditStrategy(QSqlTableModel::OnRowChange);
    //model->select();

    model->setHeaderData(0, Qt::Horizontal, tr("Id"));
    model->setHeaderData(1, Qt::Horizontal, tr("Title"));
    model->setHeaderData(2, Qt::Horizontal, tr("Author"));
    model->setHeaderData(3, Qt::Horizontal, tr("Genre"));
    model->setHeaderData(4, Qt::Horizontal, tr("Year"));
    model->setHeaderData(5, Qt::Horizontal, tr("Rating"));
    this->ui->tableView->setModel(model);
}

void MainWindow::on_pushButton_2_clicked()
{
QString del="",result="";

//   del+=model->data(ui->tableView->selectionModel()->currentIndex()).toString();
   int row = ui->tableView->selectionModel()->currentIndex().row();
   model->removeRow(row);
   model->submit();
//    result+="delete from books where id="+del;
//   QSqlQuery query;
//   query.exec(result);

//   model->setQuery(query);
//   model->submit();
//   model->setQuery("SELECT * FROM books");
//   model->setTable("books");
//   model->select();


//   model->setTable("books");
//   model->setEditStrategy(QSqlTableModel::OnRowChange);
//   model->select();



//   model->setHeaderData(0, Qt::Horizontal, tr("Id"));
//   model->setHeaderData(1, Qt::Horizontal, tr("Title"));
//   model->setHeaderData(2, Qt::Horizontal, tr("Author"));
//   model->setHeaderData(3, Qt::Horizontal, tr("Genre"));
//   model->setHeaderData(4, Qt::Horizontal, tr("Year"));
//   model->setHeaderData(5, Qt::Horizontal, tr("Rating"));
//   this->ui->tableView->setModel(model);
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


    this->ui->tableView->setModel(model);
}
}

void MainWindow::on_tableView_doubleClicked(QModelIndex index)
{
     ui->stackedWidget->setCurrentIndex(0);
}
