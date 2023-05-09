#!/bin/bash

#Prueba de concurrencia de consultas 

#Borrar
clear



# Define la lista de programas y sus argumentos 
#0-> Pagos y Anulaciones 1->Reservas 2->Administración 3->Consultas

programas_main=(
"sudo ./main_v3 7 10 4 5"
"sudo ./main_v3 3 10 3 0"
"sudo ./main_v3 0 10 2 12"
"sudo ./main_v3 7 10 2 3"
"sudo ./main_v3 8 10 2 11"
"sudo ./main_v3 5 10 1 2"
"sudo ./main_v3 9 10 4 15"
"sudo ./main_v3 3 10 4 7"
"sudo ./main_v3 8 10 4 5"
"sudo ./main_v3 4 10 4 7"
"sudo ./main_v3 1 10 3 16"
"sudo ./main_v3 8 10 1 14"
"sudo ./main_v3 5 10 2 0"
"sudo ./main_v3 2 10 3 10"
"sudo ./main_v3 0 10 2 17"
"sudo ./main_v3 9 10 3 10"
"sudo ./main_v3 0 10 2 4"
"sudo ./main_v3 6 10 3 13"
"sudo ./main_v3 5 10 4 7"
"sudo ./main_v3 6 10 3 0"
"sudo ./main_v3 5 10 4 1"
"sudo ./main_v3 0 10 3 6"
"sudo ./main_v3 7 10 3 10"
"sudo ./main_v3 3 10 4 14"
"sudo ./main_v3 2 10 1 0"
"sudo ./main_v3 6 10 4 10"
"sudo ./main_v3 3 10 2 6"
"sudo ./main_v3 1 10 4 10"
"sudo ./main_v3 8 10 1 12"
"sudo ./main_v3 6 10 2 4"
"sudo ./main_v3 7 10 2 14"
"sudo ./main_v3 0 10 1 13"
"sudo ./main_v3 2 10 2 11"
"sudo ./main_v3 4 10 2 14"
"sudo ./main_v3 5 10 2 15"
"sudo ./main_v3 3 10 3 16"
"sudo ./main_v3 0 10 1 2"
"sudo ./main_v3 6 10 4 18"
"sudo ./main_v3 7 10 3 19"
"sudo ./main_v3 7 10 3 9"
"sudo ./main_v3 0 10 2 5"
"sudo ./main_v3 2 10 4 3"
"sudo ./main_v3 8 10 3 10"
"sudo ./main_v3 1 10 4 0"
"sudo ./main_v3 9 10 3 14"
"sudo ./main_v3 7 10 4 1"
"sudo ./main_v3 1 10 1 19"
"sudo ./main_v3 4 10 3 4"
"sudo ./main_v3 6 10 2 3"
"sudo ./main_v3 2 10 2 13"
"sudo ./main_v3 1 10 3 11"
"sudo ./main_v3 3 10 3 13"
"sudo ./main_v3 3 10 1 18"
"sudo ./main_v3 0 10 1 9"
"sudo ./main_v3 9 10 1 2"
"sudo ./main_v3 2 10 2 12"
"sudo ./main_v3 6 10 1 15"
"sudo ./main_v3 3 10 1 15"
"sudo ./main_v3 6 10 2 9"
"sudo ./main_v3 9 10 1 0"
"sudo ./main_v3 8 10 3 9"
"sudo ./main_v3 7 10 1 11"
"sudo ./main_v3 5 10 2 13"
"sudo ./main_v3 4 10 1 6"
"sudo ./main_v3 4 10 1 2"
"sudo ./main_v3 5 10 4 17"
"sudo ./main_v3 4 10 2 18"
"sudo ./main_v3 9 10 3 18"
"sudo ./main_v3 9 10 3 13"
"sudo ./main_v3 0 10 4 15"
"sudo ./main_v3 4 10 2 16"
"sudo ./main_v3 7 10 3 12"
"sudo ./main_v3 8 10 2 7"
"sudo ./main_v3 2 10 4 17"
"sudo ./main_v3 2 10 1 16"
"sudo ./main_v3 8 10 2 13"
"sudo ./main_v3 4 10 1 10"
"sudo ./main_v3 5 10 1 12"
"sudo ./main_v3 8 10 3 18"
"sudo ./main_v3 8 10 3 6"
"sudo ./main_v3 4 10 2 15"
"sudo ./main_v3 1 10 1 2"
"sudo ./main_v3 6 10 4 6"
"sudo ./main_v3 3 10 1 9"
"sudo ./main_v3 4 10 4 13"
"sudo ./main_v3 1 10 4 14"
"sudo ./main_v3 8 10 3 15"
"sudo ./main_v3 2 10 4 7"
"sudo ./main_v3 1 10 3 5"
"sudo ./main_v3 7 10 2 7"
"sudo ./main_v3 5 10 1 14"
"sudo ./main_v3 2 10 1 6"
"sudo ./main_v3 1 10 3 6"
"sudo ./main_v3 5 10 1 6"
"sudo ./main_v3 5 10 2 4"
"sudo ./main_v3 6 10 3 7"
"sudo ./main_v3 0 10 3 18"
"sudo ./main_v3 3 10 2 4"
"sudo ./main_v3 0 10 1 10"
"sudo ./main_v3 3 10 3 12"
"sudo ./main_v3 5 10 4 11"
"sudo ./main_v3 3 10 1 17"
"sudo ./main_v3 4 10 2 8"
"sudo ./main_v3 8 10 1 8"
"sudo ./main_v3 4 10 2 9"
"sudo ./main_v3 7 10 4 8"
"sudo ./main_v3 1 10 2 12"
"sudo ./main_v3 4 10 3 5"
"sudo ./main_v3 1 10 4 13"
"sudo ./main_v3 6 10 1 19"
"sudo ./main_v3 1 10 1 7"
"sudo ./main_v3 3 10 4 10"
"sudo ./main_v3 6 10 1 16"
"sudo ./main_v3 2 10 4 1"
"sudo ./main_v3 2 10 1 19"
"sudo ./main_v3 8 10 2 2"
"sudo ./main_v3 4 10 4 3"
"sudo ./main_v3 1 10 3 9"
"sudo ./main_v3 1 10 3 1"
"sudo ./main_v3 5 10 3 8"
"sudo ./main_v3 0 10 3 16"
"sudo ./main_v3 1 10 1 8"
"sudo ./main_v3 8 10 1 19"
"sudo ./main_v3 7 10 4 2"
"sudo ./main_v3 0 10 1 8"
"sudo ./main_v3 5 10 4 5"
"sudo ./main_v3 3 10 1 2"
"sudo ./main_v3 2 10 1 4"
"sudo ./main_v3 4 10 4 1"
"sudo ./main_v3 7 10 3 15"
"sudo ./main_v3 2 10 4 2"
"sudo ./main_v3 9 10 1 11"
"sudo ./main_v3 0 10 2 3"
"sudo ./main_v3 4 10 2 0"
"sudo ./main_v3 9 10 2 9"
"sudo ./main_v3 8 10 2 4"
"sudo ./main_v3 0 10 4 19"
"sudo ./main_v3 2 10 3 9"
"sudo ./main_v3 0 10 3 7"
"sudo ./main_v3 7 10 1 16"
"sudo ./main_v3 1 10 4 4"
"sudo ./main_v3 9 10 4 4"
"sudo ./main_v3 2 10 4 18"
"sudo ./main_v3 0 10 4 0"
"sudo ./main_v3 9 10 1 5"
"sudo ./main_v3 9 10 4 17"
"sudo ./main_v3 9 10 1 1"
"sudo ./main_v3 1 10 2 17"
"sudo ./main_v3 6 10 3 11"
"sudo ./main_v3 1 10 3 3"
"sudo ./main_v3 7 10 4 13"
"sudo ./main_v3 4 10 4 11"
"sudo ./main_v3 7 10 4 18"
"sudo ./main_v3 7 10 4 4"
"sudo ./main_v3 8 10 2 1"
"sudo ./main_v3 3 10 3 5"
"sudo ./main_v3 3 10 4 3"
"sudo ./main_v3 9 10 1 8"
"sudo ./main_v3 4 10 4 19"
"sudo ./main_v3 4 10 3 12"
"sudo ./main_v3 2 10 4 8"
"sudo ./main_v3 7 10 2 6"
"sudo ./main_v3 7 10 3 17"
"sudo ./main_v3 3 10 2 11"
"sudo ./main_v3 9 10 4 7"
"sudo ./main_v3 8 10 4 3"
"sudo ./main_v3 9 10 3 12"
"sudo ./main_v3 1 10 3 15"
"sudo ./main_v3 6 10 4 17"
"sudo ./main_v3 0 10 2 14"
"sudo ./main_v3 9 10 1 3"
"sudo ./main_v3 2 10 1 15"
"sudo ./main_v3 2 10 3 5"
"sudo ./main_v3 9 10 4 16"
"sudo ./main_v3 9 10 3 19"
"sudo ./main_v3 9 10 1 6"
"sudo ./main_v3 5 10 2 16"
"sudo ./main_v3 5 10 4 19"
"sudo ./main_v3 0 10 2 11"
"sudo ./main_v3 5 10 1 3"
"sudo ./main_v3 6 10 4 14"
"sudo ./main_v3 6 10 4 2"
"sudo ./main_v3 8 10 1 0"
"sudo ./main_v3 3 10 1 1"
"sudo ./main_v3 2 10 1 14"
"sudo ./main_v3 6 10 4 12"
"sudo ./main_v3 3 10 2 19"
"sudo ./main_v3 8 10 2 17"
"sudo ./main_v3 5 10 2 9"
"sudo ./main_v3 7 10 3 0"
"sudo ./main_v3 4 10 3 17"
"sudo ./main_v3 5 10 2 18"
"sudo ./main_v3 1 10 3 18"
"sudo ./main_v3 3 10 4 8"
"sudo ./main_v3 6 10 2 8"
"sudo ./main_v3 0 10 2 1"
"sudo ./main_v3 6 10 3 1"
"sudo ./main_v3 5 10 4 10"
"sudo ./main_v3 6 10 3 5"
"sudo ./main_v3 8 10 2 16"
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