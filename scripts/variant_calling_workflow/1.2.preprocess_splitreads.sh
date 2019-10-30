if [ "$#" -ne 2 ]
then
	echo "usage : $0 <file_randomised.fq> <stats.txt>"
	exit
fi 

set -e
set -o pipefail

readFile=$1
stat=$2

num_lines=$(wc -l $readFile | awk '{print $1}')
num_reads=$(echo "$num_lines/4" | bc)
reads_per_dev=$(echo "$num_reads/4" | bc)
lines_per_dev=$(echo "$reads_per_dev*4" | bc)

echo "total num reads :  $num_reads" > $stat
echo "reads per device : $reads_per_dev" >> $stat

#read splitting
split -l $lines_per_dev -d -a 2 $readFile P

mv P00 P00.fq
mv P01 P01.fq
mv P02 P02.fq
mv P03 P03.fq
