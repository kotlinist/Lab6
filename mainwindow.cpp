#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    downloader = new Downloader();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pushButton_clicked() {
    downloader->getData();
    connect(downloader, &Downloader::onReady, this, &MainWindow::readFile);
}

void MainWindow::readFile() {
    QFile file("/Users/kotlinist/Downloads/file.xml");
    if (!file.open(QIODevice::ReadOnly)) return;
    ui->textEdit->setText(file.readAll());
}
