/**
 * The main function for load application
 *
 * @package Charset Converter
 * @since Charset Converter 1.0
 * @license GNU General Public License v3 or later
 * @copyright (C) 2015 Misam Saki, misam.ir
 * @author Misam Saki, http://misam.ir/
 */

#include "myapp.h"
#include "iostream"
#include "string"
#include <QFile>
#include <QTextStream>

int main(int argc, char *argv[])
{
    bool gui = false;
    if (argc > 1) if (QString::fromUtf8(argv[1]).compare("-gui") == 0) gui = true;

    if (gui) { // GUI
        MyApp app(argc, argv);
        return 0;
    } else { // Terminal
        if (!(argc == 3 || argc == 4)) {
            std::cout << "Terminal Usage: charset-converter filename encoding [output_filename]\nGUI Usage: charset-converter -gui [filename]\n";
            return 1;
        } else {
            QFile file(argv[1]);
            QString text;
            if(file.open(QIODevice::ReadOnly|QIODevice::Text)) {
                QTextStream in(&file);
                in.setCodec(argv[2]);
                text = in.readAll();
            } else {
                std::cout << "Error: The file can not be opened!\n";
                return 2;
            }
            file.close();
            if (argc == 4) file.setFileName(argv[3]);
            if(file.open(QIODevice::WriteOnly|QIODevice::Text)) {
                QTextStream out(&file);
                out << text;
                out.setCodec(argv[2]);
                file.close();
            } else {
                std::cout << "Error: The file can not be saved!\n";
                file.close();
                return 3;
            }
            return 0;
        }
    }
}
