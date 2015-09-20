#include <qapplication.h>
#include "application.h"

int main( int argc, char ** argv ) 
{
    QApplication a( argc, argv );

    Application* p_app = new Application();
    p_app->setWindowTitle( "STL Viewer" );
    p_app->show();
    a.connect( &a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()) );
    return a.exec();
}
