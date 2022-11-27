#ifndef TPFINAL_H_INCLUDED
#define TPFINAL_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

typedef struct
{
    char grupo;
    char nomEquipo[40];
    int pos;
    int mp; ///partidos jugados
    int gf;   ///goles a favor
    int ga;  ////goles en contra
    int difGol; ///Diferencia de goles
    int win;  ///partidos ganados
    int loss;  ////partidos perdidos
    int pts;  ////puntos totales
} Equipo;

typedef struct
{
    // int id; ///opcional
    int fecha; ///eligen ustedes el criterio, el tipo tambien
    Equipo* equipo1;
    Equipo* equipo2;
    int golesEq2;
    int golesEq1;
    int penales1; ///en la fase de grupos no hay penales
    int penales2; ///pueden setearlo en 1 y 0 (como un boolean)
} Partido;

typedef struct
{
    Partido partido;
    struct nodoPartido* siguiente;
} nodoPartido;


typedef struct
{
    char letra;
    nodoPartido* partidos;
} GrupoPartido;

typedef struct
{
    Equipo equipo;
    struct nodoEquipo* siguiente;
} nodoEquipo;

typedef struct
{
    char letra; ///'A','B'....
    struct nodoGrupoEquipo* equipos; ///siempre va a haber 4
} Grupo;

typedef struct
{
    Equipo* equipo;
    struct nodoGrupoEquipo* siguiente;
} nodoGrupoEquipo;

Partido CrearEquipo(int contador,Equipo* equipo1,Equipo* equipo2);
int PasarEquiposAGrupos(nodoEquipo* lista,Grupo arreglo[]);
int CrearPosicionArreglo(Grupo arreglo[],int validos,char grupo);
void CrearPosicionArregloPartidos(GrupoPartido arreglo[],int validos,char grupo);
int BuscarPosicion(Grupo arreglo[],int validos,char Grupo);
void CrearPartidos(Grupo arreglo[],int validos,GrupoPartido partidos[]);
void CrearPartidos2(nodoGrupoEquipo* lista,nodoPartido** listaP);
void CrearPartidos3(nodoGrupoEquipo* lista,nodoPartido** listaP);
void CrearPartidos4(nodoGrupoEquipo* lista,nodoPartido** listaP);
nodoPartido* CrearNodoPartidos(Partido partidos);
void PasarDatosArchivoALista(nodoEquipo** lista,char archivo[30]);
void InsertarAlFinal(nodoEquipo** lista,nodoEquipo* nuevo);
void InsertarAlFinalPartidos(nodoPartido** lista,nodoPartido* nuevo);
void InsertarAlFinalGrupos(nodoGrupoEquipo** lista,nodoGrupoEquipo* nuevo);
void InsertarAlPrincipio(nodoGrupoEquipo** lista,nodoGrupoEquipo* nuevo);
nodoEquipo* CrearNodoEquipo(Equipo equipos);
void MostrarLista(Grupo arreglo[],int validos);
void MostrarLista2(nodoGrupoEquipo* lista);
void MostrarPartidos(GrupoPartido arreglo[],int validos);
void MostrarPartidos2(nodoPartido* lista);
void JugarPartidos(GrupoPartido arreglo[],int validos,char Seleccionado[]);
void JugarPartidos2(nodoPartido* lista,char seleccionado[]);
void JugarPartidos3(Partido partidos,char seleccionado[]);
void CargaEmpate(Equipo* equipo,int golesFavor,int GolesContra);
void CargarResultadosGanador(Equipo* equipo,int golesFvor,int golesContra);
void CargarResultadosPerdedor(Equipo* equipo,int golesFvor,int golesContra);
Equipo CargarEquipo();
void CasaApuestas();
void SeleccionDelUsuario(Grupo arreglo[],int validos);
void SeleccionDelUsuario2(nodoGrupoEquipo* lista);
nodoGrupoEquipo* CrearNodoGrupoEquipo(Equipo * equipos);




#endif // TPFINAL_H_INCLUDED
