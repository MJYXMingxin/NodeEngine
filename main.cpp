#include "ne_editor.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NE_Editor w;
    w.show();
    return a.exec();
}
