if [ "$#" -lt 2 ]
then
	echo "usage : $0 <output.fq> <file1.fq.gz> <file2.fq.gz>"
	exit 1
fi 

set -e
set -o pipefail

FILETMP=singleline.fq
OUTPUT=$1

test -e $OUTPUT && echo "$OUTPUT already exists. Please remove it." && exit 1

zcat $2 | paste - - - - > $FILETMP 
for i in ${@:3}
do
	zcat $i | paste - - - - >> $FILETMP 
done
	
awk '{ 
number=int(4 * rand());
if(number=="0" ) {print $0> "temp0"} 
else if (number=="1") {print $0> "temp1"}
else if (number=="2") {print $0> "temp2"}
else if (number=="3") {print $0> "temp3"}
else {print $0> "error"}
}' $FILETMP || exit 

rm $FILETMP
cat temp0 temp1 temp2 temp3 | tr '\t' '\n' | awk 'BEGIN{i=1}{if(NR%4==1){printf("@sr%010u\n",i);i++}else{print;}}' > $OUTPUT 
rm temp0 temp1 temp2 temp3
