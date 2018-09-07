#!/bin/bash

##Borro el directorio si ya existiera
if [ -d "./sdis" ];
    then rm -r ./sdis;
fi
##Creo los directorios para el binario y las bibliotecas
mkdir ./sdis/
mkdir ./sdis/lib/

##compilo el binario
g++ -Wall -std=c++11 -ldl -I./include/ application.cpp -o ./sdis/application.exe

##compilo las bibliotecas
g++ -shared -Wall -std=c++11 -fPIC -I./include/ ./src/application/libapplication.cpp -o ./sdis/lib/libapplication.so

g++ -shared -Wall -std=c++11 -fPIC -I./include/ ./src/httprequesthandler/libhttprequesthandler.cpp -o ./sdis/lib/librequesthandler.so

g++ -shared -Wall -std=c++11 -fPIC -I./include/ ./src/potentialfunction/libpotentialfunction.cpp -o ./sdis/lib/libpotential.so
g++ -shared -Wall -std=c++11 -fPIC -I./include/ ./src/quadraticfunction/libquadraticfunction.cpp -o ./sdis/lib/libquadratic.so
g++ -shared -Wall -std=c++11 -fPIC -I./include/ ./src/sinusoidalfunction/libsinusoidalfunction.cpp -o ./sdis/lib/libsinusoidal.so
g++ -shared -Wall -std=c++11 -fPIC -I./include/ ./src/trapezoidsolver/libtrapezoidsolver.cpp -o ./sdis/lib/libtrapezoidsolver.so
g++ -shared -Wall -std=c++11 -fPIC -I./include/ ./src/simpsonsolver/libsimpsonsolver.cpp -o ./sdis/lib/libsimpsonsolver.so

##copio los archivos recursos de frontend, un readme.txt y la licencia
cp ./resources/index.html ./sdis/
cp ./resources/favicon.ico ./sdis/
cp ./resources/readme.txt ./sdis/
cp ./resources/LICENSE ./sdis/

##otorgo permisos de escritura a los ejecutables
chmod +x ./sdis/application.exe
