EON_trf="EON-ts.trf"
EON_net=("EON-ts.W10.net" "EON-ts.W11.net" "EON-ts.W12.net" "EON-ts.W13.net" "EON-ts.W14.net" "EON-ts.W15.net" "EON-ts.W16.net" "EON-ts.W17.net" "EON-ts.W18.net" "EON-ts.W19.net" "EON-ts.W20.net" "EON-ts.W21.net" "EON-ts.W22.net" "EON-ts.W23.net" "EON-ts.W24.net")

NSF_trf="nsfnet-ts.trf"
NSF_net=("nsfnet-ts.W10.net" "nsfnet-ts.W11.net" "nsfnet-ts.W12.net" "nsfnet-ts.W13.net" "nsfnet-ts.W14.net" "nsfnet-ts.W15.net" "nsfnet-ts.W16.net" "nsfnet-ts.W17.net" "nsfnet-ts.W18.net" "nsfnet-ts.W19.net" "nsfnet-ts.W20.net" "nsfnet-ts.W21.net" "nsfnet-ts.W22.net" "nsfnet-ts.W23.net" "nsfnet-ts.W24.net" "nsfnet-ts.net")



echo "Resolvendo o EON para BRKGA"
for probl in "${EON_net[@]}"
do
 echo "Instancia $probl $EON_trf\n"
  ./ga-rwa/ga_maxrwa_estatico1/rwa set-d/eon/$probl set-d/eon/$EON_trf GA 1 0 1 >> saida.txt
done


echo "Resolvendo o NSF para BRKGA"
for probl in "${NSF_net[@]}"
do
  echo "Instancia $probl $EON_trf\n"
  ./ga-rwa/ga_maxrwa_estatico1/rwa set-d/nsf/$probl set-d/nsf/$EON_trf GA 1 0 1 >> saida.txt
done


echo "\n----------------------------------------------------\n"

echo "Resolvendo o EON para gamixdecoderrwa-jogo"
for probl in "${EON_net[@]}"
do
 echo "Instancia $probl $EON_trf\n"
  ./gamixdecoderrwa-jogo/ga_maxrwa_estatico1/rwa set-d/eon/$probl set-d/eon/$EON_trf GA 1 0 1 >> saida.txt
done

echo "Resolvendo o NSF para gamixdecoderrwa-jogo"
for probl in "${NSF_net[@]}"
do
  echo "Instancia $probl $EON_trf\n"
  ./gamixdecoderrwa-jogo/ga_maxrwa_estatico1/rwa set-d/nsf/$probl set-d/nsf/$EON_trf GA 1 0 1 >> saida.txt
done

echo "\n----------------------------------------------------\n"

echo "Resolvendo o EON para gamixordenacaorwa-jogo"
for probl in "${EON_net[@]}"
do
 echo "Instancia $probl $EON_trf\n"
  ./gamixordenacaorwa-jogo/ga_maxrwa_estatico1/rwa set-d/eon/$probl set-d/eon/$EON_trf GA 1 0 1 >> saida.txt
done


echo "Resolvendo o NSF para gamixordenacaorwa-jogo"
for probl in "${NSF_net[@]}"
do
  echo "Instancia $probl $EON_trf\n"
  ./gamixordenacaorwa-jogo/ga_maxrwa_estatico1/rwa set-d/nsf/$probl set-d/nsf/$EON_trf GA 1 0 1 >> saida.txt
done

