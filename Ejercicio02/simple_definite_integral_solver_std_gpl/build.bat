:: Borro el directorio de binarios si ya existiera
IF EXIST .\sdis RMDIR /S /Q .\sdis

:: Creo los directorios para el binario y las bibliotecas
MD .\sdis
MD .\sdis\lib\

::compilo el binario
g++ -Wall -std=c++11 -I.\include\ application.cpp -o .\sdis\application.exe

::compilo las bibliotecas
g++ -shared -Wall -std=c++11 -I.\include\ .\src\application\libapplication.cpp -o .\sdis\lib\libapplication.dll

g++ -shared -Wall -std=c++11 -I.\include\ .\src\httprequesthandler\libhttprequesthandler.cpp -o .\sdis\lib\librequesthandler.dll

g++ -shared -Wall -std=c++11 -I.\include\ .\src\potentialfunction\libpotentialfunction.cpp -o .\sdis\lib\libpotential.dll
g++ -shared -Wall -std=c++11 -I.\include\ .\src\quadraticfunction\libquadraticfunction.cpp -o .\sdis\lib\libquadratic.dll
g++ -shared -Wall -std=c++11 -I.\include\ .\src\sinusoidalfunction\libsinusoidalfunction.cpp -o .\sdis\lib\libsinusoidal.dll
g++ -shared -Wall -std=c++11 -I.\include\ .\src\trapezoidsolver\libtrapezoidsolver.cpp -o .\sdis\lib\libtrapezoidsolver.dll
g++ -shared -Wall -std=c++11 -I.\include\ .\src\simpsonsolver\libsimpsonsolver.cpp -o .\sdis\lib\libsimpsonsolver.dll

::copio los archivos de frontend y la licencia
cp .\resources\index.html .\sdis\
cp .\resources\favicon.ico .\sdis\
cp .\resources\readme.txt .\sdis\
cp .\resources\LICENSE .\sdis\