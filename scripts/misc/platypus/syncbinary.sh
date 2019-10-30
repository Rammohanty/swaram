for i in $(seq 100 115)
do
rsync -avz /tmp/bin/ odroid@192.168.1.$i:/genomics/platypus/
done