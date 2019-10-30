

#Did you change the number of reads in the sorting framework source code, compile it and copied accrross?

#did u run startID.sh

#other things u might want to change : input file name, output filename, chromosome regions

time ansible all -m shell -a "/usr/bin/time /genomics/sorting_framework/dedupli 2> /genomics/scratch/duplierr.txt"
