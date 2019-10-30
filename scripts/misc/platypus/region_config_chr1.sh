chr=1
chr_size=249250621
start_pos=1
step=$(echo "$chr_size/16" | bc)
end_pos=$step
echo "chromesome step : $step"
echo "//c code generator" > ccode.c

for i in $(seq 0 15)
do
    ip=$(echo "$i+100" | bc)
    echo "$chr:$start_pos-$end_pos"
    echo "$chr:$start_pos-$end_pos" > regions_varcall.conf
    [ $i -eq 0 ] && echo -e "if(strcmp(chrom,\"$chr\")==0 && pos>=$start_pos && pos <=$end_pos){\n return $i;\n}" >> ccode.c
    [ $i -eq 0 ] || echo -e "else if(strcmp(chrom,\"$chr\")==0 && pos>=$start_pos && pos <=$end_pos){\n return $i;\n}" >> ccode.c
    scp regions_varcall.conf odroid@192.168.1.$ip:/genomics/regions_varcall.conf
    start_pos=$(echo "$start_pos+$step" | bc)
    end_pos=$(echo "$end_pos+$step" | bc)
    [ $ip -eq 114 ] && end_pos=$chr_size
done
