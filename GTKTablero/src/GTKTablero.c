/*
 ============================================================================
 Name        : GTKTablero.c
 Author      : Fernandez Julio, Franco Matias
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in GTK+
 ============================================================================
 */

#include <gtk/gtk.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "Funciones_Suffrag.h"


#define MAX_FILA (17)
#define MAX_COLUMNA (17)


int modo = 0;
int turno = 0;
int bandos[2] = {0,0};
int bandera = 0;
int coor[2] = {0,0};
int coords_PC[2] = {0,0};
int B = 0;
int cont = 0;
int num1=0, num2=0, num3=0, num4=0;



int Tablero[17][17] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,4,6,6,6,4,0,0,0,0,0,0},
	{0,0,0,0,3,4,4,6,6,6,4,4,3,0,0,0,0},
	{0,0,3,4,4,4,4,4,3,4,4,4,4,4,3,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,2,2,2,2,2,1,2,2,2,2,2,1,0,0},
	{0,0,0,0,1,2,2,5,5,5,2,2,1,0,0,0,0},
	{0,0,0,0,0,0,2,5,5,5,2,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};







GtkWidget *principal;
GtkWidget *jugar_btn;
GtkWidget *reglas_btn1;
GtkWidget *estat_btn1;
GtkWidget *btn_atras_estadists;
GtkWidget *creditos_btn1;
GtkWidget *salir_btn;
GtkWidget *window;
GtkWidget *box_tablero;
GtkWidget *box_estadisticas;
GtkWidget *grilla_estadisticas;


GtkDialog *v_jugar;
GtkDialog *v_reglas;
GtkDialog *v_creditos;
GtkDialog *v_acerca_de;
GtkWidget *v_estadisticas;
GtkDialog *v_nombres;
GtkWidget *atras_btn;
GtkWidget *nuevo_juego;
GtkWidget *nombre_1;
GtkWidget *nombre_2;
GtkWidget *sgtn_B;
GtkWidget *cerrar_reglas;
GtkWidget *cerrar_credits;

GtkWidget *vtn_modo_juego;
GtkWidget *btn_a1;
GtkWidget *btn_a2;
GtkWidget *btn_a3;
GtkWidget *btn_next1;
GtkWidget *vtn_bando;
GtkWidget *btn_b1;
GtkWidget *btn_b2;
GtkWidget *btn_b3;
GtkWidget *btn_next2;
GtkWidget *vtn_turno;
GtkWidget *btn_c1;
GtkWidget *btn_c2;
GtkWidget *btn_c3;
GtkWidget *btn_next3;
GtkWidget *vtn_fin_juego;
GtkWidget *btn_Finalizar;



GtkWidget *label_jug1;
GtkWidget *nom_jug_y;
GtkWidget *nom_jug_x;
GtkWidget *mensaje_modo_select;
GtkWidget *mensaje_bando_select;
GtkWidget *mensaje_turno_select;
GtkWidget *label_jug2;
GtkWidget *mensaje_v_bandos;
GtkWidget *fin_juego_label1;
GtkWidget *fin_juego_label2;


GtkBuilder *builder;




/*Funcion del boton "Jugar" en la ventana "Menu Principal".
 * Muestra la ventana pop-up "Jugar" */
void ventana_jugar(GtkWidget *widget, gpointer data){
	gtk_dialog_run(v_jugar);
}




/*Funcion del Boton "Juego Nuevo" en la ventana "Jugar".
 * Oculta la ventana pop-up "Jugar" y la ventana "Menu Principal"
 * Muestra la ventana "Modo de Juego" */
void Juego_Nuevo(GtkWidget *widget, gpointer data){
	gtk_widget_hide(principal);
	gtk_widget_hide(v_jugar);
	gtk_widget_show_all(vtn_modo_juego);
}


/*Funcion del boton de modalidad Usuario vs Usuario. Al darle click, modo = 1 */
void modo_uno(GtkWidget *widget, gpointer data){
	modo = 1;
	g_print("\n modo = %d \n",modo);
	g_print("\n La modalidad de juego elegida es: Usuario vs. Usuario. \n");
	const gchar *text = g_strdup_printf("La modalidad de juego elegida es:  Usuario vs. Usuario.");

	gtk_label_set_text(GTK_LABEL(mensaje_modo_select), text);	//Mensaje en ventana modo de juego
}

/*Funcion del boton de modalidad Usuario vs Computadora. Al darle click, modo = 2 */
void modo_dos(GtkWidget *widget, gpointer data){
	modo = 2;
	g_print("\n modo = %d \n",modo);
	g_print("\n La modalidad de juego elegida es: Usuario vs. Computadora. \n");
	const gchar *text = g_strdup_printf("La modalidad de juego elegida es:  Usuario vs. Computadora.");

	gtk_label_set_text(GTK_LABEL(mensaje_modo_select), text);	//Mensaje en ventana modo de juego
}

/*Funcion del boton de modalidad Computadora vs Computadora. Al darle click, modo = 3 */
void modo_tres(GtkWidget *widget, gpointer data){
	modo = 3;
	g_print("\n modo = %d \n",modo);
	g_print("\n La modalidad de juego elegida es: Computadora vs. Computadora. \n");
	const gchar *text = g_strdup_printf("La modalidad de juego elegida es:  Computadora vs. Computadora.");

	gtk_label_set_text(GTK_LABEL(mensaje_modo_select), text);	//Mensaje en ventana modo de juego

}


/*Boton atras en la ventana pop-up "Jugar". Oculta el pop-up*/
void btn_atras_en_jugar(GtkWidget *widget, gpointer data){
	gtk_widget_hide(v_jugar);
}


/*Funcion que muestra las reglas del Juego.
 * Se usa en dos lugares:
 * El boton "Reglas del Juego" en el Menu Principal,
 * y el boton "Ayuda" en la barra de menu una vez iniciado el juego.*/
void mostrar_reglas(GtkWidget *widget, gpointer data){
	gtk_dialog_run(v_reglas);
}

/* Funcion que muestra el ranking de aquellos que han jugado el Juego */
void mostrar_estadisticas(GtkWidget *widget, gpointer data){
	cargar_ranking();

	gtk_widget_show_all(v_estadisticas);
}


/* Funcion del boton 'Atras' en la ventana 'Estadisticas' */
void boton_atras_estadisticas(GtkWidget *widget, gpointer data){
	gtk_widget_hide(v_estadisticas);
}


/*Funcion que muestra los Creditos del Juego.
 * Se usa en dos lugares:
 * El boton "Creditos" en el Menu Principal,
 * y el boton "Acerca de" en la barra de menu una vez iniciado el juego. */
void mostrar_creditos(GtkWidget *widget, gpointer data){
	gtk_dialog_run(v_acerca_de);
	gtk_widget_hide(GTK_WIDGET(v_acerca_de));
}


/*Funcion del boton "Cerrar" en la ventana de las Reglas del Juego.
 * Oculta la ventana. */
void ocultar_reglas(GtkWidget *widget, gpointer data){
	/*En el caso de que quien empieza sea la Computadora, en los modos: PC vs Usuario o PC vs PC*/
	if((modo==2 && turno==1) || (modo==3 && turno==1) || (modo==3 && turno==2)){		//Juega COMPUTADORA/S
		Juega_Computadora();
		rotar_jugador();
	}
	gtk_widget_hide(v_reglas);
}


/*Funcion que carga Nombres predeterminados en la ventana "Nombres".
 * Estos pueden o no ser utilizados. El Usuario puede cambiarlos si asi lo desee. */
void set_nombres(){
	if(modo==1){	//Nombres predeterminados para el modo Usuario vs Usuario
		gtk_entry_set_text( GTK_ENTRY ( nombre_1 ), "Usuario_1");
		gtk_entry_set_text( GTK_ENTRY ( nombre_2 ), "Usuario_2");
	}
	if(modo==2){	//Nombres predeterminados para el modo Usuario vs Computadora
		gtk_entry_set_text( GTK_ENTRY ( nombre_1 ), "Computadora");
		gtk_entry_set_text( GTK_ENTRY ( nombre_2 ), "Usuario");
	}
	if(modo==3){	//Nombres predeterminados para el modo Computadora vs Computadora
		gtk_entry_set_text( GTK_ENTRY ( nombre_1 ), "Computadora_1");
		gtk_entry_set_text( GTK_ENTRY ( nombre_2 ), "Computadora_2");
	}

}

/*Funcion del boton "Siguiente" en la ventana "Nombres".
 * Al darle click, guarda los dos nombres(predeterminados o ingresados) en las variables globales: nombre1 y nombre2
 * Luego, oculta la ventana y muestra la ventana "Bandos"
 * Caso de modo 1 o modo 2:
 * Modifica el label en la ventana "Bandos" acorde al nombre2 */
void siguiente_en_v_nombres(GtkWidget *widget, gpointer data){
	nombre1 = gtk_entry_get_text( GTK_ENTRY ( nombre_1 ) );
	gtk_label_set_text(GTK_LABEL(label_jug1), nombre1);

	g_print("\n text1 = %s\n",nombre1);

	nombre2 = gtk_entry_get_text( GTK_ENTRY ( nombre_2 ) );
	gtk_label_set_text(GTK_LABEL(label_jug2), nombre2);

	g_print("\n text2 = %s\n",nombre2);

	const gchar *temp;
	if(modo==1){
		temp = g_strdup_printf("Elija el bando de %s ",nombre2);
		gtk_label_set_text(GTK_LABEL(mensaje_v_bandos), temp);
	}
	if(modo==3){
		temp = g_strdup_printf("Elija el bando de %s ",nombre2);
		gtk_label_set_text(GTK_LABEL(mensaje_v_bandos), temp);
	}

	gtk_widget_hide(v_nombres);
	gtk_widget_show_all(vtn_bando);

}



/*Asigna al Jugador 2 con el equipo Suffragetto y al Jugador 1 con el equipo Policias */
void clicked_bando_suffragetto(GtkWidget *widget, gpointer data){
	bandos[1] = 3;
	bandos[0] = 1;
	g_print("\nEl Jugador 2 es equipo Suffragettes. El Jugador 1 es equipo Policias.\n");
	g_print("bandos[0] = %d \nbandos[1] = %d",bandos[0],bandos[1]);
	const gchar *text = g_strdup_printf(" %s es equipo Suffragettes.  %s es equipo Policias.",nombre2,nombre1);

	gtk_label_set_text(GTK_LABEL(mensaje_bando_select), text);	//Mensaje en la ventana "Bandos", utiliza nombre1 y nombre2 de la ventana "Nombres"

}

/*Asigna al Jugador 2 con el equipo Policias y al Jugador 1 con el equipo Suffragetto */
void clicked_bando_policia(GtkWidget *widget, gpointer data){
	bandos[1] = 1;
	bandos[0] = 3;
	g_print("\nEl Jugador 2 es equipo Policias. El Jugador 1 es equipo Suffragettes.\n");
	g_print("bandos[0] = %d \nbandos[1] = %d",bandos[0],bandos[1]);
	const gchar *text = g_strdup_printf(" %s es equipo Policias.  %s es equipo Suffragettes.",nombre2,nombre1);
	gtk_label_set_text(GTK_LABEL(mensaje_bando_select), text);	//Mensaje en la ventana "Bandos", utiliza nombre1 y nombre2 de la ventana "Nombres"

}

/*Asigna al Jugador 1 y al Jugador 2 alguno de los dos equipos de manera aleatoria */
void clicked_bando_aleatorio(GtkWidget *widget, gpointer data){
	const gchar *text;
	bandos[1] = (rand()%2)+1;  //Seleccion aleatoria junto con un srand(time(NULL)) en el main
	if(bandos[1]==1){
		bandos[0] = 3;
		g_print("\nEl Jugador 2 es equipo Policias. El Jugador 1 es equipo Suffragettes.\n");
		text = g_strdup_printf(" %s es equipo Policias.  %s es equipo Suffragettes.",nombre2,nombre1);
		gtk_label_set_text(GTK_LABEL(mensaje_bando_select), text);
	}else{
		bandos[0] = 1;
		bandos[1] = 3;
		g_print("\nEl Jugador 2 es equipo Suffragettes. El Jugador 1 es equipo Policias.\n");
		text = g_strdup_printf(" %s es equipo Suffragettes.  %s es equipo Policias.",nombre2,nombre1);
		gtk_label_set_text(GTK_LABEL(mensaje_bando_select), text);
	}
	g_print("bandos[0] = %d \nbandos[1] = %d",bandos[0],bandos[1]);
}


/* Funcion que se utiliza en dos casos, dos botones diferentes.
 * Boton "Siguiente" en la ventana "Bandos": Oculta la ventana "Bandos" y muestra la ventana "Turnos"
 * Boton "Siguiente" en la ventana "Turnos": Oculta la ventana "Turnos" y muestra la ventana "Reglas" y la ventana Principal del Juego */
void clicked_siguiente(GtkWidget *widget, gpointer data){
	if(turno==0 && bandos[0]!=0){
		gtk_widget_show_all(vtn_turno);
		gtk_widget_hide(vtn_bando);
	}
	if(turno!=0 && modo!=0 && bandos[0]!=0 ){
		gtk_widget_hide(vtn_turno);
		gtk_widget_show_all(window);
		gtk_dialog_run(v_reglas);
	}
}


/*Funcion del boton "Siguiente" en la ventana "Modo de Juego".
 * Muestra la ventana "Nombres"
 * Oculta la ventana "Modo de Juego"
 * Activa la funcion "set_nombres()" para cargar los nombres predeterminados segun el modo de Juego
 * NO "FUNCIONA" SINO HASTA DESPUES DE HABERLE DADO CLICK A ALGUNO DE LOS TRES BOTONES EN LA VENTANA "MODO DE JUEGO" */
void siguiente_en_modo_juego(GtkWidget *widget, gpointer data){
	if(modo!=0){
		gtk_widget_show_all(v_nombres);
		gtk_widget_hide(vtn_modo_juego);
		set_nombres();
	}
}


/*Asigna turno = 1, lo cual significa que el Jugador_1(nombre1) sera quien empieza el juego
 * Muestra un mensaje en la ventana, avisando quien empieza y tambien coloca el nombre en el label_turno en la ventana del Juego */
void clicked_comienza_jugador_1(GtkWidget *widget, gpointer data){
	turno = 1;
	g_print("\n\nEl Jugador 1 empieza. \nTurno = %d ",turno);
	const gchar *text = g_strdup_printf(" %s empieza.",nombre1);
	if(turno==1 && bandos[0]==3){
		gtk_label_set_text(GTK_LABEL(nom_jug_y), nombre1);
		gtk_label_set_text(GTK_LABEL(nom_jug_x), nombre2);
	}else{
		gtk_label_set_text(GTK_LABEL(nom_jug_x), nombre1);
		gtk_label_set_text(GTK_LABEL(nom_jug_y), nombre2);
	}
	gtk_label_set_text(GTK_LABEL(mensaje_turno_select), text);
	gtk_label_set_text(GTK_LABEL(label_turno), nombre1);
}

/*Asigna turno = 2, lo cual significa que el Jugador_2(nombre2) sera quien empieza el juego
 * Muestra un mensaje en la ventana, avisando quien empieza y tambien coloca el nombre en el label_turno en la ventana del Juego*/
void clicked_comienza_jugador_2(GtkWidget *widget, gpointer data){
	turno = 2;
	g_print("\n\nEl Jugador 2 empieza. \nTurno = %d ",turno);
	const gchar *text = g_strdup_printf(" %s empieza.",nombre2);
	if(turno==2 && bandos[1]==3){
		gtk_label_set_text(GTK_LABEL(nom_jug_y), nombre2);
		gtk_label_set_text(GTK_LABEL(nom_jug_x), nombre1);
	}else{
		gtk_label_set_text(GTK_LABEL(nom_jug_x), nombre2);
		gtk_label_set_text(GTK_LABEL(nom_jug_y), nombre1);
	}
	gtk_label_set_text(GTK_LABEL(mensaje_turno_select), text);
	gtk_label_set_text(GTK_LABEL(label_turno), nombre2);
}



/* Asigna un valor a turno de manera aleatoria.
 * Si turno = 1, Jugador_1(nombre1) sera quien empieza el juego
 * Si turno = 2, Jugador_2(nombre2) sera quien empieza el juego
 * Muestra un mensaje en la ventana, avisando quien empieza y tambien coloca el nombre en el label_turno en la ventana del Juego*/
void clicked_comienza_aleatorio(GtkWidget *widget, gpointer data){
	const gchar *text;
	turno = (rand()%2)+1;		//Seleccion aleatoria junto con un srand(time(NULL)) en el main
	if(turno == 1){
		g_print("\n\nEl Jugador 1 empieza. \nTurno = %d ",turno);
		text = g_strdup_printf(" %s empieza.",nombre1);
		gtk_label_set_text(GTK_LABEL(mensaje_turno_select), text);
		if(bandos[0]==3){
			gtk_label_set_text(GTK_LABEL(nom_jug_y), nombre2);
			gtk_label_set_text(GTK_LABEL(nom_jug_x), nombre1);
		}else{
			gtk_label_set_text(GTK_LABEL(nom_jug_x), nombre2);
			gtk_label_set_text(GTK_LABEL(nom_jug_y), nombre1);
		}
		gtk_label_set_text(GTK_LABEL(label_turno), nombre1);
	}else{
		g_print("\n\nEl Jugador 2 empieza. \nTurno = %d ",turno);
		text = g_strdup_printf(" %s empieza.",nombre2);
		gtk_label_set_text(GTK_LABEL(mensaje_turno_select), text);
		if(bandos[1]==3){
			gtk_label_set_text(GTK_LABEL(nom_jug_y), nombre2);
			gtk_label_set_text(GTK_LABEL(nom_jug_x), nombre1);
		}else{
			gtk_label_set_text(GTK_LABEL(nom_jug_x), nombre2);
			gtk_label_set_text(GTK_LABEL(nom_jug_y), nombre1);
		}
		gtk_label_set_text(GTK_LABEL(label_turno), nombre2);
	}
}





/*Un vector de Strings, almacena ubicacion de imagenes que se utilizan para cargar la grilla creada en el glade
 * de acuerdo a los valores en la matriz global "Tablero" */
extern char *imagenes[] = {"./IMG/Vacio.png",
		"./IMG/Inspector.png",
		"./IMG/Policia.png",
		"./IMG/Lidereza.png",
		"./IMG/Suffragette.png"};







void tablero_cb(GtkWidget *event_box, GdkEventButton *event, gpointer data){
	guint i,j;

	/*Se verifican si se cumplen las condiciones para finalizar el juego*/
	rev_carcel_hosp(&num3,&num4);
	verificar_conquista(&num1,&num2);


	if(num1==6 || num2==6 || num3>=16 || num4>=16){	//Si se cumplen las condiciones, el juego termina.
		fin_del_juego(num1,num2,num3,num4);
		ventana_fin_del_juego();

	}else{	//Si no se cumplen las condiciones, el juego continua.

		if((modo==1 && turno==1) || (modo==1 && turno==2) || (modo==2 && turno==2)){	//Juega USUARIO/S
			i = (GUINT_FROM_LE(event->y) / 40); //las imagenes tienen son 40x40pixeles
			j = (GUINT_FROM_LE(event->x) / 40);

			if(cont!=0){//Si ya ha saltado una vez ingresa en el if y se llama a la siguinte funcion para saltos consecutivos
				Click_saltos(Tablero[coor[0]][coor[1]], coor[0], coor[1], i,j);
				/*Al finalizar un salto la variable B se cera, para su uso otra vez.*/
				B=0;
			}else{// Si no ha salto ninguna vez, llama a las respectivas funciones
				if(bandera == 0){//si es el primer click
					Primer_Click(bandos[turno-1], i,j);
				}else{//si es el segundo click
					Click_Dos(Tablero[coor[0]][coor[1]], coor[0], coor[1], i,j);
				}
			}
		}

		if((modo==2 && turno==1) || (modo==3 && turno==1) || (modo==3 && turno==2)){	//Juega COMPUTADORA/S
			Juega_Computadora();
			rotar_jugador();
		}
		mostrar_turno();
	}

}


/*Funcion para pasar el ranking/estadisticas de los jugadores desde el archivo .txt
 * a la interfaz grafica. */
int cargar_ranking(){
	int i=0,j;
	gchar *temp;
	char *linea=NULL, *token=NULL;
	size_t n=0;
	GtkLabel *texto;
	grilla_estadisticas = gtk_grid_new();
	FILE * f;

	f = fopen("estadisticas.txt","r");
	if(f==NULL){
		printf("\nNo se pudo abrir el fichero.\n");
		return 0;
	}
	getline(&linea,&n,f);

	while(!feof(f)){
		getline(&linea,&n,f);
		token = strtok(linea, "\t");
		for(j=0; j<4; i++){
			temp = g_strdup_printf(token);
			gtk_label_set_text(GTK_LABEL(texto), temp);
			gtk_grid_attach(GTK_GRID(grilla_estadisticas), GTK_LABEL(texto), j, i, 1, 1);
			g_free(temp);
			token = strtok(NULL, "\t");
		}
		i++;
	}
	gtk_container_add(GTK_CONTAINER(box_estadisticas), grilla_estadisticas);

	fclose(f);
	return 1;
}


GtkWidget *crear_tablero(){
	int i, j;
	GtkWidget *imagen; //auxiliar para cargar la imagen
	GtkWidget *eventbox;
	eventbox = GTK_WIDGET(gtk_builder_get_object(builder, "Eventos"));
	tablero = GTK_WIDGET(gtk_builder_get_object(builder, "Grilla"));
	for (i = 0; i < MAX_FILA; i++) {
		for (j = 0; j < MAX_COLUMNA; j++) {
			if( Tablero[i][j]==0 || Tablero[i][j]==5 || Tablero[i][j]==6 ){
				imagen = gtk_image_new_from_file(imagenes[0]);
				gtk_grid_attach(GTK_GRID(tablero), GTK_WIDGET(imagen), j, i, 1, 1);
			}
			if( Tablero[i][j]==1 ){
				imagen = gtk_image_new_from_file(imagenes[1]);
				gtk_grid_attach(GTK_GRID(tablero), GTK_WIDGET(imagen), j, i, 1, 1);
			}
			if( Tablero[i][j]==2 ){
				imagen = gtk_image_new_from_file(imagenes[2]);
				gtk_grid_attach(GTK_GRID(tablero), GTK_WIDGET(imagen), j, i, 1, 1);
			}
			if( Tablero[i][j]==3 ){
				imagen = gtk_image_new_from_file(imagenes[3]);
				gtk_grid_attach(GTK_GRID(tablero), GTK_WIDGET(imagen), j, i, 1, 1);
			}
			if( Tablero[i][j]==4 ){
				imagen = gtk_image_new_from_file(imagenes[4]);
				gtk_grid_attach(GTK_GRID(tablero), GTK_WIDGET(imagen), j, i, 1, 1);
			}

		}
	}
	g_signal_connect(eventbox, "button-press-event", G_CALLBACK(tablero_cb), tablero);
	return eventbox;
}


void cerrar (GtkWidget *object, gpointer user_data){
	 printf("\n\nsaludo: %s", (char*)user_data);
	 gtk_main_quit();
}







 int main (int argc, char *argv[]) {

	GObject *menu_juego_nuevo;
	GObject *menu_juego_salir;
	GObject *menu_ayuda_ayuda;
	GObject *menu_ayuda_acerca_de;


	srand(time(NULL));		//Se utiliza srand(time(NULL)) para la obtencion de numeros aleatorios mas adelante dentro de las funciones con rand()

    //Para el GtkBuilder
    guint ret, ret2;

    GError *error = NULL;

    gtk_init (&argc, &argv);

	builder = gtk_builder_new();
	//Se carga el builder
	ret = gtk_builder_add_from_file(builder, "tablero.glade", &error);
	if(ret == 0) {
		g_print("Error en la función gtk_builder_add_from_file:\n%s", error->message);
		return 1;
	}

	ret2 = gtk_builder_add_from_file(builder, "Menus_Varios.glade", &error);
	if(ret2 == 0) {
		g_print("Error en la función gtk_builder_add_from_file:\n%s", error->message);
		return 1;
	}



/* BARRA DE MENU. Botones*/

	menu_juego_nuevo = gtk_builder_get_object(builder, "menu_juego_nuevo");

	menu_juego_salir = gtk_builder_get_object(builder, "menu_juego_salir");
	g_signal_connect (menu_juego_salir, "activate", G_CALLBACK (gtk_main_quit), NULL);

	menu_ayuda_ayuda = gtk_builder_get_object(builder, "menu_ayuda_ayuda");
	g_signal_connect (menu_ayuda_ayuda, "activate", G_CALLBACK (mostrar_reglas), NULL);

	menu_ayuda_acerca_de = gtk_builder_get_object(builder, "menu_ayuda_acerca_de");
	g_signal_connect (menu_ayuda_acerca_de, "activate", G_CALLBACK (mostrar_creditos), NULL);



/*##############################################################################################################*/



/* Ventana Jugar. Iniciar una Nueva Partida o Continuar una Partida previa */
	v_jugar = GTK_WIDGET(gtk_builder_get_object(builder, "V_Jugar"));

	nuevo_juego = GTK_WIDGET(gtk_builder_get_object(builder, "JN_btn"));
	g_signal_connect (nuevo_juego, "clicked", G_CALLBACK (Juego_Nuevo), NULL);

	atras_btn = GTK_WIDGET(gtk_builder_get_object(builder, "Atras_btn"));
	g_signal_connect (atras_btn, "clicked", G_CALLBACK (btn_atras_en_jugar), NULL);

/*##############################################################################################################*/




/* Ventana Seleccion Modo de Juego. Usuario vs. Usuario ,  Usuario vs. PC.  o  PC vs. PC   */
	vtn_modo_juego = GTK_WIDGET(gtk_builder_get_object(builder, "Modo_Juego"));

	btn_a1 = GTK_WIDGET(gtk_builder_get_object(builder, "B_modo1"));
	g_signal_connect (btn_a1, "clicked", G_CALLBACK (modo_uno), NULL);

	btn_a2 = GTK_WIDGET(gtk_builder_get_object(builder, "B_modo2"));
	g_signal_connect (btn_a2, "clicked", G_CALLBACK (modo_dos), NULL);

	btn_a3 = GTK_WIDGET(gtk_builder_get_object(builder, "B_modo3"));
	g_signal_connect (btn_a3, "clicked", G_CALLBACK (modo_tres), NULL);

	btn_next1 = GTK_WIDGET(gtk_builder_get_object(builder, "Siguiente_3"));
	g_signal_connect (btn_next1, "clicked", G_CALLBACK (siguiente_en_modo_juego), NULL);



/*##############################################################################################################*/




/* Labels auxiliares para ventana de eleccion de bandos, caso PC vs. PC */

	mensaje_modo_select = GTK_WIDGET(gtk_builder_get_object(builder, "label_modo_select"));
	mensaje_bando_select = GTK_WIDGET(gtk_builder_get_object(builder, "label_bando_select"));
	mensaje_turno_select = GTK_WIDGET(gtk_builder_get_object(builder, "label_turno_select"));
	label_jug1 = GTK_WIDGET(gtk_builder_get_object(builder, "Jug1_label"));
	label_jug2 = GTK_WIDGET(gtk_builder_get_object(builder, "Jug2_label"));
	mensaje_v_bandos = GTK_WIDGET(gtk_builder_get_object(builder, "Mensaje_Seleccion"));


/*##############################################################################################################*/



/* Ventana nombres. Darle nombres a los Jugadores */
	v_nombres = GTK_WIDGET(gtk_builder_get_object(builder, "V_Nombres"));
	sgtn_B = GTK_WIDGET(gtk_builder_get_object(builder, "Siguiente_4"));
	g_signal_connect (sgtn_B, "clicked", G_CALLBACK (siguiente_en_v_nombres), NULL);


	nombre_1 = GTK_WIDGET(gtk_builder_get_object(builder, "J1_entry"));
	nombre_2 = GTK_WIDGET(gtk_builder_get_object(builder, "J2_entry"));



/*##############################################################################################################*/



/* Venta FIN DEL JUEGO. Aparece al finalizar una Partida si las condiciones de fin del Juego se han cumplido. */
	vtn_fin_juego = GTK_WIDGET(gtk_builder_get_object(builder, "V_Fin_Juego"));
	fin_juego_label1 = GTK_WIDGET(gtk_builder_get_object(builder, "fin_label1"));
	fin_juego_label2 = GTK_WIDGET(gtk_builder_get_object(builder, "fin_label2"));

	btn_Finalizar = GTK_WIDGET(gtk_builder_get_object(builder, "btn_Finalizar"));
	g_signal_connect (btn_Finalizar, "clicked", G_CALLBACK (gtk_main_quit), NULL);


	char despedida[50] = "Partida Finalizada. Gracias por jugar. ";

	g_signal_connect (vtn_fin_juego, "destroy", G_CALLBACK (gtk_main_quit), despedida);





/*##############################################################################################################*/



/* Ventana Reglas. Muestra las reglas del Juego */
	v_reglas = GTK_WIDGET(gtk_builder_get_object(builder, "V_Reglas"));
	cerrar_reglas = GTK_WIDGET(gtk_builder_get_object(builder, "Reglas_c"));
	g_signal_connect (cerrar_reglas, "clicked", G_CALLBACK (ocultar_reglas), NULL);


/*##############################################################################################################*/



/* Ventana Estadisticas. Muestra el ranking de todos los que han jugado */

	v_estadisticas = GTK_WIDGET(gtk_builder_get_object(builder, "V_Estadisticas"));

	box_estadisticas = GTK_WIDGET(gtk_builder_get_object(builder, "box_estadisticas"));

	btn_atras_estadists = GTK_WIDGET(gtk_builder_get_object(builder, "btn_atras_estadists"));
	g_signal_connect (btn_atras_estadists, "clicked", G_CALLBACK (boton_atras_estadisticas), NULL);




/*##############################################################################################################*/



/* Ventana Creditos. Muestra los creditos del juego */

	v_acerca_de = GTK_WIDGET(gtk_builder_get_object(builder, "V_Acerca_de"));



/*##############################################################################################################*/




/* MENU PRINCIPAL */
	principal = GTK_WIDGET(gtk_builder_get_object(builder, "Menu_Principal"));
	gtk_widget_show_all(principal);

	jugar_btn = GTK_WIDGET(gtk_builder_get_object(builder, "B_Jugar"));
	g_signal_connect (jugar_btn, "clicked", G_CALLBACK (ventana_jugar), NULL);

	reglas_btn1 = GTK_WIDGET(gtk_builder_get_object(builder, "B_Reglas"));
	g_signal_connect (reglas_btn1, "clicked", G_CALLBACK (mostrar_reglas), NULL);

	estat_btn1 = GTK_WIDGET(gtk_builder_get_object(builder, "B_Estadisticas"));
	g_signal_connect (estat_btn1, "clicked", G_CALLBACK (mostrar_estadisticas), NULL);

	creditos_btn1 = GTK_WIDGET(gtk_builder_get_object(builder, "B_Creditos"));
	g_signal_connect (creditos_btn1, "clicked", G_CALLBACK (mostrar_creditos), NULL);

	salir_btn = GTK_WIDGET(gtk_builder_get_object(builder, "B_Salir"));
	g_signal_connect (salir_btn, "clicked", G_CALLBACK (gtk_main_quit), NULL);



/*##############################################################################################################*/



	//Ventana principal
	window = GTK_WIDGET(gtk_builder_get_object(builder, "ventana"));

	//Box donde estara el Tablero
	box_tablero = GTK_WIDGET(gtk_builder_get_object(builder, "box_tablero"));

	//Labels
	label_turno = GTK_WIDGET(gtk_builder_get_object(builder, "label_turno"));
	label_estado = GTK_WIDGET(gtk_builder_get_object(builder, "label_estado"));

	nom_jug_y = GTK_WIDGET(gtk_builder_get_object(builder, "nom_jug_y"));
	nom_jug_x = GTK_WIDGET(gtk_builder_get_object(builder, "nom_jug_x"));

	click_uno = GTK_WIDGET(gtk_builder_get_object(builder, "Primer_Click"));
	click_dos = GTK_WIDGET(gtk_builder_get_object(builder, "Click_Dos"));




/*##############################################################################################################*/



/* Ventana Eleccion de Bandos con sus respectivos botones */
	vtn_bando = GTK_WIDGET(gtk_builder_get_object(builder, "Eleccion_Bando"));
	btn_b1 = GTK_WIDGET(gtk_builder_get_object(builder, "B_Suffragetto"));
		g_signal_connect (btn_b1, "clicked", G_CALLBACK (clicked_bando_suffragetto), NULL);

	btn_b2 = GTK_WIDGET(gtk_builder_get_object(builder, "B_Policia"));
		g_signal_connect (btn_b2, "clicked", G_CALLBACK (clicked_bando_policia), NULL);

	btn_b3 = GTK_WIDGET(gtk_builder_get_object(builder, "B_Aleatorio"));
		g_signal_connect (btn_b3, "clicked", G_CALLBACK (clicked_bando_aleatorio), NULL);

	btn_next2 = GTK_WIDGET(gtk_builder_get_object(builder, "Siguiente_1"));
		g_signal_connect (btn_next2, "clicked", G_CALLBACK (clicked_siguiente), NULL);



/*##############################################################################################################*/



/* Ventana Eleccion de turnos con sus respectivos botones */
	vtn_turno = GTK_WIDGET(gtk_builder_get_object(builder, "Eleccion_Turno"));
	btn_c1 = GTK_WIDGET(gtk_builder_get_object(builder, "B_Jugador1"));
		g_signal_connect (btn_c1, "clicked", G_CALLBACK (clicked_comienza_jugador_1), NULL);

	btn_c2 = GTK_WIDGET(gtk_builder_get_object(builder, "B_Jugador2"));
		g_signal_connect (btn_c2, "clicked", G_CALLBACK (clicked_comienza_jugador_2), NULL);

	btn_c3 = GTK_WIDGET(gtk_builder_get_object(builder, "B_Aleatorio2"));
		g_signal_connect (btn_c3, "clicked", G_CALLBACK (clicked_comienza_aleatorio), NULL);

	btn_next3 = GTK_WIDGET(gtk_builder_get_object(builder, "Siguiente_2"));
		g_signal_connect (btn_next3, "clicked", G_CALLBACK (clicked_siguiente), NULL);

/*##############################################################################################################*/


	gtk_box_pack_start(GTK_BOX(box_tablero), crear_tablero(), TRUE, FALSE, 20);

    /* Connect the destroy signal of the window to gtk_main_quit
     * When the window is about to be destroyed we get a notification and
     * stop the main GTK+ loop
     */
	char mensaje[20] = "hola que tal";
    g_signal_connect (window, "destroy", G_CALLBACK (cerrar), mensaje);

    g_signal_connect (principal, "destroy", G_CALLBACK (cerrar), mensaje);
    /* make sure that everything, window and label, are visible */

    /* start the main loop, and let it rest there until the application is closed */
    gtk_main ();

    return 0;
 }

