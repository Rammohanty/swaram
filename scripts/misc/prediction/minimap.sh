#!/bin/bash
for i in $(seq -w 00 15)
do
    ip=$(echo "$i+100" | bc )
    /usr/bin/time -v /genomics/minimap2/minimap2 -k 25 -w 20 -t 8 -K 50M /genomics/reference/human-split/$ip.fa ~/NA12878.fq  > /genomics/scratch/NA12878$i.paf
done


