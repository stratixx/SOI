export PATH=$PATH":./../bin"
mkmfs disc 40
echo "----------------------"
infomfs disc
echo "----------------------"
for n in `seq 1 7`;
    do
        cpmfs disc -TO lorem_1000.txt -AS lorem_1000_"$n".txt
        echo "----------------------"
    done

echo "----------------------"
infomfs disc
echo "----------------------"
lsmfs disc
echo "----------------------"
rmmfs disc lorem_1000_2.txt
rmmfs disc lorem_1000_5.txt
echo "----------------------"
lsmfs disc
echo "----------------------"
cpmfs disc -TO lorem_1000.txt -AS lorem_1000_8.txt
echo "----------------------"
cpmfs disc -TO lorem_1000.txt -AS lorem_1000_9.txt
echo "----------------------"
cpmfs disc -TO lorem_1000.txt -AS lorem_1000_10.txt
echo "----------------------"
lsmfs disc
echo "----------------------"
rm disc