#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define LIMITEBUFFER 1024

int main (int argc, char *argv[])
{
	struct sockaddr_in dataserver;
	struct hostent *he;
	char buffer[LIMITEBUFFER];
	char buffer1[LIMITEBUFFER];
	int socket_cliente, puerto, status, i;
	int salidacliente = 1, salidaservidor = 1;

	if (argc < 2) {
	    fprintf(stderr,"Uso: %s hostname [port]\n", argv[0]);
	    exit(1);
	}
	puerto = atoi(argv[2]);
	printf ("Prueba 2\n");
	if ((he=gethostbyname((const char *)argv[1])) == NULL) { // obtener información de máquina
	    herror("Error en gethostbyname");
	    exit(1);
	}
	printf ("Prueba 3\n");
	//creo el socket
	if ((socket_cliente = socket(AF_INET,SOCK_STREAM,0)) == -1) {
	    perror("Error al crear socket");
	    exit(1); 
	}
	  printf ("Prueba 4\n");

	//Cargo los datos del socket en la estructura
	dataserver.sin_family = AF_INET;
	dataserver.sin_port = (argc == 2)? htons (puerto):htons (atoi(argv[2]));
	dataserver.sin_addr = *((struct in_addr *)he->h_addr);
	memset(&(dataserver.sin_zero),'\0',8);

	//conecto al cliente con el servidor
	if (connect(socket_cliente, (struct sockaddr *) &dataserver, sizeof (struct sockaddr)) == -1) {
		perror ("Error al tratar de conectar el server");
		exit (1);
	}
	printf ("Prueba 6\n");
	
	while (salidaservidor != 0 && salidacliente != 0)
	{
		status = 0;
		while (status == 0)
			status = read(socket_cliente, buffer, sizeof(buffer));
			salidaservidor = strcmp(buffer, "q\n");
		if (salidaservidor != 0)
		{
			printf("servidor: %s", buffer);
			for(i = 0; i <= LIMITEBUFFER; i++) buffer[i] = 0;

			printf ("CLIENTE: ");
			fgets(buffer1, LIMITEBUFFER, stdin);
			salidacliente = strcmp(buffer1, "q\n");
			write(socket_cliente, buffer1, strlen(buffer1));
			for(i = 0; i <= LIMITEBUFFER; i++) buffer1[i] = 0;
		}
	}
	printf ("Hasta la proxima\n");
	close(socket_cliente);
	return 0;
}
	
	
	
	
