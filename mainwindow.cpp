#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QSet>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
QString MainWindow::boolToString(const bool v)
{
    return (v) ? "+" : "-";
}
void MainWindow::redraw(QTableWidget* table)
{
    table->setRowCount(0);
    for(Flight a : flights)
    {
        table->setRowCount(table->rowCount() + 1);
        table->setItem(table->rowCount() - 1, 0, new QTableWidgetItem(a.getDepartureDate().toString("dd.MM.yyyy")));
        table->setItem(table->rowCount() - 1, 1, new QTableWidgetItem(a.getDepartureTime().toString()));
        table->setItem(table->rowCount() - 1, 2, new QTableWidgetItem(a.getFlightTime().toString()));
        table->setItem(table->rowCount() - 1, 3, new QTableWidgetItem(boolToString(a.getBreakfast())));
        table->setItem(table->rowCount() - 1, 4, new QTableWidgetItem(a.getAirport()));
    }
}
void MainWindow::pause()
{
    QEventLoop el;
    QTimer t;
    connect(&t, SIGNAL(timeout()), &el, SLOT(quit()));
    t.start(2500);
    el.exec();
    return;
}
void MainWindow::on_flightDate_dateChanged(const QDate &date)
{
    flightDateToPush = date;
}

void MainWindow::on_flightTimeEdit_timeChanged(const QTime &time)
{
    flightTimeToPush = time;
}


void MainWindow::on_airTimeEdit_timeChanged(const QTime &time)
{
    airTimeToPush = time;
}


void MainWindow::on_addButton_clicked()
{
    airportToPush = ui->airportEdit->text();
    flights.push_back(Flight(flightDateToPush, flightTimeToPush, airTimeToPush, airportToPush));
    ui->airportEdit->clear();
    ui->flightDate->setDate(QDate(2021, 1, 1));
    ui->flightTimeEdit->setTime(QTime(0, 0, 0, 0));
    ui->airTimeEdit->setTime(QTime(0, 0, 0, 0));
    ui->addButton->setText("Done!");
    ui->addButton->setStyleSheet("QPushButton { color : green; }");
    pause();
    ui->addButton->setText("Add");
    ui->addButton->setStyleSheet("QPushButton { color : black; }");
    redraw(ui->tableWidget);
    redraw(ui->tableWidget_2);
    redraw(ui->tableWidget_3);

}

void MainWindow::on_txtImportButton_clicked()
{
    QRegularExpression rx("[.!?;:, ]");
    QFileDialog dialog = QFileDialog();
    QString fname = dialog.getOpenFileName(this, "Import txt file", "../Lab12", "*.txt");
    QFile inputFile(fname);
    QTextStream out(stdout);
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          QString data = in.readLine();
          QString air = in.readLine();
          QStringList list = data.split(rx, Qt::SkipEmptyParts);
          flightDateToPush = QDate(list.at(2).toInt(), list.at(1).toInt(), list.at(0).toInt());
          flightTimeToPush = QTime(list.at(3).toInt(), list.at(4).toInt());
          airTimeToPush = QTime(list.at(5).toInt(), list.at(6).toInt());
          airportToPush = air;
          flights.push_back(Flight(flightDateToPush, flightTimeToPush, airTimeToPush, airportToPush));
       }
       inputFile.close();
       redraw(ui->tableWidget);
    }
}
void MainWindow::on_csvImportButton_clicked()
{
    QRegularExpression rx("[.!?;:,]");
    QFileDialog dialog = QFileDialog();
    QString fname = dialog.getOpenFileName(this, "Import csv file", "../Lab12", "*.csv");
    QFile inputFile(fname);
    QTextStream out(stdout);
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          QString data = in.readLine();
          QStringList list = data.split(rx);
          flightDateToPush = QDate(list.at(2).toInt(), list.at(1).toInt(), list.at(0).toInt());
          flightTimeToPush = QTime(list.at(3).toInt(), list.at(4).toInt());
          airTimeToPush = QTime(list.at(5).toInt(), list.at(6).toInt());
          airportToPush = list.at(7);
          flights.push_back(Flight(flightDateToPush, flightTimeToPush, airTimeToPush, airportToPush));
       }
       inputFile.close();
       redraw(ui->tableWidget);
    }
}
void MainWindow::on_binImportButton_clicked()
{
    QRegularExpression rx("[.!?;:,\n]");
    QFileDialog dialog = QFileDialog();
    QString fname = dialog.getOpenFileName(this, "Import bin file", "../Lab12", "*.dat");
    QFile inputFile(fname);
    QTextStream out(stdout);
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QDataStream in(&inputFile);
       while (!in.atEnd())
       {
          QString data;
          in >> data;
          QStringList list = data.split(rx, Qt::SkipEmptyParts);
          flightDateToPush = QDate(list.at(2).toInt(), list.at(1).toInt(), list.at(0).toInt());
          flightTimeToPush = QTime(list.at(3).toInt(), list.at(4).toInt());
          airTimeToPush = QTime(list.at(5).toInt(), list.at(6).toInt());
          airportToPush =  list.at(7);
          flights.push_back(Flight(flightDateToPush, flightTimeToPush, airTimeToPush, airportToPush));
       }
       inputFile.close();
       redraw(ui->tableWidget);
    }
}




void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    switch (index)
    {
    case 1:
    {
        redraw(ui->tableWidget_2);
        break;
    }
    case 2:
    {
        redraw(ui->tableWidget_3);
        break;
    }
    }
}

void MainWindow::on_deleteButton_clicked()
{
    QSet<int> rowsToDeleteSet;
    QVector<int> rowsToDelete;
    for (auto item : ui->tableWidget_2->selectedItems())
    {
        rowsToDeleteSet.insert(item->row());
    }
    for (int i : rowsToDeleteSet)
    {
        rowsToDelete.append(i);
    }
    std::sort(rowsToDelete.begin(), rowsToDelete.end(), std::greater<int>());
    for (int rtd : rowsToDelete)
    {
        flights.remove(rtd);
        flights.squeeze();
    }
    redraw(ui->tableWidget);
    redraw(ui->tableWidget_2);
    redraw(ui->tableWidget_3);
    ui->tableWidget->setRowCount(flights.length());
    ui->tableWidget_2->setRowCount(flights.length());
    ui->tableWidget_3->setRowCount(flights.length());
}

void MainWindow::on_deleteAllButton_clicked()
{
    flights.clear();
    redraw(ui->tableWidget);
    redraw(ui->tableWidget_2);
    redraw(ui->tableWidget_3);
    ui->tableWidget->setRowCount(flights.length());
    ui->tableWidget_2->setRowCount(flights.length());
    ui->tableWidget_3->setRowCount(flights.length());
}

void MainWindow::on_ascRadio_clicked()
{
    order = 1;
}

void MainWindow::on_desRadio_clicked()
{
    order = -1;
}

void MainWindow::on_dfSortButton_clicked()
{
    switch (order)
    {
    case 1:
    {
        std::sort(flights.begin(), flights.end(), [](Flight a, Flight b) {
            return (a.getDepartureDate() < b.getDepartureDate());
        });
        break;
    }
    default:
    {
        std::sort(flights.begin(), flights.end(), [](Flight a, Flight b) {
            return (a.getDepartureDate() > b.getDepartureDate());
        });
        break;
    }
    }
    redraw(ui->tableWidget);
    redraw(ui->tableWidget_2);
    redraw(ui->tableWidget_3);
}

void MainWindow::on_tfSortButton_clicked()
{
    switch (order)
    {
    case 1:
    {
        std::sort(flights.begin(), flights.end(), [](Flight a, Flight b) {
            return (a.getDepartureTime() < b.getDepartureTime());
        });
        break;
    }
    default:
    {
        std::sort(flights.begin(), flights.end(), [](Flight a, Flight b) {
            return (a.getDepartureTime() > b.getDepartureTime());
        });
        break;
    }
    }
    redraw(ui->tableWidget);
    redraw(ui->tableWidget_2);
    redraw(ui->tableWidget_3);
}

void MainWindow::on_taSortButton_clicked()
{
    switch (order)
    {
    case 1:
    {
        std::sort(flights.begin(), flights.end(), [](Flight a, Flight b) {
            return (a.getFlightTime() < b.getFlightTime());
        });
        break;
    }
    default:
    {
        std::sort(flights.begin(), flights.end(), [](Flight a, Flight b) {
            return (a.getFlightTime() > b.getFlightTime());
        });
        break;
    }
    }
    redraw(ui->tableWidget);
    redraw(ui->tableWidget_2);
    redraw(ui->tableWidget_3);
}

void MainWindow::on_baSortButton_clicked()
{
    on_taSortButton_clicked();
}

void MainWindow::on_adSortButton_clicked()
{
    switch (order)
    {
    case 1:
    {
        std::sort(flights.begin(), flights.end(), [](Flight a, Flight b) {
            return (a.getAirport() < b.getAirport());
        });
        break;
    }
    default:
    {
        std::sort(flights.begin(), flights.end(), [](Flight a, Flight b) {
            return (a.getAirport() > b.getAirport());
        });
        break;
    }
    }
    redraw(ui->tableWidget);
    redraw(ui->tableWidget_2);
    redraw(ui->tableWidget_3);
}

void MainWindow::on_plainExportButton_clicked()
{
    QFileDialog dialog = QFileDialog();
    QString fname = dialog.getSaveFileName(this, "Save txt file", "../Lab12", "*.txt");
    QFile outputFile(fname);
    if (outputFile.open(QIODevice::WriteOnly))
    {
       QTextStream out(&outputFile);
       for (Flight s : flights)
       {
           out << s.getDepartureDate().toString("dd MM yyyy") << " " << s.getDepartureTime().toString("hh mm") << " " << s.getFlightTime().toString("hh mm") << "\n" << s.getAirport() << "\n";
       }
    }
}

void MainWindow::on_tableExportButton_clicked()
{

    QFileDialog dialog = QFileDialog();
    QString fname = dialog.getSaveFileName(this, "Save txt file", "../Lab12", "*.txt");
    QFile outputFile(fname);
    int count = 1;
    if (outputFile.open(QIODevice::WriteOnly))
    {
       QTextStream out(&outputFile);
       out << "+----+------------+--------+-------------+-----------+---------------+\n";
       out << "| No |    Date    |  Time  | Travel time | Breakfast |    Airport    |\n";
       out << "+----+------------+--------+-------------+-----------+---------------+\n";
       if (flights.isEmpty())
       {
           out << "|                     There's no flights yet...                      |\n";
           out << "+--------------------------------------------------------------------+\n";
       }
       for (Flight s : flights)
       {
           out << "| " << QStringLiteral("%1").arg(count++, 2, 10, QLatin1Char('0')) << " | ";
           out << s.getDepartureDate().toString("dd.MM.yyyy") << " | ";
           out << s.getDepartureTime().toString("hh:mm") << "  |    ";
           out << s.getFlightTime().toString("hh:mm") << "    |     ";
           out << boolToString(s.getBreakfast()) << "     | ";
           out <<  s.getAirport().rightJustified(13, ' ', true) << " |\n";
           out << "+----+------------+--------+-------------+-----------+---------------+\n";
       }
    }
}

void MainWindow::on_csvExportButton_clicked()
{
    QFileDialog dialog = QFileDialog();
    QString fname = dialog.getSaveFileName(this, "Save csv file", "../Lab12", "*.csv");
    QFile outputFile(fname);
    if (outputFile.open(QIODevice::WriteOnly))
    {
       QTextStream out(&outputFile);
       for (Flight s : flights)
       {
           out << s.getDepartureDate().toString("dd.MM.yyyy") << ";" << s.getDepartureTime().toString("hh:mm") << ";" << s.getFlightTime().toString("hh:mm") << ";""" << s.getAirport() << """\n";
       }
    }
}



void MainWindow::on_binExportButton_clicked()
{
    QFileDialog dialog = QFileDialog();
    QString fname = dialog.getSaveFileName(this, "Save dat file", "../Lab12", "*.dat");
    QFile outputFile(fname);
    if (outputFile.open(QIODevice::WriteOnly))
    {
       QDataStream out(&outputFile);
       for (Flight s : flights)
       {
           QString str = s.getDepartureDate().toString("dd.MM.yyyy") + ";" + s.getDepartureTime().toString("hh:mm") + ";" + s.getFlightTime().toString("hh:mm") + ";" + s.getAirport() + "\n";
           out << str;
       }
    }
}

void MainWindow::on_flightDate_userDateChanged(const QDate &date)
{
    flightDateToPush = date;
}

void MainWindow::on_flightTimeEdit_userTimeChanged(const QTime &time)
{
    flightTimeToPush = time;
}


void MainWindow::on_airTimeEdit_userTimeChanged(const QTime &time)
{
    airTimeToPush = time;
}
