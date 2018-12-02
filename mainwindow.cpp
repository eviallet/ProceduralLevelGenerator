#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

	// setting up the table
    _table = ui->table;
    _table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	_table->setSelectionMode(QAbstractItemView::NoSelection);
    _table->setRowCount(DEFAULT_HEIGHT);
    _table->setColumnCount(DEFAULT_WIDTH);
	for (int i = 0; i < DEFAULT_HEIGHT; i++)
		_table->setRowHeight(i, _table->height() / DEFAULT_HEIGHT);
	for (int i = 0; i < DEFAULT_WIDTH; i++)
		_table->setColumnWidth(i, _table->width() / DEFAULT_WIDTH);
	_table->setShowGrid(false);
	
	// setting up the combo box
    ui->comboBox->addItems(QStringList({
		"Overworld",
		"Underground"
		}
	));
    ui->comboBox->setCurrentIndex(0);
	
    connect(ui->btn_generate, &QPushButton::clicked, this, &MainWindow::generate);
    generate();
}

void MainWindow::generate() {
	Map *map = new Map(DEFAULT_WIDTH, DEFAULT_HEIGHT);
	Generator::randomize(map, (MapType)ui->comboBox->currentIndex());

	// Applying colors and icons
	for (int y = 0; y < map->getHeight(); y++) {
		for (int x = 0; x < map->getWidth(); x++) {
			QTableWidgetItem *item = new QTableWidgetItem;
			item->setData(Qt::BackgroundRole, QBrush(QPixmap(map->getTile(x, y).getIcon())));
			_table->setItem(y, x, item);
		}
	}
}

MainWindow::~MainWindow() {
    delete ui; 
}
