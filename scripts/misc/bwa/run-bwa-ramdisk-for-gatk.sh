bwalog=/genomics/scratch/bwa.log
reads_per_device=109753378
time ansible all -m shell -a "/usr/bin/time /home/odroid/Ram_Research_V04/exec.o 80000 $reads_per_device 2> $bwalog" -f 16 

