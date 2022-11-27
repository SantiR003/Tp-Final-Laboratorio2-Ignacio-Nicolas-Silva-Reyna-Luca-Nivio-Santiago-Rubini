#ifndef FUNCIONESPARTIDOS_H_INCLUDED
#define FUNCIONESPARTIDOS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <windows.h>


typedef struct
{
    char grupo;
    char nomEquipo[40];
    char abreviatura[5];
    int mp; ///partidos jugados
    int gf;   ///goles a favor
    int ga;  ////goles en contra
    int win;  ///partidos ganados
    int loss;  ////partidos perdidos
    int pts;  ///puntos totales
    int difGol;
    int pe;///partidos empatados

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

typedef struct
{
int idFase;
nodoPartido* partidos;
}fase;

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
void JugarPartidos(GrupoPartido arreglo[],int validos,char Seleccionado[],int DecisionJugador);
void JugarPartidos2(nodoPartido* lista,char seleccionado[],int DecisionJugador);
void JugarPartidos3(Partido partidos,char seleccionado[],int DecisionJugador);
void CargaEmpate(Equipo* equipo,int golesFavor,int GolesContra);
void CargarResultadosGanador(Equipo* equipo,int golesFvor,int golesContra);
void CargarResultadosPerdedor(Equipo* equipo,int golesFvor,int golesContra);
Equipo CargarEquipo();
void CasaApuestas();
void SeleccionDelUsuario(Grupo arreglo[],int validos);
void SeleccionDelUsuario2(nodoGrupoEquipo* lista);
nodoGrupoEquipo* CrearNodoGrupoEquipo(Equipo * equipos);
void CargarDiferenciaGoles(Equipo* equipos,Equipo* equipos2);
int PasarEquiposOrdenados(Grupo arreglo[],nodoEquipo* lista);
void OrdenarEquipos(nodoGrupoEquipo** lista,nodoGrupoEquipo* nuevo);
int verificacionEquipo(Grupo arreglo[],int validos,char nombreEquipo[]);
int verificacionEquipoSublista(nodoGrupoEquipo* lista,char nombreEquipo[]);
void Gotoxy(int x,int y);
void Muestra();
void Fecha3(nodoGrupoEquipo* sublista);
void Fecha2(nodoGrupoEquipo* sublista);
void Fecha1(nodoGrupoEquipo* sublista);
void muestraFechas(Grupo arreglo[],int validos);
int CargarPartidosOctavos(int validos,Grupo partidosOrdenados[],fase eliminatorias[],int validos2);
void mostrarOctavos(fase eliminatorias[]);
void partidosOctavos2(nodoPartido* partidos);
nodoPartido*  crearNodoPartidos2(Equipo* primero,Equipo* segundo);
void PartidosDeOctavos(nodoPartido** partidos,nodoGrupoEquipo* sublista,nodoGrupoEquipo* sublista2);
void CrearPosicionArregloPartidosFases(fase arreglo[],int validos);

int JugarOctavosYDefinirCuartos(int validosFase,fase elimatorias[]);
int cargaCuartos(nodoPartido* lista,fase eliminatorias[],int validos);
void PasaACuartos1(fase eliminatorias[],int validos,nodoPartido*nuevo);

int golesConvertidos(char equipo[],GrupoPartido partidos [],int validos);
int goles(nodoEquipo* listam,char equipo[]);

#endif // FUNCIONESPARTIDOS_H_INCLUDED
