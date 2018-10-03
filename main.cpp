#include "src/ui/MainWindow.hpp"
#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    ui::MainWindow window;
    window.show();

    return app.exec();
}
