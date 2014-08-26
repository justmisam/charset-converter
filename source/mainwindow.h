/**
 * The main window library
 *
 * @package Charset Converter
 * @since Charset Converter 1.0
 * @license GNU General Public License v3 or later
 * @copyright (C) 2014 Misam Saki, misam.ir
 * @author Misam Saki, http://misam.ir/
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setFile(QString);

private:
    Ui::MainWindow *ui;
    QString filename;

private slots:
    void openFile();
    void saveFile();
    void saveasFile();
    void switchEncode();

    void close();
    void showAbout();

    void dropEvent(QDropEvent *ev);
    void dragEnterEvent(QDragEnterEvent *ev);
};

#endif // MAINWINDOW_H
