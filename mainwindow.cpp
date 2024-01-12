#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(
        ui->actionExit,
        &QAction::triggered,
        this,
        &QApplication::quit
    );

    model = new QStandardItemModel();
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Name")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Phone")));
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    setWindowIcon(QIcon(":images/contacts.png"));
    setWindowTitle(QString("Contacts"));
}

bool MainWindow::event(QEvent *e)
{
    if(e->type() == QEvent::KeyPress) {
        QKeyEvent *key = static_cast<QKeyEvent*>(e);
        if ( (key->key()==Qt::Key_Enter) || (key->key()==Qt::Key_Return) ) {
            emit on_pushButton_clicked();
        }
    }
    return QWidget::event(e);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QStandardItem *name = new QStandardItem(ui->lineEditName->text());
    if(name->text().trimmed() == QString()) {
        QMessageBox::critical(this, QString("Error!"), QString("Name cannot be empty!"));
        return;
    }

    QStandardItem *phone = new QStandardItem(ui->lineEditPhone->text());
    if(phone->text().trimmed() == QString()) {
        QMessageBox::critical(this, QString("Error!"), QString("Phone cannot be empty!"));
        return;
    }
    model->appendRow({name, phone});
    clearFields();

}

void MainWindow::clearFields()
{
    ui->lineEditName->setText(QString());
    ui->lineEditName->setFocus();
    ui->lineEditPhone->setText(QString());
}


void MainWindow::on_actionAbout_App_triggered()
{
    QMessageBox::about(this, QString("About App"), QString("This is the first app written with Qt"));
}


void MainWindow::on_pushButton_2_clicked()
{
    if(model->rowCount() == 0) {
        QMessageBox::critical(this, QString("Error!"), QString("No data to delete"));
        return;
    }
    msg = new QMessageBox();
    msg->setText(QString("Deleting all contacts."));
    msg->setInformativeText(QString("Are you sure deleting all contacts?"));
    msg->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msg->setWindowTitle("Contacts");
    msg->setWindowIcon(QIcon(":images/contacts.png"));
    int result = msg->exec();
    if(result == QMessageBox::Yes) {
        model->clear();
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    if(model->rowCount() == 0) {
        QMessageBox::critical(this, QString("Error!"), QString("No data to delete"));
        return;
    }
    bool ok;
    int result = QInputDialog::getInt(this, QString("Select a row to delete"), QString("Please select a row to delete"), 1, 1, model->rowCount(), 1, &ok);

    if(ok) {
        model->removeRow(result - 1);
    }
}


void MainWindow::on_actionClear_triggered()
{
    emit on_pushButton_2_clicked();
}


void MainWindow::on_actionSave_triggered()
{
    emit on_pushButton_clicked();
}

