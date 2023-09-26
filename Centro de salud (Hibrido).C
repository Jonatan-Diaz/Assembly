#include<stdio.h>
#include<stdlib.h>

//variables del programa
int menu, enfermos, cantidad, costoTotal, cuotas;

//scripts de ensamblador
//script 1: hacer gráficos con la interrupción 10
void dibujarCruz(){	
	asm{
		mov ax,0600h
   		mov bh,47h
    		mov cx,0324h
    		mov dh,22
    		mov dl,44
    		int 10h         
    	
    		mov ax,0600h
   		mov bh,47h
    		mov cx,0919h
    		mov dh,12
    		mov dl,55
    		int 10h 
	}
}

//script 2: para limpiar la pantalla
void limpiarPantalla(){	
	asm{	
		mov ax,0600h                   
    		mov bh,07h           
    		mov cx,00h
    		mov dh,25h
    		mov dl,80h              
    		int 10h
	}
}

//script 3: para imprimir caracteres especiales
void imprimirCaracter(int c){	
	asm{ 
		mov ah, 02h 
		mov dx, c 
		int 21h
	}
}

//script 4: para cambiar de color las letras de las entradas
void colorDeEntrada(){
	asm{	
		mov ax,0600h
             	mov bh,1010b           
             	mov cx,00h
	     	mov dx,175fh
             	int 10h 
	}
}

//script 5: para introducir un valor (en el registro al) sin mostrarse a menos que sea un numero
void entradaNoVisible(){
	asm{
		mov ah,07	
    		int 21h
	}
}

//script 8: para terminar el programa
void terminarPrograma(){
	asm{
		mov ah,4ch         
    		int 21h
	}
}

//script 10: posicionar cursor
void posicionarCursor(){
	asm{
		mov ah, 02
		mov bh, 0
		mov dh, 0
		mov dl, 0
		int 10h
	}
}

//funciones del programa
void altas(){
	imprimirCaracter(168);
	printf("Cu");
	imprimirCaracter(160);
	printf("ntos pacientes ser");
	imprimirCaracter(160);
	printf("n dados de alta?: ");
	scanf("%d", &cantidad);
	//script 11: para sumar
	asm{
		mov ax, enfermos
		add ax, cantidad
		mov enfermos, ax
	}
	printf("Ahora hay ");
	printf("%d", enfermos);
	printf(" pacientes internados.\n\n");
}

void bajas(){
	imprimirCaracter(168);
	printf("Cu");
	imprimirCaracter(160);
	printf("ntos pacientes ser");
	imprimirCaracter(160);
	printf("n dados de baja?: ");
	scanf("%d", &cantidad);
	//script 12: para restar
	asm{
		mov ax, enfermos
		sub ax, cantidad
		mov enfermos, ax
	}
	printf("Ahora hay ");
	printf("%d", enfermos);
	printf(" pacientes internados.\n\n");
}

void costos(){
	imprimirCaracter(168);
	printf("Cu");
	imprimirCaracter(160);
	printf("ntos dias estuvo internado el paciente?: ");
	scanf("%d", &cantidad);
	//script 13: multiplicar
	asm{
		mov ax, cantidad
		mov bx, 800
		mul bx
		mov costoTotal, ax
	}
	printf("El costo total de la estancia es de: $");
	printf("%d", costoTotal);
	printf("MXN. \n\n");
}

void pagos(){
	printf("El pago ha sido dividido en 12 meses");
	//script 14: división
	asm{
		xor dx, dx
		mov ax, costoTotal
		mov bx, 12
		div bx
		mov cuotas, ax
	}
	printf("\nEl pago de cada cuota es de: $");
	printf("%d", cuotas);
	printf("MXN. \n\n");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{	
	dibujarCruz();
pausa:	//script 9: para hacer una pausa en el programa
	printf("Pulsa cualquier tecla para continuar");
	BuffKeyCheck:
	asm{
		mov ah, 11h
		int 16h
		jz BuffKeyEmpty
		mov ah, 10h
		int 16h
		jmp BuffKeyCheck
	}	
	BuffKeyEmpty:
	asm{
		mov ah, 10h
		int 16h
	}
	limpiarPantalla();
	
menu:	//aquí empieza el bucle
	posicionarCursor();
	colorDeEntrada();
	printf("BIENVENIDO A EL CSSA. ");
	imprimirCaracter(168);
	printf("Qu");
	imprimirCaracter(130);
 	printf(" se le ofrece?\n");
	printf("Pulsa 1 para a");
	imprimirCaracter(164);
	printf("adir un paciente al registro de internados.\n");
	printf("Pulsa 2 para quitar un paciente del registro de internados.\n");
	printf("Pulsa 3 para calcular el costo de estancia de un paciente internado.\n");
	printf("Pulsa 4 para consultar pagos a cuotas de un paciente internado.\n");
	printf("Pulsa 5 para salir.\n\n");
	entradaNoVisible();

	//script 6: para validar que la entrada sea un numero 
	asm{	
		cmp al,48	//0
        	je mostrar
        	cmp al,49	//1 
        	je mostrar
        	cmp al,50	//2
        	je mostrar
        	cmp al,51	//3  
        	je mostrar
        	cmp al,52	//4  
        	je mostrar
        	cmp al,53	//5  
        	je mostrar
        	cmp al,54	//6 
        	je mostrar
        	cmp al,55	//7  
        	je mostrar
        	cmp al,56	//8  
        	je mostrar
        	cmp al,57	//9 
        	je mostrar  
                   
        	cmp al,48  
        	jne noMostrar
        	cmp al,49 
        	jne noMostrar 
        	cmp al,50 
        	jne noMostrar
        	cmp al,51 
        	jne noMostrar
        	cmp al,52 
        	jne noMostrar
        	cmp al,53 
        	jne noMostrar
        	cmp al,54 
        	jne noMostrar
        	cmp al,55 
        	jne noMostrar
        	cmp al,56 
        	jne noMostrar
        	cmp al,57 
        	jne noMostrar
	}

	mostrar:	//mostramos el valor una vez que se confirma que no es una letra y hacemos un ajuste 
	asm{	
       		mov dl,al 
        	mov ah,02
        	int 21h
		mov al,dl
		mov menu,ax
		sub menu,560
	}
	printf("\n\n");
        asm jmp continuar
        
        noMostrar:	//si el valor es una letra imprimiremos el siguiente mensaje
        	printf("Favor de ingresar solo numeros\n\n");  
		asm jmp menu
	//fin del script 6

	//script 7: para simular un switch y un bucle        
	continuar:	//una vez tengamos el numero se compara con las opciones del menú
	asm{
		cmp menu,1
		je altas
		cmp menu,2
		je bajas
		cmp menu,3
		je costos
		cmp menu,4
		je pagos
		cmp menu,5
		je terminar

		cmp menu,1
		jne noexiste
		cmp menu,2
		jne noexiste
		cmp menu,3
		jne noexiste
		cmp menu,4
		jne noexiste
		cmp menu,5
		jne noexiste		
	}	

altas:
	altas();
	asm jmp pausa
	asm jmp menu
bajas:
	bajas();
	asm jmp pausa
	asm jmp menu
costos:
	costos();
	asm jmp pausa
	asm jmp menu
pagos:
	pagos();
	asm jmp pausa
	asm jmp menu

terminar:
	terminarPrograma();
noexiste: 
	printf("Opci");
	imprimirCaracter(162);	//script para caracteres especiales
	printf("n no existente.\n\n");
	asm jmp menu	
	//fin del script 7
	return 0;
}