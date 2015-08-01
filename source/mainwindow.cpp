/**
 * The main window class
 *
 * @package Charset Converter
 * @since Charset Converter 1.0
 * @license GNU General Public License v3 or later
 * @copyright (C) 2015 Misam Saki, misam.ir
 * @author Misam Saki, http://misam.ir/
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());

    ui->comboBoxEncode->addItem(tr("Default"));
    ui->comboBoxEncode->addItem(tr("UTF-8"));
    ui->comboBoxEncode->addItem(tr("Windows-1256"));
    ui->comboBoxEncode->addItem(tr("ISO-8859-1"));
    ui->comboBoxEncode->addItem(tr("Windows-1252"));

    setAcceptDrops(true);

    connect(ui->pushButtonSave, SIGNAL(clicked()), this, SLOT(saveFile()));
    connect(ui->pushButtonSaveas, SIGNAL(clicked()), this, SLOT(saveasFile()));
    connect(ui->comboBoxEncode,SIGNAL(currentIndexChanged(int)), this, SLOT(switchEncode()));

    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openFile()));
    addAction(ui->actionOpen);
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveFile()));
    addAction(ui->actionSave);
    connect(ui->actionSaveas, SIGNAL(triggered()), this, SLOT(saveasFile()));
    addAction(ui->actionSaveas);
    connect(ui->actionClose, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(showAbout()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setFile(QString filename) {
    this->filename = filename;
    if (!filename.isEmpty()) {
        ui->comboBoxEncode->setCurrentIndex(0);
        ui->pushButtonSave->setEnabled(true);
        ui->pushButtonSaveas->setEnabled(true);
        ui->actionSave->setEnabled(true);
        ui->actionSaveas->setEnabled(true);
        QFile file(filename);
        if(file.open(QIODevice::ReadOnly|QIODevice::Text)) {
            QTextStream in(&file);
            ui->textEdit->setText(in.readAll());
        }
        file.close();
    }
}

void MainWindow::dropEvent(QDropEvent *ev) {
    QList<QUrl> urls = ev->mimeData()->urls();
    foreach(QUrl url, urls) {
        filename = url.toLocalFile();
        if (!filename.isEmpty()) {
            ui->comboBoxEncode->setCurrentIndex(0);
            ui->pushButtonSave->setEnabled(true);
            ui->pushButtonSaveas->setEnabled(true);
            ui->actionSave->setEnabled(true);
            ui->actionSaveas->setEnabled(true);
            QFile file(filename);
            if(file.open(QIODevice::ReadOnly|QIODevice::Text)) {
                QTextStream in(&file);
                ui->textEdit->setText(in.readAll());
            }
            file.close();
        }
    }
}

void MainWindow::dragEnterEvent(QDragEnterEvent *ev) {
    ev->accept();
}

void MainWindow::openFile() {
    QFileDialog::Options options;
    QString selectedFilter;
    filename = QFileDialog::getOpenFileName(this,
                                            tr("Open File"),
                                            NULL,
                                            tr("All Files (*);;Text Files (*.txt);;Text Files (*.srt)"),
                                            &selectedFilter,
                                            options);
    if (!filename.isEmpty()) {
        ui->comboBoxEncode->setCurrentIndex(0);
        ui->pushButtonSave->setEnabled(true);
        ui->pushButtonSaveas->setEnabled(true);
        ui->actionSave->setEnabled(true);
        ui->actionSaveas->setEnabled(true);
        QFile file(filename);
        if(file.open(QIODevice::ReadOnly|QIODevice::Text)) {
            QTextStream in(&file);
            ui->textEdit->setText(in.readAll());
        }
        file.close();
    }
}
void MainWindow::saveFile() {
    QString code = ui->comboBoxEncode->currentText();
    if (code != "Default") {
        QFile file(filename);
        if(file.open(QIODevice::WriteOnly|QIODevice::Text)) {
            QTextStream out(&file);
            out << ui->textEdit->toPlainText();
            out.setCodec(code.toUtf8());
        }
        file.close();
    }
}
void MainWindow::saveasFile() {
    QFileDialog::Options options;
    QString selectedFilter;
    QString newfile;
    newfile = QFileDialog::getSaveFileName(this,
                                            tr("Save File"),
                                            filename,
                                            tr("All Files (*);;Text Files (*.txt);;Text Files (*.srt)"),
                                            &selectedFilter,
                                            options);
    if (!newfile.isEmpty()) {
        QString code = ui->comboBoxEncode->currentText();
        QFile file(newfile);
        if(file.open(QIODevice::WriteOnly|QIODevice::Text)) {
            QTextStream out(&file);
            out << ui->textEdit->toPlainText();
            out.setCodec(code.toUtf8());
            file.close();
        }
    }
}
void MainWindow::switchEncode() {
    QString code = ui->comboBoxEncode->currentText();
    QFile file(filename);
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)) {
        QTextStream in(&file);
        if (code != "Default") in.setCodec(code.toUtf8());
        ui->textEdit->setText(in.readAll());
    }
}

void MainWindow::close() {
    QApplication::quit();
}
void MainWindow::showAbout() {
    QMessageBox::information(this, tr("About"), "Charset Converter\nVersion 1.0\nLicense GNU General Public License v3 or later\nCopyright (C) 2014 Misam Saki, misam.ir\nAuthor: Misam Saki, http://misam.ir/\nGithub: http://github.com/misamplus/charset-converter/");
}

