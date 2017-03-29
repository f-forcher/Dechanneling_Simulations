#!/bin/bash

# ALWAYS check:
# beam 1 or 2
# batch queue


# LocalPWD : where on the mac should the files be copied. Does the directory exist?
# post-processing programs to run
# which output files should be copied back
# should previous dirs run* be deleted


PWD=`pwd`
LocalPWD="/media/Daniele/STF45_H8_eff90_th/"

beam=b1
LIMIT=1000

echo $PWD
#scp -r $PWD/clean_input dmirarch@pcen33066:"${LocalPWD}"
#scp $PWD/sixtrack_batch.sh dmirarch@pcen33066:"${LocalPWD}clean_input"






#rm -r run*

for ((a=1; a <= LIMIT ; a++))
  do
  index=$a
  zero=0
  while [ "${#index}" -lt "4" ]
    do
    index=$zero$index
  done 
  mkdir run$index

  cat > run$index/SixTr$index.job << EOF
  #!/bin/bash
  cp $PWD/clean_input/* .
  cp $PWD/../H8_initial_distr_xp_uniforme.dat .

  ./make_distr H8_initial_distr_xp_uniforme.dat $a 100
  ./SixTrack_dan_RELEASE_CRYSTAL_VRAM_corretto5 > screenout

  cp cr_interaction.dat $PWD/run$index/

#  scp -r $PWD/run${index} dmirarch@pcen33066:"${LocalPWD}"
#  rm -r $PWD/run${index}
  exit
EOF
if [ -d "run$index" ]; then
    cd run$index
    chmod 777 SixTr$index.job
    bsub -q 1nh -R "rusage[pool=30000]" SixTr$index.job
    cd ..
fi
  
done
