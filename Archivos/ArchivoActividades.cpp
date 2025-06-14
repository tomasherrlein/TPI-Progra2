#include <iostream>
#include "ArchivoActividades.h"
using namespace std;

///Se le manda el nombre al constructor del padre, porque lo necesita
ArchivoActividades::ArchivoActividades(string nombre) : Archivo(nombre) { }

int ArchivoActividades::getCantidadRegistros()
{
    if(!abrirLecturaPlus()) return -1;

    fseek(_pArchivo, 0, SEEK_END);
    int cantidadRegistros = ftell(_pArchivo) / sizeof(Actividad);
    cerrar();
    return cantidadRegistros;
}


bool ArchivoActividades::modificar(Actividad actividad, int posicion)
{
    if(!abrirLecturaPlus()) return false;

    fseek(_pArchivo, sizeof(Actividad) * posicion, SEEK_SET);
    bool ok = fwrite(&actividad, sizeof(Actividad), 1, _pArchivo);
    cerrar();
    return ok;
}


bool ArchivoActividades::guardar(Actividad actividad)
{
    if(!abrirEscritura()) return false;
    bool ok = fwrite(&actividad, sizeof(Actividad), 1, _pArchivo);
    cerrar();
    return ok;
}

int ArchivoActividades::buscar(int idActividad)
{

    if(!abrirLectura()) return false;
    int posicion = 0;
    Actividad actividad;
    while(fread(&actividad,sizeof(Actividad),1,_pArchivo)){
        if(actividad.getIdActividad() == idActividad){
            cerrar();
            return posicion;
        }
        posicion++;
    }
    cerrar();
    return -1;
}

Actividad ArchivoActividades::leer(int posicion){

    Actividad actividad;
    if(!abrirLectura()){
        actividad.setIdActividad(-1);
        return actividad;
    }


    fseek(_pArchivo, sizeof(Actividad) * posicion, SEEK_SET);
    fread(&actividad, sizeof(Actividad), 1, _pArchivo);
    cerrar();
    return actividad;
}

void ArchivoActividades::leerTodos(int cantidadRegistros, Actividad *vec){

    if(!abrirLectura()) return;
    fread(vec, sizeof(Actividad), cantidadRegistros, _pArchivo);
    cerrar();
}

int ArchivoActividades::getNuevoId(){

    ///Por si es el primer id
    if (getCantidadRegistros() == -1){
        abrirEscritura();
        cerrar();
    }

    return getCantidadRegistros() + 1;
}

bool ArchivoActividades::exportarCSV(){

    FILE *csv;
    csv = fopen("Actividades.csv", "w");
    if (csv == nullptr){
        return false;
    }

    int cantRegistros = getCantidadRegistros();
    Actividad *actividades = new Actividad[cantRegistros];
    leerTodos(cantRegistros, actividades);

    fprintf(csv, "ID Socio;DNI;Nombre;Apellido;Email;FechaNacimiento\n");

    for (int i=0; i < cantRegistros; i++){
        if (!actividades[i].getEliminado()){
            fprintf(csv, "%s\n", actividades[i].toCSV().c_str());
        }
    }

    fclose(csv);

    delete[] actividades;
    return true;
}
