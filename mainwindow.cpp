#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

	connect(ui->btn_debug, &QPushButton::clicked, this, &MainWindow::debug);

	// setting up the table
    _table = ui->table;
    _table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
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
	switch ((MapType)ui->comboBox->currentIndex()) {
	case OVERWORLD:
		Overworld(map).generate();
		//_table->setStyleSheet("QWidget {border-image: url(:/bkg/res/bkg_aerial.png) 0 0 0 0 stretch stretch; }");
		break;
	case UNDERGROUND:
		Underground(map).generate();
		break;
	} 
	

	// Applying colors and icons
	for (int y = 0; y < map->getHeight(); y++) {
		for (int x = 0; x < map->getWidth(); x++) {
			QTableWidgetItem *item = new QTableWidgetItem;
			item->setData(Qt::BackgroundRole, QBrush(QPixmap(map->getTile(x, map->getHeight() - 1 - y).getIcon(ui->comboBox->currentIndex()))));
			_table->setItem(y, x, item);
		}
	}
}

MainWindow::~MainWindow() {
    delete ui; 
}

void MainWindow::debug() {
	
}
