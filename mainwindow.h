#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "flight.h"
#include <QMainWindow>
#include <QDate>
#include <QTimer>
#include <QFileDialog>
#include <QTableWidget>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void pause();
    void redraw(QTableWidget* table);
    QString boolToString(const bool);
    QTime airTimeToPush = QTime(0, 0, 1, 0);
    QTime flightTimeToPush = QTime(12, 0, 0, 0);
    QDate flightDateToPush = QDate(2021, 01, 01);
    QString airportToPush = QString("");
    QList<Flight> flights;
    int order = 1;
    ~MainWindow();

private slots:
    void on_flightDate_dateChanged(const QDate &date);

    void on_flightTimeEdit_timeChanged(const QTime &time);

    void on_airTimeEdit_timeChanged(const QTime &time);

    void on_addButton_clicked();

    void on_txtImportButton_clicked();

    void on_binImportButton_clicked();

    void on_tabWidget_tabBarClicked(int index);

    void on_deleteButton_clicked();

    void on_deleteAllButton_clicked();

    void on_ascRadio_clicked();

    void on_desRadio_clicked();

    void on_dfSortButton_clicked();

    void on_tfSortButton_clicked();

    void on_taSortButton_clicked();

    void on_baSortButton_clicked();

    void on_adSortButton_clicked();

    void on_plainExportButton_clicked();

    void on_tableExportButton_clicked();

    void on_csvExportButton_clicked();

    void on_csvImportButton_clicked();

    void on_binExportButton_clicked();

    void on_flightDate_userDateChanged(const QDate &date);

    void on_flightTimeEdit_userTimeChanged(const QTime &time);

    void on_airTimeEdit_userTimeChanged(const QTime &time);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
