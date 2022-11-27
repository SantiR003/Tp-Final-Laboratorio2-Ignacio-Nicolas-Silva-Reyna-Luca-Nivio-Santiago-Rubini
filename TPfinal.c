#include "TPfinal.h"


int PasarEquiposAGrupos(nodoEquipo* lista,Grupo arreglo[])
{
    int validos = 0;
    int Pos = 0;
    while(lista!=NULL)
    {
        nodoGrupoEquipo* nuevo=CrearNodoGrupoEquipo(&(lista->equipo));
        Pos=BuscarPosicion(arreglo,validos,lista->equipo.grupo);
        if(Pos==-1)
        {
            validos=CrearPosicionArreglo(arreglo,validos,lista->equipo.grupo);
            Pos=validos-1;
        }
        InsertarAlFinalGrupos(&arreglo[Pos].equipos,nuevo);
        lista=lista->siguiente;
    }
    return validos;
}

int CrearPosicionArreglo(Grupo arreglo[],int validos,char grupo)
{
    arreglo[validos].letra=grupo;
    arreglo[validos].equipos=NULL;
    validos++;

    return validos;
}

void CrearPosicionArregloPartidos(GrupoPartido arreglo[],int validos,char grupo)
{
    arreglo[validos].letra=grupo;
    arreglo[validos].partidos=NULL;
    validos++;
}

int BuscarPosicion(Grupo arreglo[],int validos,char Grupo)
{
    int i = 0;
    while(i<validos)
    {
        if(arreglo[i].letra==Grupo)
        {
            return i;
        }
        i++;
    }

    return -1;
}

void CrearPartidos(Grupo arreglo[],int validos,GrupoPartido partidos[])
{
    int i = 0;
    int j = 0;
    for(i=0; i<validos; i++)
    {
        CrearPosicionArregloPartidos(partidos,j,arreglo[i].letra);
        CrearPartidos2(arreglo[i].equipos,&partidos[j].partidos);
        CrearPartidos3(arreglo[i].equipos,&partidos[j].partidos);
        CrearPartidos4(arreglo[i].equipos,&partidos[j].partidos);
        j++;
    }
}

void CrearPartidos2(nodoGrupoEquipo* lista,nodoPartido** listaP)
{
    Partido partidos;
    int contador = 1;
    nodoGrupoEquipo* equipo1=NULL;
    nodoGrupoEquipo* equipo2=NULL;
    equipo1=lista;
    lista=lista->siguiente;
    while(lista!=NULL)
    {
        equipo2=lista;
        partidos=CrearEquipo(contador,(equipo1->equipo),(equipo2->equipo));
        nodoPartido* nuevo=CrearNodoPartidos(partidos);
        InsertarAlFinalPartidos(listaP,nuevo);
        contador++;
        lista=lista->siguiente;
    }
}

void CrearPartidos3(nodoGrupoEquipo* lista,nodoPartido** listaP)
{
    Partido partidos;
    int contador = 2;
    nodoGrupoEquipo* equipo1=NULL;
    nodoGrupoEquipo* equipo2=NULL;
    lista=lista->siguiente;
    equipo1=lista;
    lista=lista->siguiente;
    while(lista!=NULL)
    {
        equipo2=lista;
        partidos=CrearEquipo(contador,(equipo1->equipo),(equipo2->equipo));
        nodoPartido* nuevo=CrearNodoPartidos(partidos);
        InsertarAlFinalPartidos(listaP,nuevo);
        contador++;
        lista=lista->siguiente;
    }
}

void CrearPartidos4(nodoGrupoEquipo* lista,nodoPartido** listaP)
{
    Partido partidos;
    int contador = 1;
    nodoGrupoEquipo* equipo1=NULL;
    nodoGrupoEquipo* equipo2=NULL;
    lista=lista->siguiente;
    lista=lista->siguiente;
    equipo1=lista;
    lista=lista->siguiente;
    while(lista!=NULL)
    {
        equipo2=lista;
        partidos=CrearEquipo(contador,(equipo1->equipo),(equipo2->equipo));
        nodoPartido* nuevo=CrearNodoPartidos(partidos);
        InsertarAlFinalPartidos(listaP,nuevo);
        contador++;
        lista=lista->siguiente;
    }
}

nodoPartido* CrearNodoPartidos(Partido partidos)
{
    nodoPartido* nuevo=(nodoPartido*)malloc(sizeof(nodoPartido));
    nuevo->partido=partidos;
    nuevo->siguiente=NULL;

    return nuevo;
}

Partido CrearEquipo(int contador,Equipo* equipo1,Equipo* equipo2)
{
    Partido equipos;

    equipos.equipo1=equipo1;
    equipos.equipo2=equipo2;
    equipos.fecha=contador;
    equipos.golesEq1=0;
    equipos.golesEq2=0;
    equipos.penales1=0;
    equipos.penales2=0;

    return equipos;
}

void PasarDatosArchivoALista(nodoEquipo** lista,char archivo[30])
{
    FILE*buffer=fopen(archivo,"rb");
    Equipo equipos;
    if(buffer!=NULL)
    {
        while(fread(&equipos,sizeof(Equipo),1,buffer)>0)
        {
            nodoEquipo* nuevo=CrearNodoEquipo(equipos);
            InsertarAlFinal(lista,nuevo);
        }
        fclose(buffer);
    }
}

void InsertarAlFinal(nodoEquipo** lista,nodoEquipo* nuevo)
{
    if(*lista==NULL)
    {
        *lista=nuevo;
    }
    else
    {
        nodoEquipo* seg=*lista;
        while(seg->siguiente!=NULL)
        {
            seg=seg->siguiente;
        }
        seg->siguiente=nuevo;
    }
}

void InsertarAlFinalPartidos(nodoPartido** lista,nodoPartido* nuevo)
{
    if(*lista==NULL)
    {
        *lista=nuevo;
    }
    else
    {
        nodoPartido* seg=*lista;
        while(seg->siguiente!=NULL)
        {
            seg=seg->siguiente;
        }
        seg->siguiente=nuevo;
    }
}

void InsertarAlFinalGrupos(nodoGrupoEquipo** lista,nodoGrupoEquipo* nuevo)
{
    if(*lista==NULL)
    {
        *lista=nuevo;
    }
    else
    {
        nodoGrupoEquipo* seg=*lista;
        while(seg->siguiente!=NULL)
        {
            seg=seg->siguiente;
        }
        seg->siguiente=nuevo;
    }
}


void InsertarAlPrincipio(nodoGrupoEquipo** lista,nodoGrupoEquipo* nuevo)
{
    if(*lista!=NULL)
    {
        nuevo->siguiente=*lista;
    }
    *lista=nuevo;
}

nodoGrupoEquipo* CrearNodoGrupoEquipo(Equipo * equipos)
{
    nodoGrupoEquipo* nuevo=(nodoGrupoEquipo*)malloc(sizeof(nodoGrupoEquipo));
    nuevo->equipo=equipos;
    nuevo->siguiente=NULL;

    return nuevo;
}

nodoEquipo* CrearNodoEquipo(Equipo equipos)
{
    nodoEquipo* nuevo=(nodoEquipo*)malloc(sizeof(nodoEquipo));
    nuevo->equipo=equipos;
    nuevo->siguiente=NULL;

    return nuevo;
}

void MostrarLista(Grupo arreglo[],int validos)
{
    int i = 0;
    while(i<validos)
    {
        printf("\n-----------\n");
        printf("Grupo:%c \n",arreglo[i].letra);
        MostrarLista2(arreglo[i].equipos);
        printf("\n-----------\n");
        i++;
    }
}

void MostrarLista2(nodoGrupoEquipo* lista)
{
    while(lista!=NULL)
    {
        printf("\nNombre equipo:%s ",(lista->equipo->nomEquipo));
        printf("\nPJ:%i",(lista->equipo->mp));
        printf("\nGAF:%i",(lista->equipo->gf));
        printf("\nGEN:%i",(lista->equipo->ga));
        printf("\nDG:%d",(lista->equipo->difGol));
        printf("\nPG:%i",(lista->equipo->win));
        printf("\nPP:%i",(lista->equipo->loss));
        printf("\nPT:%i",(lista->equipo->pts));
        lista=lista->siguiente;
    }
}

void MostrarPartidos(GrupoPartido arreglo[],int validos)
{
    int i = 0;
    while(i<validos)
    {
        printf("\n");
        printf("-----------\n");
        printf("Grupo:%c \n",arreglo[i].letra);
        MostrarPartidos2(arreglo[i].partidos);
        i++;
        printf("-----------\n");
        printf("\n");
    }
}

void MostrarPartidos2(nodoPartido* lista)
{
    int partido = 1;
    while(lista!=NULL)
    {
        printf("-----------\n");
        printf("Partido %d:%s [%d] VS [%d] %s\n",partido,(lista->partido.equipo1->nomEquipo),(lista->partido.golesEq1),(lista->partido.golesEq2),(lista->partido.equipo2->nomEquipo));
        //printf("Equipo2:%s\n",(lista->partido.equipo2->nomEquipo));
//        printf("Goles Equipo1:%d\n",(lista->partido.golesEq1));
//        printf("Goles Equipo2:%d\n",(lista->partido.golesEq2));
        printf("Fecha:%d\n",(lista->partido.fecha));
//        printf("Penales Equipo1:%d\n",(lista->partido.penales1));
//        printf("Penales Equipo2:%d\n",(lista->partido.penales2));
//        printf("-----------\n");
        partido++;
        lista=lista->siguiente;
    }
}

void JugarPartidos(GrupoPartido arreglo[],int validos,char Seleccionado[])
{
    int i = 0;
    srand (time(NULL));
    for(i=0; i<validos; i++)
    {
        JugarPartidos2(arreglo[i].partidos,Seleccionado);
    }
}

void JugarPartidos2(nodoPartido* lista,char seleccionado[])
{
    while(lista!=NULL)
    {
        JugarPartidos3(lista->partido,seleccionado);
        lista=lista->siguiente;
    }
}

void JugarPartidos3(Partido partidos,char seleccionado[])
{

    if(strcmpi(partidos.equipo1->nomEquipo,seleccionado)==0)
    {
        int flag=0;
        while(flag==0)
        {
            partidos.golesEq1=rand()%(0+5);
            partidos.golesEq2=rand()%(0+5);
            if(partidos.golesEq1>partidos.golesEq2)
            {
                flag=1;
            }
        }
        CargarResultadosGanador(partidos.equipo1,partidos.golesEq1,partidos.golesEq2);
        CargarResultadosPerdedor(partidos.equipo2,partidos.golesEq1,partidos.golesEq2);
        printf("\n");
        printf("Resultado:%s [%d] VS [%d] %s\n",(partidos.equipo1->nomEquipo),(partidos.golesEq1),(partidos.golesEq2),(partidos.equipo2->nomEquipo));
        printf("\n");
    }
    else if((strcmpi(partidos.equipo2->nomEquipo,seleccionado)==0))
    {
        int flag=0;
        while(flag==0)
        {
            partidos.golesEq1=rand()%(0+5);
            partidos.golesEq2=rand()%(0+5);
            if(partidos.golesEq1<partidos.golesEq2)
            {
                flag=1;
            }
        }
        CargarResultadosGanador(partidos.equipo2,partidos.golesEq1,partidos.golesEq2);
        CargarResultadosPerdedor(partidos.equipo1,partidos.golesEq1,partidos.golesEq2);
        printf("\n");
        printf("Resultado:%s [%d] VS [%d] %s\n",(partidos.equipo1->nomEquipo),(partidos.golesEq1),(partidos.golesEq2),(partidos.equipo2->nomEquipo));
        printf("\n");
    }
    else
    {
        partidos.golesEq1=rand()%(0+5);
        partidos.golesEq2=rand()%(0+5);

        if(partidos.golesEq1>partidos.golesEq2)
        {
            CargarResultadosGanador(partidos.equipo1,partidos.golesEq1,partidos.golesEq2);
            CargarResultadosPerdedor(partidos.equipo2,partidos.golesEq1,partidos.golesEq2);
            printf("\n");
            printf("Resultado:%s [%d] VS [%d] %s\n",(partidos.equipo1->nomEquipo),(partidos.golesEq1),(partidos.golesEq2),(partidos.equipo2->nomEquipo));
            printf("\n");
        }
        else if(partidos.golesEq1<partidos.golesEq2)
        {
            CargarResultadosGanador(partidos.equipo2,partidos.golesEq1,partidos.golesEq2);
            CargarResultadosPerdedor(partidos.equipo1,partidos.golesEq1,partidos.golesEq2);
            printf("\n");
            printf("Resultado:%s [%d] VS [%d] %s\n",(partidos.equipo1->nomEquipo),(partidos.golesEq1),(partidos.golesEq2),(partidos.equipo2->nomEquipo));
            printf("\n");
        }
        else
        {
            CargaEmpate(partidos.equipo1,partidos.golesEq1,partidos.golesEq2);
            CargaEmpate(partidos.equipo2,partidos.golesEq1,partidos.golesEq2);
            printf("\n");
            printf("Resultado:%s [%d] VS [%d] %s\n",(partidos.equipo1->nomEquipo),(partidos.golesEq1),(partidos.golesEq2),(partidos.equipo2->nomEquipo));
            printf("\n");
        }
    }
}

void CargaEmpate(Equipo* equipo,int golesFavor,int GolesContra)
{
    (equipo->mp)=(equipo->mp+1);
    (equipo->gf)=(equipo->gf+golesFavor);
    (equipo->ga)=(equipo->ga+GolesContra);
    (equipo->difGol)=(golesFavor-GolesContra);
    (equipo->pts)=(equipo->pts+1);
}

void CargarResultadosGanador(Equipo* equipo,int golesFvor,int golesContra)
{
    (equipo->mp)=(equipo->mp+1);
    (equipo->gf)=(equipo->gf+golesFvor);
    (equipo->ga)=(equipo->ga+golesContra);
    (equipo->win)=(equipo->win+1);
    (equipo->difGol)=(golesFvor-golesContra);
    (equipo->pts)=(equipo->pts+3);
}

void CargarResultadosPerdedor(Equipo* equipo,int golesFvor,int golesContra)
{
    (equipo->mp)=(equipo->mp+1);
    (equipo->gf)=(equipo->gf+golesFvor);
    (equipo->ga)=(equipo->ga+golesContra);
    (equipo->loss)=(equipo->win+1);
    (equipo->difGol)=(golesFvor-golesContra);
}


Equipo CargarEquipo()
{
    Equipo equipos;

    printf("Nombre de Equipo:");
    fflush(stdin);
    gets(equipos.nomEquipo);

    printf("Partidos Jugados:");
    scanf("%d",&equipos.mp);

    printf("Goles a Favor:");
    scanf("%d",&equipos.gf);

    printf("Goles en Contra:");
    scanf("%d",&equipos.ga);

    printf("Partidos Ganados:");
    scanf("%d",&equipos.win);

    printf("Partidos Perdidos:");
    scanf("%d",&equipos.loss);

    printf("Puntos Totales:");
    scanf("%d",&equipos.pts);

    return equipos;
}

void CasaApuestas()
{
    system("color 6");
    printf("\n\n\n");
    printf("                                                     ((((((    /////((// .(((( *((((..((((((((( .*((((((/.((((((((((/ .(((((/   ,/((((((.                                                                       \n");
    printf("                                                   .(#####(   ,####(####./(##/ (##(*  *###((##*,###//(##./##/(##((##,.(#####(  (##((##*                                                                       \n");
    printf("                                                   (## ###(   ,###((###* /##(  *###,  *#####(   (######(* .(###,... (## ###(  /#######/                                                                        \n");
    printf("                                                  .(#######/   #(##   .  ,###/ ###/   (##    ,. .,  ###*   ,###(   .########/     (##(                                                                        \n");
    printf("                                                 (###   ####,.(### .     /###((###. ,(###((##( /#######(  /(###(  ((##  ###(,,#######(.                                                                         \n");
    printf("                                                                                                                                                                                           \n");
    printf("                         ..........                                           ......      ............                                                                                     \n");
    printf("                        #@@@@@@@@@@@@@@. *@@@@@@@@@@@@@& /@@@@@@@@@@@@@@/ #@@@@@@@@@@@@, *@@@@@@@@@@@@@@( &@@@@@@@@@@@@@@@@ @@@@@@@@. @@@@@@@ ,@@@@@@@@, &@@@@@@@@@,    (@@@@@@@@@@@@/      \n");
    printf("                       .&@@@@@@@@@@@@@@ .&@@@@@@&&@@@@@*.@@@@@@@@@@@@@@@.#@@@@@@@@@@@@@..&@@@@@@@@@@@@@@*#@@@@&@@@@@@@@@@@(,@@@@@@@# /&@@@@@&.&@@@@@@@# #@@@@@@@@@@.   (@@@@@@&@@@@@@       \n");
    printf("                        /@@@@@# #@@@@@.  ,@@@@@&,,,,      @@@@@# (@@@@@*,@@@@@& /@@@@@*  ,@@@@@@.(@@@@@(.@@@@##@@@@@/#@@@@  &@@@@@.    @@@@@# @@@@@@.  #@@@@@@@@@@@.   &@@@@@*             \n");
    printf("                       .@@@@@@ *@@@@@#   @@@@@@@@@@      @@@@@@@@@@@@@& #@@@@@,,@@@@@#   @@@@@@@@@@@@#       ,@@@@@@       ,@@@@@,     @@@@@(&@@@@@   #@@@@@,&@@@@@   .@@@@@@@@@@@@@        \n");
    printf("                       #@@@@@/ &@@@@@.  /@@@@@# .,,...  *@@@@@&#####,  /@@@@@( %@@@@@*  /@@@@@&(&@@@@@/      &@@@@@/       @@@@@#      @@@@@@@@@@@   %@@@@@@@@@@@@@      ***,(@@@@@#         \n");
    printf("                     ,(@@@@@@/#@@@@@( .(@@@@@@(#@@@@@*.(@@@@@@(.       &@@@@@((@@@@@# ./@@@@@@ .@@@@@@(    ,#@@@@@@(     *#@@@@@#.    /@@@@@@@@@# .(@@@@@@&&@@@@@@@# *@@@@@&#@@@@@@,         \n");
    printf("                     @@@@@@@@@@@@@@#  @@@@@@@@@@@@@@& &@@@@@@@&       ,@@@@@@@@@@@@#  @@@@@@@( #@@@@@@#   .@@@@@@@@/    ,@@@@@@@#     (@@@@@@@@(  #@@@@@@#  &@@@@@@( &@@@@@@@@@@@@*          \n");
    printf("                    ,**********,,    .************** .********          ,********.   .*******   ******    ,********     ,*******.     ,*******,   *******   ******* .**********,              \n");
}

void SeleccionDelUsuario(Grupo arreglo[],int validos)
{
    int i = 0;
    for(i=0; i<validos; i++)
    {
        //printf("|--------------------|\n");
        printf("\t    [GRUPO:%c]  \n",arreglo[i].letra);
        SeleccionDelUsuario2(arreglo[i].equipos);
        printf("|--------------------|\n");

    }
}

void SeleccionDelUsuario2(nodoGrupoEquipo* lista)
{
    int contador=0;
    while(lista!=NULL)
    {
        printf("[%s]-\n",lista->equipo->nomEquipo);
        lista=lista->siguiente;
    }
}
