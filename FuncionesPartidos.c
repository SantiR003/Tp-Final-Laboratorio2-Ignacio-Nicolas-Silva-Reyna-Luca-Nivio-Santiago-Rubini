#include "FuncionesPartidos.h"



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

        printf("\n\n");
        printf("GRUPO:%c \n",arreglo[i].letra);
        printf("\n----------------------------");
        printf("\n| POS | EQUIPO | PTS | DIF |\n");
        printf("----------------------------\n");
        MostrarLista2(arreglo[i].equipos);
        i++;
    }
}

void MostrarLista2(nodoGrupoEquipo* lista)
{
    int i=0;
    while(lista!=NULL)
    {
        if(i>4)
        {
            i=0;
        }

        //printf("%s\t",(lista->equipo->nomEquipo));
        printf("  \n  %i ",i+1);
        printf(" \t%s",(lista->equipo->abreviatura));
//        printf("\nPJ:%i",(lista->equipo->mp));
//        printf("\nGAF:%i",(lista->equipo->gf));
//        printf("\nGEN:%i",(lista->equipo->ga));
        printf("  \t %i",(lista->equipo->pts));
//        printf("\nPG:%i",(lista->equipo->win));
//        printf("\nPP:%i",(lista->equipo->loss));
//        printf("\nPE:%i",(lista->equipo->pe));
        printf("\t%d",(lista->equipo->difGol));
        printf("\n----------------------------");
        printf("\n");
        lista=lista->siguiente;
        i++;
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

void JugarPartidos(GrupoPartido arreglo[],int validos,char Seleccionado[],int DecisionJugador)
{
    int i = 0;
    srand (time(NULL));
    for(i=0; i<validos; i++)
    {
        printf("\n---------------------\n");
        printf("Grupo:%c\n",arreglo[i].letra);
        printf("---------------------\n");
        JugarPartidos2(arreglo[i].partidos,Seleccionado,DecisionJugador);
    }
}

void JugarPartidos2(nodoPartido* lista,char seleccionado[],int DecisionJugador)
{
    while(lista!=NULL)
    {
        JugarPartidos3(lista->partido,seleccionado,DecisionJugador);
        lista=lista->siguiente;
    }
}

void JugarPartidos3(Partido partidos,char seleccionado[],int DecisionJugador)
{

    if(strcmpi(partidos.equipo1->nomEquipo,seleccionado)==0)
    {
        int flag=0;
        if(DecisionJugador==1)
        {
            while(flag==0)
            {
                partidos.golesEq1=rand()%(0+5);
                partidos.golesEq2=rand()%(0+5);
                if(partidos.golesEq1>partidos.golesEq2)
                {
                    flag=1;
                }
            }
        }
        else
        {
            while(flag==0)
            {
                partidos.golesEq1=rand()%(0+5);
                partidos.golesEq2=rand()%(0+5);
                if(partidos.golesEq1<partidos.golesEq2)
                {
                    flag=1;
                }
            }
        }
        if(DecisionJugador==1)
        {
            CargarResultadosGanador(partidos.equipo1,partidos.golesEq1,partidos.golesEq2);
            CargarResultadosPerdedor(partidos.equipo2,partidos.golesEq2,partidos.golesEq1);
        }
        else
        {
            CargarResultadosGanador(partidos.equipo2,partidos.golesEq2,partidos.golesEq1);
            CargarResultadosPerdedor(partidos.equipo1,partidos.golesEq1,partidos.golesEq2);
        }
        printf("\n");
        printf("%s [%d] VS [%d] %s\n",(partidos.equipo1->nomEquipo),(partidos.golesEq1),(partidos.golesEq2),(partidos.equipo2->nomEquipo));
        printf("\n");
    }
    else if((strcmpi(partidos.equipo2->nomEquipo,seleccionado)==0))
    {
        int flag=0;
        if(DecisionJugador==1)
        {
            while(flag==0)
            {
                partidos.golesEq1=rand()%(0+5);
                partidos.golesEq2=rand()%(0+5);
                if(partidos.golesEq1<partidos.golesEq2)
                {
                    flag=1;
                }
            }
        }
        else
        {
            while(flag==0)
            {
                partidos.golesEq1=rand()%(0+5);
                partidos.golesEq2=rand()%(0+5);
                if(partidos.golesEq1>partidos.golesEq2)
                {
                    flag=1;
                }
            }
        }
        if(DecisionJugador==1)
        {
            CargarResultadosGanador(partidos.equipo2,partidos.golesEq2,partidos.golesEq1);
            CargarResultadosPerdedor(partidos.equipo1,partidos.golesEq1,partidos.golesEq2);
        }
        else
        {
            CargarResultadosGanador(partidos.equipo1,partidos.golesEq1,partidos.golesEq2);
            CargarResultadosPerdedor(partidos.equipo2,partidos.golesEq2,partidos.golesEq1);
        }
        printf("\n");
        printf("%s [%d] VS [%d] %s\n",(partidos.equipo1->nomEquipo),(partidos.golesEq1),(partidos.golesEq2),(partidos.equipo2->nomEquipo));
        printf("\n");
    }
    else
    {
        partidos.golesEq1=rand()%(0+5);
        partidos.golesEq2=rand()%(0+5);

        if(partidos.golesEq1>partidos.golesEq2)
        {
            CargarResultadosGanador(partidos.equipo1,partidos.golesEq1,partidos.golesEq2);
            CargarResultadosPerdedor(partidos.equipo2,partidos.golesEq2,partidos.golesEq1);
            printf("\n");
            printf("%s [%d] VS [%d] %s\n",(partidos.equipo1->nomEquipo),(partidos.golesEq1),(partidos.golesEq2),(partidos.equipo2->nomEquipo));
            printf("\n");
        }
        else if(partidos.golesEq2>partidos.golesEq1)
        {
            CargarResultadosGanador(partidos.equipo2,partidos.golesEq2,partidos.golesEq1);
            CargarResultadosPerdedor(partidos.equipo1,partidos.golesEq1,partidos.golesEq2);
            printf("\n");
            printf("%s [%d] VS [%d] %s\n",(partidos.equipo1->nomEquipo),(partidos.golesEq1),(partidos.golesEq2),(partidos.equipo2->nomEquipo));
            printf("\n");
        }
        else if(partidos.golesEq1==partidos.golesEq2)
        {
            CargaEmpate(partidos.equipo1,partidos.golesEq1,partidos.golesEq2);
            CargaEmpate(partidos.equipo2,partidos.golesEq2,partidos.golesEq1);
            printf("\n");
            printf("%s [%d] VS [%d] %s\n",(partidos.equipo1->nomEquipo),(partidos.golesEq1),(partidos.golesEq2),(partidos.equipo2->nomEquipo));
            printf("\n");
        }
    }
    CargarDiferenciaGoles(partidos.equipo1,partidos.equipo2);
}

void CargarDiferenciaGoles(Equipo* equipos,Equipo* equipos2)
{
    (equipos->difGol)=((equipos->gf)-(equipos->ga));
    (equipos2->difGol)=((equipos2->gf)-(equipos2->ga));
}

void CargaEmpate(Equipo* equipo,int golesFavor,int GolesContra)
{
    (equipo->mp)=(equipo->mp+1);
    (equipo->gf)=(equipo->gf+golesFavor);
    (equipo->ga)=(equipo->ga+GolesContra);
    (equipo->pts)=(equipo->pts+1);
    (equipo->pe)=(equipo->pe+1);
}

void CargarResultadosGanador(Equipo* equipo,int golesFvor,int golesContra)
{
    (equipo->mp)=(equipo->mp+1);
    (equipo->gf)=(equipo->gf+golesFvor);
    (equipo->ga)=(equipo->ga+golesContra);
    (equipo->win)=(equipo->win+1);
    (equipo->pts)=(equipo->pts+3);
}

void CargarResultadosPerdedor(Equipo* equipo,int golesFvor,int golesContra)
{
    (equipo->mp)=(equipo->mp+1);
    (equipo->gf)=(equipo->gf+golesFvor);
    (equipo->ga)=(equipo->ga+golesContra);
    (equipo->loss)=(equipo->loss+1);
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

int PasarEquiposOrdenados(Grupo arreglo[],nodoEquipo* lista)
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
        OrdenarEquipos(&arreglo[Pos].equipos,nuevo);
        lista=lista->siguiente;
    }
    return validos;
}

void OrdenarEquipos(nodoGrupoEquipo** lista,nodoGrupoEquipo* nuevo)
{
    if((*lista)==NULL)
    {
        (*lista)=nuevo;
    }
    else
    {
        if((*lista)->equipo->pts < nuevo->equipo->pts)
        {
            nuevo->siguiente=(*lista);
            (*lista)=nuevo;
        }

        else if((*lista)->equipo->pts == nuevo->equipo->pts)
        {
            if((*lista)->equipo->difGol <= nuevo->equipo->difGol)
            {
                nuevo->siguiente=(*lista);
                (*lista)=nuevo;
            }
            else
            {
                nodoGrupoEquipo* aux=(*lista)->siguiente;
                (*lista)->siguiente=nuevo;
                nuevo->siguiente=aux;
            }
        }

        else
        {
            nodoGrupoEquipo* ante=(*lista);
            nodoGrupoEquipo* seg=(*lista)->siguiente;

            while(seg!=NULL && (seg->equipo->pts > nuevo->equipo->pts))
            {
                ante=seg;
                seg=seg->siguiente;
            }

            if(seg!=NULL && seg->equipo->pts == nuevo->equipo->pts)
            {
                if(seg->equipo->difGol <= nuevo->equipo->difGol)
                {
                    ante->siguiente=nuevo;
                    nuevo->siguiente=seg;
                }
                else
                {

                    nodoGrupoEquipo* aux=seg->siguiente;
                    seg->siguiente=nuevo;
                    nuevo->siguiente=aux;
                }
            }
            else
            {
                ante->siguiente=nuevo;
                nuevo->siguiente=seg;
            }

        }
    }
}

int verificacionEquipo(Grupo arreglo[],int validos,char nombreEquipo[])
{
    int buscar;
    int flag=0;
    int i=0;
    while(i<validos && flag==0)
    {

        buscar=verificacionEquipoSublista(arreglo[i].equipos,nombreEquipo);
        if(buscar==1)
        {
            flag=1;
        }
        i++;
    }
    return flag;

}

int verificacionEquipoSublista(nodoGrupoEquipo* lista,char nombreEquipo[])
{
    int flag=0;

    while(lista!=NULL && flag==0)
    {
        if(strcmpi(lista->equipo->nomEquipo,nombreEquipo)==0)
        {
            flag=1;
        }
        lista=lista->siguiente;
    }
    return flag;
}

void muestraFechas(Grupo arreglo[],int validos)
{
    int i=0;
    int j=0;
    while(i<3)///3 por las fechas
    {
        printf("\tFecha %i:\n\n",i+1);

        if(i==0) ///Si esta en la primer fecha va entrar aca
        {
            while(j<validos)
            {
                printf("\t\nGrupo: %c",arreglo[j].letra);
                Fecha1(arreglo[j].equipos);
                printf("\n\n");
                j++;
            }
            limpieza();
        }
        else if(i==1)///Fecha 2
        {
            j=0;
            while(j<validos)
            {
                printf("\t\nGrupo: %c",arreglo[j].letra);
                Fecha2(arreglo[j].equipos);
                printf("\n\n");
                j++;
            }
            limpieza();
        }
        if(i==2)///Fecha 3
        {
            j=0;
            while(j<validos)
            {
                printf("\t\nGrupo: %c",arreglo[j].letra);
                Fecha3(arreglo[j].equipos);
                printf("\n\n");
                j++;
            }
            limpieza();
        }
        i++;
    }
    printf("\n");
}
void Fecha1(nodoGrupoEquipo* sublista)
{

    nodoGrupoEquipo* primero=NULL;

    nodoGrupoEquipo* segundo=NULL;  ///nodos auxiliares

    nodoGrupoEquipo* tercero= NULL;

    nodoGrupoEquipo* cuarto=NULL;

    primero=sublista;
    segundo=sublista->siguiente; ///Dos primeros
    printf("\n[%s] VS [%s] ",primero->equipo->nomEquipo,segundo->equipo->nomEquipo);

    ///avanzo la sublista
    while(sublista->siguiente!=NULL)
    {
        tercero=sublista;
        sublista=sublista->siguiente;
    }
    while(sublista!=NULL)
    {
        cuarto=sublista;
        sublista=sublista->siguiente;
    }
    printf("\n[%s] VS [%s]",tercero->equipo->nomEquipo,cuarto->equipo->nomEquipo);

}

void Fecha2(nodoGrupoEquipo* sublista)
{

    nodoGrupoEquipo* primero=NULL;

    nodoGrupoEquipo* segundo=NULL;  ///nodos auxiliares

    nodoGrupoEquipo* tercero= NULL;

    nodoGrupoEquipo* cuarto=NULL;

    primero=sublista;
    segundo=sublista->siguiente; ///Dos primeros


    ///avanzo la sublista
    while(sublista->siguiente!=NULL)
    {
        tercero=sublista;
        sublista=sublista->siguiente;
    }
    while(sublista!=NULL)
    {
        cuarto=sublista;
        sublista=sublista->siguiente;
    }
    printf("\n[%s] VS [%s] ",primero->equipo->nomEquipo,tercero->equipo->nomEquipo);
    printf("\n[%s] VS [%s]",segundo->equipo->nomEquipo,cuarto->equipo->nomEquipo);

}

void Fecha3(nodoGrupoEquipo* sublista)
{

    nodoGrupoEquipo* primero=NULL;

    nodoGrupoEquipo* segundo=NULL;  ///nodos auxiliares

    nodoGrupoEquipo* tercero= NULL;

    nodoGrupoEquipo* cuarto=NULL;

    primero=sublista;
    segundo=sublista->siguiente; ///Dos primeros


    ///avanzo la sublista
    while(sublista->siguiente!=NULL)
    {
        tercero=sublista;
        sublista=sublista->siguiente;
    }
    while(sublista!=NULL)
    {
        cuarto=sublista;
        sublista=sublista->siguiente;
    }
    printf("\n[%s] VS [%s] ",primero->equipo->nomEquipo,cuarto->equipo->nomEquipo);
    printf("\n[%s] VS [%s]",segundo->equipo->nomEquipo,tercero->equipo->nomEquipo);

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





int CargarPartidosOctavos(int validos,Grupo partidosOrdenados[],fase eliminatorias[],int validos2)
{
    int i=0;


    while(i<2)///2 vueltas para cargar los 8 partidos divididos en 4
    {
        /// a b c d e f g h
        /// 0 1 2 3 4 5 6 7
        if(i==0)
        {
            CrearPosicionArregloPartidosFases(eliminatorias,i);
            PartidosDeOctavos(&eliminatorias[0].partidos,partidosOrdenados[0].equipos,partidosOrdenados[1].equipos);
            PartidosDeOctavos(&eliminatorias[0].partidos,partidosOrdenados[2].equipos,partidosOrdenados[3].equipos);
            PartidosDeOctavos(&eliminatorias[0].partidos,partidosOrdenados[4].equipos,partidosOrdenados[5].equipos);
            PartidosDeOctavos(&eliminatorias[0].partidos,partidosOrdenados[6].equipos,partidosOrdenados[7].equipos);

        }
        else if(i==1)
        {
            CrearPosicionArregloPartidosFases(eliminatorias,i);
            PartidosDeOctavos(&eliminatorias[0].partidos,partidosOrdenados[1].equipos,partidosOrdenados[0].equipos);
            PartidosDeOctavos(&eliminatorias[0].partidos,partidosOrdenados[3].equipos,partidosOrdenados[2].equipos);
            PartidosDeOctavos(&eliminatorias[0].partidos,partidosOrdenados[5].equipos,partidosOrdenados[4].equipos);
            PartidosDeOctavos(&eliminatorias[0].partidos,partidosOrdenados[7].equipos,partidosOrdenados[6].equipos);
        }
        i++;
    }
    validos++;
    return validos;
}

void CrearPosicionArregloPartidosFases(fase arreglo[],int validos)
{
    arreglo[validos].partidos=NULL;

}

void PartidosDeOctavos(nodoPartido** partidos,nodoGrupoEquipo* sublista,nodoGrupoEquipo* sublista2)
{
    nodoPartido* nuevo;
    nuevo=crearNodoPartidos2(sublista->equipo,((nodoGrupoEquipo*)sublista2->siguiente)->equipo);
    InsertarAlFinalPartidos(partidos,nuevo);
}

nodoPartido*  crearNodoPartidos2(Equipo* primero, Equipo* segundo)
{

    nodoPartido* nuevo=(nodoPartido*)malloc(sizeof(nodoPartido));
    nuevo->partido.equipo1= primero;
    nuevo->partido.equipo2= segundo;

    nuevo->partido.golesEq1=0;
    nuevo->partido.golesEq2=0;
    nuevo->partido.penales1=0;
    nuevo->partido.penales2=0;
    nuevo->siguiente=NULL;
    return nuevo;
}



int JugarOctavosYDefinirCuartos(int validosFase,fase elimatorias[])
{

    srand (time(NULL));
    validosFase=cargaCuartos(elimatorias[0].partidos,elimatorias,validosFase);
    return validosFase;
}

void mostrarFaseOctavos(fase eliminatorias[],int validos)
{
    Octavos(eliminatorias[validos].partidos);
}
void Octavos(nodoPartido*lista)
{
    int i=3;
    int j=0;
    while(lista!=NULL)
    {
        if(j %2==0)
        {
            i++;
            printf("\n\n\n\n");
        }
        printf("\nFecha: %i/12/2022\n",i);
        printf("\n[%s] VS [%s] \n",lista->partido.equipo1->nomEquipo,lista->partido.equipo2->nomEquipo);
        lista=lista->siguiente;
       j++;
    }
}

int cargaCuartos(nodoPartido* lista,fase eliminatorias[],int validos)
{
    int vueltas=1;
    Equipo* primero;///primer y segundo clasificado
    Equipo* segundo;
    nodoPartido* nuevo=NULL;
    int flag=0;


    while(lista!=NULL)
    {
       flag=0;///Limpio la variable en caso de que hayan penales en un partido anterior
        if(vueltas %2==0)///si da par es porque esta cargando el segundo clasificado
        {
          lista=lista->siguiente;
          if(lista!=NULL)
          {
              lista->partido.golesEq1=rand()%(0+5);
          lista->partido.golesEq2=rand()%(0+5);

            if(lista->partido.golesEq1==lista->partido.golesEq2) ///Si empatan en goles
            {
                while(flag==0)
                {
                    lista->partido.penales1=rand()%(0+5);
                    lista->partido.penales2=rand()%(0+5);
                    if(lista->partido.penales1>lista->partido.penales2)
                    {
                        segundo= (lista->partido.equipo1);
                        flag=1;
                    }
                    else if(lista->partido.penales1<lista->partido.penales2)
                    {
                        segundo=(lista->partido.equipo2);
                        flag=1;
                    }
                }
            }
            else if(lista->partido.golesEq1 > lista->partido.golesEq2)
            {
                segundo = (lista->partido.equipo1);
            }
            else
            {
                segundo= (lista->partido.equipo2);
            }

            nuevo=crearNodoPartidos2(primero,segundo);
            PasaACuartos1(eliminatorias,validos,nuevo);
            lista=lista->siguiente;
          }
        }
        else
        {
             lista->partido.golesEq1=rand()%(0+5);
             lista->partido.golesEq2=rand()%(0+5);
            if(lista->partido.golesEq1==lista->partido.golesEq2) ///Si empatan en goles
            {
                while(flag==0)
                {
                    lista->partido.penales1=rand()%(0+5);
                    lista->partido.penales2=rand()%(0+5);
                    if(lista->partido.penales1>lista->partido.penales2)
                    {
                        primero=(lista->partido.equipo1);
                        flag=1;

                    }
                    else if(lista->partido.penales1<lista->partido.penales2)
                    {
                        primero=(lista->partido.equipo2);
                        flag=1;
                    }
                }
            }
            else if(lista->partido.golesEq1 > lista->partido.golesEq2)
            {
                primero = (lista->partido.equipo1);

            }
            else
            {
                primero= (lista->partido.equipo2);
            }
        }
        vueltas++;

    }
    validos++;
    return validos;
}



void muestraCuartos(fase eliminatorias[])
{
   partidosCuartos(eliminatorias[1].partidos);

}
void partidosCuartos(nodoPartido* lista)
{
   int i=9;
    int j=0;
    while(lista!=NULL)
    {
        if(j %2==0)
        {
            i++;
            printf("\n\n\n");
        }
        printf("\nFecha: %i/12/2022\n",i);
        printf("\n[%s] VS [%s] \n",lista->partido.equipo1->nomEquipo,lista->partido.equipo2->nomEquipo);
        lista=lista->siguiente;
       j++;
    }
}

void MuestraPartidosOctavos(fase eliminatoria[])
{
    ResultadosOctavos(eliminatoria[0].partidos);
}
void ResultadosOctavos (nodoPartido* lista)
{
    int i=3;
    int j=0;
    while(lista!=NULL)
    {
        if(j %2==0)
        {
            i++;
            printf("\n\n\n\n");
        }
        printf("\nFecha: %i/12/2022\n",i);
        printf("\n[%s] %i VS %i [%s]  (%i-%i) \n",lista->partido.equipo1->nomEquipo,lista->partido.golesEq1,lista->partido.golesEq2,lista->partido.equipo2->nomEquipo,lista->partido.penales1,lista->partido.penales2);
        lista=lista->siguiente;
        j++;
    }
}


void PasaACuartos1(fase eliminatorias[],int validos,nodoPartido*nuevo)
{
    InsertarAlFinalPartidos(&eliminatorias[validos].partidos,nuevo);
}

void mostrarResultadosCuartos(fase eliminatorias[])
{
    ResultadosCuartos(eliminatorias[1].partidos);
}
void ResultadosCuartos(nodoPartido* lista)
{
    int i=9;
    int j=0;
    while(lista!=NULL)
    {
        if(j %2==0)
        {
            i++;
            printf("\n\n\n\n");
        }
        printf("\nFecha: %i/12/2022\n",i);
        printf("\n[%s] %i VS %i [%s]  (%i-%i) \n",lista->partido.equipo1->nomEquipo,lista->partido.golesEq1,lista->partido.golesEq2,lista->partido.equipo2->nomEquipo,lista->partido.penales1,lista->partido.penales2);
        lista=lista->siguiente;
        j++;
    }
}

int jugarCuartosYdefinirSemis(fase eliminatorias[],int validos)
{
    ///los cuartos estan en la fase [1]
    CrearPosicionArregloPartidosFases(eliminatorias,validos);
    srand (time(NULL));
    validos=definirSemiFinalistas(eliminatorias[1].partidos,eliminatorias,validos);
    return validos;
}

int definirSemiFinalistas(nodoPartido* lista,fase eliminatorias[],int validos)
{

    int vueltas=1;
    Equipo* primero;///primer y segundo clasificado
    Equipo* segundo;
    nodoPartido* nuevo=NULL;
    int flag=0;


    while(lista!=NULL)
    {
       flag=0;///Limpio la variable en caso de que hayan penales en un partido anterior
        if(vueltas %2==0)///si da par es porque esta cargando el segundo clasificado
        {
          lista=lista->siguiente;
          if(lista!=NULL)
          {
              lista->partido.golesEq1=rand()%(0+5);
              lista->partido.golesEq2=rand()%(0+5);

            if(lista->partido.golesEq1==lista->partido.golesEq2) ///Si empatan en goles
            {
                while(flag==0)
                {
                    lista->partido.penales1=rand()%(0+5);
                    lista->partido.penales2=rand()%(0+5);
                    if(lista->partido.penales1>lista->partido.penales2)
                    {
                        segundo= (lista->partido.equipo1);
                        flag=1;
                    }
                    else if(lista->partido.penales1<lista->partido.penales2)
                    {
                        segundo=(lista->partido.equipo2);
                        flag=1;
                    }
                }
            }
            else if(lista->partido.golesEq1 > lista->partido.golesEq2)
            {
                segundo = (lista->partido.equipo1);
            }
            else
            {
                segundo= (lista->partido.equipo2);
            }

            nuevo= crearNodoPartidos2(primero,segundo);

            pasaASemis(eliminatorias,nuevo,validos);
            lista=lista->siguiente;
          }
       }
        else
        {
             lista->partido.golesEq1=rand()%(0+5);
             lista->partido.golesEq2=rand()%(0+5);

            if(lista->partido.golesEq1==lista->partido.golesEq2) ///Si empatan en goles
            {
                while(flag==0)
                {
                    lista->partido.penales1=rand()%(0+5);
                    lista->partido.penales2=rand()%(0+5);
                    if(lista->partido.penales1>lista->partido.penales2)
                    {
                        primero=(lista->partido.equipo1);
                        flag=1;

                    }
                    else if(lista->partido.penales1<lista->partido.penales2)
                    {
                        primero=(lista->partido.equipo2);
                        flag=1;
                    }
                }
            }
            else if(lista->partido.golesEq1 > lista->partido.golesEq2)
            {
                primero = (lista->partido.equipo1);

            }
            else
            {
                primero= (lista->partido.equipo2);
            }
        }
        vueltas++;
    }
    validos++;
    return validos;
}

void pasaASemis(fase eliminatorias[],nodoPartido* nuevo,int validos)
{
   InsertarAlFinalPartidos(&eliminatorias[validos].partidos,nuevo);
}

void semiFinales(fase eliminatorias[])
{
  semiFinales2(eliminatorias[2].partidos);
}

void semiFinales2(nodoPartido* lista)
{
    int i=13;
    while(lista!=NULL)
    {

        printf("\nFecha: %i/12/2022\n",i);
        printf("\n[%s] VS [%s] \n\n",lista->partido.equipo1->nomEquipo,lista->partido.equipo2->nomEquipo);
        lista=lista->siguiente;
       i++;
    }
}


int Finales(int validos,fase eliminatorias[])
{
    CrearPosicionArregloPartidosFases(eliminatorias,validos);
    CrearPosicionArregloPartidosFases(eliminatorias,validos+1);
    validos=GanadoresDeSemifinales(eliminatorias[2].partidos,eliminatorias,validos);
    return validos;
}

void terceryCuartoMuestra(fase eliminatorias[])
{
    partidosTercero(eliminatorias[3].partidos);
}
void partidosTercero(nodoPartido*lista)
{
    while(lista!=NULL)
    {
        printf("\nFecha: 17/12/2022\n");
        printf("\n[%s] VS [%s] \n",lista->partido.equipo1->nomEquipo,lista->partido.equipo2->nomEquipo);
        lista=lista->siguiente;
    }

}

void finalcita(fase eliminatorias[])
{
 final2(eliminatorias[4].partidos);
}
void final2(nodoPartido* lista)
{
    while(lista!=NULL)
    {
        printf("\nFecha: 18/12/2022\n");
        printf("\n[%s] VS [%s] \n",lista->partido.equipo1->nomEquipo,lista->partido.equipo2->nomEquipo);
        lista=lista->siguiente;
    }
}


void resultadosSemis(fase arreglo[])
{
    semis(arreglo[2].partidos);///Los semifinalistas
}
void semis(nodoPartido* lista)
{
    int i=13;
    while(lista!=NULL)
    {
        if(i!=13)
        {
            printf("\n\n");
        }
        printf("\nFecha: %i/12/2022\n",i);
        printf("\n[%s] %i VS %i [%s]  (%i-%i) \n",lista->partido.equipo1->nomEquipo,lista->partido.golesEq1,lista->partido.golesEq2,lista->partido.equipo2->nomEquipo,lista->partido.penales1,lista->partido.penales2);
        lista=lista->siguiente;
        i++;
    }
}

int GanadoresDeSemifinales(nodoPartido* lista,fase eliminatorias[],int validos)
{
    int vueltas=1;
    Equipo* primeroGanador;///primer y segundo clasificado
    Equipo* segundoGanador;
    Equipo* primeroPerdedor;
    Equipo* segundoPerdedor;
    nodoPartido* nuevo=NULL;
    nodoPartido* nuevo2=NULL;
    int flag=0;


    while(lista!=NULL)
    {
       flag=0;///Limpio la variable en caso de que hayan penales en un partido anterior
        if(vueltas %2==0)///si da par es porque esta cargando el segundo clasificado
        {
          lista=lista->siguiente;
          if(lista!=NULL)
          {
              lista->partido.golesEq1=rand()%(0+5);
              lista->partido.golesEq2=rand()%(0+5);

            if(lista->partido.golesEq1==lista->partido.golesEq2) ///Si empatan en goles
            {
                while(flag==0)
                {
                    lista->partido.penales1=rand()%(0+5);
                    lista->partido.penales2=rand()%(0+5);
                    if(lista->partido.penales1>lista->partido.penales2)
                    {
                        segundoGanador= (lista->partido.equipo1);
                        segundoPerdedor= (lista->partido.equipo2);
                        flag=1;
                    }
                    else if(lista->partido.penales1<lista->partido.penales2)
                    {
                        segundoGanador=(lista->partido.equipo2);
                        segundoPerdedor=(lista->partido.equipo1);
                        flag=1;
                    }
                }
            }
            else if(lista->partido.golesEq1 > lista->partido.golesEq2)
            {
                segundoGanador = (lista->partido.equipo1);
                segundoPerdedor= (lista->partido.equipo2);
            }
            else
            {
                segundoGanador= (lista->partido.equipo2);
                segundoPerdedor=(lista->partido.equipo1);
            }

            nuevo= crearNodoPartidos2(primeroGanador,segundoGanador); ///FINALISTAS
            nuevo2=crearNodoPartidos2(primeroPerdedor,segundoPerdedor);

            tercerYCuartoPuesto(eliminatorias,nuevo2,validos);
            Finalistas(eliminatorias,nuevo,validos+1);

            lista=lista->siguiente;
          }
       }
        else
        {
             lista->partido.golesEq1=rand()%(0+5);
             lista->partido.golesEq2=rand()%(0+5);

            if(lista->partido.golesEq1==lista->partido.golesEq2) ///Si empatan en goles
            {
                while(flag==0)
                {
                    lista->partido.penales1=rand()%(0+5);
                    lista->partido.penales2=rand()%(0+5);
                    if(lista->partido.penales1>lista->partido.penales2)
                    {
                        primeroGanador=(lista->partido.equipo1);
                        primeroPerdedor=(lista->partido.equipo2);
                        flag=1;

                    }
                    else if(lista->partido.penales1<lista->partido.penales2)
                    {
                        primeroGanador=(lista->partido.equipo2);
                        primeroPerdedor=(lista->partido.equipo1);
                        flag=1;
                    }
                }
            }
            else if(lista->partido.golesEq1 > lista->partido.golesEq2)
            {
                primeroGanador = (lista->partido.equipo1);
                primeroPerdedor=(lista->partido.equipo2);

            }
            else
            {
                primeroGanador= (lista->partido.equipo2);
                primeroPerdedor=(lista->partido.equipo1);
            }
        }
        vueltas++;
    }
    validos++;
    validos++;
    return validos;

}


void tercerYCuartoPuesto(fase eliminatorias[],nodoPartido* nuevo,int validos)
{
    InsertarAlFinalPartidos(&eliminatorias[validos].partidos,nuevo);
}
void Finalistas(fase eliminatorias[],nodoPartido* nuevo,int validos)
{
    InsertarAlFinalPartidos(&eliminatorias[validos].partidos,nuevo);
}

void Campeon(nodoPartido** lista)
{
    int flag=0;
    if((*lista) != NULL)
    {
             (*lista)->partido.golesEq1=rand()%(0+5);
             (*lista)->partido.golesEq2=rand()%(0+5);

            if((*lista)->partido.golesEq1==(*lista)->partido.golesEq2) ///Si empatan en goles
            {
                while(flag==0)
                {
                    (*lista)->partido.penales1=rand()%(0+5);
                    (*lista)->partido.penales2=rand()%(0+5);
                    if((*lista)->partido.penales1>(*lista)->partido.penales2)
                    {
                        flag=1;
                    }
                    else if((*lista)->partido.penales1<(*lista)->partido.penales2)
                    {
                        flag=1;
                    }
                }
            }

    }
}

void jugarTercerPuesto(nodoPartido** lista)
{
    int flag=0;
    if(*lista != NULL)
    {
             (*lista)->partido.golesEq1=rand()%(0+5);
             (*lista)->partido.golesEq2=rand()%(0+5);

            if((*lista)->partido.golesEq1==(*lista)->partido.golesEq2) ///Si empatan en goles
            {
                while(flag==0)
                {
                    (*lista)->partido.penales1=rand()%(0+5);
                    (*lista)->partido.penales2=rand()%(0+5);
                    if((*lista)->partido.penales1>(*lista)->partido.penales2)
                    {
                        flag=1;
                    }
                    else if((*lista)->partido.penales1<(*lista)->partido.penales2)
                    {
                        flag=1;
                    }
                }
            }

    }
}

///ESTA FUNCION INVOCA A LAS DOS DE ARRIBA CARGANDOLE LOS RESULTADOS DE LOS PARTIDOS

void jugarUltimosPartidos(fase eliminatorias[])
{
    ///DIRECTAMENTE USAMOS EL INDICE DEL ARREGLO PORQUE EN UN INDICE EN ESPECIFICO VAN CIERTOS PARTIDOS
    jugarTercerPuesto(&eliminatorias[3].partidos);
    Campeon(&eliminatorias[4].partidos);
}







/************************PASAJE A ARREGLOS AUXILIARES********************************/

void arregloOctavosF(fase eliminatorias[],Partido arreglo[])
{
  arregloOctavos2(eliminatorias[0].partidos,arreglo);
}
void arregloOctavos2(nodoPartido* lista,Partido arreglo[])
{
  Partido auxiliar;
  int i=0;
  while(lista!=NULL)
  {
      auxiliar=lista->partido;
      arreglo[i]=auxiliar;
      i++;
      lista=lista->siguiente;
  }
}


void arregloCuartosF(fase eliminatorias[],Partido arreglo[])
{
 arregloCuartos2(eliminatorias[1].partidos,arreglo);
}
void arregloCuartos2(nodoPartido* lista,Partido arreglo[])
{
  Partido auxiliar;
  int i=0;
  while(lista!=NULL)
  {
      auxiliar=lista->partido;
      arreglo[i]=auxiliar;
      i++;
      lista=lista->siguiente;
  }
}


void arregloSemisF(fase eliminatorias[],Partido arreglo[])
{
 arregloSemis2(eliminatorias[2].partidos,arreglo);
}
void arregloSemis2(nodoPartido* lista,Partido arreglo[])
{
Partido auxiliar;
  int i=0;
  while(lista!=NULL)
  {
      auxiliar=lista->partido;
      arreglo[i]=auxiliar;
      i++;
      lista=lista->siguiente;
  }
}
void arregloTerceroF(fase eliminatorias[],Partido arreglo[])
{
 arregloTercero2(eliminatorias[3].partidos,arreglo);
}
void arregloTercero2(nodoPartido* lista,Partido arreglo[])
{
  Partido auxiliar;
  int i=0;
  while(lista!=NULL)
  {
      auxiliar=lista->partido;
      arreglo[i]=auxiliar;
      i++;
      lista=lista->siguiente;
  }
}

void arregloCampeonF(fase eliminatorias[],Partido arreglo[])
{
    arregloCampeon2(eliminatorias[4].partidos,arreglo);

}

void arregloCampeon2(nodoPartido* lista,Partido arreglo[])
{
  Partido auxiliar;
  int i=0;
  while(lista!=NULL)
  {
      auxiliar=lista->partido;
      arreglo[i]=auxiliar;
      i++;
      lista=lista->siguiente;
  }
}


/**********************MUESTREOS************************/

void Gotoxy(int x,int y)
{
    COORD coordenadas;
    HANDLE manipulador=GetStdHandle(STD_OUTPUT_HANDLE);
    coordenadas.X=x;
    coordenadas.Y=y;
    SetConsoleCursorPosition(manipulador,coordenadas);
}

void Muestra()
{
   int i=0;

    ///GRUPO A
    for(i=3;i<15;i++)
    {
        Gotoxy(5,i);
        printf("|");
    }

     for(i=3;i<15;i++)
    {
        Gotoxy(26,i);
        printf("|");
    }

     for(i=6;i<26;i++)
    {
        Gotoxy(i,2);
        printf("-");
    }

    for(i=6;i<26;i++)
    {
        Gotoxy(i,5);
        printf("-");
    }

    for(i=6;i<26;i++)
    {
        Gotoxy(i,15);
        printf("-");
    }

    Gotoxy(12,4);

    printf("GRUPO A");

    Gotoxy(13, 7);

    printf("QATAR");

    Gotoxy(12, 9);

    printf("ECUADOR");

    Gotoxy(12, 11);

    printf("SENEGAL");

    Gotoxy(10, 13);

    printf("PAISES BAJOS");

    ///GRUPO B

    for(i=3;i<15;i++)
    {
        Gotoxy(29,i);
        printf("|");
    }

     for(i=3;i<15;i++)
    {
        Gotoxy(50,i);
        printf("|");
    }

     for(i=30;i<50;i++)
    {
        Gotoxy(i,2);
        printf("-");
    }

    for(i=30;i<50;i++)
    {
        Gotoxy(i,5);
        printf("-");
    }

    for(i=30;i<50;i++)
    {
        Gotoxy(i,15);
        printf("-");
    }

    Gotoxy(37,4);

    printf("GRUPO B");

    Gotoxy(35, 7);

    printf("INGLATERRA");

    Gotoxy(38, 9);

    printf("IRAN");

    Gotoxy(33, 11);

    printf("ESTADOS UNIDOS");

    Gotoxy(38, 13);

    printf("GALES");

    ///GRUPO C

      for(i=3;i<15;i++)
    {
        Gotoxy(52,i);
        printf("|");
    }

     for(i=3;i<15;i++)
    {
        Gotoxy(73,i);
        printf("|");
    }

     for(i=53;i<73;i++)
    {
        Gotoxy(i,2);
        printf("-");
    }

    for(i=53;i<73;i++)
    {
        Gotoxy(i,5);
        printf("-");
    }

    for(i=53;i<73;i++)
    {
        Gotoxy(i,15);
        printf("-");
    }

    Gotoxy(60,4);

    printf("GRUPO C");

    Gotoxy(59, 7);

    printf("ARGENTINA");

    Gotoxy(56, 9);

    printf("ARABIA SAUDITA");

    Gotoxy(60, 11);

    printf("MEXICO");

    Gotoxy(60, 13);

    printf("POLONIA");

    ///GRUPO D

      for(i=3;i<15;i++)
    {
        Gotoxy(75,i);
        printf("|");
    }

     for(i=3;i<15;i++)
    {
        Gotoxy(96,i);
        printf("|");
    }

     for(i=76;i<96;i++)
    {
        Gotoxy(i,2);
        printf("-");
    }

    for(i=76;i<96;i++)
    {
        Gotoxy(i,5);
        printf("-");
    }

    for(i=76;i<96;i++)
    {
        Gotoxy(i,15);
        printf("-");
    }

    Gotoxy(82,4);

    printf("GRUPO D");

    Gotoxy(82, 7);

    printf("FRANCIA");

    Gotoxy(81, 9);

    printf("AUSTRALIA");

    Gotoxy(81, 11);

    printf("DINAMARCA");

    Gotoxy(83, 13);

    printf("TUNEZ");

    ///GRUPO e
    for(i=20;i<32;i++)
    {
        Gotoxy(5,i);
        printf("|");
    }

     for(i=20;i<32;i++)
    {
        Gotoxy(26,i);
        printf("|");
    }

     for(i=6;i<26;i++)
    {
        Gotoxy(i,19);
        printf("-");
    }

    for(i=6;i<26;i++)
    {
        Gotoxy(i,22);
        printf("-");
    }

    for(i=6;i<26;i++)
    {
        Gotoxy(i,32);
        printf("-");
    }

    Gotoxy(12,21);

    printf("GRUPO E");

    Gotoxy(13, 24);

    printf("ESPANA");

    Gotoxy(11, 26);

    printf("COSTA RICA");

    Gotoxy(12, 28);

    printf("ALEMANIA");

    Gotoxy(13, 30);

    printf("JAPON");

    ///GRUPO F
    for(i=20;i<32;i++)
    {
        Gotoxy(29,i);
        printf("|");
    }

     for(i=20;i<32;i++)
    {
        Gotoxy(50,i);
        printf("|");
    }

     for(i=30;i<50;i++)
    {
        Gotoxy(i,19);
        printf("-");
    }

    for(i=30;i<50;i++)
    {
        Gotoxy(i,22);
        printf("-");
    }

    for(i=30;i<50;i++)
    {
        Gotoxy(i,32);
        printf("-");
    }

    Gotoxy(36,21);

    printf("GRUPO F");

    Gotoxy(36, 24);

    printf("BELGICA");

    Gotoxy(36, 26);

    printf("CANADA");

    Gotoxy(35, 28);

    printf("MARRUECOS");

    Gotoxy(36, 30);

    printf("CROACIA");

     ///GRUPO G
    for(i=20;i<32;i++)
    {
        Gotoxy(52,i);
        printf("|");
    }

     for(i=20;i<32;i++)
    {
        Gotoxy(73,i);
        printf("|");
    }

     for(i=53;i<73;i++)
    {
        Gotoxy(i,19);
        printf("-");
    }

    for(i=53;i<73;i++)
    {
        Gotoxy(i,22);
        printf("-");
    }

    for(i=53;i<73;i++)
    {
        Gotoxy(i,32);
        printf("-");
    }

    Gotoxy(59,21);

    printf("GRUPO G");

    Gotoxy(59, 24);

    printf("BRASIL");

    Gotoxy(59, 26);

    printf("SERBIA");

    Gotoxy(59, 28);

    printf("SUIZA");

    Gotoxy(59, 30);

    printf("CAMERUN");

     ///GRUPO H
    for(i=20;i<32;i++)
    {
        Gotoxy(75,i);
        printf("|");
    }

     for(i=20;i<32;i++)
    {
        Gotoxy(96,i);
        printf("|");
    }

     for(i=76;i<96;i++)
    {
        Gotoxy(i,19);
        printf("-");
    }

    for(i=76;i<96;i++)
    {
        Gotoxy(i,22);
        printf("-");
    }

    for(i=76;i<96;i++)
    {
        Gotoxy(i,32);
        printf("-");
    }

    Gotoxy(82,21);

    printf("GRUPO H");

    Gotoxy(82, 24);

    printf("PORTUGAL");

    Gotoxy(83, 26);

    printf("GHANA");

    Gotoxy(82, 28);

    printf("URUGUAY");

    Gotoxy(80, 30);

    printf("REP. DE KOREA");


               Gotoxy(102,10);
               printf("     ..''','.");
               Gotoxy(102,11);
               printf("   .lOKOdlll;;:.");
               Gotoxy(102,12);
               printf("  ,x0Kk;......oo.");
               Gotoxy(102,13);
               printf(" .odol.   .'. .d;");
               Gotoxy(102,14);
               printf(" .kNXd.    .. .d:");
               Gotoxy(102,15);
               printf("  lNMK;   .'. ,o'");
               Gotoxy(102,16);
               printf("  .dNW0,  '. .c,");
               Gotoxy(102,17);
               printf("   .dNWKoc, .:'");
               Gotoxy(102,18);
               printf("    .oNMX0l,:'");
               Gotoxy(102,19);
               printf("     .dNX0ko'");
               Gotoxy(102,20);
               printf("     .,l0Kkl,");
               Gotoxy(102,21);
               printf("    .,..o0kxo,");
               Gotoxy(102,22);
               printf("    ''  lXXX0x,");
               Gotoxy(102,23);
               printf("    ,;..oK0OKNc");
               Gotoxy(102,24);
               printf("    .;loolccdo.");
               Gotoxy(102,25);
               printf("       ...    ");




    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
      printf("\n");
    printf("\n");
      printf("\n");
    printf("\n");


}

void muestraELIMINATORIAS(Partido arregloOctavos[],Partido arregloCuartos[],Partido arregloSemis[],Partido arregloTer[],Partido arregloCampeon[])
{
    int flag = 0;

    while (flag == 0)
    {
        int i = 0;

        Gotoxy(0,1);

        printf("OCTAVOS");



        ///PARTIDO 1 OCTAVOS
        Gotoxy(0,3);
        printf(" -----------");
        Gotoxy(0,4);
        printf("|%s %i-%i %s|",arregloOctavos[0].equipo1->abreviatura,arregloOctavos[0].golesEq1,arregloOctavos[0].golesEq2,arregloOctavos[0].equipo2->abreviatura);
        Gotoxy(0,5);
        printf(" ----------- ");
        Gotoxy(4,6);
        printf("(%i-%i)",arregloOctavos[0].penales1,arregloOctavos[0].penales2);

        for(i=13; i<18;i++)
        {
            Sleep(100);
            Gotoxy(i,4); printf("-");
        }
        for(i=5; i<8;i++)
        {
            Sleep(100);
            Gotoxy(18,i); printf("|");
        }
        for(i=18; i<23;i++)
        {
            Sleep(100);
            Gotoxy(i,8); printf("-");
        }



        ///PARTIDO 2 OCTAVOS
        Gotoxy(0,11);
        printf(" -----------");
        Gotoxy(0,12);
        printf("|%s %i-%i %s|",arregloOctavos[1].equipo1->abreviatura,arregloOctavos[1].golesEq1,arregloOctavos[1].golesEq2,arregloOctavos[1].equipo2->abreviatura);
        Gotoxy(0,13);
        printf(" ----------- ");
        Gotoxy(4,14);
        printf("(%i-%i)",arregloOctavos[1].penales1,arregloOctavos[1].penales2);

        for(i=13; i<18;i++)
        {
            Sleep(100);
            Gotoxy(i,12); printf("-");
        }
        for(i=11; i>8;i--)
        {
            Sleep(100);
            Gotoxy(18,i); printf("|");
        }


        ///PARTIDO 3 OCTAVOS
        Gotoxy(0,16);
        printf(" -----------");
        Gotoxy(0,17);
        printf("|%s %i-%i %s|",arregloOctavos[2].equipo1->abreviatura,arregloOctavos[2].golesEq1,arregloOctavos[2].golesEq2,arregloOctavos[2].equipo2->abreviatura);
        Gotoxy(0,18);
        printf(" ----------- ");
        Gotoxy(4,19);
        printf("(%i-%i)",arregloOctavos[2].penales1,arregloOctavos[2].penales2);

        for(i=13; i<18;i++)
        {
            Sleep(100);
            Gotoxy(i,17); printf("-");
        }
        for(i=18; i<21;i++)
        {
            Sleep(100);
            Gotoxy(18,i); printf("|");
        }
        for(i=18; i<23;i++)
        {
            Sleep(100);
            Gotoxy(i,21); printf("-");
        }


        ///PARTIDO 4 OCTAVOS
        Gotoxy(0,24);
        printf(" -----------");
        Gotoxy(0,25);
        printf("|%s %i-%i %s|",arregloOctavos[3].equipo1->abreviatura,arregloOctavos[3].golesEq1,arregloOctavos[3].golesEq2,arregloOctavos[3].equipo2->abreviatura);
        Gotoxy(0,26);
        printf(" ----------- ");
        Gotoxy(4,27);
        printf("(%i-%i)",arregloOctavos[3].penales1,arregloOctavos[3].penales2);

        for(i=13; i<18;i++)
        {
            Sleep(100);
            Gotoxy(i,25); printf("-");
        }
        for(i=24; i>21;i--)
        {
            Sleep(100);
            Gotoxy(18,i); printf("|");
        }



        ///PARTIDO 5 OCTAVOS
        Gotoxy(0,29);
        printf(" -----------");
        Gotoxy(0,30);
        printf("|%s %i-%i %s|",arregloOctavos[4].equipo1->abreviatura,arregloOctavos[4].golesEq1,arregloOctavos[4].golesEq2,arregloOctavos[4].equipo2->abreviatura);
        Gotoxy(0,31);
        printf(" ----------- ");
        Gotoxy(4,32);
        printf("(%i-%i)",arregloOctavos[4].penales1,arregloOctavos[4].penales2);

        for(i=13; i<18;i++)
        {
            Sleep(100);
            Gotoxy(i,30); printf("-");
        }
        for(i=31; i<34;i++)
        {
            Sleep(100);
            Gotoxy(18,i); printf("|");
        }
        for(i=18; i<23;i++)
        {
            Sleep(100);
            Gotoxy(i,34); printf("-");
        }



        ///PARTIDO 6 OCTAVOS
        Gotoxy(0,37);
        printf(" -----------");
        Gotoxy(0,38);
        printf("|%s %i-%i %s|",arregloOctavos[5].equipo1->abreviatura,arregloOctavos[5].golesEq1,arregloOctavos[5].golesEq2,arregloOctavos[5].equipo2->abreviatura);
        Gotoxy(0,39);
        printf(" ----------- ");
        Gotoxy(4,40);
        printf("(%i-%i)",arregloOctavos[5].penales1,arregloOctavos[5].penales2);




        for(i=13; i<18;i++)
        {
            Sleep(100);
            Gotoxy(i,38); printf("-");
        }
        for(i=37; i>34;i--)
        {
            Sleep(100);
            Gotoxy(18,i); printf("|");
        }



        ///PARTIDO 7 OCTAVOS
        Gotoxy(0,42);
        printf(" -----------");
        Gotoxy(0,43);
        printf("|%s %i-%i %s|",arregloOctavos[6].equipo1->abreviatura,arregloOctavos[6].golesEq1,arregloOctavos[6].golesEq2,arregloOctavos[6].equipo2->abreviatura);
        Gotoxy(0,44);
        printf(" ----------- ");
        Gotoxy(4,45);
        printf("(%i-%i)",arregloOctavos[6].penales1,arregloOctavos[6].penales2);

        for(i=13; i<18;i++)
        {
            Sleep(100);
            Gotoxy(i,43); printf("-");
        }
        for(i=44; i<47;i++)
        {
            Sleep(100);
            Gotoxy(18,i); printf("|");
        }
        for(i=18; i<23;i++)
        {
            Sleep(100);
            Gotoxy(i,47); printf("-");
        }
        ///PARTIDO 8 OCTAVOS
        Gotoxy(0,50);
        printf(" -----------");
        Gotoxy(0,51);
        printf("|%s %i-%i %s|",arregloOctavos[7].equipo1->abreviatura,arregloOctavos[7].golesEq1,arregloOctavos[7].golesEq2,arregloOctavos[7].equipo2->abreviatura);
        Gotoxy(0,52);
        printf(" ----------- ");
        Gotoxy(4,53);
        printf("(%i-%i)",arregloOctavos[7].penales1,arregloOctavos[7].penales2);

        for(i=13; i<18;i++)
        {
            Sleep(100);
            Gotoxy(i,51); printf("-");
        }
        for(i=50; i>47;i--)
        {
            Sleep(100);
            Gotoxy(18,i); printf("|");
        }

        Gotoxy(0,55); printf("FIN DE OCTAVOS!");

        ///CUARTOS

        Gotoxy(23,1);
        printf("Cuartos");

        ///PARTIDO 1 CUARTOS

        Gotoxy(23,7);
        printf(" -----------");
        Gotoxy(23,8);
        printf("|%s %i-%i %s|",arregloCuartos[0].equipo1->abreviatura,arregloCuartos[0].golesEq1,arregloCuartos[0].golesEq2,arregloCuartos[0].equipo2->abreviatura);
        Gotoxy(23,9);
        printf(" ----------- ");
        Gotoxy(27,10);
        printf("(%i-%i)",arregloCuartos[0].penales1,arregloCuartos[0].penales2);

        for(i=36; i<41;i++)
        {
            Sleep(100);
            Gotoxy(i,8); printf("-");
        }
        for(i=9; i<15;i++)
        {
            Sleep(100);
            Gotoxy(41,i); printf("|");
        }
        for(i=41; i<46;i++)
        {
            Sleep(100);
            Gotoxy(i,15); printf("-");
        }

        ///PARTIDO 2 CUARTOS

        Gotoxy(23,20);
        printf(" -----------");
        Gotoxy(23,21);
        printf("|%s %i-%i %s|",arregloCuartos[1].equipo1->abreviatura,arregloCuartos[1].golesEq1,arregloCuartos[1].golesEq2,arregloCuartos[1].equipo2->abreviatura);
        Gotoxy(23,22);
        printf(" ----------- ");
        Gotoxy(27,23);
        printf("(%i-%i)",arregloCuartos[1].penales1,arregloCuartos[1].penales2);

        for(i=36; i<41;i++)
        {
            Sleep(100);
            Gotoxy(i,21); printf("-");
        }
        for(i=20; i>15;i--)
        {
            Sleep(100);
            Gotoxy(41,i); printf("|");
        }

        ///PARTIDO 3 CUARTOS
        Gotoxy(23,33);
        printf(" -----------");
        Gotoxy(23,34);
        printf("|%s %i-%i %s|",arregloCuartos[2].equipo1->abreviatura,arregloCuartos[2].golesEq1,arregloCuartos[2].golesEq2,arregloCuartos[2].equipo2->abreviatura);
        Gotoxy(23,35);
        printf(" ----------- ");
        Gotoxy(27,36);
        printf("(%i-%i)",arregloCuartos[2].penales1,arregloCuartos[2].penales2);

        for(i=36; i<41;i++)
        {
            Sleep(100);
            Gotoxy(i,34); printf("-");
        }
        for(i=35; i<41;i++)
        {
            Sleep(100);
            Gotoxy(41,i); printf("|");
        }
        for(i=41; i<46;i++)
        {
            Sleep(100);
            Gotoxy(i,41); printf("-");
        }

        ///PARTIDO 4 CUARTOS

        Gotoxy(23,46);
        printf(" -----------");
        Gotoxy(23,47);
        printf("|%s %i-%i %s|",arregloCuartos[3].equipo1->abreviatura,arregloCuartos[3].golesEq1,arregloCuartos[3].golesEq2,arregloCuartos[3].equipo2->abreviatura);
        Gotoxy(23,48);
        printf(" ----------- ");
        Gotoxy(27,49);
        printf("(%i-%i)",arregloCuartos[3].penales1,arregloCuartos[3].penales2);

        for(i=36; i<41;i++)
        {
            Sleep(100);
            Gotoxy(i,47); printf("-");
        }
        for(i=46; i>41;i--)
        {
            Sleep(100);
            Gotoxy(41,i); printf("|");
        }

        Gotoxy(23,55);
        printf("FIN DE CUARTOS!");

        ///SEMIS
        ///PARTIDO 1 SEMIS

        Gotoxy(46,1);
        printf("Semis");

        Gotoxy(46,14);
        printf(" -----------");
        Gotoxy(46,15);
        printf("|%s %i-%i %s|" ,arregloSemis[0].equipo1->abreviatura,arregloSemis[0].golesEq1,arregloSemis[0].golesEq2,arregloSemis[0].equipo2->abreviatura);
        Gotoxy(46,16);
        printf(" ----------- ");
        Gotoxy(50,17);
        printf("(%i-%i)" ,arregloSemis[0].penales1,arregloSemis[0].penales2);

        for(i=59; i<64;i++)
        {
            Sleep(100);
            Gotoxy(i,15); printf("-");
        }
        for(i=16; i<28;i++)
        {
            Sleep(100);
            Gotoxy(64,i); printf("|");
        }
        for(i=64; i<69;i++)
        {
            Sleep(100);
            Gotoxy(i,28); printf("-");
        }

        ///PARTIDO 2 SEMIS

        Gotoxy(46,40);
        printf(" -----------");
        Gotoxy(46,41);
        printf("|%s %i-%i %s|",arregloSemis[1].equipo1->abreviatura,arregloSemis[1].golesEq1,arregloSemis[1].golesEq2,arregloSemis[1].equipo2->abreviatura);
        Gotoxy(46,42);
        printf(" ----------- ");
        Gotoxy(50,43);
        printf("(%i-%i)",arregloSemis[1].penales1,arregloSemis[1].penales2);

        for(i=59; i<64;i++)
        {
            Sleep(100);
            Gotoxy(i,41); printf("-");
        }
        for(i=40; i>28;i--)
        {
            Sleep(100);
            Gotoxy(64,i); printf("|");
        }

        Gotoxy(46,55);
        printf("FIN DE SEMIS!");

        ///TERCER PUESTO

        Gotoxy(69,1);
        printf("3ER Y 4TO ");

        Gotoxy(69,27);
        printf(" -----------");
        Gotoxy(69,28);
        printf("|%s %i-%i %s|",arregloTer[0].equipo1->abreviatura,arregloTer[0].golesEq1,arregloTer[0].golesEq2,arregloTer[0].equipo2->abreviatura);
        Gotoxy(69,29);
        printf(" ----------- ");
        Gotoxy(73,30);
        printf("(%i-%i)",arregloTer[0].penales1,arregloTer[0].penales2);



        for(i=31; i<36;i++)
        {
            Sleep(100);
            Gotoxy(75,i); printf("|");
        }

        Gotoxy(68,37);
        if(arregloTer[0].golesEq1>arregloTer[0].golesEq2)
        {
            printf("3ERO: %s!",arregloTer[0].equipo1->nomEquipo);
        }
        else if(arregloTer[0].golesEq1<arregloTer[0].golesEq2)
        {
            printf("3ERO: %s!",arregloTer[0].equipo2->nomEquipo);
        }
        if(arregloTer[0].golesEq1==arregloTer[0].golesEq2)
        {
            if(arregloTer[0].penales1>arregloTer[0].penales2)
            {
                printf("3ERO: %s!",arregloTer[0].equipo1->nomEquipo);
            }
            else
            {
                printf("3ERO: %s!",arregloTer[0].equipo2->nomEquipo);
            }

        }


        Gotoxy(69,55);
        printf("3ER Y 4TO");

        ///FINAL

        for(i=82; i<87;i++)
        {
            Sleep(100);
            Gotoxy(i,28); printf("-");
        }

        Gotoxy(87,1);
        printf("Final");

        Gotoxy(87,27);
        printf(" -----------");
        Gotoxy(87,28);
        printf("|%s %i-%i %s|",arregloCampeon[0].equipo1->abreviatura,arregloCampeon[0].golesEq1,arregloCampeon[0].golesEq2,arregloCampeon[0].equipo2->abreviatura);
        Gotoxy(87,29);
        printf(" ----------- ");
        Gotoxy(91,30);
        printf("(%i-%i)",arregloCampeon[0].penales1,arregloCampeon[0].penales2);


        Gotoxy(87,55);
        printf("FINAL DEL MUNDIAL");

        for(i=101; i<105;i++)
        {
            Sleep(100);
            Gotoxy(i,28); printf("-");
        }

        Gotoxy(105,28);
        printf(">");


        Gotoxy(107,28);

        if(arregloCampeon[0].golesEq1>arregloCampeon[0].golesEq2)
        {
            printf("%s CAMPEON DEL MUNDIAL!!!",arregloCampeon[0].equipo1->nomEquipo);
        }
        else if(arregloCampeon[0].golesEq1<arregloCampeon[0].golesEq2)
        {
            printf("%s CAMPEON DEL MUNDIAL!!!",arregloCampeon[0].equipo2->nomEquipo);
        }
        if(arregloCampeon[0].golesEq1==arregloCampeon[0].golesEq2)
        {
            if(arregloCampeon[0].penales1>arregloCampeon[0].penales2)
            {
                printf("%s CAMPEON DEL MUNDIAL!!!",arregloCampeon[0].equipo1->nomEquipo);
            }
            else
            {
                printf("%s CAMPEON DEL MUNDIAL!!!",arregloCampeon[0].equipo2->nomEquipo);
            }

        }

        flag = 1;


    }


    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");

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

void LogoMundial()
{


    printf("            @@@@@@@@@,    ,/*,,. @@@@@@@@@@@   \n");
    printf("            @@@@@@   .**/////*.    ..,,@@@@@    \n");
    printf("            @@@....,****,.&&&#(*,#(((/., @@@    \n");
    printf("            @ ...#,,*,.#((/////*((((((((..@@    \n");
    printf("             .,#(*#,, @@@@@@@@,(**(((((//..@    \n");
    printf("             .#.###, @@@@@@@@@@@*////((//*.#    \n");
    printf("             ... ... @@@@@@@@@@@./**/(((//.      \n");
    printf("             ..   .. @@@@@@@@@@@./*//((((*.#     \n");
    printf("              .    ..@@@@@@@@@@@.////(((( .@     \n");
    printf("            @  .    ..@@@@@@@@@.*///(((/,.@@     \n");
    printf("            @@        .@@@@@@@ *////((/,.@@@     \n");
    printf("            @@@ .       @@@@@ ,////((/. @@@@     \n");
    printf("            @@@@(.        @@ *///((//  @@@@@     \n");
    printf("            @@@@@@.      .. *(//((/* @@@@@@@     \n");
    printf("            @@@@@@@ .     ...////*, @@@@@@@@      \n");
    printf("            @@@@@@@@@. .   ..,**,. @@@@@@@@@       \n");
    printf("           @@@@@@@@@@..    .... @@@@@@@@@@@      \n");
    printf("           @@@@@@@@@@  . . ./ .(@@@@@@@@@@@       \n");
    printf("            @@@@@@@@@.(#,.. #.,# %*@@@@@@@@@      \n");
    printf("           @@@@@@@@ (//**..   ###.(@@@@@@@@      \n");
    printf("          @@@@@@@.****((..# #. (. %@@@@@@@      \n");
    printf("           @@@@@@ ,*,**//(.. ###( (, @@@@@@      \n");
    printf("           @@@@@@.,,,,****...   # #*.%@@@@@      \n");
    printf("           @@@@@/.,,.,,,,,............@@@@@     \n");
    printf("           @@@@@@..... ......(.#......@@@@@      \n");
    printf("           @@@@@@*.   . ..#/,#...,,,.@@@@@@      \n");
    printf("           @@@@@@@@@     /(/&#.,##*&@@@@@@@    \n");
}
