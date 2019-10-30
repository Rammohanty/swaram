#!/bin/bash
ansible all -m shell -a "/genomics/samtools/samtools reheader /genomics/regions_headers.sam /genomics/scratch/tmp.bam | /genomics/samtools/samtools addreplacerg -R 'group1' -O BAM -o /genomics/scratch/tmp2.bam -"
ansible all -m shell -a "/genomics/samtools/samtools index /genomics/scratch/tmp2.bam"
