#!/bin/bash

#Prueba de concurrencia de consultas 

#Borrar
clear



# Define la lista de programas y sus argumentos 
#0-> Pagos y Anulaciones 1->Reservas 2->Administración 3->Consultas

#Prueba 1
# programas_main=(
#   "./main_v3 0 4 4 0"
#   "./main_v3 0 4 4 1"
#   "./main_v3 0 4 4 2"
#   "./main_v3 3 4 4 0" 
#   "./main_v3 3 4 4 1"
#   "./main_v3 2 4 1 0" #Cuando llega este pagos tiene que parar todo atenderlos y despues ejecutar concurrentemente el resto de consultas
#   "./main_v3 2 4 4 1"
#   "./main_v3 2 4 4 2"
#   "./main_v3 1 4 4 0"
#   "./main_v3 1 4 4 1"
#   "./main_v3 1 4 4 2"
#   "./main_v3 1 4 4 3"
#   "./main_v3 1 4 4 4"
#   "./main_v3 0 4 4 3"
#   "./main_v3 0 4 4 4"
#   "./main_v3 3 4 4 2"
#   "./main_v3 3 4 4 3"
#   "./main_v3 3 4 4 4"
#   "./main_v3 2 4 4 3"
#   "./main_v3 2 4 4 4"
# )









programas_main=(
  "./main_v3 0 4 1 0"
  "./main_v3 0 4 2 1"
  "./main_v3 0 4 3 2"
  "./main_v3 3 4 3 0" 
  "./main_v3 3 4 2 1"
  "./main_v3 2 4 1 0" #Cuando llega este pagos tiene que parar todo atenderlos y despues ejecutar concurrentemente el resto de consultas
  "./main_v3 2 4 1 1"
  "./main_v3 2 4 2 2"
  "./main_v3 1 4 1 0"
  "./main_v3 1 4 1 1"
  "./main_v3 1 4 2 2"
  "./main_v3 1 4 3 3"
  "./main_v3 1 4 2 4"
  "./main_v3 0 4 1 3"
  "./main_v3 0 4 1 4"
  "./main_v3 3 4 2 2"
  "./main_v3 3 4 1 3"
  "./main_v3 3 4 3 4"
  "./main_v3 2 4 1 3"
  "./main_v3 2 4 1 4"
)







#  programas_main=(
# "./main_v3 0 10 3 0"
# "./main_v3 0 10 2 1"
# "./main_v3 0 10 2 2"
# "./main_v3 0 10 2 3"
# "./main_v3 0 10 1 4"
# "./main_v3 0 10 2 5"
# "./main_v3 0 10 2 6"
# "./main_v3 0 10 1 7"
# "./main_v3 0 10 4 8"
# "./main_v3 0 10 3 9"
# "./main_v3 0 10 1 10"
# "./main_v3 0 10 4 11"
# "./main_v3 0 10 1 12"
# "./main_v3 0 10 3 13"
# "./main_v3 0 10 3 14"
# "./main_v3 0 10 3 15"
# "./main_v3 0 10 4 16"
# "./main_v3 0 10 2 17"
# "./main_v3 0 10 3 18"
# "./main_v3 0 10 2 19"
# "./main_v3 1 10 2 0"
# "./main_v3 1 10 2 1"
# "./main_v3 1 10 2 2"
# "./main_v3 1 10 2 3"
# "./main_v3 1 10 1 4"
# "./main_v3 1 10 1 5"
# "./main_v3 1 10 4 6"
# "./main_v3 1 10 3 7"
# "./main_v3 1 10 2 8"
# "./main_v3 1 10 2 9"
# "./main_v3 1 10 3 10"
# "./main_v3 1 10 4 11"
# "./main_v3 1 10 4 12"
# "./main_v3 1 10 4 13"
# "./main_v3 1 10 4 14"
# "./main_v3 1 10 1 15"
# "./main_v3 1 10 4 16"
# "./main_v3 1 10 1 17"
# "./main_v3 1 10 4 18"
# "./main_v3 1 10 1 19"
# "./main_v3 2 10 1 0"
# "./main_v3 2 10 2 1"
# "./main_v3 2 10 1 2"
# "./main_v3 2 10 3 3"
# "./main_v3 2 10 2 4"
# "./main_v3 2 10 2 5"
# "./main_v3 2 10 4 6"
# "./main_v3 2 10 1 7"
# "./main_v3 2 10 1 8"
# "./main_v3 2 10 3 9"
# "./main_v3 2 10 3 10"
# "./main_v3 2 10 3 11"
# "./main_v3 2 10 3 12"
# "./main_v3 2 10 3 13"
# "./main_v3 2 10 1 14"
# "./main_v3 2 10 2 15"
# "./main_v3 2 10 4 16"
# "./main_v3 2 10 4 17"
# "./main_v3 2 10 3 18"
# "./main_v3 2 10 4 19"
# "./main_v3 3 10 1 0"
# "./main_v3 3 10 4 1"
# "./main_v3 3 10 3 2"
# "./main_v3 3 10 3 3"
# "./main_v3 3 10 1 4"
# "./main_v3 3 10 3 5"
# "./main_v3 3 10 2 6"
# "./main_v3 3 10 2 7"
# "./main_v3 3 10 1 8"
# "./main_v3 3 10 3 9"
# "./main_v3 3 10 2 10"
# "./main_v3 3 10 4 11"
# "./main_v3 3 10 2 12"
# "./main_v3 3 10 4 13"
# "./main_v3 3 10 2 14"
# "./main_v3 3 10 3 15"
# "./main_v3 3 10 2 16"
# "./main_v3 3 10 4 17"
# "./main_v3 3 10 1 18"
# "./main_v3 3 10 3 19"
# "./main_v3 4 10 3 0"
# "./main_v3 4 10 3 1"
# "./main_v3 4 10 4 2"
# "./main_v3 4 10 1 3"
# "./main_v3 4 10 2 4"
# "./main_v3 4 10 2 5"
# "./main_v3 4 10 4 6"
# "./main_v3 4 10 1 7"
# "./main_v3 4 10 3 8"
# "./main_v3 4 10 3 9"
# "./main_v3 4 10 3 10"
# "./main_v3 4 10 2 11"
# "./main_v3 4 10 1 12"
# "./main_v3 4 10 1 13"
# "./main_v3 4 10 3 14"
# "./main_v3 4 10 2 15"
# "./main_v3 4 10 4 16"
# "./main_v3 4 10 1 17"
# "./main_v3 4 10 3 18"
# "./main_v3 4 10 2 19"
# "./main_v3 5 10 3 0"
# "./main_v3 5 10 3 1"
# "./main_v3 5 10 4 2"
# "./main_v3 5 10 2 3"
# "./main_v3 5 10 3 4"
# "./main_v3 5 10 4 5"
# "./main_v3 5 10 2 6"
# "./main_v3 5 10 4 7"
# "./main_v3 5 10 4 8"
# "./main_v3 5 10 2 9"
# "./main_v3 5 10 3 10"
# "./main_v3 5 10 4 11"
# "./main_v3 5 10 1 12"
# "./main_v3 5 10 2 13"
# "./main_v3 5 10 2 14"
# "./main_v3 5 10 1 15"
# "./main_v3 5 10 4 16"
# "./main_v3 5 10 2 17"
# "./main_v3 5 10 4 18"
# "./main_v3 5 10 3 19"
# "./main_v3 6 10 2 0"
# "./main_v3 6 10 1 1"
# "./main_v3 6 10 2 2"
# "./main_v3 6 10 1 3"
# "./main_v3 6 10 1 4"
# "./main_v3 6 10 4 5"
# "./main_v3 6 10 4 6"
# "./main_v3 6 10 4 7"
# "./main_v3 6 10 4 8"
# "./main_v3 6 10 3 9"
# "./main_v3 6 10 1 10"
# "./main_v3 6 10 4 11"
# "./main_v3 6 10 4 12"
# "./main_v3 6 10 2 13"
# "./main_v3 6 10 4 14"
# "./main_v3 6 10 2 15"
# "./main_v3 6 10 1 16"
# "./main_v3 6 10 4 17"
# "./main_v3 6 10 2 18"
# "./main_v3 6 10 1 19"
# "./main_v3 7 10 1 0"
# "./main_v3 7 10 3 1"
# "./main_v3 7 10 4 2"
# "./main_v3 7 10 2 3"
# "./main_v3 7 10 4 4"
# "./main_v3 7 10 4 5"
# "./main_v3 7 10 2 6"
# "./main_v3 7 10 3 7"
# "./main_v3 7 10 2 8"
# "./main_v3 7 10 1 9"
# "./main_v3 7 10 4 10"
# "./main_v3 7 10 2 11"
# "./main_v3 7 10 2 12"
# "./main_v3 7 10 2 13"
# "./main_v3 7 10 4 14"
# "./main_v3 7 10 2 15"
# "./main_v3 7 10 4 16"
# "./main_v3 7 10 1 17"
# "./main_v3 7 10 4 18"
# "./main_v3 7 10 1 19"
# "./main_v3 8 10 3 0"
# "./main_v3 8 10 3 1"
# "./main_v3 8 10 4 2"
# "./main_v3 8 10 2 3"
# "./main_v3 8 10 1 4"
# "./main_v3 8 10 3 5"
# "./main_v3 8 10 4 6"
# "./main_v3 8 10 3 7"
# "./main_v3 8 10 2 8"
# "./main_v3 8 10 4 9"
# "./main_v3 8 10 2 10"
# "./main_v3 8 10 1 11"
# "./main_v3 8 10 3 12"
# "./main_v3 8 10 3 13"
# "./main_v3 8 10 1 14"
# "./main_v3 8 10 4 15"
# "./main_v3 8 10 3 16"
# "./main_v3 8 10 4 17"
# "./main_v3 8 10 4 18"
# "./main_v3 8 10 4 19"
# "./main_v3 9 10 1 0"
# "./main_v3 9 10 3 1"
# "./main_v3 9 10 1 2"
# "./main_v3 9 10 4 3"
# "./main_v3 9 10 1 4"
# "./main_v3 9 10 1 5"
# "./main_v3 9 10 1 6"
# "./main_v3 9 10 2 7"
# "./main_v3 9 10 4 8"
# "./main_v3 9 10 2 9"
# "./main_v3 9 10 2 10"
# "./main_v3 9 10 3 11"
# "./main_v3 9 10 2 12"
# "./main_v3 9 10 3 13"
# "./main_v3 9 10 4 14"
# "./main_v3 9 10 1 15"
# "./main_v3 9 10 3 16"
# "./main_v3 9 10 3 17"
# "./main_v3 9 10 3 18"
# "./main_v3 9 10 2 19"
#  )



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
