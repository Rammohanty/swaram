#!/bin/bash
ansible all -m shell -a "/genomics/samtools/samtools reheader /genomics/regions_headers.sam /genomics/scratch/tmp.bam > /genomics/scratch/tmp2.bam"
ansible all -m shell -a "/genomics/samtools/samtools index /genomics/scratch/tmp2.bam"
