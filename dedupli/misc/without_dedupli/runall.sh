time ansible-playbook runall.yml -f 16

for i in $(seq 100 115)
do
rsync -avz odroid@192.168.1.$i:/genomics/scratch/separate.txt /home/odroid/sorting_framework/without_dedupli/tmp/separate$i.txt
done