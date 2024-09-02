#include "client.h"
#include <readline/readline.h>

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */
	
	logger = iniciar_logger();
	
	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"

	log_info(logger,"BIenveninooo");


	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();

	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'

	if(config_has_property(config, "CLAVE") == NULL ){	
		printf("no se ha encontrado la key");
		abort();
	}

	ip=config_get_string_value(config,"IP");
	puerto=config_get_string_value(config,"PUERTO");
	valor=config_get_string_value(config,"CLAVE");


	// Loggeamos el valor de config
	log_info(logger,"ip=%s",ip);
	log_info(logger,"puerto=%s",puerto);
	log_info(logger,"clave=%s",valor);



	/* ---------------- LEER DE CONSOLA ---------------- */

	//leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	
	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);
	printf("conexion: %i\n",conexion);

	// Enviamos al servidor el valor de CLAVE como mensaje
	enviar_mensaje(valor,conexion);

	// Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion, logger, config);
	
	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger = log_create("tp0.log","tp0",1,LOG_LEVEL_INFO);

	if(nuevo_logger == NULL){
		printf("error al crear archivo logger");
		abort();
	}
	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config = config_create("cliente.config");

	if(nuevo_config==NULL){
		printf("error al crear archivo de configuracion");
		abort();
	}

	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	// La primera te la dejo de yapa
	

	while(1){
		leido = readline("> ");
		if(leido[0]!='\0'){
			log_info(logger, leido);
		}else{
			break;
		}
	}
	// El resto, las vamos leyendo y logueando hasta recibir un string vacío


	// ¡No te olvides de liberar las lineas antes de regresar!
	free(leido);
}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete;
	paquete = crear_paquete();

	// Leemos y esta vez agregamos las lineas al paquete y enviamos el paquete
	while(1){
		leido = readline("> ");
		if(leido[0]!='\0'){
			agregar_a_paquete(paquete,leido,strlen(leido)+1);
		}else{
			break;
		}
	}
	enviar_paquete(paquete,conexion);

	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	free(leido);
	eliminar_paquete(paquete);
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
	log_destroy(logger);
	config_destroy(config);
	liberar_conexion(conexion);
}
