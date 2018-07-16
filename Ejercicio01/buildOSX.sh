#!/bin/bash

## Borro el directorio bin si ya existiera
if [ -d "./bin" ];
    then rm -r ./bin;
fi

## Creo el directorio para los binarios
mkdir ./bin/

## Compilo todo
g++    -Wall -std=c++11 -ldl -I./include/ main.cpp -o ./bin/main.out
g++ -shared -Wall -std=c++11 -fPIC -I./include/ ./src/Application/Application.cpp -o ./bin/Application.dylib
g++ -shared -Wall -std=c++11 -fPIC -I./include/ ./src/ConsoleGreeter/ConsoleGreeter.cpp -o ./bin/Greeter.dylib
##g++ -shared -Wall -std=c++11 -fPIC -I./include/ ./src/MessengerEnglish/MessengerEnglish.cpp -o ./bin/Messenger.dylib
g++ -shared -Wall -std=c++11 -fPIC -I./include/ ./src/MessengerSpanish/MessengerSpanish.cpp -o ./bin/Messenger.dylib

## Otorgo permisos de escritura al ejecutable
chmod +x ./bin/main.out

