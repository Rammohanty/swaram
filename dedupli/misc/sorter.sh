rm /genomics/scratch/*.bam

cd /genomics/scratch
for file in newparted*.sam; do 
	bamname=$(echo $file | awk -F. '{print $1}'); 
	bamname="$bamname""$(hostname)"".bam" ; 
	/usr/bin/time /genomics/samtools/samtools sort $file -o $bamname -@2
done

#rm /genomics/scratch/newparted*.sam

/usr/bin/time /genomics/samtools/samtools merge -f -@8 /genomics/scratch/tmp.bam /genomics/scratch/newparted*.bam 

/usr/bin/time samtools index /genomics/scratch/tmp.bam

 