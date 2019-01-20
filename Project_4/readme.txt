Wydział Elektroniki i Technik Informacyjnych, 
Politechnika Warszawska

-------------------------------------------------------------


System plików MalditoFS stworzony w ramach przedmiotu Systemy Operacyjne, 


----------------------------------------------------------------

aby skorzystać należy kolejno wywołać w głównym katalogu projektu polecenia:
    -   make clean
    -   make all

aby uruchamiać programy jako polecenia konsoli należy dodać folder bin do PATH:
    -   export PATH=$PATH":./bin"

dostępne polecenia:
    -   mkfsFS  -   stworzenie systemu plików
    -   rmfsFS  -   usunięcie systemu plików
    -   infoFS  -   wypisanie informacji o systemie plików
    -   lsFS    -   wypisanie zawartości systemu plików
    -   cpFS    -   kopiowanie dwukierunkowe plików na system plików
    -   rmFS    -   usunięcie plików z systemu plików

Polecenia w ogólności zachowują się tak ich systemowe odpowiedniki bez dopisku 'FS'
Więcej informacji o poleceniach można uzyskać po wpisaniu nazwy polecenia z argumentem --help