#include <QApplication>
#include <QCoreApplication>

#include "pch.h"

int main(int argc, char *argv[]) {
#if (QT_VERSION > QT_VERSION_CHECK(5,4,0))
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
#endif
    checkConfig();
    QApplication a(argc, argv);
    NE_Editor w;
    w.setWindowIcon(QIcon(":/resource/icons/NE.png"));
    w.show();
    return QApplication::exec();
}
