#include <stdio.h>	/*libreria estandar*/
#include <stdlib.h>	/*libreria estandar*/
#include <string.h>	/*libreria estandar para el manejo de strings*/
#include <sys/utsname.h>
#include <sys/types.h>	/*libreria para la creacion y manejo de sockets*/
#include <sys/socket.h> /*libreria para la creacion y manejo de sockets*/
#include <netinet/in.h> /*libreria para las diferentes funciones como bind, accept, listen, connect*/
#include <arpa/inet.h>	/*libreria para las diferentes funciones como bind, accept, listen, connect*/
#include <netdb.h>	/*libreria para las diferentes funciones como bind, accept, listen, connect*/
#include <unistd.h>

#define MAXCONEX 30		/*Limite de conexiones en espera*/
#define LIMITEBUFFER 1024 	/*Limite del buffer*/

int main (int argc, char *argv[])
{
  char buffer[LIMITEBUFFER];
  char buffer1[LIMITEBUFFER];
  int i, childPid, salidaservidor = 1, salidacliente = 1, sin_size;
  int servidorfd = 0, clientefd = 0, on = 0, puerto = 0, status = 0, contador = 0;
  struct sockaddr_in dataserver; 
  struct sockaddr_in dataclient;
  
	if (2 != argc)
	{
		fprintf(stderr, "Uso: %s <puerto>\n", argv[0]);
		exit (1);
	}
	puerto = atoi(argv[1]);
	
	if ((servidorfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket()");
		exit(1);
	}
	printf ("Prueba 2\n");
	on = 1;
	
	/*Si el socket se cierra de golpe queda ocupado el puerto hasta que 
	  * se reinicie. setsockop es una funcion que lo soluciona*/
	if (setsockopt(servidorfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof (on)) == -1) 
	{
		perror("setsockopt()");
		exit(1);
	}
		  printf ("Prueba 3\n");
	//Cargo la info del server en la estructura
	dataserver.sin_family = AF_INET;
	dataserver.sin_port = htons(puerto);//convierte el entero formato pc a entero formato network
	dataserver.sin_addr.s_addr = INADDR_ANY;//automaticamente usa la ip local
	memset(&(dataserver.sin_zero),'\0',8);//rellena con ceros el resto de la estructura

	//bindeo el socket con los datos de la estructura
	if (bind(servidorfd, (struct sockaddr*) &dataserver, sizeof (struct sockaddr)) == -1) 
	{ 
		perror("bind"); 
		exit(1);
	}
	
	//el socket se queda escuchando(
	if (listen(servidorfd, MAXCONEX) == -1) 
	{ 
		perror("listen");
		exit(1);
	}
	
	for(;;)
	{
	  sin_size = sizeof(struct sockaddr_in);
	  //Aceptamos la conexion 
	  if ((clientefd = accept (servidorfd, (struct sockaddr *)&dataclient, &sin_size))== -1) 
	  {     
		perror("accept()");
		exit(1);
	  }
	  
	  contador = contador + 1;
	  childPid = fork();
	  
	  //Con el switch evaluamos lo que devuelve el fork()
	  switch (childPid)
	  {
	      case -1: /*Error*/
		    perror ("fork()");
		    exit(1);
	      case 0: /* Proceso hijo */
		    close (servidorfd); //El proceso hijo no lo necesita
		    printf ("Conexion establecida con: %s\n", inet_ntoa(dataclient.sin_addr));
		
		    sprintf(buffer, "Bienvenido al chat del curso R1031\n Si desea desconectarse escriba \"salir\"\n", inet_ntoa(dataclient.sin_addr));
		    write(clientefd, buffer, strlen(buffer)); //envia el mensaje escrito en el buffer al cliente
	
		    for (i=0; i<=LIMITEBUFFER; i++) buffer[i] = 0; //limpia el buffer
		    
		    while (salidaservidor != 0 && salidacliente != 0)
		    {
			    status = 0;
			    while (status == 0)
			    status = read(servidorfd, buffer1, sizeof(buffer1));
			    salidacliente = strcmp(buffer1, "q\n");
	
			    if (salidacliente != 0)
			    {
				printf("cliente: %s", buffer1);
				for (i = 0; i <= LIMITEBUFFER; i++) buffer1[i] = 0;
			
				printf("SERVIDOR: ");
				fgets(buffer, LIMITEBUFFER, stdin);
				salidaservidor = strcmp(buffer, "q\n");
				write(clientefd, buffer, strlen(buffer));
				for (i = 0; i <= LIMITEBUFFER; i++) buffer[i] = 0;
			    }
		    }
		    printf("Hasta la proxima\n");
		    close(clientefd);
		    exit(0);

		    default:/* Proceso padre */
			close(clientefd);
	  }
	}
	
	return 0;
}
