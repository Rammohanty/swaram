for i in $(seq 100 115)
do
rsync -avz odroid@192.168.1.$i:/genomics/scratch/platyerr.txt platy_stderr/$i.txt
rsync -avz odroid@192.168.1.$i:/genomics/scratch/out.vcf platy_vcf/$i.vcf
done

grep '^#' platy_vcf/100.vcf > platy_vcf/concat.vcf && cat platy_vcf/1*.vcf | grep -v '^#'  >> platy_vcf/concat.vcf
