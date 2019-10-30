for i in $(seq 100 115)
do
rsync -avz odroid@192.168.1.$i:/genomics/scratch/time.txt times/$i.txt
done
