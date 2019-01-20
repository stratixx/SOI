# Author: Konrad Winnicki
# Github account: stratixx
# My makefile - type 'make all' to compile project

# Latest working version
###################################################################

# nazwa projektu
project_name = MalditoFS

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
all: malditoFS mkfsFS cpFS lsFS rmFS rmfsFS infoFS

# wyczyszczenie projektu
clean: 
	rm -r -f $o $b
	mkdir $o $b

# kompilacja poszczegolnych zaleznosci. wywolywane przez regule all
object0 = malditoFS
$(object0): $s/$(object0).cpp
	$(CC) $s/$(object0).cpp -c -o $o/$(object0).o

object1 = mkfsFS
$(object1): malditoFS $s/$(object1).cpp 
	$(CC) $o/malditoFS.o $s/$(object1).cpp   -o $b/$(object1)

object2 = cpFS
$(object2): malditoFS $s/$(object2).cpp
	$(CC) $o/malditoFS.o $s/$(object2).cpp     -o $b/$(object2)

object3 = lsFS
$(object3): malditoFS $s/$(object3).cpp
	$(CC) $o/malditoFS.o $s/$(object3).cpp     -o $b/$(object3)

object4 = rmFS
$(object4): malditoFS $s/$(object4).cpp
	$(CC) $o/malditoFS.o $s/$(object4).cpp     -o $b/$(object4)

object5 = rmfsFS
$(object5): malditoFS $s/$(object5).cpp
	$(CC) $o/malditoFS.o $s/$(object5).cpp   -o $b/$(object5)

object6 = infoFS
$(object6): malditoFS $s/$(object6).cpp 
	$(CC) $o/malditoFS.o $s/$(object6).cpp   -o $b/$(object6)


