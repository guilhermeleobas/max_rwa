#!/bin/bash

EON_trf="EON-ts"
EON_net=("EON-ts.W10" "EON-ts.W11" "EON-ts.W12" "EON-ts.W13" "EON-ts.W14" "EON-ts.W15" "EON-ts.W16" "EON-ts.W17" "EON-ts.W18" "EON-ts.W19" "EON-ts.W20" "EON-ts.W21" "EON-ts.W22" "EON-ts.W23" "EON-ts.W24")

NSF_trf="nsfnet-ts"
NSF_net=("nsfnet-ts.W10" "nsfnet-ts.W11" "nsfnet-ts.W12" "nsfnet-ts.W13" "nsfnet-ts.W14" "nsfnet-ts.W15" "nsfnet-ts.W16" "nsfnet-ts.W17" "nsfnet-ts.W18" "nsfnet-ts.W19" "nsfnet-ts.W20" "nsfnet-ts.W21" "nsfnet-ts.W22" "nsfnet-ts.W23" "nsfnet-ts.W24" "nsfnet-ts")

echo "Resolvendo o EON para GAMixOrdenacao"
for probl in "${EON_net[@]}"
do
 echo -e "Instancia $probl $EON_trf\n"
  ./rwa instances/set-d/eon/$probl.net instances/set-d/eon/$EON_trf.trf GA 1 0 1 >> saida.txt
done


echo "Resolvendo o NSF para GAMixOrdenacao"
for probl in "${NSF_net[@]}"
do
  echo -e "Instancia $probl $NSF_trf\n"
  ./rwa instances/set-d/nsf/$probl.net instances/set-d/nsf/$EON_trf.trf GA 1 0 1 >> saida.txt
done