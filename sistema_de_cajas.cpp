#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include <cstdlib>

//========================================================
#define USER "ELI"//USUARIO ADMINISTRADOR!	//
#define PASS "112471"//CONTRASEÑA MAESTRA!	//
//========================================================

using namespace std; 
//================ESTRUCTURAS=================================================
//----ESTRUCTURA DE DATOS DE USUSARIO------------------
typedef struct{
	char user_name[50], user_NAME[50], user_pass[50];
	int user_id;
}user_system;
//----ESTRUCTURA DE DATOS DE CLIENTE-------------------
typedef struct{
	char name[50], address[50], phone[50], fecha_n[50], email[50];
	int client_id=0;
}client; 
//----ESTRUCTURA DE INFORMACIÓN DE PRODUCTO------------
typedef struct{
	char description[100];
	float price=0, cost=0;
	int code=0,stock=0;
}product;
//----ESTRUCTURA DE DATOS DE FACTURA-------------------
typedef struct{
	int num_fact=0, id_user=0, id_client=0;
	char date[50], compras[];
}factura;
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
void crear_facturas(){
    FILE *arch;
    arch=fopen("base_de_datos//facuras.dat","wb");
    if (arch==NULL)
		exit(1);
	//printf("\n Borrado Exitoso...");
	printf("\n");
	system("pause");
    fclose(arch);
}
void crear_usuarios(){
    FILE *arch;
    arch=fopen("base_de_datos//usuarios.dat","wb");
    if (arch==NULL)
		exit(1);
	printf("\n Borrado Exitoso...");
	printf("\n");
	system("pause");
    fclose(arch);
    
}
void crear_clientes(){
    FILE *arch;
    arch=fopen("base_de_datos//clientes.dat","wb");
    if (arch==NULL)
		exit(1);
	printf("\n Borrado Exitoso...");
	printf("\n");
	system("pause");
    fclose(arch);
}
void crear_productos(){
    FILE *arch;
    arch=fopen("base_de_datos//productos.dat","wb");
    if (arch==NULL)
		exit(1);
	printf("\n Borrado Exitoso...");
	printf("\n");
	system("pause");
    fclose(arch);
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
	printf("\n Registre Contraseña del Usuario: ");
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
		printf("\n Contraseña del Usuario: %s",usua.user_pass);
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
void registrar_clientes(){
	fflush(stdin);
	system("cls");
    FILE *arch;
    arch=fopen("base_de_datos//clientes.dat","ab");

    if (arch==NULL)
		exit(1);
		
    client cl;
	printf("\n Nombres y Apellidos: ");
	gets(cl.name);
	fflush(stdin);
	printf("\n Ingrese ID: ");
	scanf("%d",&cl.client_id);
	fflush(stdin);
	printf("\n Teléfono: ");
	gets(cl.phone);
	fflush(stdin);
	printf("\n Correo: ");
	gets(cl.email);
	fflush(stdin);
	printf("\n Dirección: ");
	gets(cl.address);
	fflush(stdin);
	printf("\n Fecha de Nacimiento: ");
	gets(cl.fecha_n);
	fflush(stdin);
	
    fwrite(&cl, sizeof(client), 1, arch);
    fclose(arch);
    printf("\n");
    system("pause");
}
void consultar_clientes(){
	int c=1;
    FILE *arch;
    arch=fopen("base_de_datos//clientes.dat","rb");

    if (arch==NULL)
		exit(1);

    client cl;
    
    fread(&cl, sizeof(client), 1, arch);
    	system("cls");
    while(!feof(arch)){
    	printf("\t\tCLIENTE #%d",c);
    	printf("\n----------------------------------------------");
		printf("\n Nombres y Apellidos: %s",cl.name);
		printf("\n ID: %d",cl.client_id);
		printf("\n Teléfono: %s",cl.phone);
		printf("\n Correo: %s",cl.email);
		printf("\n Dirección: %s",cl.address);
		printf("\n Fecha de Nacimiento: %s",cl.fecha_n);
		printf("\n----------------------------------------------");
		printf("\n");
        fread(&cl, sizeof(client), 1, arch);
        c++;
    }
	    
    fclose(arch);
	printf("\n");
    system("pause");
}
void buscar_por_id(){
	system("cls");
    FILE *arch;
    arch=fopen("base_de_datos//clientes.dat","r+b");

    if (arch==NULL)
        exit(1);

    int ID, existe=0;

    printf("Ingrese el ID:");
    fflush(stdin);
    scanf("%d",&ID);
    
    client cl;
    fread(&cl, sizeof(client), 1, arch);
    
    while(!feof(arch)){
        if (ID==cl.client_id){
            fflush(stdin);
			printf("\n----------------------------------------------");
			printf("\n Nombres y Apellidos: %s",cl.name);
			printf("\n ID: %d",cl.client_id);
			printf("\n Teléfono: %s",cl.phone);
			printf("\n Correo: %s",cl.email);
			printf("\n Dirección: %s",cl.address);
			printf("\n Fecha de Nacimiento: %s",cl.fecha_n);
			printf("\n----------------------------------------------");
           	existe=1;
           break;
        }
        fread(&cl, sizeof(client), 1, arch);
    }
    if (existe==0)
        printf("Cliente No Registrado!");
    fclose(arch);
	printf("\n");
    system("pause");
}
void actualizar_datos(){
	system("cls");
    FILE *arch;
    arch=fopen("base_de_datos//clientes.dat","r+b");

    if (arch==NULL)
        exit(1);

    int ID, existe=0, si=0;

    printf("Ingrese el ID: ");
    fflush(stdin);
    scanf("%d",&ID);
    
    client cl;
    fread(&cl, sizeof(client), 1, arch);
    
    while(!feof(arch)){
        if (ID==cl.client_id){
           fflush(stdin);
           	printf("\n----------------------------------------------");
			printf("\n Nombres y Apellidos: %s",cl.name);
			printf("\n ID: %d",cl.client_id);
			printf("\n----------------------------------------------");
			printf("\n Continuar?");
			printf("\n 1. SI\n 2.NO");
			printf("\n Opción: ");
			scanf("%d",&si);
			if(si==1){
				system("cls");
		       	printf("\n Nombres y Apellidos: ");
				gets(cl.name);
				fflush(stdin);
				printf("\n Ingrese ID: ");
				scanf("%d",&cl.client_id);
				fflush(stdin);
				printf("\n Teléfono: ");
				gets(cl.phone);
				fflush(stdin);
				printf("\n Correo: ");
				gets(cl.email);
				fflush(stdin);
				printf("\n Dirección: ");
				gets(cl.address);
				fflush(stdin);
				printf("\n Fecha de Nacimiento: ");
				gets(cl.fecha_n);
				fflush(stdin);
		
		       	int pos=ftell(arch)-sizeof(client);
		       	fseek(arch,pos,SEEK_SET);
		       	fwrite(&cl, sizeof(client), 1, arch);
		       	printf("\n");
		       	printf("\n Datos Actualizados Exitosamente!");
		       	existe=1;
		       	break;
			}else if(si==2){
				break;
			}
			
        }
        fread(&cl, sizeof(client), 1, arch);
    }
    if (existe==0)
        printf("No existe Usuario!");
        
    fclose(arch);
	printf("\n");
    system("pause");
}
void registrar_productos(){
	system("cls");
    FILE *arch;
    arch=fopen("base_de_datos//productos.dat","r+b");

    if (arch==NULL)
		exit(1);
		
    product pr;
	printf("\n Código del Producto: ");
	scanf("%d",&pr.code);
	fflush(stdin);
	printf("\n Descripición: ");
	gets(pr.description);
	fflush(stdin);
	printf("\n Cantidad: ");
	scanf("%d",&pr.stock);
	fflush(stdin);
	printf("\n Costo del Producto por Unidad: ");
	cin>>pr.cost;
	fflush(stdin);
	printf("\n Precio del Producto por Unidad: ");
	cin>>pr.price;
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

    printf("\n Código: ");
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
           printf("\n Operación Realizada Exitosamente!");
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

    printf("\n Código: ");
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

    printf("Código: ");
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
void borrar_productos(){
    FILE *arch;
    arch=fopen("base_de_datos//productos.dat","r+b");
    if (arch==NULL)
        exit(1);
    printf("\n Código: ");
    int cod, si;
    scanf("%i", &cod);
    product pr;
    int existe=0;
    fread(&pr, sizeof(product), 1, arch);
    while(!feof(arch)){
        if (cod==pr.code){
           printf("\n-------------------------------------------");
		   printf("\n Descripción: %s",pr.description);
		   printf("\n Código: %d",pr.code);
           printf("\n Stock:*************** %d",pr.stock);
		   printf("\n Precio:************* $%.2f",pr.price);
		   printf("\n-------------------------------------------");
		   printf("\n");
           printf("¿Está Seguro de Eliminar el Producto?");
           printf("\n 1. SI\n 2. NO");
           printf("\n Opción: ");
           scanf("%d",&si);
           if(si==1){
	           int pos=ftell(arch)-sizeof(product);
	           fseek(arch,pos,SEEK_SET);
	           fwrite(&pr, sizeof(product), 1, arch);
	           printf("\n Se ha borrado el Producto...");
	           existe=1;
	           break;
		   }else{
		   	printf("Proceso Cancelado!");
		   	system("pause");
		   	break;
		   }
           
        }
        fread(&pr, sizeof(product), 1, arch);
    }
    if (existe==0)
        printf("Producto No Existe!");
    fclose(arch);
    printf("\n");
    system("pause");
}
void cliente_factura(){
	fflush(stdin);
	int ID=0, existe=0;
	FILE *arch;
    arch=fopen("base_de_datos//clientes.dat","r+b");
    
    client cl;
    fread(&cl, sizeof(client), 1, arch);
    inicio:
    printf("\n Cédula o RUC: "); scanf("%d",&ID);
    lineas();
	fflush(stdin);
	while(!feof(arch)){
        if(ID==cl.client_id){
           lineas();
           printf("\n Nombre:   %s",cl.name);
           printf("\n Teléfono: %s",cl.phone);
           existe=1;
           break;
        }
			fread(&cl, sizeof(client), 1, arch);
	}
	if (existe==0){
	 	   printf("Cliente No Registrado!");
		   system("pause");
		   registrar_clientes();
		   goto inicio;		
	}   
    
    fclose(arch);
}
void producto_factura(){
	float p_total=0, sub_total=0, iva=0, total=0;
	int codigo=0, cant_p, code_f=0;
	int code=0, existe=0, ingreso=0;
	
    FILE *arch;
    arch=fopen("base_de_datos//productos.dat","r+b");

    if (arch==NULL)
        exit(1);

    printf("\n|Código: ");
    fflush(stdin);
    scanf("%d",&code);
    product pr;
    fread(&pr, sizeof(product), 1, arch);
    
    while(!feof(arch)){
        if (code==pr.code){
           	   fflush(stdin);
			   printf("\n|Descripción: %.*s",15,pr.description);
			   printf("|Cantidad: "); scanf("%i",cant_p);
			   fflush(stdin);
			   fread(&pr, sizeof(product), 1, arch);
			   if(cant_p<pr.stock){
			   		pr.stock=(pr.stock - cant_p);
					printf("|PrecioUnit:  $%.2f",pr.price);
				    p_total=(cant_p * pr.price);
				    printf("|PrecioTotal: $%.2f|",p_total);
			   }else{
			   		printf("\n Artículo no disponible!");
			   }
			   
			   int pos=ftell(arch)-sizeof(product);
		       fseek(arch,pos,SEEK_SET);
		       fwrite(&pr, sizeof(product), 1, arch);
		       sub_total=sub_total+p_total;
			   lineas();
			   existe=1;
			   break;
		   
        }
        fread(&pr, sizeof(product), 1, arch);
    }
    if(existe==0 || codigo!=pr.code){
	printf("\n Cancelando Proceso de Factura...");
	printf("\n");
	system("pause");
	}
	printf("\n Sub Total******************************* $%.2f",sub_total);
	iva=sub_total*0.12;
	total=iva+sub_total;
	printf("\n I.V.A (12%%)**************************** $%.2f",iva);
	printf("\n Total a Pagar*************************** $%.2f",total);
        
    fclose(arch);
}

//LPTM!!!! SON MUCHAS FUNCIONES Y AUN FALTAN! :c
//=============================================================================


//====================================================================================================================================
int main(int argc,char* argv[]){
	setlocale(LC_ALL,"spanish");
	
	time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    char output[128];
	strftime(output,128,"\n Fecha:   %d/%m/%y \n Hora:    %H:%M:%S",tlocal);
	
//=============DECLARAR VARIABLES A USAR===========================================
	int main_option=0, back_to_menu=0, num_users=0, num_clients=0, menu_adm_us=0;//--VARIABLES ENTERAS PARA SELECCIONADOR DE MENUS
	int i=0, j=0, k=0, si;//-------------------------------------------------------------VARIABLES ENTERAS DE ITERACIÓN
	int compP=1, compU=1;//-----------------------VARIABLES ENTERAS PARA VALIDAR CREDENCIALES
	char validate_user[50], validate_pass[50];//----------------VARIABLES CHAR PARA INGRESAR CREDENCIALES
	
//===============INICIO DEL PROGRAMA========================================================================================================

//==============INICIO DE SESIÓN PARA INGRESAR AL PROGRAMA=========================
	init:
	int wrong_pass, comp, comp2, validate=0;
	do{
		fflush(stdin);
		FILE *arch;
    	arch=fopen("base_de_datos//usuarios.dat","rb");
    	if (arch==NULL)
			exit(1);
			
	    user_system usua;
	    
		system("cls");
		fflush(stdin);
		printf("\n ***INICIO DE SESIÓN*** ");
		printf("\n Usuario: ");
		gets(validate_user);
		fflush(stdin);
		printf("\n Contraseña: ");
		asterisco(validate_pass);
		fflush(stdin);
		compU=strcmp(validate_user,USER);
		compP=strcmp(validate_pass,PASS);
    	comp =strcmp(validate_pass,usua.user_pass);
    	comp2=strcmp(validate_user,usua.user_NAME);
    	fread(&usua, sizeof(user_system), 1, arch);
    	while(!feof(arch)){
        	if(comp==0 && comp2==0){
				validate=1;
        	}
        fread(&usua, sizeof(user_system), 1, arch);
    	}
    	wrong_pass=compU+compP;
		if(compU==0 && compP==0){
			printf("\n****Bienvenido Administrador/a**** ");
			printf("\n");
			printf("\n");
			system("pause");
			goto admin_menu;
		}else if(validate==1){
			printf("\n****Bienvenido(a) Sr(a): %s****",usua.user_name);
			printf("\n");
			printf("\n");
			system("pause");
			goto user_menu;
			fclose(arch);
		}if(wrong_pass!=0 || validate==0){
			system("cls");
			printf("\n Usuario y/o Contraseña Incorrecto!");
			printf("\n");
			system("pause");
		}
	}while(wrong_pass!=0 || validate==0);
//=============MENU DEL ADMINISTRADOR========================================================================================================
	admin_menu:
	char user[50];
	strcpy(user,validate_user);
	system("cls");
	printf("\n Bienvenido!");
	printf("\n 1. Sistema de Facturas");
	printf("\n 2. Administrar Usuarios");
	printf("\n 3. Administrar Clientes");
	printf("\n 4. Ingresar al inventario");
	printf("\n 5. Borrar Registros");
	printf("\n 6. Cerrar Sesión");
	printf("\n 7. Salir");
	printf("\n");
	printf("\n Opción: ");
	scanf("%d",&main_option);
	//strcpy(output);
	if(main_option<=0 || main_option>7) {
		printf("Opción Inválida!");
		system("pause");
	}
	switch(main_option){
		case 1:{
			menu1:
			system("cls");
		    FILE *arch;
		    arch=fopen("base_de_datos//facturas.dat","wb");
		    
		    factura fact;
		    
		    if (arch==NULL)
				exit(1);
			fwrite(&fact, sizeof(factura), 1, arch);
				
		    fact.num_fact=fact.num_fact+1;
		    printf("\n---------------------------------------------------");
		    printf("\n              ****TIENDA****");
		    printf("\n               LA VENTURA");
		    printf("\n             BABHOYO-ECUADOR");
		    printf("\n            FACTURA N° %04d",fact.num_fact);
		    printf("\n---------------------------------------------------");	
			printf("\n Usuario: %s",user);
			printf("%s",output);
		    printf("\n---------------------------------------------------");
		   	cliente_factura();
			printf("\n---------------------------------------------------");
			producto_factura();
			printf("\n---------------------------------------------------");
			printf("\n             Muchas Gracias Por Su Compra");
			printf("\n                   Vuelva Pronto");
			printf("\n---------------------------------------------------");
			printf("\n                    ELIAS CANDO");
			printf("\n                       2021");
			fclose(arch);
			goto admin_menu;
		}
		case 2:
			menu2:
			system("cls");
			printf("\n ADMINISTRADOR DE USUARIOS");
			printf("\n 1. Registrar Usuario");
			printf("\n 2. Consultar Usuarios");
			printf("\n 3. Cambiar Contraseña de Usuario");
			printf("\n 4. Regresar al Menú Principal");
			printf("\n Opción: ");
			scanf("%d",&i);
			switch(i){
				case 1: registrar_usuarios();
						goto menu2;
						break;
				case 2: consultar_usuarios();
						goto menu2;
						break;
				case 3: cambiar_password();
						goto menu2;
						break;
				case 4: goto admin_menu;
						break;
				default: goto menu2;
			}
			
		case 3:
			menu3:
			system("cls");
			printf("\n ADMINISTRADOR DE CLIENTES");
			printf("\n 1. Registrar Cliente");
			printf("\n 2. Consultar Lista Total Clientes");
			printf("\n 3. Buscar Cliente por ID");
			printf("\n 4. Actualizar Datos");
			printf("\n 5. Regresar al Menú Principal");
			printf("\n Opción: ");
			scanf("%d",&j);
			switch(j){
				case 1: registrar_clientes();
						goto menu3;
						break;
				case 2: consultar_clientes();
						goto menu3;
						break;
				case 3: buscar_por_id();
						goto menu3;
						break;
				case 4: actualizar_datos();
						goto admin_menu;
						break;
				case 5: goto admin_menu;
						break;
				default: goto menu3;
			}
		case 4:
			menu4:
			system("cls");
			printf("\n MENÚ DE INVENTARIO");
			printf("\n 1. Registrar Producto Nuevo");
			printf("\n 2. Ingreso De Stock");
			printf("\n 3. Consultar Lista de Productos");
			printf("\n 4. Consultar Productos por Código");
			printf("\n 5. Actualizar Precio de Producto");
			printf("\n 6. Eliminar Un Producto");
			printf("\n 7. Regresar al Menú Principal");
			printf("\n Opción: ");
			scanf("%d",&k);
			switch(k){
				case 1: registrar_productos();
						goto menu4;
						break;
				case 2: ingreso_stock();
						goto menu4;
						break;
				case 3: lista_productos();
						goto menu4;
						break;
				case 4: consultar_productos();
						goto menu4;
						break;
				case 5: actualizar_precios();
						goto menu4;
						break;
				case 6: borrar_productos();
						goto menu4;
						break;
				case 7: goto admin_menu;
						break;
				default: goto menu4;
			}
			goto admin_menu;
		case 5:
			do{
				system("cls");
				fflush(stdin);
				printf("\n ***CONFIRMAR CONTRASEÑA*** ");
				printf("\n Contraseña: ");
				fflush(stdin);
				asterisco(validate_pass);
				compP=strcmp(validate_pass,PASS);
				if(compP==0){
					printf("\n Acceso Concedido...");
					printf("\n");
					system("pause");
					goto menu_crear;
				}else{
					printf("\n Acceso Denegado!");
					printf("\n");
					system("pause");
				}
			}while(comp!=0);
			menu_crear:
			system("cls");
			printf("\n BORRAR REGISTROS");
			printf("\n 1. Usuarios");
			printf("\n 2. Clientes");
			printf("\n 3. Inventario");
			printf("\n 4. Regresar al Menú Principal");
			printf("\n Opcion: ");
			scanf("%d",&i);
			switch(i){
				case 1: crear_usuarios();
						goto menu_crear;
				case 2: crear_clientes();
						goto menu_crear;
				case 3: crear_productos();
						goto menu_crear;
				case 4: goto admin_menu;
						break;
				default: goto menu_crear;
			}
			system("pause");
		case 6:
			printf("Cerrando Sesión...\n");
			system("pause");
			goto init;
		case 7:
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
	printf("\n 1. Sistema de Facturas");
	printf("\n 2. Registrar Cliente");
	printf("\n 3. Consultar Producto");
	printf("\n 4. Cerrar Sesión");
	printf("\n 5. Salir");
	printf("\n");
	printf("\n Opcion: ");
	scanf("%d",&j);
	switch(j){
		case 1: {
				system("cls");
			    FILE *arch;
			    arch=fopen("base_de_datos//facturas.dat","wb");
			    
			    factura fact;
			    
			    if (arch==NULL)
					exit(1);
				fwrite(&fact, sizeof(factura), 1, arch);
					
			    fact.num_fact=fact.num_fact+1;
			    printf("\n---------------------------------------------------");
			    printf("\n              ****TIENDA****");
			    printf("\n                LA VENTURA");
			    printf("\n             BABHOYO-ECUADOR");
			    printf("\n            FACTURA N° %04d",fact.num_fact);
			    printf("\n---------------------------------------------------");	
				printf("\n Usuario: %s",user);
				printf("%s",output);
			    printf("\n---------------------------------------------------");
			   	cliente_factura();
				printf("\n---------------------------------------------------");
				producto_factura();
				printf("\n---------------------------------------------------");
				printf("\n             Muchas Gracias Por Su Compra");
				printf("\n                   Vuelva Pronto");
				printf("\n---------------------------------------------------");
				printf("\n                    ELIAS CANDO");
				printf("\n                       2021");
				fclose(arch);
				goto user_menu;
				break;
				}
		case 2: registrar_clientes();
				system("pause");
				goto user_menu;
				break;
		case 3: consultar_productos();
				system("pause");
				goto user_menu;
				break;
		case 4:printf("Cerrando Sesión...\n");
				system("pause");
				goto init;
		case 5:
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
