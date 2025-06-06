#pragma once
#include "Fecha.h"


class Inscripcion {
private:
    int idActividad;
    int idSocio;
    Fecha fechaInscripcion;
    bool eliminado;

public:

    // Getters
    int getIdActividad();
    int getIdSocio();
    Fecha getFechaInscripcion();
    bool getEliminado();

    // Setters
    void setIdActividad(int idActividad);
    void setIdSocio(int idSocio);
    void setFechaInscripcion(Fecha fechaInscripcion);
    void setEliminado(bool eliminado);
};
