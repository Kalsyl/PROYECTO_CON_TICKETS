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



#define N 4
#define cola_main 0
#define cola_receptor 1

// -------------VARIABLES COMPARTIDAS--------------
typedef struct datos_comp{
	int mi_ticket;
	int mi_id;
	int id_nodos_pend[100];
	int num_pend;
	int quiero;
	int max_ticket;
	//añadidas
	int dentro;
	int procesos;
}datos_comp;

struct enviar{
	int mi_ticket;
	int mi_pid;
	int mi_id;
	char text[100];
	long type;
}datos_enviar;

struct recibir{
	long type;
	int id_nodo;
}datos_recibir;

struct enviar_ack{ 
    long type;
    int mi_pid;
}ack;

pid_t getpid(void);
int main(int argc,char *argv[]) {
	
 
	//----------VARIABLES PROPIAS-------------------------------
	int i=0;
	int posicion=atoi(argv[1]);
	int id_nodos=1235+posicion;
	int buzon=getpid();
	
	char* cadena="Quiero entrar en la SC";
	strcpy(datos_enviar.text,cadena);
	
	 if (argc != 2){
		printf("formato incorrecto: ./v1_main posicion \n");
		exit(-1);
	}
	
	
	//----------VARIABLES DE LA MEMORIA COMPARTIDA---------------
	key_t clave1; //clave de acceso a la memoria 1
	int shmid1; //identificador de la zona de memoria 1
	
	//-------------INICIALIZAMOS ZONA DE MEMORIA COMPARTIDA--------------

	clave1 = ftok(".",posicion); //creamos la clave que utilizaremos para vincularnos a la zona de memoria ya creada
	 
	shmid1 = shmget(clave1,8*sizeof(int),0);//Creación de zona_mem1, Al no poner el flag IPC_CREAT, estamos suponiendo que dicha memoria ya está creada.
	 
	if(shmid1 !=-1){
		printf("Zona de memoria vinculada OK! con identificador %d \n", shmid1);
	}else{
		printf("ERROR al crear zona de memoria 1 !! \n");
		exit(1);
	}
	 
	datos_comp *datos =(datos_comp *)shmat(shmid1,0,0);//Vinculamos el proceso con la zona de memoria
	 
	if(datos == (datos_comp*)-1){
		printf("Error al vincular el proceso a la zona de memoria 1! \n");
		exit(1);
	} 

	//---------------------------------------DECLARACION SEMÁFOROS---------------------
	char name_mutex[50];
	sprintf(name_mutex, "/MUTEX%s", argv[1]);
	sem_t *sem_mutex;
	sem_mutex = sem_open(name_mutex, O_CREAT, 0777, 1);
	if (sem_mutex == SEM_FAILED) {
	     perror("Failed to open semphore for empty");
	     exit(-1);
	}
	char name_mutex2[50];
	sprintf(name_mutex2, "/MUTEX%s", argv[1]);
	sem_t *sem_mutex2;
	sem_mutex2 = sem_open(name_mutex2, O_CREAT, 0777, 1);
	if (sem_mutex2 == SEM_FAILED) {
	     perror("Failed to open semphore for empty");
	     exit(-1);
	}
	char name_mutex3[50];
	sprintf(name_mutex3, "/MUTEX%s", argv[1]);
	sem_t *sem_mutex3;
	sem_mutex3 = sem_open(name_mutex3, O_CREAT, 0777, 1);
	if (sem_mutex3 == SEM_FAILED) {
	     perror("Failed to open semphore for empty");
	     exit(-1);
	}
	char name_mutex_between_main[50];
	sprintf(name_mutex_between_main, "/MUTEXMAIN%s", argv[1]);
	sem_t *sem_mutex_between_main;
	sem_mutex_between_main = sem_open(name_mutex_between_main, O_CREAT, 0777, 1);
	if (sem_mutex_between_main == SEM_FAILED) {
	     perror("Failed to open semphore for empty");
	     exit(-1);
	}
		
	//-------------------INICIALIZACIÓN DE LAS VARIABLES COMPARTIDAS--------------------
	datos->mi_id=id_nodos;
	datos->mi_ticket=0;
	datos->quiero=0;
	for(int i=0;i<N;i++){
		datos->id_nodos_pend[i]=0;
	}
	datos->num_pend=0;
	datos->max_ticket=0;
	datos->procesos++;

	datos_enviar.mi_ticket=0;
	
	printf("Mi PID %d\n",getpid());
	printf("Numero de procesos %d\n",datos->procesos);

	//--------------------------BUCLE DE ACCIONES DEL PROGRAMA-----------------------
	while (1) { 
		// Sección no crítica
		printf("Esperando para entrar en la Sección Critica\n");
		getchar();
		// Sección crítica
	 	printf("Quiero entrar en la Sección Critica\n");
	 	
	 	sem_wait(sem_mutex);
		datos->quiero = 1;
		//datos->dentro++; 
		datos->mi_ticket = datos->max_ticket + 1; // generas un ticket mayor que el ultimo 
		sem_post(sem_mutex);
		
		datos_enviar.mi_ticket=datos->mi_ticket;
		datos_enviar.mi_pid=getpid();
		datos_enviar.mi_id=id_nodos;
	
		for (i = 0; i <=N-1; i++){
			if(1235+i==id_nodos){}
			else{
				datos_enviar.type=1235+i;
				msgsnd(cola_receptor, &datos_enviar, sizeof(datos_enviar.text)+3*sizeof(int), 0);//envias mensajes request a todos los nodos,incluido a ti
				
				printf("Mensaje enviado a %ld\n",datos_enviar.type);
			}
		}
		
		
		for (i = 0; i < N-1; i++){
	
			msgrcv(cola_main, &datos_recibir, sizeof(int),buzon, 0);
			printf("Mensaje OK recibido de %d\n",datos_recibir.id_nodo);
		}
		
		printf("Voy a entrar a la seccion critica\n");
		
		sem_wait(sem_mutex3);
		datos->dentro++;
		sem_post(sem_mutex3);
		
		sem_wait(sem_mutex_between_main);
		
		printf("Tengo todos los permisos,entrando en la Sección Crítica...\n");
		
		
		//SECCIÓN CRÍTICA; 

		printf("En la Seccion Crítica\n");
		//printf("Dentro %d\n",datos->dentro);
		
		getchar();
		
		printf("Saliendo de la sección crítica...\n");
		
		sem_wait(sem_mutex2);
		datos->quiero=0;
		datos->dentro--;
		sem_post(sem_mutex2);
		
		
		sem_post(sem_mutex_between_main);
		
		
		if(datos->dentro==0){
			for (i = 0; i <datos->num_pend; i++){
				
				ack.mi_pid=getpid();
				ack.type=datos->id_nodos_pend[i];
					
				msgsnd(cola_main, &ack, sizeof(int), 0); //envias las respuestas que te qudaron pendientes, por estar dentro o por que sean mayor que tu
				
				printf("Enviando OK pendiente a %d \n",datos->id_nodos_pend[i]);
			}
		
			datos->num_pend = 0; 
			
			printf("Todos los OK pendientes enviados\n");
		}
		
		
		printf("Fuera de la Sección Critica\n");		
		
	}
	 
}





