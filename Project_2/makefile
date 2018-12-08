# Author: Konrad Winnicki
# Github account: stratixx
# My makefile - type 'make all' to compile project

# Latest working version
###################################################################

# nazwa projektu
project_name = project2

# komenda kompilacji
CC = gcc

# katalog zawierajacy pliki *.c
s = src

# katalog zawierajacy wynikowy plik wykonywalny 'project_name'
b = bin

# katalog zawierajacy skompilowane obiekty *.o
o = obj

###################################################################

# kompilacja wszystkich zaleznosci do pliku wykonywalnego
all: tools producer consumer

# wyczyszczenie projektu
clean: 
	rm -f $o/*.o $b/.

# kompilacja poszczegolnych zaleznosci. wywolywane przez regule all
object1 = tools
$(object1): $s/$(object1).c
	$(CC) $s/$(object1).c -c -o $o/$(object1).o

object2 = producer
$(object2): $s/$(object2).c $s/tools.c
	$(CC) $s/$(object2).c $s/tools.c -o $b/$(object2).bin

object3 = consumer
$(object3): $s/$(object3).c $s/tools.c
	$(CC) $s/$(object3).c $s/tools.c -o $b/$(object3).bin


