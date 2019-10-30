time ansible-playbook -f 16 sorter.yml

for i in $(seq 100 115)
do
rsync -avz odroid@192.168.1.$i:/genomics/scratch/sorterr.txt /home/odroid/sorting_framework/tmp/sort$i.txt
done

