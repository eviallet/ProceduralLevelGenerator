#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "Generator/generator.h"
#include "tile.h"

constexpr auto DEFAULT_WIDTH = 65;
constexpr auto DEFAULT_HEIGHT = 10;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void generate();
private:
    Ui::MainWindow *ui;
    QTableWidget *_table;
};

#endif // MAINWINDOW_H
