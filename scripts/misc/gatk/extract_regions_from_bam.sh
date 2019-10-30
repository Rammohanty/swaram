#!/bin/bash
region=$(cat /genomics/regions_varcall.conf | tr ',' ' ')
samtools view /mnt/Platypus-NA12878/CEUTrio.HiSeq.WGS.b37_decoy.NA12878.clean.dedup.recal.20120117.bam $region | cat /genomics/regions_headers.sam - | samtools view -Sb - > /genomics/scratch/tmp.bam 
samtools index /genomics/scratch/tmp.bam
