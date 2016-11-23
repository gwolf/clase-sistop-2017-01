#! /bin/bash

#Removemos los archivos anteriores
rm *.o dfs

#Compilamos
make -f makefile.mk

#Ejecutamos
./dfs
