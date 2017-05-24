#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>

void printKey(int *vector, int tamaño)
{
	printf("\nllave generada: ");
	for (int i = 0; i < tamaño; i++)
	{
		printf("%i ", vector[i]);
	}
	printf("\nGuarda la llave en algun lugar seguro!!");
	return;
}

int crearllave(int *vector, int tamaño)
{
	for (int i = 0; i < tamaño; i++)
	{
		printf("Array: %i -> ", i);
		scanf_s("%i", vector[i]);
	}
	printf("\nGuarda la llave en algun lugar seguro!!");
	return 1;
}

int generarllave(int *vector, int tamaño)
{
	//la llave debe generarse solo una vez y 
	//guardarla en un fichero para luego poder descifrar
	int aleatorio = 0;
	for (int i = 0; i < tamaño; i++)
	{
		aleatorio = rand() % 100;
		vector[i] = aleatorio;
	}
	return 1;
}

char *cifrar(char *cadena, int *vector, int tamaño)
{
	int cont = 0, valor = 0, caracter_ascii = 0;
	char caracter[1];
	while (cadena[cont] != '\0')
	{
		cadena[cont] += vector[valor];
		cont++;
		valor++;
		if (valor >= tamaño)
		{
			valor = 0;
		}
	}
	return cadena;
}

char *descifrar(char *cadena, int *vector, int tamaño)
{
	int cont = 0, valor = 0;
	while (cadena[cont] != '\0')
	{
		cadena[cont] -= vector[valor];
		cont++;
		valor++;
		if (valor >= tamaño)
		{
			valor = 0;
		}
	}
	return cadena;
}

void cleanURL(char *url)
{
	int cont = 0;
	while (url[cont] != '\0')
	{
		if (url[cont] == '\n')
		{
			url[cont] = '\0'; 
			return;
		}
		cont++;
	}
}

void main()
{
	//global variables
	int llave[10] = { 0 }, cont, lineas, valorLlave;
	char opcion, url[255], contenido[255][255]; //el contenido es una matriz de lineas y longitud de lineas del fichero
	FILE *fichero = NULL;
	printf("\nFILE ENCRYPTER v1.0\n*******************");
	printf("\n\nEntra la ruta del fichero con el que vamos a operar:\n");
	fgets(url, 10000, stdin); //leemos teclado
	cleanURL(url);
	do {
		fichero = fopen(url, "r");
		cont = 0;
		while(feof(fichero) == 0)
		{
			fgets(contenido[cont], 10000, fichero);
			cont++;
		}
		fclose(fichero);
		lineas = cont; //almacenamos las lineas que tiene el fichero en una variable
		printf("\n0: Mostrar contenido del fichero\n1: Generar/Crear llave (si no tienes llave genera una)\n2: Cifrar fichero (txt)\n3: Descifrar fichero (txt)\n4: Usar llave (usar solo en caso de haber cerrado el programa!!)");
		opcion = _getch();
	
		switch (opcion)
		{
			case '0':
				printf("\nContenido del fichero\n*********************\n");
				for (cont = 0; cont < lineas; cont++)
				{
					printf("%s", contenido[cont]); //printamos de linea a linea
				}
				printf("\n*********************");
			break;
			case '1':
				printf("\nQuieres generar una llave de forma aleatoria?(S/N)");
				opcion = _getch();
				if (opcion == 's' || opcion == 'S')
				{
					generarllave(llave, 10);
					printKey(llave, 10);
				}
				else
				{
					printf("\nVamos a crear la llave para cifrar. Introduce un valor que quieras en cada array:");
					crearllave(llave, 10);
				}
				break;
			case '2':
				printf("\nCIFRANDO FICHERO >> ");
				for (int linea = 0; linea < lineas; linea++)
				{
					cifrar(contenido[linea], llave, 10);
				}
				fichero = fopen(url, "w"); //abrimos el fichero destruyendo su contenido en modo escritura
				fwrite(contenido, 255, lineas, fichero); //escribimos el contenido cifrado en el fichero
				printf("\nLISTO!!");
				fclose(fichero);
				break;
			case '3':
				printf("\nDESCIFRANDO FICHERO >>");
				for (int linea = 0; linea < lineas; linea++)
				{
					descifrar(contenido[linea], llave, 10);
					printf("\n%s", contenido[linea]);
				}
				printf("\nConfirmamos el descifrado? (S/N)");
				opcion = _getch();
				if (opcion == 'S' || opcion == 's')
				{
					fichero = fopen(url, "w"); //abrimos el fichero destruyendo su contenido en modo escritura
					fwrite(contenido, 255, lineas, fichero); //escribimos el contenido descifrado en el fichero
					printf("\nLISTO!!");
					fclose(fichero);
				}
				else
				{
					printf("Adios!!");
					Sleep(999);
					return; //rage quit
				}
				break;
			case '4':
				printf("\nIntroduce los valores de la llave:");
				for (int i = 0; i < 10; i++)
				{
					printf("\nVector %i -> ", i);
					scanf("%i", llave[i]);
				}
				printf("\nTodo listo!!");
				break;
		}
		printf("\nDeseas usar otra opcion? (S/N)");
		opcion = _getch();
	} while (opcion == 'S' || opcion == 's');
	printf("\nAdios!!");
	Sleep(1000);
	return;
}