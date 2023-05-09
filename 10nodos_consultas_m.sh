#!/bin/bash

#Prueba de concurrencia de consultas 

#Borrar
clear



# Define la lista de programas y sus argumentos 
#0-> Pagos y Anulaciones 1->Reservas 2->Administración 3->Consultas

programas_main=(
"sudo ./main_v3 9 10 4 0"
"sudo ./main_v3 1 10 4 3"
"sudo ./main_v3 0 10 4 3"
"sudo ./main_v3 2 10 4 5"
"sudo ./main_v3 8 10 4 12"
"sudo ./main_v3 7 10 4 15"
"sudo ./main_v3 1 10 4 7"
"sudo ./main_v3 6 10 4 14"
"sudo ./main_v3 4 10 4 6"
"sudo ./main_v3 9 10 4 3"
"sudo ./main_v3 0 10 4 8"
"sudo ./main_v3 8 10 4 5"
"sudo ./main_v3 9 10 4 1"
"sudo ./main_v3 6 10 4 3"
"sudo ./main_v3 5 10 4 4"
"sudo ./main_v3 5 10 4 11"
"sudo ./main_v3 7 10 4 13"
"sudo ./main_v3 0 10 4 12"
"sudo ./main_v3 7 10 4 4"
"sudo ./main_v3 9 10 4 11"
"sudo ./main_v3 4 10 4 14"
"sudo ./main_v3 2 10 4 13"
"sudo ./main_v3 9 10 4 18"
"sudo ./main_v3 6 10 4 16"
"sudo ./main_v3 1 10 4 6"
"sudo ./main_v3 1 10 4 10"
"sudo ./main_v3 8 10 4 1"
"sudo ./main_v3 4 10 4 13"
"sudo ./main_v3 2 10 4 12"
"sudo ./main_v3 2 10 4 2"
"sudo ./main_v3 1 10 4 5"
"sudo ./main_v3 0 10 4 14"
"sudo ./main_v3 8 10 4 15"
"sudo ./main_v3 8 10 4 16"
"sudo ./main_v3 1 10 4 13"
"sudo ./main_v3 7 10 4 9"
"sudo ./main_v3 5 10 4 7"
"sudo ./main_v3 3 10 4 18"
"sudo ./main_v3 8 10 4 2"
"sudo ./main_v3 8 10 4 10"
"sudo ./main_v3 2 10 4 16"
"sudo ./main_v3 8 10 4 0"
"sudo ./main_v3 4 10 4 11"
"sudo ./main_v3 9 10 4 17"
"sudo ./main_v3 2 10 4 4"
"sudo ./main_v3 7 10 4 17"
"sudo ./main_v3 9 10 4 9"
"sudo ./main_v3 5 10 4 6"
"sudo ./main_v3 6 10 4 5"
"sudo ./main_v3 1 10 4 18"
"sudo ./main_v3 3 10 4 15"
"sudo ./main_v3 7 10 4 19"
"sudo ./main_v3 7 10 4 16"
"sudo ./main_v3 6 10 4 2"
"sudo ./main_v3 7 10 4 2"
"sudo ./main_v3 9 10 4 10"
"sudo ./main_v3 6 10 4 15"
"sudo ./main_v3 4 10 4 12"
"sudo ./main_v3 4 10 4 16"
"sudo ./main_v3 8 10 4 7"
"sudo ./main_v3 2 10 4 0"
"sudo ./main_v3 2 10 4 10"
"sudo ./main_v3 6 10 4 6"
"sudo ./main_v3 9 10 4 8"
"sudo ./main_v3 2 10 4 18"
"sudo ./main_v3 5 10 4 5"
"sudo ./main_v3 2 10 4 11"
"sudo ./main_v3 5 10 4 15"
"sudo ./main_v3 6 10 4 19"
"sudo ./main_v3 9 10 4 19"
"sudo ./main_v3 7 10 4 10"
"sudo ./main_v3 0 10 4 16"
"sudo ./main_v3 9 10 4 14"
"sudo ./main_v3 4 10 4 5"
"sudo ./main_v3 6 10 4 7"
"sudo ./main_v3 9 10 4 13"
"sudo ./main_v3 8 10 4 14"
"sudo ./main_v3 2 10 4 1"
"sudo ./main_v3 6 10 4 13"
"sudo ./main_v3 1 10 4 0"
"sudo ./main_v3 9 10 4 6"
"sudo ./main_v3 4 10 4 3"
"sudo ./main_v3 1 10 4 12"
"sudo ./main_v3 9 10 4 5"
"sudo ./main_v3 3 10 4 10"
"sudo ./main_v3 6 10 4 9"
"sudo ./main_v3 2 10 4 15"
"sudo ./main_v3 8 10 4 3"
"sudo ./main_v3 5 10 4 9"
"sudo ./main_v3 5 10 4 17"
"sudo ./main_v3 1 10 4 19"
"sudo ./main_v3 7 10 4 14"
"sudo ./main_v3 5 10 4 14"
"sudo ./main_v3 7 10 4 18"
"sudo ./main_v3 0 10 4 18"
"sudo ./main_v3 4 10 4 2"
"sudo ./main_v3 0 10 4 15"
"sudo ./main_v3 3 10 4 7"
"sudo ./main_v3 2 10 4 3"
"sudo ./main_v3 7 10 4 5"
"sudo ./main_v3 3 10 4 13"
"sudo ./main_v3 6 10 4 12"
"sudo ./main_v3 3 10 4 4"
"sudo ./main_v3 4 10 4 4"
"sudo ./main_v3 0 10 4 10"
"sudo ./main_v3 0 10 4 5"
"sudo ./main_v3 3 10 4 3"
"sudo ./main_v3 8 10 4 6"
"sudo ./main_v3 4 10 4 18"
"sudo ./main_v3 9 10 4 12"
"sudo ./main_v3 1 10 4 8"
"sudo ./main_v3 7 10 4 6"
"sudo ./main_v3 6 10 4 4"
"sudo ./main_v3 0 10 4 4"
"sudo ./main_v3 4 10 4 10"
"sudo ./main_v3 3 10 4 1"
"sudo ./main_v3 3 10 4 16"
"sudo ./main_v3 0 10 4 13"
"sudo ./main_v3 3 10 4 5"
"sudo ./main_v3 5 10 4 2"
"sudo ./main_v3 7 10 4 3"
"sudo ./main_v3 2 10 1 9"
"sudo ./main_v3 8 10 4 17"
"sudo ./main_v3 5 10 4 18"
"sudo ./main_v3 0 10 4 1"
"sudo ./main_v3 3 10 4 9"
"sudo ./main_v3 4 10 4 1"
"sudo ./main_v3 5 10 4 0"
"sudo ./main_v3 7 10 4 1"
"sudo ./main_v3 4 10 4 7"
"sudo ./main_v3 1 10 4 17"
"sudo ./main_v3 2 10 4 19"
"sudo ./main_v3 9 10 4 7"
"sudo ./main_v3 7 10 4 0"
"sudo ./main_v3 4 10 4 17"
"sudo ./main_v3 2 10 4 8"
"sudo ./main_v3 5 10 1 8"
"sudo ./main_v3 9 10 4 4"
"sudo ./main_v3 8 10 4 13"
"sudo ./main_v3 3 10 4 14"
"sudo ./main_v3 0 10 4 0"
"sudo ./main_v3 5 10 4 16"
"sudo ./main_v3 6 10 4 18"
"sudo ./main_v3 6 10 4 1"
"sudo ./main_v3 8 10 4 4"
"sudo ./main_v3 8 10 4 18"
"sudo ./main_v3 5 10 4 3"
"sudo ./main_v3 1 10 4 4"
"sudo ./main_v3 9 10 4 2"
"sudo ./main_v3 6 10 4 10"
"sudo ./main_v3 4 10 4 19"
"sudo ./main_v3 8 10 4 19"
"sudo ./main_v3 1 10 4 14"
"sudo ./main_v3 7 10 4 7"
"sudo ./main_v3 6 10 4 0"
"sudo ./main_v3 5 10 4 12"
"sudo ./main_v3 3 10 4 6"
"sudo ./main_v3 7 10 4 11"
"sudo ./main_v3 2 10 4 7"
"sudo ./main_v3 4 10 4 15"
"sudo ./main_v3 0 10 4 6"
"sudo ./main_v3 6 10 4 11"
"sudo ./main_v3 9 10 4 16"
"sudo ./main_v3 3 10 4 19"
"sudo ./main_v3 5 10 4 10"
"sudo ./main_v3 4 10 4 0"
"sudo ./main_v3 3 10 4 2"
"sudo ./main_v3 3 10 4 11"
"sudo ./main_v3 4 10 4 8"
"sudo ./main_v3 1 10 4 1"
"sudo ./main_v3 8 10 4 9"
"sudo ./main_v3 9 10 4 15"
"sudo ./main_v3 3 10 4 17"
"sudo ./main_v3 5 10 4 1"
"sudo ./main_v3 3 10 4 8"
"sudo ./main_v3 5 10 4 13"
"sudo ./main_v3 0 10 4 11"
"sudo ./main_v3 6 10 4 8"
"sudo ./main_v3 3 10 4 12"
"sudo ./main_v3 4 10 4 9"
"sudo ./main_v3 8 10 4 11"
"sudo ./main_v3 1 10 4 15"
"sudo ./main_v3 1 10 4 11"
"sudo ./main_v3 7 10 4 12"
"sudo ./main_v3 0 10 4 2"
"sudo ./main_v3 6 10 4 17"
"sudo ./main_v3 2 10 4 6"
"sudo ./main_v3 7 10 4 8"
"sudo ./main_v3 2 10 4 14"
"sudo ./main_v3 0 10 4 17"
"sudo ./main_v3 0 10 4 9"
"sudo ./main_v3 1 10 4 16"
"sudo ./main_v3 0 10 4 7"
"sudo ./main_v3 3 10 4 0"
"sudo ./main_v3 5 10 4 19"
"sudo ./main_v3 2 10 4 17"
"sudo ./main_v3 1 10 4 9"
"sudo ./main_v3 0 10 4 19"
"sudo ./main_v3 1 10 4 2"
"sudo ./main_v3 8 10 4 8"
)

procesos_lanzados=0


# Itera sobre la lista de programas y abre una nueva ventana de terminal para cada uno

i=1
for programa in "${programas_main[@]}"
do
echo "Ejecutando $i"
 $programa &
     ((procesos_lanzados++))
((i++))

done

# Esperar a que todos los procesos hayan finalizado
while [ $procesos_lanzados -gt 0 ]
do
    wait
    ((procesos_lanzados--))
done

echo "Todos los procesos han finalizado"