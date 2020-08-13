#include "widget.h"

#include <QApplication>
#include <QTranslator>
#include <QInputDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Objeto para menjar las traducciones
    QTranslator traduccion;
    //Solicitando al usuario que seleccione un idioma
    QStringList idiomas;
    idiomas <<"Ingles" <<"Español";
    QString idiomaSeleccionado = QInputDialog::getItem(NULL,
                                           "Lista de idiomas",
                                           "Seleccione el idioma",
                                           idiomas);
    //Dependiendo del idioma cargar archivo de traduccion
    if(idiomaSeleccionado == "Ingles"){
        traduccion.load(":/ListaActividades_en_US.qm");
    }
    //Si es diferente de español se instala la traduccion en toda la aplicacion
    if(idiomaSeleccionado != "Español"){
        a.installTranslator(&traduccion);
    }

    //venta principal
    a.setStyle("fusion");
    Widget w;
    w.show();
    return a.exec();
}
