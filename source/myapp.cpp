/**
 * The application class
 *
 * @package Charset Converter
 * @since Charset Converter 1.1
 * @license GNU General Public License v3 or later
 * @copyright (C) 2015 Misam Saki, misam.ir
 * @author Misam Saki, http://misam.ir/
 */

#include "myapp.h"
#include "mainwindow.h"
#include <QFileOpenEvent>

MyApp::MyApp(int& argc, char**argv): QApplication(argc, argv)
{
    if (argc == 3) {
        w.setFile(QString::fromUtf8(argv[2]));
    }
    w.show();
    exec();
}

MyApp::~MyApp()
{
}

bool MyApp::event(QEvent *event)
{
    switch(event->type())
    {
    case QEvent::FileOpen:
    {
        QFileOpenEvent * fileOpenEvent = static_cast<QFileOpenEvent *>(event);
        if(fileOpenEvent)
        {
            QString m_macFileOpenOnStart;
            m_macFileOpenOnStart = fileOpenEvent->file();
            if(!m_macFileOpenOnStart.isEmpty())
            {
                w.setFile(m_macFileOpenOnStart);
                return true;
            }
        }
    }
    default:
        return QApplication::event(event);
    }
    return QApplication::event(event);
}
