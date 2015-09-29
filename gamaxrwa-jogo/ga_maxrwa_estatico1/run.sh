#!/bin/bash

PS2=("ATT" "ATT2" "Finland" "NSF3" "NSF12" "NSF212" "NSF1" "NSF48" "NSF21" "NSF23" "NSF248" "brasil" "cost266" "dfn-bwin" "dfn-gwin" "EON" "france" "giul" "janos-us" "nobel-eu" "nobel-germany" "nobel-us" "norway" "sun") 

PS3=("NSF48" "NSF248" "NSF12" "NSF212" "ATT2" "Finland" "brasil" "cost266" "dfn-bwin" "dfn-gwin" "france" "giul" "janos-us" "nobel-eu" "nobel-germany" "nobel-us" "norway" "sun")

echo "Resolvendo o GA-SPT para W=10"
for probl in "${PS2[@]}"
do
 echo -e "Instancia $probl\n"
 ./rwa instances/table4/w10/$probl.net instances/table4/w10/$probl.trf  GA 1 0 1 >> saida.txt 
done

echo "Resolvendo o GA-SPT para W=20"
for probl in "${PS2[@]}"
do
 echo -e "Instancia $probl\n"
 ./rwa instances/table4/w20/$probl.net instances/table4/w20/$probl.trf  GA 1 0 1 >> saida.txt 
done

echo "Resolvendo o GA-SPT para W=30"
for probl in "${PS3[@]}"
do
 echo -e "Instancia $probl\n"
 ./rwa instances/table4/w30/$probl.net instances/table4/w30/$probl.trf  GA 1 0 1 >> saida.txt 
done

echo "Resolvendo o MS-SPT para W=10"
for probl in "${PS2[@]}"
do
 echo -e "Instancia $probl\n"
 ./rwa instances/table4/w10/$probl.net instances/table4/w10/$probl.trf  SPT 1 0 1 >> saida.txt 
done

echo "Resolvendo o MS-SPT para W=20"
for probl in "${PS2[@]}"
do
 echo -e "Instancia $probl\n"
 ./rwa instances/table4/w20/$probl.net instances/table4/w20/$probl.trf  SPT 1 0 1 >> saida.txt 
done

echo "Resolvendo o MS-SPT para W=30"
for probl in "${PS3[@]}"
do
 echo -e "Instancia $probl\n"
 ./rwa instances/table4/w30/$probl.net instances/table4/w30/$probl.trf  SPT 1 0 1 >> saida.txt 
done
