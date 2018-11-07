# Author: Konrad Winnicki
# Github account: stratixx
# My makefile - type 'make all' to compile project

# Latest working version
###################################################################

# nazwa projektu
project_name = getprocnr

# komenda kompilacji
CC = cc

# katalog zawierajacy pliki *.c
s = src

# katalog zawierajacy wynikowy plik wykonywalny 'project_name'
b = bin

# katalog zawierajacy skompilowane obiekty *.o
o = obj

###################################################################

# kompilacja wszystkich zaleznosci do pliku wykonywalnego
all: main
	$(CC) $o/main.o -o $b/$(project_name)

# wyczyszczenie projektu
clean: 
	rm -f $o/*.o $b/$(project_name)

# kompilacja poszczegolnych zaleznosci. wywolywane przez regule all
object1 = main
$(object1): $s/$(object1).c
	$(CC) $s/$(object1).c -c -o $o/$(object1).o


