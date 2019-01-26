export PATH=$PATH":./../bin"
mkmfs disc 1000
echo "----- STAN POCZĄTKOWY ------------------------------------"
lsmfs disc
echo "----------------------------------------------------------"
infomfs disc
echo "----- KOPIOWANIE WIELU PLIKÓW 100B -----------------------"
for n in `seq 1 20`;
    do
        cpmfs disc -TO lorem_100.txt -AS lorem_100_"$n".txt
        echo "----------------------"
    done

echo "----- STAN PRZED USUWANIEM PLIKÓW ------------------------"
infomfs disc
echo "----------------------"
lsmfs disc
echo "----- USUWANIE 9 PLIKÓW PO 100B, UWZGLĘDNIONY NIEISTNIEJACY PLIK ---"
rmmfs disc lorem_100_2.txt lorem_100_5.txt "działa to.txt" lorem_100_6.txt lorem_100_7.txt lorem_100_8.txt lorem_100_9.txt lorem_100_10.txt lorem_100_11.txt lorem_100_12.txt lorem_100_13.txt
echo "----- STAN PRZED KOPIOWANIEM PLIKÓW 1KB ------------------"
lsmfs disc
echo "----------------------------------------------------------"
infomfs disc
echo "----- KOPIOWANIE WIELU PLIKÓW 1KB ------------------------"
cpmfs disc -TO lorem_1000.txt -AS lorem_1000_1.txt
echo "----------------------------------------------------------"
cpmfs disc -TO lorem_1000.txt -AS lorem_1000_2.txt
echo "----------------------------------------------------------"
cpmfs disc -TO lorem_1000.txt -AS lorem_1000_3.txt
echo "---- STAN PO KOPIOWANIU PLIKÓW 1KB -----------------------"
lsmfs disc
echo "----------------------------------------------------------"
infomfs disc
echo "---- USUNIĘCIE PLIKU 100B --------------------------------"
rmmfs disc lorem_100_14.txt
echo "---- POWINNA POWSTAĆ JUŻ DZIURA W PAMIĘCI O ROZMIARZE 1KB "
cpmfs disc -TO lorem_1000.txt -AS lorem_1000_4.txt
echo "---- STAN PO KOPIOWANIU PLIKU 1KB ------------------------"
lsmfs disc
echo "----------------------------------------------------------"
infomfs disc
echo "---- PRÓBA ZAPEŁNIENIA DYSKU -----------------------------"
echo "----- KOPIOWANIE WIELU PLIKÓW 100KB ----------------------"
for n in `seq 1 20`;
    do
        cpmfs disc -TO lorem_100k.txt -AS lorem_100k_"$n".txt
        echo "----------------------"
    done
echo "---- STAN PO KOPIOWANIU PLIKÓW 100KB ---------------------"
lsmfs disc
echo "----------------------------------------------------------"
infomfs disc
echo "---- SYSTEM WYGLĄDA NA ZAPEŁNIONY... ---------------------"
echo "----- KOPIOWANIE WIELU PLIKÓW 1KB ------------------------"
for n in `seq 100 160`;
    do
        cpmfs disc -TO lorem_1000.txt -AS lorem_1000_"$n".txt
        echo "----------------------"
    done
echo "---- STAN PO KOPIOWANIU PLIKÓW 1KB -----------------------"
lsmfs disc
echo "----------------------------------------------------------"
infomfs disc
echo "----------------------------------------------------------"
echo "---- SYSTEM WYGLĄDA NA ZAPEŁNIONY... ---------------------"
echo "----- KOPIOWANIE WIELU PLIKÓW 100B ------------------------"
for n in `seq 200 240`;
    do
        cpmfs disc -TO lorem_100.txt -AS lorem_100_"$n".txt
        echo "----------------------"
    done
echo "---- STAN PO KOPIOWANIU PLIKÓW 100B -----------------------"
lsmfs disc
echo "----------------------------------------------------------"
infomfs disc
echo "----------------------------------------------------------"
rm disc