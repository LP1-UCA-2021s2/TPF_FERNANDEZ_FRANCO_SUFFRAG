#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


#include "Funciones_Suffrag.h"





void ventana_fin_del_juego(){
	gtk_widget_show_all(vtn_fin_juego);
}




/*###############################################################################################################################################*/



/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~COMUNICACION EN RED~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


//Existen tres palabras claves: SIMPLE , SALTO y PASO.



/* Si se lee la palabra:  "SIMPLE" */
void Simple_en_PCvPC(int x1, int y1, int x2, int y2){
	int pieza=0;

	pieza = Tablero[x1][y1];

	Movimiento(pieza,x1,y1,x2,y2);

	rotar_jugador();
}





/* Si se lee la palabra:  "SALTO" */
int Saltos_en_PCvPC(int x1, int y1, int x3, int y3){
	int x2,y2,pieza1,pieza2;

	pieza1 = Tablero[x1][y1];

	Movimiento(pieza1,x1,y1,x3,y3);

	if(x1>x3){
		x2 = x1 -1;
	}
	if(x1==x3){
		x2 = x1 +0;
	}
	if(x1<x3){
		x2 = x1 +1;
	}
	if(y1>y3){
		y2 = y1 -1;
	}
	if(y1==y3){
		y2 = y1 +0;
	}
	if(y1<y3){
		y2 = y1 +1;
	}

	pieza2 = Tablero[x2][y2];

	if( pieza2!=bandos[turno-1] || pieza2!=(bandos[turno-1] +1) ){
		if(!verificar_arena(x2,y2)){
			return 0;
		}else{
			Pieza_Derrotada(pieza2);
		}
	}

	return 1;
}




/*Si se lee la palabra:  "PASO" */
void Paso_en_PCvPC(){
	rotar_jugador();
}






/*###############################################################################################################################################*/



/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ESTADISTICAS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/



/*Funcion para mostrar primero en el arvhico los nombres de los usuarios, con mayor cantidad de veces ganadas */
char *ordenar(char *v){
	char *token1=NULL;
	char *token2=NULL;
	char matriz[100][100];//se guarda todos los elementos del archivo, separandolos en filas
	char aux1[100];
	char aux2[100];
	char aux3[100];
	int i,j;
	int pos=0;
	int cont=0;
	int num1=0,num2=0;
	/*se guardan todos los elementos de archivo*/
	for(i=0;i<100;i++){
		for(j=0;j<100 && (v[pos]!='\n'&& v[pos]!='\0');j++){
			matriz[i][j]=v[pos++];


		}
		matriz[i][j]='\0';
		cont++;
		if(v[pos]=='\0'){
			break;
		}
		++pos;
	}
	/*se  controla cual es el jugador que mayor veces gano,y se lo pone en primera linea en el arvhivo*/
	for(i=1;i<cont;i++){
		for(j=1;j<(cont-1);j++){
			strcpy(aux1,matriz[j]);
			token1 = strtok(aux1, "\t");
			token1 = strtok(NULL, "\t");
			token1 = strtok(NULL, "\t");
			num1 = atoi(token1);//valor de veces ganadas
			strcpy(aux2,matriz[j+1]);
			token2=strtok(aux2,"\t");
			token2=strtok(NULL,"\t");
			token2=strtok(NULL,"\t");
			num2=atoi(token2);
			if(num1<num2){
				strcpy(aux3,matriz[j]);//se copia los elementos
				strcpy(matriz[j],matriz[j+1]);
				strcpy(matriz[j+1],aux3);
			}


		}
	}

	for(i=0;i<cont;i++){//se imprimime en el vector v el cambio realizado
		if(i==0){
			sprintf(v, "%s",matriz[i]);
		}else{
			sprintf(v, "%s\n%s", v, matriz[i]);
		}
	}
	return v;
}


/*Funcion que maneja un archivo, cuyo contenido es la estadistia de juego del jugador */
void Estadisticas(int ganador){

	char archivo[]="estadisticas.txt";
	FILE *fichero=fopen(archivo,"r+");// se habre para lectura y escritura, el puntero se posiciona al inicio

	if(fichero==NULL){//si no existe el archivo se crea uno
		fichero=fopen(archivo,"w");
		fprintf(fichero,"Nombre \tJ\tG\tP");
		fclose(fichero);
		fichero=fopen(archivo,"r+");
	}
	int existe=0,firstTime=0;
	char *linea=NULL,*token=NULL;
	char auxiliar[1000];//variable auxiliar usada para guardar todos los caracteres leidos del archivo, para luego actualizar de nuevo el contenido del archivo
	size_t n=0;
	while(!feof(fichero)){//bucle while para controlar si se apunta al EOF del archivo

		getline(&linea,&n,fichero);//se obtiene una linea del archivo, y se guarda en la variable linea
		token=strtok(linea,"\t");// se separa linea en tokens cada vez que halla el caracter \t
		if(strcmp(token,nombre2)==0){// si las dos cadena son igaules strcmp arroja el valor 0, esto es para ver si ya ha jugado con anterioridad el jugador

			sprintf (auxiliar,"%s%s",auxiliar,token);//imprime es auxiliar
			if(ganador){ //ganador, se actualizan los correspondientes valores de J y G
				token=strtok(NULL,"\t");
				int aux=atoi(token);
				aux++;
				sprintf (auxiliar,"%s\t%d",auxiliar,aux);
				token=strtok(NULL,"\t");

				aux=atoi(token);
				aux++;
				sprintf (auxiliar,"%s\t%d",auxiliar,aux);
				token=strtok(NULL,"\t");
				sprintf (auxiliar,"%s\t%s",auxiliar,token);
			}else{ //perdio,se actualizan los correspondientes valores de J y P
				token=strtok(NULL,"\t");
				int aux=atoi(token);
				aux++;
				sprintf (auxiliar,"%s\t%d",auxiliar,aux);
				token=strtok(NULL,"\t");
				sprintf (auxiliar,"%s\t%s",auxiliar,token);
				token=strtok(NULL,"\t");

				aux=atoi(token);
				aux++;
				if(feof(fichero)){
					sprintf (auxiliar,"%s\t%d",auxiliar,aux);


				}else{
					sprintf (auxiliar,"%s\t%d\n",auxiliar,aux);
				}


			}
			existe=1;
			continue;// se vuelve a preguntar en el while
		}
		/*se carga Nombre J G P*/
		if(firstTime){

			sprintf(auxiliar, "%s%s", auxiliar, token);
			token = strtok(NULL, "\t");
			sprintf(auxiliar, "%s\t%s", auxiliar, token);
			token = strtok(NULL, "\t");
			sprintf(auxiliar, "%s\t%s",auxiliar, token);
			token = strtok(NULL, "\t");
			sprintf(auxiliar, "%s\t%s",auxiliar, token);
		} else {
			sprintf(auxiliar, "%s",token);
			token = strtok(NULL, "\t");
			sprintf(auxiliar, "%s\t%s", auxiliar, token);
			token = strtok(NULL, "\t");
			sprintf(auxiliar, "%s\t%s", auxiliar, token);
			token = strtok(NULL, "\t");
			sprintf(auxiliar, "%s\t%s", auxiliar, token);
			firstTime = 1;
		}

	}
	if(existe){//si el arvhivo ya no fue creado una primera vez, si no que ya existia
		fclose(fichero);
		remove(archivo);
		fichero=fopen(archivo,"w");
		fputs(ordenar(auxiliar),fichero);// se imprime en el archivo el nombre y se actualiza sus valores, o se carga otro nombre y sus valores
		fclose(fichero);
	}else{//si no existe el archivo, se crea uno, el cual se carga con el primer nombre y sus valores
		fclose(fichero);
		fichero=fopen(archivo,"a");//se abre el archivo para escritura

		if(ganador){
			fprintf (fichero,"\n%s\t1\t1\t0",nombre2);

		}else{
			fprintf (fichero,"\n%s\t1\t0\t1",nombre2);

		}
		fclose(fichero);
	}

}




/*###############################################################################################################################################*/



/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~INTELIGENCIA ARTIFICIAL~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/



int mas_cercano(int x, int y, int *filas, int *columnas){
	int i,aux;
	float menor;
	int xabs[3] = {0,0,0};
	int yabs[3] = {0,0,0};

	float modulos[3] = {0,0,0};		// Vector que contiene las distancias entre la ficha y las tres posibles casillas a invadir

	for(i=0; i<3; i++){
		if(filas[i]!=0 && columnas[i]!=0){
			xabs[i] = abs(filas[i] - x);
			yabs[i] = abs(columnas[i] - y);
		}
	}

	/* Se obtienen los modulos/distancias. Se utiliza la formula matematica del modulo */
	for(i=0; i<3; i++){
		if(filas[i]!=0 && columnas[i]!=0){	//Si esto es verdadero, se obtiene el modulo. Si es falso, modulo = 0
			modulos[i] = sqrt(pow((abs(filas[i] - x)),2) + pow((abs(columnas[i] - y)),2));
		}
	}

	/* Se busca el menor modulo en el vector modulos[ ] , o sea, la menor distancia entre la ficha y una casilla */
	menor = modulos[0];
	for(i=0; i<3; i++){
		if(modulos[i]<menor && modulos[i]!=0){	// Si uno de los modulos es cero, no se lo toma en cuenta
			menor = modulos[i];
			aux = i;
		}
	}

	return aux;

}



int mov_intel(int x, int y){

	int i,j,k=0,aux;

	int xs[3] = {0,0,0};

	int ys[3] = {0,0,0};

	//Modo de Juego: Usuario vs. Computadora
	if(modo==2){
		/*Si la computadora es equipo policias, se hallan hasta tres 6s en la matriz Tablero */
		if(bandos[0]==1){
			for(i=4; i>2; i--){
				for(j=7; j<10; j++){
					if(Tablero[i][j]==6 && xs[2]==0){	// Las coordenadas de los 6s se guardan
						xs[k] = i;
						ys[k] = j;
						k++;
					}
				}
			}
		}

		/*Si la computadora es equipo suffragetto, se hallan hasta tres 5s en la matriz Tablero */
		if(bandos[0]==3){
			for(i=12; i<14; i++){
				for(j=7; j<10; j++){
					if(Tablero[i][j]==5 && xs[2]==0){	// Las coordenadas de los 5s se guardan
						xs[k] = i;
						ys[k] = j;
						k++;
					}
				}
			}
		}
	}else if(modo==3){	//Modo de Juego: Computadora vs. Computadora.
		/*Si la computadora es equipo policias, se hallan hasta tres 6s en la matriz Tablero */
		if(bandos[turno-1]==1){
			for(i=4; i>2; i--){
				for(j=7; j<10; j++){
					if(Tablero[i][j]==6 && xs[2]==0){	// Las coordenadas de los 6s se guardan
						xs[k] = i;
						ys[k] = j;
						k++;
					}
				}
			}
		}

		/*Si la computadora es equipo suffragetto, se hallan hasta tres 5s en la matriz Tablero */
		if(bandos[turno-1]==3){
			for(i=12; i<14; i++){
				for(j=7; j<10; j++){
					if(Tablero[i][j]==5 && xs[2]==0){	// Las coordenadas de los 5s se guardan
						xs[k] = i;
						ys[k] = j;
						k++;
					}
				}
			}
		}
	}

	aux = mas_cercano(x,y,xs,ys);


	int num=0;

	if((xs[aux]-x)<0){
		num = num+8;
	}

	if((xs[aux]-x)==0){
		num = 0;
	}

	if((xs[aux]-x)>0){
		num = num+3;
	}

	if((ys[aux]-y)<0){
		num = num+4;
	}

	if((ys[aux]-y)==0){
		num = num+0;
	}

	if((ys[aux]-y)>0){
		num = num+6;
	}

	jugada_comp(x,y,num);

	return num;

}



void jugada_comp(int x, int y, int target){
	int x2=0, y2=0;
	if(target==8){
		x2 = x-1;
		y2 = (rand()%((y+1)-(y-1)+1))+(y-1);
	}

	if(target==14){
		x2 = (rand()%((x)-(x-1)+1))+(x-1);
		y2 = (rand()%((y+1)-(y)+1))+(y);
	}

	if(target==12){
		x2 = (rand()%((x)-(x-1)+1))+(x-1);
		y2 = (rand()%((y)-(y-1)+1))+(y-1);
	}

	if(target==6){
		x2 = (rand()%((x+1)-(x-1)+1))+(x-1);
		y2 = y+1;
	}

	if(target==4){
		x2 = (rand()%((x+1)-(x-1)+1))+(x-1);
		y2 = y-1;
	}

	if(target==3){
		x2 = x+1;
		y2 = (rand()%((y+1)-(y-1)+1))+(y-1);
	}

	if(target==7){
		x2 = (rand()%((x+1)-(x)+1))+(x);
		y2 = (rand()%((y)-(y-1)+1))+(y-1);
	}

	if(target==9){
		x2 = (rand()%((x+1)-(x)+1))+(x);
		y2 = (rand()%((y+1)-(y)+1))+(y);
	}

	coords_PC[0] = x2;
	coords_PC[1] = y2;

}




/*###############################################################################################################################################*/




/*FUNCION PARA LAS JUGADAS HECHAS POR LA COMPUTADORA*/
void Juega_Computadora(){
	int x,y,x2,y2,pieza,m,n=0;
	do{
		x = (rand() % (16-0+1));
		y = (rand() % (15-2+1))+2;
	}while(!Primer_Click(bandos[turno-1],x,y));
	g_print("\n x = %d \n\n y = %d \n",x,y);
	g_print("\n coor[0] = %d\n coor[1] = %d \n",coor[0],coor[1]);
	pieza = Tablero[x][y];
	do{
		do{
			if(n==5){
				do{
					x = (rand() % (16-0+1));
					y = (rand() % (15-2+1))+2;
				}while(!Primer_Click(bandos[turno-1],x,y));
				n = 0;
			}
			mov_intel(coor[0] , coor[1]);

			x2 = coords_PC[0];
			y2 = coords_PC[1];
			n++;

		}while(!limite_movimiento(x2,y2) || !verificar_adyacente(x,y,x2,y2) || !Limitacion_Bases(x2,y2,pieza));
		m = Movimiento(x,y,x2,y2,pieza);
		if(m==0){
			do{
				x = (rand() % (16-0+1));
				y = (rand() % (15-2+1))+2;
			}while(!Primer_Click(bandos[turno-1],x,y));
		}
	}while(m==0);
	bandera = 0;
	g_print("\n x2 = %d \n\n y2 = %d \n",x2,y2);

}



/*Funcion que recibe dos contadores. Uno para la carcel, otro para el hospital.
 * Esta funcion se utiliza para saber si el numero de fichas habilitadas de ambos bandos es menor o igual a 5
 * puesto que si algun equipo tiene solo 5 fichas, no podra conquistar las seis casillas de la base enemiga.
 * Se alguno de estos dos contadores resulta ser mayor o igual a 16, algun equipo no podra ganar. Luego, su oponente es el ganador.*/
void rev_carcel_hosp(int *num3, int *num4){
	int i,j;
	*num3 = 0;
	*num4 = 0;

	/*Contar el numero de policias y/o Inspectores en el hospital*/
	for(i=0; i<17; i++){
		j = 0;
		if(Tablero[i][j]==1 || Tablero[i][j]==2){
			(*num3)++;
		}
	}
	/*Contar el numero de suffragettes y/o Lideres en la carcel*/
	for(i=0; i<17; i++){
		j = 16;
		if(Tablero[i][j]==3 || Tablero[i][j]==4){
			(*num4)++;
		}
	}

}


/*Limitacion para evitar que los bando entren en sus propias bases*/
int Limitacion_Bases(int x, int y, int pieza){
	int aux = pieza,m;
	if(aux==3 || aux==4){
		m = limitacion_Suffrag(x,y);
	}
	if(aux==1 || aux==2){
		m = limitacion_Polic(x,y);
	}
	return m;
}


/*Limitacion para evitar que las suffragettes entren en su propia base*/
int limitacion_Suffrag(int x, int y){
	gchar *text;
	if((x==3 || x==4) && (y>=7 && y<10)){
		printf("\nNo puede ingresar a esta casilla. \n");
		text = g_strdup_printf("\nError. No puede entrar en esta casilla. \nIntente con una casilla diferente. ");
		gtk_label_set_text(GTK_LABEL(label_estado), text);
		g_free(text);
		return 0;
	}else{
		return 1;
	}
}

/*Limitacion para evitar que los policias entren en su propia base*/
int limitacion_Polic(int x, int y){
	gchar *text;
	if((x==12 || x==13) && (y>=7 && y<10)){
		printf("\nNo puede ingresar a esta casilla. \n");
		text = g_strdup_printf("\nError. No puede entrar en esta casilla. \nIntente con una casilla diferente. ");
		gtk_label_set_text(GTK_LABEL(label_estado), text);
		g_free(text);
		return 0;
	}else{
		return 1;
	}
}

/*Combinacion con limite_tablero para impedir que las piezas entren en la carcel
 * u hospital*/
int limite_movimiento(int x, int y){
	gchar *text;
	int aux = limite_tablero(x,y);
	switch(aux){
		case 0:
			return 0;
		case 1:
			if((y==1 && x<4) || (y==15 && x>12)){
				printf("\nError. No puede entrar en esta casilla. \n");
				text = g_strdup_printf("\nError. No puede entrar en esta casilla. \nIntente con una casilla diferente. ");
				gtk_label_set_text(GTK_LABEL(label_estado), text);
				g_free(text);
				return 0;
			}else{
				return 1;
			}
	}
}

/*Verifica que las coordenadas de movimiento sean las de una casilla adyacentes
 * a la casilla seleccionada*/
int verificar_adyacente(int x, int y, int x2, int y2){
	gchar *text;
	if((x2==x) && (y2==y)){		//para evitar la misma casilla
		printf("\nCoordenadas inicial y final coinciden. Vuelva a ingresar las coordenadas. ");
		text = g_strdup_printf("\nCoordenadas inicial y final coinciden. \nIntente con una casilla diferente. ");
		gtk_label_set_text(GTK_LABEL(label_estado), text);
		g_free(text);
		return 0;
	}
	if(abs(x2-x)<=1 && abs(y2-y)<=1){	//abs es una funcion de stdlib.h
		return 1;
	}else{
		printf("\nCasilla fuera de la adyacencia. \n");
		text = g_strdup_printf("\nCasilla fuera de la adyacencia. \nIntente con una casilla diferente. ");
		gtk_label_set_text(GTK_LABEL(label_estado), text);
		g_free(text);
		g_print("x = %d\n y = %d\n x2=%d\n y2= %d\n",x,y,x2,y2);
		return 0;
	}
}


/*Rotar jugadores*/
void rotar_jugador(){
	gchar *temp =  g_strdup_printf("   ");
	if(turno==1){		//si antes era turno = 1, ahora sera turno = 2
		turno = 2;
	}else{
		turno = 1;		//turno era = 2, luego pasa a ser 1.
	}
	if(bandera==1){
		bandera = 0;
	}
	gtk_label_set_text(GTK_LABEL(label_estado), temp);
	g_free(temp);
	g_print("\n turno = %d \n",turno);
}

/*Mostrar turnos. Imprime un mensaje sobre a quien le toca jugar */
void mostrar_turno(){
	if(turno == 1){
		gtk_label_set_text(GTK_LABEL(label_turno), nombre1);
	}else{
		gtk_label_set_text(GTK_LABEL(label_turno), nombre2);
	}
}


/*Imprime el Mensaje de fin del juego de acuerdo a las condiciones de fin del juego*/
void fin_del_juego(int num1, int num2, int num3, int num4){
	gchar *text1, *text2;
	int ganador=0;//si es 0 significa que el usuario perdio, si es 1 significa que el usuario gano

	if(num3>=16){
		if(bandos[0]==1){
			g_print("\nEl equipo Policias no tiene suficientes fichas para conquistar la base enemiga.\n\n\t\tVICTORIA DE LAS SUFFRAGETTES! \n");
			g_print("\nEl Usuario ha ganado.\n");
			ganador=1;
			Estadisticas(ganador);
			text2 = g_strdup_printf("VICTORIA DE  %s  !!!",nombre2);
			gtk_label_set_text(GTK_LABEL(fin_juego_label2), text2);
			g_free(text2);
			text1 = g_strdup_printf("El equipo Policias no tiene suficientes fichas \npara conquistar la base enemiga.\n\nVICTORIA DE LAS SUFFRAGETTES!!");
			gtk_label_set_text(GTK_LABEL(fin_juego_label1), text1);
			g_free(text1);
		}else{
			g_print("\nEl equipo Policias no tiene suficientes fichas para conquistar la base enemiga.\n\n\t\tVICTORIA DE LAS SUFFRAGETTES! \n");
			g_print("\nLa Computadora ha ganado.\n");
			ganador=0;
			Estadisticas(ganador);
			text2 = g_strdup_printf("VICTORIA DE  %s  !!!",nombre1);
			gtk_label_set_text(GTK_LABEL(fin_juego_label2), text2);
			g_free(text2);
			text1 = g_strdup_printf("El equipo Policias no tiene suficientes fichas \npara conquistar la base enemiga.\n\nVICTORIA DE LAS SUFFRAGETTES!!");
			gtk_label_set_text(GTK_LABEL(fin_juego_label1), text1);
			g_free(text1);
		}
	}
	if(num4>=16){
		if(bandos[1]==3){
			g_print("\nEl equipo Suffragetto no tiene suficientes fichas para conquistar la base enemiga.\n\n\t\tVICTORIA DE LOS POLICIAS! \n");
			g_print("\nEl Usuario ha ganado.\n");
			ganador=1;
			Estadisticas(ganador);
			text2 = g_strdup_printf("VICTORIA DE  %s  !!!",nombre2);
			gtk_label_set_text(GTK_LABEL(fin_juego_label2), text2);
			g_free(text2);
			text1 = g_strdup_printf("El equipo Suffragetto no tiene suficientes fichas \npara conquistar la base enemiga.\n\nVICTORIA DE LOS POLICIAS!!");
			gtk_label_set_text(GTK_LABEL(fin_juego_label1), text1);
			g_free(text1);
		}else{
			g_print("\nEl equipo Suffragetto no tiene suficientes fichas para conquistar la base enemiga.\n\n\t\tVICTORIA DE LOS POLICIAS! \n");
			g_print("\nLa Computadora ha ganado.\n");
			ganador=0;
			Estadisticas(ganador);
			text2 = g_strdup_printf("VICTORIA DE %s  !!!",nombre1);
			gtk_label_set_text(GTK_LABEL(fin_juego_label2), text2);
			g_free(text2);
			text1 = g_strdup_printf("El equipo Suffragetto no tiene suficientes fichas \npara conquistar la base enemiga.\n\nVICTORIA DE LOS POLICIAS!!");
			gtk_label_set_text(GTK_LABEL(fin_juego_label1), text1);
			g_free(text1);
		}
	}
	if(num1==6){
		g_print("\n\n\t\t\tALBERT HALL CONQUISTADO! \n\n\t\t\tVICTORIA DE LOS POLICIAS! \n\n");
		text1 = g_strdup_printf("ALBERT HALL CONQUISTADO! \nVICTORIA DE LOS POLICIAS!");
		gtk_label_set_text(GTK_LABEL(fin_juego_label1), text1);
		g_free(text1);
		if(bandos[0]==1){
			g_print("\n\n\n\tLa Computadora ha ganado. ");
			ganador=0;
			Estadisticas(ganador);
			text2 = g_strdup_printf("%s   HA GANADO!!!",nombre1);
			gtk_label_set_text(GTK_LABEL(fin_juego_label2), text2);
			g_free(text2);
		}else{
			g_print("\n\n\n\tEl Usuario ha ganado. ");
			ganador=1;
			Estadisticas(ganador);
			text2 = g_strdup_printf("%s   HA GANADO!!!",nombre2);
			gtk_label_set_text(GTK_LABEL(fin_juego_label2), text2);
			g_free(text2);
		}
	}
	if(num2==6){
		g_print("\n\n\t\t\tHOUSE OF COMMONERS CONQUISTADO! \n\n\t\t\tVICTORIA DE LAS SUFFRAGETTES! \n\n");
		text1 = g_strdup_printf("HOUSE OF COMMONERS CONQUISTADO! \nVICTORIA DE LAS SUFFRAGETTES!!");
		gtk_label_set_text(GTK_LABEL(fin_juego_label1), text1);
		g_free(text1);
		if(bandos[0]==3){
			g_print("\n\n\n\tLa Computadora ha ganado. ");
			ganador=0;
			Estadisticas(ganador);
			text2 = g_strdup_printf("%s   HA GANADO!!!",nombre1);
			gtk_label_set_text(GTK_LABEL(fin_juego_label2), text2);
			g_free(text2);
		}else{
			g_print("\n\n\n\tEl Usuario ha ganado. ");
			ganador=1;
			Estadisticas(ganador);
			text2 = g_strdup_printf("%s   HA GANADO!!!",nombre2);
			gtk_label_set_text(GTK_LABEL(fin_juego_label2), text2);
			g_free(text2);
		}
	}
	printf("\n\n\n\n\t\tFIN DEL JUEGO\n");
}





/*Maximo y Minimo valores posibles que pueden tomar las coordenadas x e y*/
int limite_tablero(int x, int y){
	gchar *text;
	if(x>=0 && x<17 && y>=1 && y<16){
		return 1;
	}else{
		g_print("\nCasilla fuera de limites. \n");
		text = g_strdup_printf("\nCasilla fuera de limites. \nIntente con una casilla diferente. ");
		gtk_label_set_text(GTK_LABEL(label_estado), text);
		g_free(text);
		return 0;
	}
}



/*Para verificar si alguna de las bases ha sido conquistada
 * Se utilizan num1 y num2(o mejor dicho sus direcciones), ambos se van incrmentando.
 * Si alguno de estos dos llega a valer seis, quiere decir que una de las bases
 * enemigas ha sido completamente invadida*/
void verificar_conquista(int *num1, int *num2){
	int i,j;
	*num1 = 0;
	*num2 = 0;

	/*Base de las Suffragettes. ALBERT HALL*/
	for(i=3; i<5; i++){
		for(j=7; j<10; j++){
			if(Tablero[i][j]==1 || Tablero[i][j]==2){
				(*num1)++;
			}
		}
	}
	/*Base de los Policias. COMMONERS HALL*/
	for(i=12; i<14; i++){
		for(j=7; j<10; j++){
			if(Tablero[i][j]==3 || Tablero[i][j]==4){
				(*num2)++;
			}
		}
	}
}




/*Verifica si la casilla seleccionada esta vacia o no*/
int verificar_vacia(int x, int y){
	gchar *text;
	if(Tablero[x][y]==0){
		return 1;
	}
	if(Tablero[x][y]==5 && bandos[turno-1]==3){
		return 1;
	}
	if(Tablero[x][y]==6 && bandos[turno-1]==1){
		return 1;
	}
	if(Tablero[x][y]>0 && bandera==0){
		printf("\nCasilla Ocupada o NO habilitada para su equipo. ");
		text = g_strdup_printf("\nCasilla Ocupada o NO habilitada para su Equipo. \nIntente con una casilla diferente. \n");
		gtk_label_set_text(GTK_LABEL(label_estado), text);
		g_free(text);
		return 0;
	}else if(Tablero[x][y]>0 && bandera==1){
		return 0;
	}
}



/*Revisa los alrededores de una ficha en busca de otras que esten en su adyacencia
 * Auxiliar para saltos en cadena */
int revisar_vecinos(int x, int y){
//	B = 0;
	int i,j;
	int aux=0;

	for(i=x-1; i<x+2; i++){
		if(i<0)	// Para el caso en que la ficha este en la fila 0
			i = i+1;
		if(i>16)	// Para el caso en que la ficha este en la fila 16
			break;
		for(j=y-1; j<y+2; j++){
			if(j<1)	// Para el caso en que la ficha este en la columna 1
				j = j+1;
			if(j>15)	// Para el caso en que la ficha este en la columna 15
				break;
			if(!verificar_vacia(i,j)){
				aux = aux +1;
			}
		}
	}
	if(!verificar_vacia(x,y)){
		aux = aux-1;
	}
	g_print("cantida de vecinos %d",aux);

	return aux;		//Retorna aux, que es una cantidad que indica que existe al menos una o ninguna ficha en las cercanias
					//Esta funcion es mas que nada para ayudar en la accion de saltos multiples
}



/*Verifica si la pieza que se encuentra en la casilla seleccionada pertenece al bando
 * propio o al bando enemigo*/
int verificar_bando(int x, int y, int bando){
	gchar *text;
	if(Tablero[x][y]==bando || Tablero[x][y]==bando+1){
		return 1;
	}
	if(Tablero[x][y]!=bando){
		printf("\nCoordenada no valida. Pieza del bando opuesto o casilla vacia. \n");
		text = g_strdup_printf("\n\nCoordenada no valida. \nPieza del bando opuesto o casilla vacia. \n");
		gtk_label_set_text(GTK_LABEL(label_estado), text);
		g_free(text);
		return 0;
	}
}

/*Para verificar que la ficha enemiga este dentro de la arena de combate
 * de asi serlo, podra ser incapacitada por sus oponentes a la hora de ser saltada*/
int verificar_arena(int x, int y){
	gchar *text;
	if(x>=0 && x<17 && y>=4 && y<13){
		return 1;
	}else{
		printf("\nFuera de la arena de combate. \nNo puede incapacitar a esta pieza. \n");
		text = g_strdup_printf("\n\nFuera de la arena de combate. \nNo puede incapacitar a esta pieza. \n");
		gtk_label_set_text(GTK_LABEL(label_estado), text);
		g_free(text);
		return 0;
	}
}



/*Funcion encargada de cargar en la carcel/hostpital a las piezas derrotadas*/
void Pieza_Derrotada(int derrotado){
	int i,j;
	int aux = derrotado;
	if(aux==1 || aux==2){		//Inspector(1) o policia(2)
		for(j=0; j<2; j++){
			if(aux==0){
				break;
			}
			for(i=0; i<17; i++){
				if(Tablero[i][j]==0){
					Tablero[i][j] = aux;
					gtk_image_set_from_file(GTK_IMAGE(gtk_grid_get_child_at(GTK_GRID(tablero),j,i)), imagenes[aux]);
					aux = 0;
					break;
				}else{
					Tablero[i][j] = Tablero[i][j] +0;
				}
			}
		}
	}
	if(aux==3 || aux==4){		//Lider Suffragetto(3) o suffragette(4)
		for(j=16; j>14; j--){
			if(aux==0){
				break;
			}
			for(i=16; i>-1; i--){
				if(Tablero[i][j]==0){
					Tablero[i][j] = aux;
					gtk_image_set_from_file(GTK_IMAGE(gtk_grid_get_child_at(GTK_GRID(tablero),j,i)), imagenes[aux]);
					aux = 0;
					break;
				}else{
					Tablero[i][j] = Tablero[i][j] +0;
				}
			}
		}
	}
}


/*Auxiliar para la funcion Mov_Salto. Recoge las direcciones del posible salto*/
int aux_salto(int x, int y, int x2, int y2){
	if(x2>x && y2==y){		//Direccion vertical, descendiente
		return 1;
	}
	if(x2>x && y2<y){		//Diagonal derecha descendiente
		return 2;
	}
	if(x2>x && y2>y){		//Diagonal izquierda descendiente
		return 3;
	}
	if(x2==x && y2<y){		//Horizontal, de derecha a izquierda
		return 4;
	}
	if(x2==x && y2>y){		//Horizontal, de izquierda a derecha
		return 5;
	}
	if(x2<x && y2<y){		//Diagonal derecha ascendiente
		return 6;
	}
	if(x2<x && y2>y){		//Diagonal izquierda ascendiente
		return 7;
	}
	if(x2<x && y2==y){		//Vertical ascendiente
		return 8;
	}
}



/*Recoge y verifica las coordenadas de los posibles saltos*/

int Mov_Salto(int x, int y, int x2, int y2, int pieza){
	gchar *text;
	int x3,y3,m;
	//B = 0;

	int mov = aux_salto(x,y,x2,y2);		//Entra en accion la funcion aux_salto
	if(pieza==1 || pieza==3){	//1 y 3 son piezas especiales. Inspector y Lider suffragetto respectivamente
		switch(mov){			//pueden saltar en 8 direcciones
			case 1:
				x3 = x2 +1;
				y3 = y2 +0;
				break;
			case 2:
				x3 = x2 +1;
				y3 = y2 -1;
				break;
			case 3:
				x3 = x2 +1;
				y3 = y2 +1;
				break;
			case 4:
				x3 = x2 +0;
				y3 = y2 -1;
				break;
			case 5:
				x3 = x2 +0;
				y3 = y2 +1;
				break;
			case 6:
				x3 = x2 -1;
				y3 = y2 -1;
				break;
			case 7:
				x3 = x2 -1;
				y3 = y2 +1;
				break;
			case 8:
				x3 = x2 -1;
				y3 = y2 +0;
				break;
		}
	}
	if(pieza==2 || pieza==4){	//2 y 4 son piezas basicas. Policia y suffragette respectivamente
		switch(mov){			//solo pueden saltar en diagonal
			case 1:
				if(cont>0){
					printf("\nNo puede saltar en vertical u horizontal con esta ficha. \n");
					text = g_strdup_printf("\n\nNo puede saltar en vertical u horizontal con esta ficha. \n");
					gtk_label_set_text(GTK_LABEL(label_estado), text);
					g_free(text);
					cont = 4;
					return 9;
				}else{
					printf("\nNo puede saltar en vertical u horizontal con esta ficha. \nIntente con otras coordenadas. \n");
					text = g_strdup_printf("\n\nNo puede saltar en vertical u horizontal con esta ficha. \nIntente con una casilla distinta. \n");
					gtk_label_set_text(GTK_LABEL(label_estado), text);
					g_free(text);
					return 0;
				}
			case 2:
				x3 = x2 +1;
				y3 = y2 -1;
				break;
			case 3:
				x3 = x2 +1;
				y3 = y2 +1;
				break;
			case 4:
				if(cont>0){
					printf("\nNo puede saltar en vertical u horizontal con esta ficha. \n");
					text = g_strdup_printf("\n\nNo puede saltar en vertical u horizontal con esta ficha. \n");
					gtk_label_set_text(GTK_LABEL(label_estado), text);
					g_free(text);
					cont = 4;
					return 9;
				}else{
					printf("\nNo puede saltar en vertical u horizontal con esta ficha. \nIntente con otras coordenadas. /n");
					text = g_strdup_printf("\n\nNo puede saltar en vertical u horizontal con esta ficha. \nIntente con una casilla distinta. \n");
					gtk_label_set_text(GTK_LABEL(label_estado), text);
					g_free(text);
					return 0;
				}
			case 5:
				if(cont>0){
					printf("\nNo puede saltar en vertical u horizontal con esta ficha. \n");
					text = g_strdup_printf("\n\nNo puede saltar en vertical u horizontal con esta ficha. \n");
					gtk_label_set_text(GTK_LABEL(label_estado), text);
					g_free(text);
					cont = 4;
					return 9;
				}else{
					printf("\nNo puede saltar en vertical u horizontal con esta ficha. \nIntente con otras coordenadas. \n");
					text = g_strdup_printf("\n\nNo puede saltar en vertical u horizontal con esta ficha. \nIntente con una casilla distinta. \n");
					gtk_label_set_text(GTK_LABEL(label_estado), text);
					g_free(text);
					return 0;
				}
			case 6:
				x3 = x2 -1;
				y3 = y2 -1;
				break;
			case 7:
				x3 = x2 -1;
				y3 = y2 +1;
				break;
			case 8:
				if(cont>0){
					printf("\nNo puede saltar en vertical u horizontal con esta ficha. \n");
					text = g_strdup_printf("\n\nNo puede saltar en vertical u horizontal con esta ficha. \n");
					gtk_label_set_text(GTK_LABEL(label_estado), text);
					g_free(text);
					cont = 4;
					return 9;
				}else{
					printf("\nNo puede saltar en vertical u horizontal con esta ficha. \nIntente con otras coordenadas. \n");
					text = g_strdup_printf("\n\nNo puede saltar en vertical u horizontal con esta ficha. \nIntente con una casilla distinta. \n");
					gtk_label_set_text(GTK_LABEL(label_estado), text);
					g_free(text);
					return 0;
				}
		}
	}
	//Para verificar que las coordenadas del posible salto esten sean validas
	if(!limite_movimiento(x3,y3) || !verificar_vacia(x3,y3)){
		printf("\n\nLa casilla X2 = %d , Y2 = %d y su adyacente estan ocupadas. \nNo es posible saltar en esa direccion. ",x2,y2);
		text = g_strdup_printf("\nLa casilla X2 = %d , Y2 = %d y su adyacente estan ocupadas. \nNo es posible saltar en esa direccion. \n",x2,y2);
		gtk_label_set_text(GTK_LABEL(label_estado), text);
		g_free(text);
		//rotar_jugador();
		return 0;
	}
	g_print("\n\n x2 = %d\n y2 = %d\n x3 = %d\n y3 = %d \n\n",x2,y2,x3,y3);
	/*Si la funcion llego hasta aqui, quiere decir que es posible realizar el salto.
	 * Por lo tanto se pregunta si la ficha a ser saltada pertenece al bando propio, sino, es un enemigo y puede ser incapacitada
	 * Se utilizan el vector bandos con turno como subindice*/
	if(Tablero[x2][y2] != bandos[turno-1] && Tablero[x2][y2] != (bandos[turno-1] +1) && verificar_arena(x2,y2)){
		Pieza_Derrotada(Tablero[x2][y2]);	//Entra en accion la funcion Pieza_Derrotada
		Tablero[x2][y2] = 0;
		gtk_image_set_from_file(GTK_IMAGE(gtk_grid_get_child_at(GTK_GRID(tablero),y2,x2)), imagenes[0]);
	}
	Movimiento(x,y,x3,y3,pieza);
	B = revisar_vecinos(x3,y3);
	/*Se guardan las coordenadas finales despues de la accion salto
	 * esto es por si es posible volver a saltar*/
	coor[0] = x3;
	coor[1] = y3;

	return 1;
}



/* Desplazamiento de piezas.
 * Si la casilla de destino esta vacia, se realiza un movimiento simple */
int Movimiento(int x, int y, int x2, int y2, int pieza){
	int p=0;
	if(verificar_vacia(x2,y2)){		//verificar_vacia() retorna verdadero (1)

		/*Si estamos dentro del bucle de saltos que llega a 3 veces, y queremos hacer por ejemplo solo un salto
		 * entonces si seleccionamos una casilla vacia adyacente, no se actualizaria con la ficha nuestra
		 *  y movimiento() retornaria 0 y pararia el bucle de saltos, ya que se rotaria los saltos*/
		if(verificar_adyacente(x,y,x2,y2) && cont!=0){
			return 0;
/*Si no pasa lo primero entonces si se actualiza con nuestra ficha la casilla vacia seleccionada */
		}else{
			//La casilla del tablero de las coordenadas de destino se llena con la pieza
			Tablero[x2][y2] = pieza;
		}
		//Tablero[x2][y2] = pieza;
		gtk_image_set_from_file(GTK_IMAGE(gtk_grid_get_child_at(GTK_GRID(tablero),y2,x2)), imagenes[pieza]);

		//La casilla del tablero con las coordenadas iniciales se vacia
		Tablero[x][y] = 0;
		gtk_image_set_from_file(GTK_IMAGE(gtk_grid_get_child_at(GTK_GRID(tablero),y,x)), imagenes[0]);
		return 10;
	}
	/*Si no esta vacia, puede que sea posible saltar */
	if(!verificar_vacia(x2,y2) ){	//verificar_vacia() retorna falso (0)
		/*Como puede que sea posible saltar, entra en accion la funcion Mov_Salto*/
		p = Mov_Salto(x,y,x2,y2,pieza);
		g_print("\nvalor de p: %d\n",p);
		cont = cont+1;	//cont se incrementa en 1. Cont se puede incrementar hasta 3, que es el numero maximo de saltos consecutivos.
		return p;
	}

}



/*Funcion que se encarga de la coordenadas de destino, depues de ejecutarse la funcion del primer click */
void Click_Dos(int pieza, int x, int y, int x2, int y2){
	int m=0;
	gchar *temp2 = g_strdup_printf("Presiono la casilla coordenada [%d,%d]", x2,y2);
	gtk_label_set_text(GTK_LABEL(click_dos), temp2);
	g_free(temp2);
/*Se verifica que las coordenadas sean las correctas*/
	if(limite_movimiento(x2,y2) && verificar_adyacente(x,y,x2,y2) && Limitacion_Bases(x2,y2,pieza)){

		m=Movimiento(x,y,x2,y2,pieza);
		if(m==10 && B==0 && cont<=1){//Condicion para rotar el turno
			g_print("\nValor movimiento normal %d\n",m);
			rotar_jugador();
		}

	}
	g_print("\n\n B = %d\n cont = %d\n m = %d \n\n",B,cont,m);

}
void Click_saltos(int pieza, int x, int y, int x2, int y2){
	int m=0;
//	if(limite_movimiento(x2,y2) && verificar_adyacente(x,y,x2,y2) && Limitacion_Bases(x2,y2,pieza)){
//		rotar_jugador();
//	}else{
//		m=Movimiento(x,y,x2,y2,pieza);
//
//	}
	/*Condicion para la verificacion, si la coordena es valida;
	 *si lo es, llama a la funcion que se encargar del movimiento respectivo de las fichas */
	if(limite_movimiento(x2,y2) && verificar_adyacente(x,y,x2,y2) && Limitacion_Bases(x2,y2,pieza)){
		m=Movimiento(x,y,x2,y2,pieza);

	}else{
		m=0;
	}



/*si no hay fichas aydacentes a la fichas seleccionada ingresa al if.
 * si la variable m que seria el valor arrojado por movimiento, es 9 o 0, entonces
 * para los saltos ya que se rota ek turno */
	if(B==0||m==9|| m==0){
		rotar_jugador();
		cont=0;
	}
/*Si se ha saltado ya 3 veces, entonces se rota el turno*/
	if(cont==3){
		rotar_jugador();
		cont=0;
	}
	g_print("\n\n B = %d\n cont = %d\n m = %d \n\n",B,cont,m);
}


/*Inicio. Se selecciona la pieza a mover y se guardan sus coordenadas.*/

int Primer_Click(int bando, int x, int y){
	gchar *temp = g_strdup_printf("Presiono la casilla coordenada [%d,%d]", x,y);
	gtk_label_set_text(GTK_LABEL(click_uno), temp);
	g_free(temp);
	/*Verificacion si el usuario realmente selecciono la ficha del bando que le corresponde, ademas
	 * de saber si la casilla seleccionada esta dentro del rango establecido en el juego.
	 * */
    if(verificar_bando(x,y,bando) && limite_movimiento(x,y) && limitacion_Polic(x,y) && limitacion_Suffrag(x,y)){
    	bandera = 1;
    	coor[0] = x;
    	coor[1] = y;
    	g_print("\n OK! \n");
    	return 1;
    }else{
		g_print("\n NOT OK!! \n");
		return 0;
	}
}

