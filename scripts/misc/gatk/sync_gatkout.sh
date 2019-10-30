for i in $(seq 100 115)
do
rsync -avz odroid@192.168.1.$i:/genomics/scratch/gatk.err gatk_stderr/err_$i.txt
rsync -avz odroid@192.168.1.$i:/genomics/scratch/gatk.out gatk_stderr/out_$i.txt
rsync -avz odroid@192.168.1.$i:/genomics/scratch/out.vcf gatk_vcf/$i.vcf
done

grep '^#' gatk_vcf/100.vcf > gatk_vcf/concat.vcf && cat gatk_vcf/1*.vcf | grep -v '^#'  >> gatk_vcf/concat.vcf
