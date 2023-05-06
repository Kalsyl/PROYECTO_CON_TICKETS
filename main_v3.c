#include <stdio.h> 
#include <stdlib.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <semaphore.h>
#include <fcntl.h>
#include <math.h>
#include <signal.h>

int posicionv;
#define pagos_anulaciones 1
#define reservas 2
#define administracion 3
#define consultas 4

// -------------VARIABLES COMPARTIDAS--------------
typedef struct datos_comp{
	int mi_ticket;
	int mi_id;
	int id_nodos_pend[100];
	int quiero;
	int max_ticket;
	//añadidas
	int dentro;
	int prioridad_request;
	int procesos;
	int primero;
	int cont_prioridades[10];
	int prioridad_procesos[100];
	int tickets_procesos[100];
	int ack;
	int numero_consultas;
	int grifo;
}datos_comp;
	
struct msg{
	long mtype;                                          //TIPO DE MENSAJE
	int mi_ticket;										 //TICKET MENSAJE
	int mi_id;										     //ID NODO
	int tipo_mensaje;									 //TIPO DEL MENSAJE   '0' ===> REQUEST         '1' ======> ACK
	int prioridad;										 //PRIORIDAD MENSAJE 
}mensaje;





 void handle_sigint(int signal) {
	key_t clave1 = ftok(".",posicionv); //creamos la clave que utilizaremos para vincularnos a la zona de memoria ya creada
	 
	int shmid1 = shmget(clave1,8*sizeof(int),0);//Creación de zona_mem1, Al no poner el flag IPC_CREAT, estamos suponiendo que dicha memoria ya está creada.
	 	 
	datos_comp *datos =(datos_comp *)shmat(shmid1,0,0);//Vinculamos el proceso con la zona de memoria
	datos->procesos--;
    exit(0);
}

int main(int argc,char *argv[]) {

//--------------------------ctrl+c----------------------------


struct sigaction ss;
ss.sa_handler = handle_sigint;
ss.sa_flags = 0;
sigaction(2,&ss,NULL);


//--------------------------FIN ctrl+c----------------------------



	//----------VARIABLES PROPIAS-------------------------------
	int posicion=atoi(argv[1]);													//POSICION DEL NODO
	posicionv = posicion;														//"" ""
	int N = atoi(argv[2]);														//NUMERO NODOS
	int prioridad=atoi(argv[3]);												//PRIORIDAD DEL PROCESO
	int id_nodos=1235+posicion;													//ID DEL NODO	

	char array_prioridades[5][20] = { "","Pagos&Anulaciones","Reservas", "Administración","Consultas"};
	//DE APOYO						
	int anteriores;
	int mayor=0;	
	int contadores = 0;
	int max_prioridad=0;
	

	 if (argc != 4){
		printf("formato incorrecto: ./v1_main posicion N prioridad\n");
		exit(-1);
	}

	

	//-----------------------CREACION DE BUZONES DE MENSAJES-----------------------------------------------------------------

	int msqid = msgget(500,0666 | IPC_CREAT);

	//-----------------------FIN DE CREACION DE BUZONES DE MENSAJES----------------------------------------------------------




	//-------------INICIALIZAMOS ZONA DE MEMORIA COMPARTIDA-------------------------------------------------------------------

	key_t clave1; 
	int shmid1; 
	clave1 = ftok(".",posicion); 
	 
	shmid1 = shmget(clave1,8*sizeof(int),0);
	 
	if(shmid1 !=-1){
		printf("Zona de memoria vinculada OK! con identificador %d \n", shmid1);
	}else{
		printf("ERROR al crear zona de memoria 1 !! \n");
		exit(1);
	}
	 
	datos_comp *datos =(datos_comp *)shmat(shmid1,0,0);
	 
	if(datos == (datos_comp*)-1){
		printf("Error al vincular el proceso a la zona de memoria 1! \n");
		exit(1);
	} 

	//-------------FIN INICIALIZAMOS ZONA DE MEMORIA COMPARTIDA-----------------------------------------------------------------




	//---------------------------------------DECLARACION SEMÁFOROS--------------------------------------------------------------

	char name_mutex[50];
	sprintf(name_mutex, "/MUTEX%s", argv[1]);
	sem_t *sem_mutex;
	sem_mutex = sem_open(name_mutex, O_CREAT, 0777, 1);
	if (sem_mutex == SEM_FAILED) {
	     perror("Failed to open semphore for empty");
	     exit(-1);
	}
	char name_mutex2[50];
	sprintf(name_mutex2, "/MUTEX1%s", argv[1]);
	sem_t *sem_mutex2;
	sem_mutex2 = sem_open(name_mutex2, O_CREAT, 0777, 1);
	if (sem_mutex2 == SEM_FAILED) {
	     perror("Failed to open semphore for empty");
	     exit(-1);
	}



	char name_paso[50];
	sprintf(name_paso, "/MUTEXPASO%s", argv[1]);
	sem_t *sem_name_paso;
	sem_name_paso = sem_open(name_paso, O_CREAT, 0777, 0);
	if (sem_name_paso == SEM_FAILED) {
	     perror("Failed to open semphore for empty");
	     exit(-1);
	}

		char name_paso_consulta[50];
	sprintf(name_paso_consulta, "/MUTEXPASOCONSULTA%s", argv[1]);
	sem_t *sem_name_paso_consulta;
	sem_name_paso_consulta = sem_open(name_paso_consulta, O_CREAT, 0777, 0);
	if (sem_name_paso_consulta == SEM_FAILED) {
	     perror("Failed to open semphore for empty");
	     exit(-1);
	}

		char name_paso_administracion[50];
	sprintf(name_paso_administracion, "/MUTEXPASOADMINISTRACION%s", argv[1]);
	sem_t *sem_name_paso_administracion;
	sem_name_paso_administracion = sem_open(name_paso_administracion, O_CREAT, 0777, 0);
	if (sem_name_paso_administracion == SEM_FAILED) {
	     perror("Failed to open semphore for empty");
	     exit(-1);
	}

		char name_paso_reservas[50];
	sprintf(name_paso_reservas, "/MUTEXPASORESERVAS%s", argv[1]);
	sem_t *sem_name_paso_reservas;
	sem_name_paso_reservas = sem_open(name_paso_reservas, O_CREAT, 0777, 0);
	if (sem_name_paso_reservas == SEM_FAILED) {
	     perror("Failed to open semphore for empty");
	     exit(-1);
	}

		char name_paso_pagos_anulaciones[50];
	sprintf(name_paso_pagos_anulaciones, "/MUTEXPASOPAGOSANULACIONES%s", argv[1]);
	sem_t *sem_name_paso_pagos_anulaciones;
	sem_name_paso_pagos_anulaciones = sem_open(name_paso_pagos_anulaciones, O_CREAT, 0777, 0);
	if (sem_name_paso_pagos_anulaciones == SEM_FAILED) {
	     perror("Failed to open semphore for empty");
	     exit(-1);
	}

	char name_var_mi_ticket[50];
	sprintf(name_var_mi_ticket, "/name_var_mi_ticket%s", argv[1]);
	sem_t *sem_var_mi_ticket;
	sem_var_mi_ticket = sem_open(name_var_mi_ticket, O_CREAT, 0777, 0);
	if (sem_var_mi_ticket == SEM_FAILED)
	{
		perror("Failed to open semphore for empty");
		exit(-1);
	}

	char name_var_mi_id[50];
	sprintf(name_var_mi_id, "/name_var_mi_id%s", argv[1]);
	sem_t *sem_var_mi_id;
	sem_var_mi_id = sem_open(name_var_mi_id, O_CREAT, 0777, 0);
	if (sem_var_mi_id == SEM_FAILED)
	{
		perror("Failed to open semphore for empty");
		exit(-1);
	}

	char name_var_id_nodos_pend[50];
	sprintf(name_var_id_nodos_pend, "/name_var_id_nodos_pend%s", argv[1]);
	sem_t *sem_var_id_nodos_pend;
	sem_var_id_nodos_pend = sem_open(name_var_id_nodos_pend, O_CREAT, 0777, 0);
	if (sem_var_mi_ticket == SEM_FAILED)
	{
		perror("Failed to open semphore for empty");
		exit(-1);
	}


	char name_var_quiero[50];
	sprintf(name_var_quiero, "/name_var_quiero%s", argv[1]);
	sem_t *sem_var_quiero;
	sem_var_quiero = sem_open(name_var_quiero, O_CREAT, 0777, 0);
	if (sem_var_quiero == SEM_FAILED)
	{
		perror("Failed to open semphore for empty");
		exit(-1);
	}

	char name_var_dentro[50];
	sprintf(name_var_dentro, "/name_var_dentro%s", argv[1]);
	sem_t *sem_var_dentro;
	sem_var_dentro = sem_open(name_var_dentro, O_CREAT, 0777, 0);
	if (sem_var_dentro == SEM_FAILED)
	{
		perror("Failed to open semphore for empty");
		exit(-1);
	}

	char name_var_prioridad_request[50];
	sprintf(name_var_prioridad_request, "/name_var_prioridad_request%s", argv[1]);
	sem_t *sem_var_prioridad_request;
	sem_var_prioridad_request = sem_open(name_var_prioridad_request, O_CREAT, 0777, 0);
	if (sem_var_prioridad_request == SEM_FAILED)
	{
		perror("Failed to open semphore for empty");
		exit(-1);
	}

	char name_var_procesos[50];
	sprintf(name_var_procesos, "/name_var_procesos%s", argv[1]);
	sem_t *sem_var_procesos;
	sem_var_procesos = sem_open(name_var_procesos, O_CREAT, 0777, 0);
	if (sem_var_procesos == SEM_FAILED)
	{
		perror("Failed to open semphore for empty");
		exit(-1);
	}

	char name_var_primero[50];
	sprintf(name_var_primero, "/name_var_primero%s", argv[1]);
	sem_t *sem_var_primero;
	sem_var_primero = sem_open(name_var_primero, O_CREAT, 0777, 0);
	if (sem_var_primero == SEM_FAILED)
	{
		perror("Failed to open semphore for empty");
		exit(-1);
	}

	char name_var_cont_prioridades[50];
	sprintf(name_var_cont_prioridades, "/name_var_cont_prioridades%s", argv[1]);
	sem_t *sem_var_cont_prioridades;
	sem_var_cont_prioridades = sem_open(name_var_cont_prioridades, O_CREAT, 0777, 0);
	if (sem_var_cont_prioridades == SEM_FAILED)
	{
		perror("Failed to open semphore for empty");
		exit(-1);
	}
	
	char name_var_prioridad_procesos[50];
	sprintf(name_var_prioridad_procesos, "/name_var_prioridad_procesos%s", argv[1]);
	sem_t *sem_var_prioridad_procesos;
	sem_var_prioridad_procesos = sem_open(name_var_prioridad_procesos, O_CREAT, 0777, 0);
	if (sem_var_prioridad_procesos == SEM_FAILED)
	{
		perror("Failed to open semphore for empty");
		exit(-1);
	}	
	
	char name_var_tickets_procesos[50];
	sprintf(name_var_tickets_procesos, "/name_var_tickets_procesos%s", argv[1]);
	sem_t *sem_var_tickets_procesos;
	sem_var_tickets_procesos = sem_open(name_var_tickets_procesos, O_CREAT, 0777, 0);
	if (sem_var_tickets_procesos == SEM_FAILED)
	{
		perror("Failed to open semphore for empty");
		exit(-1);
	}

	char name_var_ack[50];
	sprintf(name_var_ack, "/name_var_ack%s", argv[1]);
	sem_t *sem_var_ack;
	sem_var_ack = sem_open(name_var_ack, O_CREAT, 0777, 0);
	if (sem_var_ack == SEM_FAILED)
	{
		perror("Failed to open semphore for empty");
		exit(-1);
	}

	char name_var_numero_consultas[50];
	sprintf(name_var_numero_consultas, "/name_var_numero_consultas%s", argv[1]);
	sem_t *sem_var_numero_consultas;
	sem_var_numero_consultas = sem_open(name_var_numero_consultas, O_CREAT, 0777, 0);
	if (sem_var_numero_consultas == SEM_FAILED)
	{
		perror("Failed to open semphore for empty");
		exit(-1);
	}

	char name_var_grifo[50];
	sprintf(name_var_grifo, "/name_var_grifo%s", argv[1]);
	sem_t *sem_var_grifo;
	sem_var_grifo = sem_open(name_var_grifo, O_CREAT, 0777, 0);
	if (sem_var_grifo == SEM_FAILED)
	{
		perror("Failed to open semphore for empty");
		exit(-1);
	}
	//---------------------------------------DECLARACION SEMÁFOROS----------------------------------------






	//-------------------INICIALIZACIÓN DE LAS VARIABLES COMPARTIDAS-------------------------------------

datos->mi_id=id_nodos;
datos->procesos++;
	
	printf("Numero de procesos %d\n",datos->procesos);

	//-------------------FIN INICIALIZACION DE LAS VARIABLES COMPARTIDAS----------------------------------


	//-----------------------------INICIO PROGRAMA--------------------------------------------------------

	printf("SOY UN PROCESO DE TIPO %s DEL NODO %d\n",array_prioridades[prioridad],id_nodos);

	while (1) { 



		// Sección no crítica
		printf("Esperando para entrar en la Sección Critica\n");


		getchar();


	 	printf("Quiero entrar en la Sección Critica\n");
	 	
		

	 
		datos->quiero = 1;													//INDICAS QUE QUIERES ENTRAR												
	




		
		//SI LLEGA UN PROCESO EN EL MISMO NODO CON MAYOR PRIORIDAD DE CONSULTAS Y EL GRIFO ESTÁ ABIERTO CERRAMOS EL GRIFO

		if(prioridad <consultas && datos->grifo == 1){
			printf("COMO SOY UN PROCESO DE MAYOR PRIORIDAD CIERRO GRIFO\n");
			datos->grifo = 0;
		}
		



		//COMPRUEBAS SI HAY EN ALGUNA COLA UN PROCESO DE MAYOR DE PRIORIDAD Y LOS GUARDAS EN "max_prioridad"

		if(datos->cont_prioridades[pagos_anulaciones]!=0){
						max_prioridad=pagos_anulaciones;
			}else if(datos->cont_prioridades[reservas]!=0){
						max_prioridad=reservas;
			}else if(datos->cont_prioridades[administracion]!=0){
						max_prioridad=administracion;
			}else if (datos->cont_prioridades[consultas]!=0){
						max_prioridad=consultas;
		}


		
		//ENVIAS TU REQUEST SI SE CUMPLE EL IF


		if((datos->primero==0 || prioridad<max_prioridad) && datos->dentro == 0){
				datos->prioridad_request = prioridad;


			//ENVIAMOS REQUEST QUE SIRVE PARA CANCELAR EN EL CASO QUE HUBIERA QUE CANCELAR

			datos->ack=0;
			datos->mi_ticket = datos->max_ticket + 1; 								// GENERACIÓN DE UN TICKET MAYOR AL ANTERIOR
			for (int i = 0; i <=N-1; i++){
				if(1235+i!=id_nodos){

					mensaje.mtype=1235+i;										//INDICA AL NODO  QUE ENVÍAS EL MENSAJE
					mensaje.mi_id=id_nodos;										//INIDICA TU NODO
					mensaje.prioridad=prioridad;								//INDICA TU PRIORIDAD
					mensaje.tipo_mensaje = 0;									//INDICA EL TIPO DE MENSAJE
					mensaje.mi_ticket=datos->mi_ticket;							//ENVIAS EL MENSAJE


					msgsnd(msqid, &mensaje, sizeof(struct msg), 0);
					
					printf("[REQUEST] enviado a %ld\n",mensaje.mtype);
				
				}
			}
			datos->primero=1;
			

		}


	//-----------------------------------------COLAS--------------------------------------------------

		


			//COLA PAGOS & ANULACIONES

			if(prioridad==pagos_anulaciones){
				printf("Semaforo pagos y anulaciones\n");
				datos->cont_prioridades[pagos_anulaciones] = datos->cont_prioridades[pagos_anulaciones] + 1 ;			//ACTUALIZAS NUMERO PROCESOS EN LA COLA
				
				sem_wait(sem_name_paso_pagos_anulaciones);
				
				datos->cont_prioridades[pagos_anulaciones] = datos->cont_prioridades[pagos_anulaciones] -1 ;			//ACTUALIZAS NUMERO PROCESOS EN LA COLA
				

			}
			
			//COLA RESERVAS 
			
			
			if(prioridad==reservas){
				printf("Semaforo reservas\n");
				datos->cont_prioridades[reservas] = datos->cont_prioridades[reservas] + 1 ;								//ACTUALIZAS NUMERO PROCESOS EN LA COLA

				sem_wait(sem_name_paso_reservas);

				datos->cont_prioridades[reservas] = datos->cont_prioridades[reservas] - 1 ;								//ACTUALIZAS NUMERO PROCESOS EN LA COLA
			}
			
			
			//COLA ADMINISTRACION
			
			
			if(prioridad==administracion){
				printf("Semaforo administración\n");
				datos->cont_prioridades[administracion] = datos->cont_prioridades[administracion] + 1 ;					//ACTUALIZAS NUMERO PROCESOS EN LA COLA

				sem_wait(sem_name_paso_administracion);

				datos->cont_prioridades[administracion] = datos->cont_prioridades[administracion] - 1 ;					//ACTUALIZAS NUMERO PROCESOS EN LA COLA
			}
			
			
			//COLA CONSULTAS 
			
			
			
			if(prioridad==consultas){
				if(datos->grifo == 0){
				printf("Semaforo consultas\n");
					printf("datos->cont_prioridades[consultas] %d\n",datos->cont_prioridades[consultas] );
				datos->cont_prioridades[consultas] = datos->cont_prioridades[consultas] + 1 ;							//ACTUALIZAS NUMERO PROCESOS EN LA COLA

				sem_wait(sem_name_paso_consulta);

				datos->cont_prioridades[consultas] = datos->cont_prioridades[consultas] - 1 ;							//ACTUALIZAS NUMERO PROCESOS EN LA COLA
				printf("datos->cont_prioridades[consultas] %d\n",datos->cont_prioridades[consultas] );
				}


				if(datos->grifo == 0) {
					datos->grifo = 1;
				int x = datos->cont_prioridades[consultas];
				while(x!=0){
					sem_post(sem_name_paso_consulta);
					x--;
				}
				}
				datos->numero_consultas = datos->numero_consultas +1;

	printf("datos->cont_prioridades[consultas] %d\n",datos->cont_prioridades[consultas] );

			}





		//-----------------------------------------FIN COLAS--------------------------------------------------


		

		
			


		printf("Tengo todos los permisos,entrando en la Sección Crítica...\n");
		
	

		
		//ENTRADA  SECCIÓN CRÍTICA 





		printf("En la Seccion Crítica\n");
		
		
		
		datos->dentro = 1;
		
		getchar();
		
		printf("Saliendo de la sección crítica...\n");


		//IF QUE SOLO HACE CONSULTAS
		if(prioridad == consultas) {
		   datos->numero_consultas = datos->numero_consultas -1;
		//SI NO SOMOS EL ÚLTIMO DE CONSULTAS NO HACEMOS NADA
			if(datos->numero_consultas == 0){

				//datos->ack=0;
			if(datos->cont_prioridades[pagos_anulaciones]!=0){
						max_prioridad=pagos_anulaciones;
			}else if(datos->cont_prioridades[reservas]!=0){
						max_prioridad=reservas;
			}else if(datos->cont_prioridades[administracion]!=0){
						max_prioridad=administracion;
			}else if (datos->cont_prioridades[consultas]!=0){
						max_prioridad=consultas;
			}else max_prioridad = 500;

	     int max_prio_pend=6;
				for (int i = 0; i <N; i++){
					if(datos->id_nodos_pend[i] !=0){
						if(datos->prioridad_procesos[i]< max_prio_pend){
							max_prio_pend = datos->prioridad_procesos[i];
						}

					}

				}

		
			if(max_prioridad>=max_prio_pend || max_prioridad == 500){
					
						//ENVIAMOS ACKS PENDIENTES
				
				for (int i = 0; i <N; i++){
					if(datos->id_nodos_pend[i]!=0){
					printf("EL NODO %d TIENE PRIORIDAD %d\n",datos->id_nodos_pend[i],datos->prioridad_procesos[i]);
					printf("COMO ÚLTIMO DE CONSULTAS ENVIO ACKS Y EN CASO DE TENER UN PROCESO EN MIS COLAS PIDO REQUEST\n");
									
					mensaje.mi_id=id_nodos;										//INIDICA TU NODO

					mensaje.tipo_mensaje = 1;									//INDICA EL TIPO DE MENSAJE

				    mensaje.mtype=datos->id_nodos_pend[i];						//INDICA AL NODO  QUE ENVÍAS EL MENSAJE

					mensaje.prioridad = datos->prioridad_procesos[i];			//ENVÍAS LA PRIORIDAD DEL REQUEST A QUIEN VA DIRIGIDO EL ACK

					mensaje.mi_ticket= datos->tickets_procesos[i];

				
					printf("ticket %d\n", mensaje.mi_ticket);
					 msgsnd(msqid, &mensaje,sizeof(struct msg), 0);
				
				    printf("[ACK] Enviando OK  a %d \n",datos->id_nodos_pend[i]);
				}

			}
				//BORRAMOS LOS ACK PENDIENTES

				for (int i = 0; i <N; i++){
						datos->id_nodos_pend[i] = 0;
				}

			}


			printf("DATOS_ACK %d\n",datos->ack);

			if(max_prioridad!= 500){
				printf("ENVIAMOS REQUEST POR UN PROCESO DE %d\n",max_prioridad);
				datos->mi_ticket = datos->max_ticket + 1;
				datos-> ack = 0;
				datos->prioridad_request = max_prioridad;
					for (int i = 0; i <N; i++){
							if(1235+i!=id_nodos){
							
							mensaje.mtype=1235+i;										//INDICA AL NODO  QUE ENVÍAS EL MENSAJE
							mensaje.mi_id=id_nodos;										//INIDICA TU NODO
							mensaje.prioridad=max_prioridad;						//INDICA TU PRIORIDAD
							mensaje.tipo_mensaje = 0;									//INDICA EL TIPO DE MENSAJE
							mensaje.mi_ticket=datos->mi_ticket;							//ENVIAS EL MENSAJE


								msgsnd(msqid, &mensaje, sizeof(struct msg), 0);//envias mensajes request a todos los nodos	
								
								printf("[REQUEST] enviado a %ld\n",mensaje.mtype);
					
							}
					}
			}


		if(max_prioridad == 500){
	
			datos->primero=0;
			datos->prioridad_request = 0;
		}
			
				sem_wait(sem_mutex2);
		datos->quiero = 0;
		datos->dentro = 0;
		datos -> grifo =0;
		sem_post(sem_mutex2);

			}
	else printf("\n\nCOMO NO SOY EL ÚLTIMO DE CONSULTAS NO HAGO NADA (me voy silenciosamente jejeje)\n\n");
	
	
	
	}else{
		
		//SALIDA SECCIÓN CRÍTICA 





		sem_wait(sem_mutex2);
		datos->quiero = 0;
		datos->dentro = 0;
	
		sem_post(sem_mutex2);


		//COMPARAMOS PRIORIDADES DE PROCESOS DE OTROS NODOS CON LOS NUESTROS QUE ESTÁN ESPERANDO
						//CASO TENEMOS ALGUNO DE PRIORIDAD MAYOR ESPERANDO  ======> 
						//CASO HAY PROCESOS MÁS PRIORITARIOS EN OTROS NODOS ======>



		//ASIGNAMOS A max_prioridad EL VALOR DE LA PRIORIDAD MÁS ALTA ENTRES LOS PROCESOS DE LAS COLAS 

		if(datos->cont_prioridades[pagos_anulaciones]!=0){
						max_prioridad=pagos_anulaciones;
			}else if(datos->cont_prioridades[reservas]!=0){
						max_prioridad=reservas;
			}else if(datos->cont_prioridades[administracion]!=0){
						max_prioridad=administracion;
			}else if (datos->cont_prioridades[consultas]!=0){
						max_prioridad=consultas;
		}else max_prioridad=500;


		//SI ENCONTRAMOS UN PROCESO DE MAYOR PRIORIDAD ENTRE LAS PENDIENTES MARCAMOS mayor COMO 1
if(max_prioridad !=500){
		for (int i = 0; i <N; i++){
			
				if(max_prioridad>datos->prioridad_procesos[i] && datos->id_nodos_pend[i]!=0){
					mayor=1;
					break;
				}
		}
}else mayor = 0;
		//SIN contadores LLEGA A 4 ESO QUIERE DECIR QUE TODAS LAS COLAS ESTÁN VACÍAS


		//SI O BIEN LAS COLAS ESTÁN VACÍA O ENCONTRAMOS EN OTRO NODO OTRO PROCESO DE PRIORIDAD MAYOR  EJECUTAMOS EL IF

		if(mayor==1 || max_prioridad==500 ){
				
			//ENVIAMOS ACK PENDIENTES

		
			for (int i = 0; i <N; i++){
				if(datos->id_nodos_pend[i]!=0){
					printf("EL NODO %d TIENE PRIORIDAD %d\n",datos->id_nodos_pend[i],datos->prioridad_procesos[i]);

					mensaje.mi_ticket= datos->tickets_procesos[i];


					mensaje.mi_id=id_nodos;										//INIDICA TU NODO

					mensaje.tipo_mensaje = 1;									//INDICA EL TIPO DE MENSAJE

				    mensaje.mtype=datos->id_nodos_pend[i];						//INDICA AL NODO  QUE ENVÍAS EL MENSAJE

					mensaje.prioridad = datos->prioridad_procesos[i];			//ENVÍAS LA PRIORIDAD DEL REQUEST A QUIEN VA DIRIGIDO EL ACK



				
					 msgsnd(msqid, &mensaje,sizeof(struct msg), 0);
				
				    printf("[ACK] Enviando OK  a %d \n",datos->id_nodos_pend[i]);
				}

			}
				//BORRAMOS LOS ACK PENDIENTES

				for (int i = 0; i <N; i++){
						datos->id_nodos_pend[i] = 0;

				}				
				printf("Todos los OK pendientes enviados\n");
			


				//ENCUENTRAS EL PROCESO EN ESPERA CON MAYOR PRIORIDAD Y HACES UN REQUEST POR ÉL
				//ACTUALIZO EL TICKET
				

				if(max_prioridad!=500){
					datos->mi_ticket = datos->max_ticket + 1;
					datos->ack =0;
					datos->prioridad_request = max_prioridad;
					for (int i = 0; i <N; i++){
							if(1235+i!=id_nodos){
							
							mensaje.mtype=1235+i;										//INDICA AL NODO  QUE ENVÍAS EL MENSAJE
							mensaje.mi_id=id_nodos;										//INIDICA TU NODO
							mensaje.prioridad=max_prioridad;						//INDICA TU PRIORIDAD
							mensaje.tipo_mensaje = 0;									//INDICA EL TIPO DE MENSAJE
							mensaje.mi_ticket=datos->mi_ticket;							//ENVIAS EL MENSAJE


								msgsnd(msqid, &mensaje, sizeof(struct msg), 0);//envias mensajes request a todos los nodos	
								
								printf("[REQUEST] enviado a %ld\n",mensaje.mtype);
					
							}
					}
	
				}
		}else{

			//EN CASO CONTRARIO DESPIERTAS AL PROCESO DE MAYOR PRIORIDAD 


			if(datos->cont_prioridades[pagos_anulaciones]!=0){
						sem_post(sem_name_paso_pagos_anulaciones);
			}else if(datos->cont_prioridades[reservas]!=0){
						sem_post(sem_name_paso_reservas);
			}else if(datos->cont_prioridades[administracion]!=0){
						sem_post(sem_name_paso_administracion);
			}else if (datos->cont_prioridades[consultas]!=0){
				for (int i = 0; i <N; i++){
							if(datos->id_nodos_pend[i]!=0){
								printf("EL NODO %d TIENE PRIORIDAD %d\n",datos->id_nodos_pend[i],datos->prioridad_procesos[i]);

								mensaje.mi_ticket= datos->tickets_procesos[i];
								mensaje.mi_id=id_nodos;										//INIDICA TU NODO

								mensaje.tipo_mensaje = 1;									//INDICA EL TIPO DE MENSAJE

								mensaje.mtype=datos->id_nodos_pend[i];						//INDICA AL NODO  QUE ENVÍAS EL MENSAJE

								mensaje.prioridad = datos->prioridad_procesos[i];			//ENVÍAS LA PRIORIDAD DEL REQUEST A QUIEN VA DIRIGIDO EL ACK



							
								if(datos->prioridad_procesos[i]==consultas)msgsnd(msqid, &mensaje,sizeof(struct msg), 0);
							
								printf("[ACK] Enviando OK  a %d \n",datos->id_nodos_pend[i]);
							}


				}

				//BORRAMOS LOS ACK PENDIENTES

				for (int i = 0; i <N; i++){
						datos->id_nodos_pend[i] = 0;

				}				
				printf("Todos los OK pendientes enviados\n");
			
				sem_post(sem_name_paso_consulta);
			}

		}
		
	
		if(max_prioridad==500){
			
			datos->primero=0;
			datos->prioridad_request = 0;
			
		}
				
		
	}
	printf("Fuera de la Sección Critica\n");
	}
}







