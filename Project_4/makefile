# Author: Konrad Winnicki
# Github account: stratixx
# My makefile - type 'make all' to compile project

# Latest working version
###################################################################

# nazwa projektu
project_name = MFS

# komenda kompilacji
CC = g++

# katalog zawierajacy pliki *.c
s = src

# katalog zawierajacy wynikowy plik wykonywalny 'project_name'
b = bin

# katalog zawierajacy skompilowane obiekty *.o
o = obj

###################################################################

# kompilacja wszystkich zaleznosci do pliku wykonywalnego
all: mfs mkmfs cpmfs lsmfs rmmfs infomfs

# wyczyszczenie projektu
clean: 
	rm -r -f $o $b
	mkdir $o $b

# kompilacja poszczegolnych zaleznosci. wywolywane przez regule all
object0 = mfs
$(object0): $s/$(object0).cpp
	$(CC) $s/$(object0).cpp  -c -o $o/$(object0).o

object1 = mkmfs
$(object1): mfs $s/$(object1).cpp 
	$(CC) $o/mfs.o $s/$(object1).cpp     -o $b/$(object1)

object2 = cpmfs
$(object2): mfs $s/$(object2).cpp
	$(CC) $o/mfs.o $s/$(object2).cpp     -o $b/$(object2)

object3 = lsmfs
$(object3): mfs $s/$(object3).cpp
	$(CC) $o/mfs.o $s/$(object3).cpp     -o $b/$(object3)

object4 = rmmfs
$(object4): mfs $s/$(object4).cpp
	$(CC) $o/mfs.o $s/$(object4).cpp     -o $b/$(object4)

object6 = infomfs
$(object6): mfs $s/$(object6).cpp 
	$(CC) $o/mfs.o $s/$(object6).cpp   -o $b/$(object6)


