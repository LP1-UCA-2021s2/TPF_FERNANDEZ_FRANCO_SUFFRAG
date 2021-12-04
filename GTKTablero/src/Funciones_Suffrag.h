/*Declaracion de Funciones utiles para el proyecto */

#ifndef FUNCIONES_SUFFRAG_H_
#define FUNCIONES_SUFFRAG_H_






int Tablero[17][17];


char *imagenes[5];


/*Variable para guardar la modalidad del Juego.
 * modo = 1 ==> Usuario vs Usuario
 * modo = 2 ==> Usuario vs Computadora
 * modo = 3 ==> Computadora vs Computadora */
int modo;


/*Variable para diferenciar entre la entrada del primer click y el segundo
 * bandera = 0 ==> primer click
 * bandera = 1 ==> segundo click */
int bandera;



const gchar *nombre1;
const gchar *nombre2;


GtkWidget *tablero;
GtkWidget *label_estado;
GtkWidget *label_turno;
GtkWidget *click_uno;
GtkWidget *click_dos;
GtkWidget *vtn_fin_juego;
GtkWidget *fin_juego_label1;
GtkWidget *fin_juego_label2;


/*Variable para determinar el turno.
 * turno = 1 le pertenece a la computadora siempre(no significa que la computadora sea la primera a jugar).
 * turno = 2 le pertenece al usuario(el 2 no quiere decir que el usuario no empiece, dependera de la funcion seleccionar_jugador1). */
int turno;


/*Array que contiene los identificadores del equipo al que el jugador pertenece
 * Este array puuuede contener solo uno de dos numero posibles: 1 ó 3.
 * 1 representa a los policias y 3 a las suffragettes.
 * bandos[0] pertenece a la computadora
 * bandos[1] pertenece al usuario
 * La variable turno se utiliza como subindice del array bandos en la forma bandos[turno-1].
 * Por ejemplo:
 * si turno = 1 ==> bandos[1-1] = bandos[0]. Luego; juega la computadora... */
int bandos[2];


/*Variable utilizada como bandera/contador para averiguar si existe alguna otra ficha alrededor
 * de una ficha que ha realizado un salto. Esto, junto con la variable cont se usa para determinar
 * si es posible ejecutar un segundo o tercer salto*/
int B;


/*Contador/bandera, utilizado junto con la variable B para determinar si una ficha que realizo un
 * salto puede volver a saltar.
 * Se permiten hasta tres salto, por lo tanto, cont comienza de cero cuando se realiza una jugada
 * y se incrementa si existe la posibilidad de volver a salta. Esta se incrementa hasta tres.*/
int cont;


/*Array auxiliar creado para guardar las coordenadas finales de una ficha que acaba de realizar
 * un salto. Esto es para, en el caso de que se pueda volver a realizar un salto, utilizar dichas
 * coordenadas como las coordenadas iniciales x,y utilizadas en la funcion Coordenadas_destino*/
int coor[2];


int coords_PC[2];






char *ordenar(char *v);

void Estadisticas(int ganador);



/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~INTELIGENCIA ARTIFICIAL~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int mas_cercano(int x, int y, int *filas, int *columnas);

int mov_intel(int x, int y);

void jugada_comp(int x, int y, int target);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


void ventana_fin_del_juego();

void Juega_Computadora();

void rev_carcel_hosp(int *num3, int *num4);

int Limitacion_Bases(int x, int y, int pieza);

int limitacion_Suffrag(int x, int y);

int limitacion_Polic(int x, int y);

int limite_movimiento(int x, int y);

int verificar_adyacente(int x, int y, int x2, int y2);

void rotar_jugador();

void mostrar_turno();

void fin_del_juego(int num1, int num2, int num3, int num4);

int limite_tablero(int x, int y);

void verificar_conquista(int *num1, int *num2);

int verificar_vacia(int x, int y);

int revisar_vecinos(int x, int y);

int verificar_bando(int x, int y, int bando);

int verificar_arena(int x, int y);

void Pieza_Derrotada(int derrotado);

int aux_salto(int x, int y, int x2, int y2);

int Mov_Salto(int x, int y, int x2, int y2, int pieza);

int Movimiento(int x, int y, int x2, int y2, int pieza);

void Click_Dos(int pieza, int x, int y, int x2, int y2);

int Primer_Click(int bando, int x, int y);

void Click_saltos(int pieza, int x, int y, int x2, int y2);







#endif
