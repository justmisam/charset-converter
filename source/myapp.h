/**
 * The application class header
 *
 * @package Charset Converter
 * @since Charset Converter 1.1
 * @license GNU General Public License v3 or later
 * @copyright (C) 2015 Misam Saki, misam.ir
 * @author Misam Saki, http://misam.ir/
 */

#ifndef MYAPP_H
#define MYAPP_H
#include <QApplication>
#include "mainwindow.h"

class MyApp : public QApplication
{
public:
    MyApp(int& argc, char**argv);
    virtual ~MyApp();
    int run();
private:
    MainWindow w;
protected:
        bool event(QEvent *);
};

#endif // MYAPP_H
