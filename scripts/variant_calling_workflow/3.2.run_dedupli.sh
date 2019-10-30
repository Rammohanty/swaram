#It is required to change the number of reads in the sorting framework source code, compile it and copied accrross?

#Need to execute the startID.sh

#Additional Information needed to be udated : input file name, output filename, chromosome regions

time ansible all -m shell -a "/usr/bin/time /genomics/sorting_framework/dedupli 2> /genomics/scratch/spurious-removal.txt"
