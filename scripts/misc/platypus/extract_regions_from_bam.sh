#!/bin/bash
region=$(cat /genomics/regions_varcall.conf | tr ',' ' ')
/usr/bin/time samtools view -h -b -o /genomics/scratch/tmp.bam /mnt/Platypus-NA12878/CEUTrio.HiSeq.WGS.b37_decoy.NA12878.clean.dedup.recal.20120117.bam $region
/usr/bin/time samtools index /genomics/scratch/tmp.bam

