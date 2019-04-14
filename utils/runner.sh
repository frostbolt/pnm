#!/bin/bash

#SBATCH --job-name=numerical_methods
#SBATCH --output=result.csv
#SBATCH --ntasks=1
#
#SBATCH --cpus-per-task=20
#
#SBATCH --time=30:00
#SBATCH --mem-per-cpu=100

################################################################

filename=result.json
touch $filename
repeats=5
maxthreads=4
maxdim=781250000

################################################################

let lastindexrepeats=$repeats-1
let lastindexthreads=$maxthreads+1

echo -ne "[" > $filename

for ((omp_threads=1; omp_threads<=$repeats; omp_threads++))
do

	for (( dim = 50000; dim <= $maxdim; dim*=5))
	do
		echo "counting for $dim"

		export OMP_NUM_THREADS=$omp_threads

		for ((i=0; i < $repeats; i++))
		do
			echo -ne $(../first/build/main -n $dim) >> $filename

			if [[ $i < $lastindexrepeats || $omp_threads < $lastindexthreads || $dim < $maxdim ]]; then
				echo "," >> $filename
			fi
		done

	done

done
echo "]" >> $filename

