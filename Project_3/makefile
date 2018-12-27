# Author: Konrad Winnicki
# Github account: stratixx
# My makefile - type 'make all' to compile project

# Latest working version
###################################################################

# nazwa projektu
project_name = project3

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
all: main tools monitor queue producer prosumer special protector
	$(CC) $o/main.o $o/tools.o $o/monitor.o $o/queue.o $o/producer.o $o/prosumer.o $o/special.o $o/protector.o -o $b/project3.bin

# wyczyszczenie projektu
clean: 
	rm -r -f $o $b
	mkdir $o $b

# kompilacja poszczegolnych zaleznosci. wywolywane przez regule all
object1 = tools
$(object1): $s/$(object1).cpp
	$(CC) $s/$(object1).cpp  -c -o $o/$(object1).o

object2 = producer
$(object2): $s/$(object2).cpp
	$(CC) $s/$(object2).cpp  -c -o $o/$(object2).o

object3 = prosumer
$(object3): $s/$(object3).cpp
	$(CC) $s/$(object3).cpp  -c -o $o/$(object3).o

object4 = special
$(object4): $s/$(object4).cpp
	$(CC) $s/$(object4).cpp  -c -o $o/$(object4).o

object5 = main
$(object5): $s/$(object5).cpp
	$(CC) $s/$(object5).cpp  -c -o $o/$(object5).o

object6 = protector
$(object6): $s/$(object6).cpp
	$(CC) $s/$(object6).cpp  -c -o $o/$(object6).o

object7 = queue
$(object7): $s/$(object7).cpp
	$(CC) $s/$(object7).cpp  -c -o $o/$(object7).o

object8 = monitor
$(object8): $s/$(object8).cpp
	$(CC) $s/$(object8).cpp  -c -o $o/$(object8).o


