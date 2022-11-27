#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "FuncionesPartidos.h"

/**
ESTRUCTURA DEL USUARIO
**/
typedef struct
{
    char empresa[20];
    char numeroTarjeta[16];
    int anioVencimiento;
    char codigoAtras[3];
} tarjeta;

typedef struct
{
    ///va tener un equipo que es al que va apostar
    char nombreYape[50];
    int edad;
    char dni[20];
    char direccion[100];
    char pais[10];
    tarjeta dato;
    char correo[50];
    char password[20];
    float montoAcumulado;
    float apuesta;
    char nombreEquipo[30];
    int seleccion;///1,clasifica 2 no clasifica
} usuario;

void muestraMiPerfil(usuario cargado);
tarjeta nueva();
usuario carga();
void menu();
void BasesYcondiciones();
void CasaApuesta();
usuario registrarse();
void FuncionamientoAPP();
void limpieza();



int main()
{
    ///PASAJE DE DATOS
    GrupoPartido partidos[100];
    Grupo EquiposOrdenados[100];
    nodoEquipo* lista=NULL;
    Grupo arreglo[100];
    int validos=0;
    int validos2=0;
    PasarDatosArchivoALista(&lista,"equipazos.bin");
    validos=PasarEquiposAGrupos(lista,arreglo);
    ///PASAJE DE DATOS



    /**VARIABLES AUXILIARES PARA EL MUESTREO FINAL**/
    Partido arregloOctavos[10];
    Partido arregloCuartos[5];
    Partido arregloSemis[3];
    Partido arregloTercero[2];
    Partido arregloCampeon[1];
    /**VARIABLES AUXILIARES PARA EL MUESTREO FINAL**/


    ///
    fase EliminatoriaEquipos[5];
    int validos3=0;
    ///

    /**DECLARACION DE VARIABLES**/
    int flag=0;
    int equipoExistente;
    char nombreEquipo[25];
    float apuesta;
    int clasifica;
    int option;
    usuario nuevoUusario;
    /**DECLARACION DE VARIABLES**/


    CasaApuestas();

    ///EMPIEZA EL PROYECTO///

    limpieza();
    system("color f");

    do
    {

        ///MENU PRINCIPAL///
        printf("\n\t\t\tApuestas La Mano de Dios");
        menu();
        scanf("%i",&option);

        switch(option)
        {

        case 1:
            ///PROYECTO
            printf("\n\tGracias por elegirnos :) \n");
            limpieza();

            nuevoUusario=carga();
            printf("\n");
            limpieza();

            while(flag==0)
            {

                Muestra();
                printf("Seleccione el equipo al cual le va apostar \n");
                fflush(stdin);
                gets(nombreEquipo);
                equipoExistente=verificacionEquipo(arreglo,validos,nombreEquipo);
                if(equipoExistente==1)
                {
                    strcpy(nuevoUusario.nombreEquipo,nombreEquipo);
                    flag=1;
                    limpieza();

                }
                else
                {
                    printf("\nPor favor ingrese un equipo existente\n");
                    limpieza();
                }
            }
            ///El usuario ingresa si clasifica o no clasifica una vez que ya eligio su equipo

            flag=0;

            while(flag==0)
            {
                printf("\n1-Su equipo clasifica de fase de grupos");
                printf("\n2-Su equipo no clasifica \n");
                scanf("%i",&clasifica);
                if(clasifica==1 || clasifica==2)
                {
                    nuevoUusario.seleccion=clasifica;
                    flag=1;
                    limpieza();
                }
                else
                {
                    printf("\nIngrese un numero Valido\n");
                    limpieza();
                }
            }


            /// El usuario ingresa la apuesta
            flag=0;

            while(flag==0)
            {
                printf("\nIngrese el monto que desea apostar por su equipo: ");
                scanf("%f",&apuesta);
                if(apuesta>=500)
                {
                    nuevoUusario.apuesta=apuesta;
                    flag=1;
                    limpieza();
                }
                else
                {

                    printf("\nEl valor minimo de apuesta es de $500\n");
                    limpieza();
                }

            }

            ///CREAR LOS PARTIDOS Y PASARLOS AL ARREGLO
            CrearPartidos(arreglo,validos,partidos);

            ///MOSTRAR PARTIDOS POR FECHAS
            muestraFechas(arreglo,validos);

            printf("\n");


            ///JUGAR LOS PARTIDOS
            printf("\n\t\tA continuacion se mostraran los resultados\n");
            printf("\t\tLos mismos se encuentran divididos por grupos\n\n");

            ///SE CARGAN Y SE MUESTRAN LOS RESULTADOS
            JugarPartidos(partidos,validos,nuevoUusario.nombreEquipo,nuevoUusario.seleccion);
            limpieza();

            ///ARREGLO AUX DONDE SE PASAN LOS EQUIPOS ORDENANDOLOS POR PUNTOS, SINO POR DIF DE GOL
            validos2=PasarEquiposOrdenados(EquiposOrdenados,lista);

            ///MOSTRAR TABLA ORDENADA
            MostrarLista(EquiposOrdenados,validos2);

            limpieza();
            nuevoUusario.montoAcumulado=nuevoUusario.apuesta*(float)2;
            if(nuevoUusario.seleccion==1)
            {
                printf("\t\nFelicitaciones su equipo avanzo a octavos");

                printf("\t\nMonto acumulado: $%.2f por acertar su apuesta\n",nuevoUusario.montoAcumulado);

            }
            else if(nuevoUusario.seleccion==2)
            {
                printf("\t\nLamentamos que su equipo no haya clasificado pero lo invitamos a ver el resto del mundial con nosotros");
                printf("\t\nMonto acumulado: $%.2f por acertar su apuesta",nuevoUusario.montoAcumulado);
            }

            limpieza();


            printf("\t\tCruces De Octavos");
            ///AL TENER LA TABLA ORDENADA ES UNICAMENTE QUITAR LOS 2 PRIMEROS DE CADA GRUPO Y PASARLOS A OCTAVOS

            validos3=CargarPartidosOctavos(validos3,EquiposOrdenados,EliminatoriaEquipos,validos2);

            ///MUESTRA DE LOS CRUCES
            mostrarFaseOctavos(EliminatoriaEquipos,validos3-1);
            limpieza();

            ///JUGAR OCTAVOS YA DEFINE LOS CUARTOS Y MUESTRA LOS RESULTADOS DE OCTAVOS
            validos3=JugarOctavosYDefinirCuartos(validos3,EliminatoriaEquipos);

            printf("\t\t\nResultados De Octavos\n");
            MuestraPartidosOctavos(EliminatoriaEquipos);

            printf("\n");
            limpieza();

            printf("\t\tCruces De Cuartos");
            muestraCuartos(EliminatoriaEquipos);
            printf("\n\n");

            ///JUGAR CUARTOS YA DEFINE LOS CRUCES DE SEMIS
            validos3=jugarCuartosYdefinirSemis(EliminatoriaEquipos,validos3);
            printf("\n");
            limpieza();
            printf("\t\t\nResultados De Cuartos\n");

            ///MUESTRA RESULTADOS CUARTOS
            mostrarResultadosCuartos(EliminatoriaEquipos);
            printf("\n");
            limpieza();

            ///CRUCES DE SEMIFINALES
            printf("\t\tCruces de Semi-Finales \n");

            ///FUNCION QUE DEFINE 2 FINALISTAS, O 3ER Y 4TO PUESTO
            validos3=Finales(validos3,EliminatoriaEquipos);
            semiFinales(EliminatoriaEquipos);
            printf("\n");
            limpieza();


            printf("\t\t\nResultados De Semi-Finales\n");
            resultadosSemis(EliminatoriaEquipos);
            printf("\n");
            limpieza();

            ///UNICAMENTE SE VA MOSTRAR LOS CRUCES DE LA FINAL Y QUIENES DISPUTAN 3ER Y CUARTO PUESTO
            printf("\t\t3er y 4to Puesto \n");
            terceryCuartoMuestra(EliminatoriaEquipos);
            printf("\n");
            limpieza();
            printf("\t\tFinalistas\n");
            finalcita(EliminatoriaEquipos);
            printf("\n");
            limpieza();

            printf("\nAntes de mostrar el campeon haremos un recorrido de las eliminatorias\n");

            ///DEFINE EL CAMPEON, SUBCAMPEON Y 3ER PUESTO
            jugarUltimosPartidos(EliminatoriaEquipos);
            printf("\n");
            limpieza();


            /**TRASPASO A ARREGLOS AUXILIAR PARA FACILITAR LA MUESTRA FINAL**/
            arregloOctavosF(EliminatoriaEquipos,arregloOctavos);
            arregloCuartosF(EliminatoriaEquipos,arregloCuartos);
            arregloSemisF(EliminatoriaEquipos,arregloSemis);
            arregloTerceroF(EliminatoriaEquipos,arregloTercero);
            arregloCampeonF(EliminatoriaEquipos,arregloCampeon);
            /**DATOS COPIADOS**/


            ///MUESTRA NUEVAMENTE DE TODAS LAS ELIMINATORIAS PERO ESTA VEZ CON EL RESULTADO DEL FINALISTA
            muestraELIMINATORIAS(arregloOctavos,arregloCuartos,arregloSemis,arregloTercero,arregloCampeon);
            limpieza();
            printf("\nEsperemos que haya disfrutado del evento, lo esperamos cuando lo desee\n");
            limpieza();

            break;
        case 2: ///MANUAL PARA EL USUARIO
            FuncionamientoAPP();
            limpieza();
            break;
        case 3: ///TERMINOS Y CONDICIONES
            BasesYcondiciones();
            limpieza();
            break;
        }
    }
    while(option!=0);
    return 0;
}




/*********************************FUNCIONES PARA EL USUARIO Y EL MENU*********************************************/
void muestraMiPerfil(usuario cargado)
{
    printf("\nNombre: %s",cargado.nombreYape);
    printf("\nEdad %i",cargado.edad);
    printf("\nDni %s",cargado.dni);
    printf("\nDireccion %s",cargado.direccion);
    printf("\nPais %s",cargado.pais);
    printf("\nCorreo %s",cargado.correo);
    printf("\nContrasena %s",cargado.password);
    printf("\nTarjeta empresa %s",cargado.dato.empresa);
    printf("\nVencimiento empresa %i",cargado.dato.anioVencimiento);
    printf("\nReves tarjeta %s",cargado.dato.codigoAtras);
    printf("\nNum tarjeta %s",cargado.dato.numeroTarjeta);

}

tarjeta nueva()
{
    tarjeta tarjetita;
    int flag=0;
    int anio;
    printf("\nVISA/MASTERCARD\n");
    printf("\nEmpresa: ");
    fflush(stdin);
    gets(tarjetita.empresa);
    printf("\nNumero de tarjeta: ");
    fflush(stdin);
    gets(tarjetita.numeroTarjeta);
    while(flag==0)
    {
        printf("\nAnio de vencimiento: ");
        scanf("%i",&anio);
        if(anio>=2022)
        {
            tarjetita.anioVencimiento=anio;
            flag=1;
        }
        else
        {
            printf("\nTarjeta vencida, ingrese un anio valido\n");
        }
    }
    printf("\nCodigo(reves de la tarjeta): ");
    scanf("%s",&tarjetita.codigoAtras);

    return tarjetita;

}

usuario carga()
{
    int edad,flag=0;
    usuario aux;
    usuario contra;
    printf("\nNombre y Apellido: ");
    fflush(stdin);
    gets(aux.nombreYape);
    while(flag==0)
    {
        printf("\nEdad: ");
        scanf("%i",&edad);
        if(edad>=18)
        {
            aux.edad=edad;
            flag=1;
        }
        else
        {
            printf("\nUsted debe ser mayor de edad para apostar\n");
        }
    }
    printf("\nDNI: ");
    fflush(stdin);
    gets(aux.dni);
    printf("\nPais: ");
    fflush(stdin);
    gets(aux.pais);
    printf("\nDireccion: ");
    fflush(stdin);
    gets(aux.direccion);
    system("pause");
    system("cls");
    printf("\nCorreo electronico:\t");
    fflush(stdin);
    gets(aux.correo);
    contra=registrarse();
    strcpy(aux.password,contra.password);
    printf("\n");
    limpieza();
    printf("\nYa casi terminamos, agregue su metodo de pago\n");
    aux.dato=nueva();

    return aux;
}

void limpieza()
{
    system("pause");
    system("cls");
}
void menu()
{
    printf("\n\n1-[Registrarse]\n");
    printf("\n\n2-[Funcionamiento de nuestra plataforma]\n");
    printf("\n\n3-[Bases y condiciones]\t\n ");
    printf("\n\n0-[Salir]\n");
}


void BasesYcondiciones()
{
    printf("\nAl utilizar, visitar y/o acceder a cualquier parte (incluidas ");
    printf("\n, pero no limitadas a, subdominios, codigo fuente y/o API de la pagina");
    printf("\n, visible o no) del sitio Web o aplicacion movil de Apuestas ");
    printf("\nLa Mano de Dios (el sitio Web),, y/o al registrarse en el sitio Web  o");
    printf("\naplicaciones de nuestra propiedad o bajo nuestra operacion, se ");
    printf("\nconsidera que el cliente esta obligado a cumplir: (i) Estos Terminos");
    printf("\ny Condiciones, (ii) nuestra Politica de Privacidad; (iii) Politica ");
    printf("\napuestas y otros productos de Juego, tal y como se explica ");
    printf("\nmas adelante en el parrafo 2 (en su conjunto, los Terminos), por lo tanto,");
    printf("\nha comprendido y aceptado estos Terminos y Condiciones. La ");
    printf("\nconformidad con los Terminos no implica que estemos obligados a aceptar");
    printf("\ncualquier apuesta realizada por un jugador. Los participantes ");
    printf("\npueden realizar apuestas en los mercados/productos disponibles en el sitio");
    printf("\nWeb. Sin embargo, solo se consideraran validas y completadas ");
    printf("\ntales apuestas y, por lo tanto, aprobadas por Apuestas La Mano de Dios cuando");
    printf("\nel cliente reciba la confirmacion de Apuestas La Mano de Dios de aceptacion de su apuesta.");
    printf("\nPor favor, lea atentamente los Terminos y Condiciones y si ");
    printf("\nno se encuentra de acuerdo, no utilice, visite o acceda a ninguna parte");
    printf("\ndel sitio Web (incluidas, pero no limitadas a subdominios, codigo ");
    printf("\nfuente y/o API de la pagina,sea visible o no). Estos Términos y Condiciones");
    printf("\nse aplicaran igualmente a todas las apuestas realizadas a traves");
    printf("\n de dispositivos moviles, incluidas las aplicaciones descargables para dispositivos");
    printf("\nmoviles (entendiendo que las referencias al uso del sitio Web lo son tambien al uso de aplicaciones de apuesta en dispositivos moviles).");

}

void FuncionamientoAPP()
{
    printf("\n\tApuestas La Mano de Dios es una casa de apuestas deportivas Online activa en el mercado hace mas de una decada,");
    printf("\nfundadad por Rubini Santiago,Reyna Ignacio y Nivio Luca.");
    printf("\nApuestas La Mano de Dios  Es una de las mas elegidas por los grandes inversores ya que, contamos");
    printf("\ncon varios deportes y competiciones de renombre, de las cuales poseemos los derechos para que todas las apuestas sean");
    printf("\nrealizadas dentro del marco de la ley y asi poder brindarle la mayor seguridad posible.");
    printf("\n\tDebido al gran evento que nos acontece dentro de unos meses, para ser mas precisos, 20/11/2022 en Qatar, por el momento");
    printf("\nunicamente nos encontramos ofreciendo cuentas TEMPORALES(no poseen costo de mantenimiento),");
    printf("\nni tampoco poseen un costo de apertura. El unico monto que se le pedira es el que debera efectuar como metodo de apuesta");
    printf("\n\ni-APUESTA MINIMA $500");
    printf("\nii-LA APUESTA DEBE SER POR EL EQUIPO QUE USTED ELIJA, ANTES QUE EL MUNDIAL INICIE, Y EN LA FASE DE GRUPOS ");
    printf("\niii-UNA VEZ QUE EL MUNDIAL INICIE, USTED NO PODRA CAMBIAR EL EQUIPO POR EL QUE QUIERE APOSTAR O CAMBIAR SU APUESTA");
    printf("\niv-USTED APOSTARA A UN EQUIPO SI CLASIFICA O NO DE FASE DE GRUPOS");
    printf("\niv-a)Si su equipo cumple con lo que usted aposto,su apuesta se multiplicara por 2");
    printf("\niv-b)En caso de no acertar, perdera su apuesta");

}
usuario registrarse()
{
    usuario aux;
    int j=0;
    char clave[30];
    char verificacion[30];
    int v=0;
    int letra=0;
    int flag=0;
    printf("\nIngrese su nueva contrasena:  ");
    for (int i=0; i<30; i++)
    {
        v=getch();
        if((v>='a')&&(v<='z')||(v>='A')&&(v<='Z')&&(v<=9))
        {
            clave[i]=v;
            printf("*");
        }
        if(v=='\r')
        {
            clave[i]='\0';
            break;
        }
    }
    strcpy(aux.password,clave);
    return aux;
}
