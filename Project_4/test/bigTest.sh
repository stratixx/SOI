export PATH=$PATH":./../bin"
mkmfs disc 4000000
echo "----- STAN POCZĄTKOWY ------------------------------------"
lsmfs disc
echo "----------------------------------------------------------"
infomfs disc
echo "----- KOPIOWANIE WIELU PLIKÓW 100MB -----------------------"
export linuxFiles
export MFSfiles

for n in `seq 1 50`;
    do
        linuxFiles=$linuxFiles"lorem_100M.txt "
        MFSfiles=$MFSfiles"lorem_100M_$n.txt "
    done
cpmfs disc -TO $linuxFiles -AS $MFSfiles
echo "----- STAN PO KOPIOWANIU ------------------------"
infomfs disc
echo "----------------------"
lsmfs disc
rm disc