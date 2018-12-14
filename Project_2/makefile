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
all: main tools producer prosumer special
	$(CC) $o/main.o $o/tools.o $o/producer.o $o/prosumer.o $o/special.o -o $b/project2.bin
	#$(CC) $o/producer.o $o/tools.o -o $b/producer.bin
	#$(CC) $o/prosumer.o $o/tools.o -o $b/prosumer.bin
	#$(CC) $o/special.o  $o/tools.o -o $b/special.bin

# wyczyszczenie projektu
clean: 
	rm -r -f $o $b
	mkdir $o $b

# kompilacja poszczegolnych zaleznosci. wywolywane przez regule all
object1 = tools
$(object1): $s/$(object1).c
	$(CC) $s/$(object1).c    -c -o $o/$(object1).o

object2 = producer
$(object2): $s/$(object2).c
	$(CC) $s/$(object2).c -c -o $o/$(object2).o

object3 = prosumer
$(object3): $s/$(object3).c
	$(CC) $s/$(object3).c -c -o $o/$(object3).o

object4 = special
$(object4): $s/$(object4).c
	$(CC) $s/$(object4).c  -c -o $o/$(object4).o

object5 = main
$(object5): $s/$(object5).c
	$(CC) $s/$(object5).c  -c -o $o/$(object5).o


