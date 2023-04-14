#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include <cstdlib>
#include <io.h>

//========================================================
//Credenciales de administrador
#define USER "ADMIN"
#define PASS "123"
//========================================================

using namespace std; 
//================ESTRUCTURAS=================================================

//----ESTRUCTURA DE DATOS DE USUSARIO------------------
typedef struct{
	char user_name[50], user_NAME[50], user_pass[50];
	int user_id;
}user_system;
//----ESTRUCTURA DE INFORMACIÓN DE PRODUCTO------------
typedef struct{
	char description[100];
	float price=0, cost=0;
	int code=0,stock=0;
}product;

//============FUNCIONES=======================================================
void lineas(){
	printf("\n---------------------------------------------------");
}
void asterisco(char frase[]){												
    int i=0;
    cout.flush();
    fflush(stdin);
    do{
        frase[i] = (unsigned char)getch();
        fflush(stdin);
        if(frase[i]!=8){
            cout << '*';// muestra por pantalla
            fflush(stdin);
            i++;
        }
        else if(i>0){
            cout << (char)8 << (char)32 << (char)8;
            fflush(stdin);
            i--;//el caracter a borrar e el backspace
        }
        cout.flush();
        fflush(stdin);
    }while(frase[i-1]!=13);// si presiona ENTER
    frase[i-1] = NULL;
    fflush(stdin);
    cout << endl;
    fflush(stdin);
} 
void validar_base_de_datos(){
    FILE *arch;
    int existencia;

    // Verificar archivo de usuarios
    existencia = access("base_de_datos//usuarios.dat", F_OK);
    if (existencia == -1) {
        arch = fopen("base_de_datos//usuarios.dat", "wb");
        if (arch == NULL) {
            printf("Error al crear archivo de usuarios.\n");
            exit(1);
        } else {
            fclose(arch);
        }
    }

    // Verificar archivo de productos
    existencia = access("base_de_datos//productos.dat", F_OK);
    if (existencia == -1) {
        arch = fopen("base_de_datos//productos.dat", "wb");
        if (arch == NULL) {
            printf("Error al crear archivo de productos.\n");
            exit(1);
        } else {
            fclose(arch);
        }
    }
}

int autenticar_usuario(char *usuario, char *contrasenia) {
    FILE *arch;
    user_system usua;
    int encontrado = 0;

    arch = fopen("base_de_datos//usuarios.dat", "rb");
    if (arch == NULL) {
        exit(1);
    }

    while (fread(&usua, sizeof(user_system), 1, arch) == 1) {
        if (strcmp(usuario, usua.user_NAME) == 0 && strcmp(contrasenia, usua.user_pass) == 0) {
            encontrado = 1;
            break;
        }
    }

    fclose(arch);
    return encontrado;
}

void registrar_usuarios(){
	system("cls");
    FILE *arch;
    arch=fopen("base_de_datos//usuarios.dat","ab");

    if (arch==NULL)
		exit(1);
		
    user_system usua;
	fflush(stdin);
	printf("\n Ingrese Nombres y Apellidos: ");
	gets(usua.user_name);
	fflush(stdin);
	printf("\n Ingrese ID del Operador: ");
	scanf("%d",&usua.user_id);
	fflush(stdin);
	printf("\n Ingrese Nombre de Usuario: ");
	gets(usua.user_NAME);
	fflush(stdin);
	printf("\n Registre ContraseÃ±a del Usuario: ");
	gets(usua.user_pass);
	fflush(stdin);
	
    fwrite(&usua, sizeof(user_system), 1, arch);
    fclose(arch);
    printf("\n");
    system("pause");
}
void consultar_usuarios(){
	int c=1;
    FILE *arch;
    arch=fopen("base_de_datos//usuarios.dat","rb");

    if (arch==NULL)
		exit(1);

    user_system usua;
    
    fread(&usua, sizeof(user_system), 1, arch);
    	system("cls");
    while(!feof(arch)){
    	printf("\t\tUSUARIO #%d",c);
    	printf("\n----------------------------------------------");
		printf("\n Nombre y Apellido: %s",usua.user_name);
		printf("\n ID del Usuario: %d",usua.user_id);
		printf("\n Usuario: %s",usua.user_NAME);
		printf("\n ContraseÃ±a del Usuario: %s",usua.user_pass);
		printf("\n----------------------------------------------");
		printf("\n");
        fread(&usua, sizeof(user_system), 1, arch);
        c++;
    }
    
    fclose(arch);
	printf("\n");
    system("pause");
}
void cambiar_password(){
	system("cls");
    FILE *arch;
    arch=fopen("base_de_datos//usuarios.dat","r+b");

    if (arch==NULL)
        exit(1);

    int ID, existe=0;

    printf("Ingrese el ID del Usuario: ");
    fflush(stdin);
    scanf("%d",&ID);
    
    user_system usua;
    fread(&usua, sizeof(user_system), 1, arch);
    
    while(!feof(arch)){
        if (ID==usua.user_id){
           fflush(stdin);
           printf("\n Usuario: %s",usua.user_NAME);
		   printf("\n Nombre y Apellido: %s",usua.user_name);
	   	   printf("\n ID del Usuario: %d",usua.user_id);
           printf("\n Ingrese nueva Contraseña: ");
           gets(usua.user_pass);
           fflush(stdin);
           int pos=ftell(arch)-sizeof(user_system);
           fseek(arch,pos,SEEK_SET);
           fwrite(&usua, sizeof(user_system), 1, arch);
           printf("\n Contraseña Cambiada Exitosamente!");
           existe=1;
           break;
        }
        fread(&usua, sizeof(user_system), 1, arch);
    }
    if (existe==0)
        printf("No existe Usuario!");
        
    fclose(arch);
	printf("\n");
    system("pause");
}

void eliminar_usuario() {
    system("cls");
    FILE *arch;
    FILE *temp;
    arch = fopen("base_de_datos//usuarios.dat", "rb");
    temp = fopen("base_de_datos//temp.dat", "wb");
    if (arch == NULL || temp == NULL) {
        printf("\nError al abrir archivo!");
        exit(1);
    }
    int ID, existe = 0;
    printf("Ingrese el ID del Usuario que desea eliminar: ");
    fflush(stdin);
    scanf("%d", &ID);
    user_system usua;
    fread(&usua, sizeof(user_system), 1, arch);
    while (!feof(arch)) {
        if (ID == usua.user_id) {
            existe = 1;
            printf("\nUsuario eliminado: %s", usua.user_NAME);
        } else {
            fwrite(&usua, sizeof(user_system), 1, temp);
        }
        fread(&usua, sizeof(user_system), 1, arch);
    }
    if (existe == 0) {
        printf("\nNo existe Usuario!");
    }
    fclose(arch);
    fclose(temp);
    remove("base_de_datos//usuarios.dat");
    rename("base_de_datos//temp.dat", "base_de_datos//usuarios.dat");
    printf("\n");
    system("pause");
}


void registrar_productos(){
	system("cls");
    FILE *arch;
    arch=fopen("base_de_datos//productos.dat","a+b");

    if (arch==NULL)
		exit(1);
		
    product pr;
	printf("\n Código del Producto: ");
	scanf("%d",&pr.code);
	fflush(stdin);
	printf("\n Descripción: ");
	gets(pr.description);
	fflush(stdin);
	printf("\n Cantidad: ");
	scanf("%d",&pr.stock);
	fflush(stdin);
	printf("\n Costo del Producto por Unidad: ");
	scanf("%f", &pr.cost);
	fflush(stdin);
	printf("\n Precio del Producto por Unidad: ");
	scanf("%f", &pr.price);
	fflush(stdin);
	
    fwrite(&pr, sizeof(product), 1, arch);
    fclose(arch);
    printf("\n");
    system("pause");
}
void ingreso_stock(){
	system("cls");
    FILE *arch;
    arch=fopen("base_de_datos//productos.dat","r+b");

    if (arch==NULL)
        exit(1);

    int code=0, existe=0, ingreso=0;
	float total=0, p_total=0;

    printf("\n Código de Producto: ");
    fflush(stdin);
    scanf("%d",&code);
    product pr;
    fread(&pr, sizeof(product), 1, arch);
    
    while(!feof(arch)){
        if (code==pr.code){
           fflush(stdin);
           total=pr.cost*pr.stock;
           printf("\n ***%s***",pr.description);
           printf("\n-------------------------------------");
           printf("\n Stock:*************** %d",pr.stock);
		   printf("\n Total Inventario:*** $%.2f",total);
		   printf("\n-------------------------------------");
		   printf("\n");
		   system("pause");
           printf("\n Cantidad a Ingresar: ");
           scanf("%d",&ingreso);
           pr.stock=pr.stock+ingreso;
           fflush(stdin);
           total=pr.cost*pr.stock;
           fflush(stdin);
           p_total=pr.price*pr.stock;
           fflush(stdin);
		   printf("\n ***%s***",pr.description);
           printf("\n-------------------------------------");
           printf("\n Stock Actual:******** %d",pr.stock);
		   printf("\n Costo Total:******** $%.2f",total);
		   printf("\n Precio Total:******* $%.2f",p_total);
		   printf("\n-------------------------------------");
           fflush(stdin);
           
           int pos=ftell(arch)-sizeof(product);
           fseek(arch,pos,SEEK_SET);
           fwrite(&pr, sizeof(product), 1, arch);
           printf("\n OperaciÃ³n Realizada Exitosamente!");
           existe=1;
           break;
        }
        fread(&pr, sizeof(product), 1, arch);
    }
    if (existe==0)
        printf("No existe Usuario!");
        
    fclose(arch);
	printf("\n");
    system("pause");
}
void lista_productos(){
	float c_total=0, p_total=0, pti=0, cti=0;
    FILE *arch;
    arch=fopen("base_de_datos//productos.dat","rb");

    if (arch==NULL)
		exit(1);

    product pr;
    
    fread(&pr, sizeof(product), 1, arch);
    	system("cls"); 	
    
	while(!feof(arch)){
	   c_total=0,p_total=0;
	   c_total=pr.cost*pr.stock;
       p_total=pr.price*pr.stock;
	   printf("\n-------------------------------------------");
	   printf("\n Descripción: %s",pr.description);
	   printf("\n Código: %d",pr.code);
       printf("\n Stock:*************** %d",pr.stock);
	   printf("\n Costo Unitario:***** $%.2f",pr.cost);
	   printf("\n Precio Unitario:**** $%.2f",pr.price);
	   printf("\n Costo Total:*********$%.2f",c_total);
	   printf("\n Precio Total:********$%.2f",p_total);
	   printf("\n-------------------------------------------");
	   printf("\n");
	   cti=cti+c_total;
	   pti=pti+p_total;
       fread(&pr, sizeof(product), 1, arch);  	
	}
	   printf("\n===========================================");
	   printf("\n COSTO TOTAL DEL INVENTARIO:***** $%.2f",cti);
	   printf("\n PRECIO TOTAL DEL INVENTARIO:**** $%.2f",pti);
	   printf("\n===========================================");
    
    fclose(arch);
	printf("\n");
    system("pause");
}
void consultar_productos(){
	system("cls");
    FILE *arch;
    arch=fopen("base_de_datos//productos.dat","r+b");

    if (arch==NULL)
        exit(1);

    int code=0, existe=0;

    printf("\n Código de Producto: ");
    fflush(stdin);
    scanf("%d",&code);
    
    product pr;
    fread(&pr, sizeof(product), 1, arch);
    
    while(!feof(arch)){
        if (code==pr.code){
           fflush(stdin);
		   printf("\n-------------------------------------------");
		   printf("\n Descripción: %s",pr.description);
		   printf("\n Código: %d",pr.code);
           printf("\n Stock:*************** %d",pr.stock);
		   printf("\n Precio:************* $%.2f",pr.price);
		   printf("\n-------------------------------------------");
		   existe=1;
           break;
        }
        fread(&pr, sizeof(product), 1, arch);
    }
    if (existe==0)
        printf("Producto No Existe!");
    fclose(arch);
	printf("\n");
    system("pause");
}
void actualizar_precios(){
	system("cls");
    FILE *arch;
    arch=fopen("base_de_datos//productos.dat","r+b");

    if (arch==NULL)
        exit(1);

    int code=0, existe=0;

    printf("Código de Producto: ");
    scanf("%d",&code);
    fflush(stdin);
    
    product pr;
    fread(&pr, sizeof(product), 1, arch);
    
    while(!feof(arch)){
        if (code==pr.code){
           fflush(stdin);
           printf("\n-------------------------------------");
           printf("\n Descripción: %s",pr.description);
           printf("\n Código: %d",pr.code);
		   printf("\n Precio:******** $%.2f",pr.price);
		   printf("\n-------------------------------------");
           printf("\n Nuevo Precio: ");
           scanf("%f",&pr.price);
           fflush(stdin);
           int pos=ftell(arch)-sizeof(user_system);
           fseek(arch,pos,SEEK_SET);
           fwrite(&pr, sizeof(product), 1, arch);
           printf("\n Cambio de Precio Exitoso!");
           existe=1;
           break;
        }
        fread(&pr, sizeof(product), 1, arch);
    }
    if (existe==0)
        printf("No Existe Producto!");
        
    fclose(arch);
	printf("\n");
    system("pause");
}

//===============INICIO DEL PROGRAMA========================================================================================================
int main(int argc,char* argv[]){
	setlocale(LC_ALL,"spanish");
	
//=============DECLARAR VARIABLES A USAR===========================================
	int main_option=0, back_to_menu=0, num_users=0, num_clients=0, menu_adm_us=0;//--VARIABLES ENTERAS PARA SELECCIONADOR DE MENUS
	int i=0, j=0, k=0, si;//-------------------------------------------------------------VARIABLES ENTERAS DE ITERACIÓN
	int compP=1, compU=1;//-----------------------VARIABLES ENTERAS PARA VALIDAR CREDENCIALES
	char validate_user[50], validate_pass[50];//----------------VARIABLES CHAR PARA INGRESAR CREDENCIALES
	
//==============INICIO DE SESIÓN PARA INGRESAR AL PROGRAMA=========================
	init:
	validar_base_de_datos();
	int validate=0, menu=0;
	
	do{
		validate=0;
		system("cls");
		fflush(stdin);
		printf("\n ***INICIO DE SESIÓN*** ");
		printf("\n Usuario: ");
		gets(validate_user);
		fflush(stdin);
		printf("\n Contraseña: ");
		asterisco(validate_pass);
		fflush(stdin);
		printf("\n");

		if (strcmp(validate_user, USER) == 0 && strcmp(validate_pass, PASS) == 0) {
		    printf("\n****Bienvenido Administrador/a**** ");
		    printf("\n\n");
		    system("pause");
		    validate =1;
		    menu = 1;
		} else if (autenticar_usuario(validate_user, validate_pass)) {
		    printf("\n****Bienvenido Usuario****");
		    printf("\n\n");
		    system("pause");
		    validate=1;
		    menu = 2;
		} else {
		    printf("\n Usuario y/o Contraseña Incorrecto!");
		    printf("\n\n");
		    system("pause");
		}
	} while ( validate == 0);
	
//==========IR A LOS MENUS CORRESPONDIENTES================
	if(menu == 1){
		goto admin_menu;
	}
	if(menu == 2){
		goto user_menu;
	}
	
//=============MENU DEL ADMINISTRADOR========================================================================================================
	admin_menu:
	char user[50];
	strcpy(user,validate_user);
	system("cls");
	printf("\n Bienvenido!");
	printf("\n 1. Administrar Usuarios");
	printf("\n 2. Ingresar al inventario");
	printf("\n 3. Cerrar Sesión");
	printf("\n 4. Salir");
	printf("\n");
	printf("\n Opción: ");
	scanf("%d",&main_option);
	
	if(main_option<=0 || main_option>4) {
		printf("Opción Inválida!");
		system("pause");
	}
	switch(main_option){
		case 1:
			menu1:
			system("cls");
			printf("\n ADMINISTRADOR DE USUARIOS");
			printf("\n 1. Registrar Usuario");
			printf("\n 2. Consultar Usuarios");
			printf("\n 3. Cambiar Contraseña de Usuario");
			printf("\n 4. Eliminar Usuario");
			printf("\n 5. Regresar al Menú Principal");
			printf("\n Opción: ");
			scanf("%d",&i);
			switch(i){
				case 1: registrar_usuarios();
						goto menu1;
						break;
				case 2: consultar_usuarios();
						goto menu1;
						break;
				case 3: cambiar_password();
						goto menu1;
						break;
				case 4:  eliminar_usuario();
						goto menu1;
				case 5: goto admin_menu;
						break;
				default: goto menu1;
			}	
		case 2:
			menu2:
			system("cls");
			printf("\n MENÚ DE INVENTARIO");
			printf("\n 1. Registrar Producto Nuevo");
			printf("\n 2. Ingreso De Stock");
			printf("\n 3. Consultar Lista de Productos");
			printf("\n 4. Consultar Productos por Código");
			printf("\n 5. Actualizar Precio de Producto");
			printf("\n 6. Regresar al Menú Principal");
			printf("\n Opción: ");
			scanf("%d",&k);
			switch(k){
				case 1: registrar_productos();
						goto menu2;
						break;
				case 2: ingreso_stock();
						goto menu2;
						break;
				case 3: lista_productos();
						goto menu2;
						break;
				case 4: consultar_productos();
						goto menu2;
						break;
				case 5: actualizar_precios();
						goto menu2;
						break;
				case 6: goto admin_menu;
						break;
				default: goto menu2;
			}
			goto admin_menu;
		case 3:
			printf("Cerrando Sesión...\n");
			system("pause");
			goto init;
		case 4:
			system("cls");
			printf("\n ¿Realmente desea Salir del Programa?");
			printf("\n 1. SI");
			printf("\n 2. NO");
			do{
				printf("\n Opción: ");
				scanf("%d",&si);
				if(si==1){
				printf("Saliendo del Programa...\n");
				system("pause");	
				exit(1);
				}else if(si==2){
					system("pause");
					goto admin_menu;
				}else{
					printf("\n Opción Inválida!");
				}
			}while(si>=1 && si<3);
		default: goto admin_menu;
	}	
//================MENU DE USUARIO================================================================================================================
	user_menu:
	strcpy(user,validate_user);
	system("cls");
	printf("\n Bienvenido!");
	printf("\n 1. Consultar Producto");
	printf("\n 2. Cerrar Sesión");
	printf("\n 3. Salir");
	printf("\n");
	printf("\n Opción: ");
	scanf("%d",&j);
	switch(j){
		case 1: consultar_productos();
				system("pause");
				goto user_menu;
				break;
		case 2:printf("Cerrando Sesión...\n");
				system("pause");
				goto init;
		case 3:
			system("cls");
			printf("\n ¿Realmente desea Salir del Programa?");
			printf("\n 1. SI");
			printf("\n 2. NO");
			do{
				printf("\n Opción: ");
				scanf("%d",&si);
				if(si==1){
				printf("Saliendo del Programa...\n");
				system("pause");	
				exit(1);
				}else if(si==2){
					system("pause");
					goto user_menu;
				}else{
					printf("\n Opción Inválida!");
				}
			}while(si>=1 && si<3);
		default: goto user_menu;
	}
	system("pause");
	
	getch();
}
