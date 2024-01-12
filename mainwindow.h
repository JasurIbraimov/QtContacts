#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QFontDatabase>
#include <QStandardItemModel>
#include <QKeyEvent>
#include <QMessageBox>
#include <QInputDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_actionAbout_App_triggered();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_actionClear_triggered();

    void on_actionSave_triggered();

private:
    bool event(QEvent *e) override;
    void clearFields();
    Ui::MainWindow *ui;
    QMessageBox *msg;
    QStandardItemModel *model;

};
#endif // MAINWINDOW_H
