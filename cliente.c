#include <stdio.h>


int main (){
  
    char nick[20];	//modo ilustrativo, necesitamos pedir memoria con malloc, creo que seria la mejor opcion
    char mensaje[x];	//lo mismo que arriba.
    //Leer la IP del server desde un archivo de configuracion
    //Conectar con el servidor de chat
    printf ("Seleccione un apodo. Con este sera visto por el resto de los usuarios");
    scanf ("%s",&nick);
    //Envio el apodo al servidor
    //Esperar la respuesta del servidor
    if (//error de conexion)
	{
	printf ("Hubo un problema con la conexion al servidor. Intente nuevamente");
	return (1);
	  
	}
    while (!mensaje='/logout'){ //mientras el usuario no tipee /logout
      printf("Mensaje: ");
      scanf("%s",&mensaje);
      if (mensaje[0]='/'){
	//case con los diferentes comandos

      }
      else
	{
	  //serializar mensaje
	  //enviar al servidor
	}
    }
    //cierro el cliente
    return (0);
    
}

Para el CLIENTE:

1- Se tiene que conectar y "escuchar" al servidor.

2- Si el usuario quiere mandar un mensaje, tiene que leer lo que entra por teclado. Si lo que mando empieza con 
  '\' tiene que evaluar si fue un comando o no. Si fue, lo ejectuta, si no fue un comando pero empezaba con '\' 
  tiene que mostrar un error y si no empezaba con '\' manda el mensaje al servidor.

3- Si el cliente se quiere desconectar se cierra la conexion con el servidor.
