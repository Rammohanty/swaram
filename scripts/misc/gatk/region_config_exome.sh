#device 0
cp begin_interval.txt regions.interval_list
awk '{if($1=="1" && $3<200000000) print $0}' Broad.human.exome.b37.interval_list >> regions.interval_list
scp regions.interval_list odroid@192.168.1.100:/genomics/regions.interval_list

#device 1
cp begin_interval.txt regions.interval_list
awk '{if($1=="2" && $3<200000000) print $0}' Broad.human.exome.b37.interval_list >> regions.interval_list
scp regions.interval_list odroid@192.168.1.101:/genomics/regions.interval_list

#device 2
cp begin_interval.txt regions.interval_list
awk '{if($1=="3") print $0}' Broad.human.exome.b37.interval_list >> regions.interval_list
scp regions.interval_list odroid@192.168.1.102:/genomics/regions.interval_list

#device 3
cp begin_interval.txt regions.interval_list
awk '{if($1=="4") print $0}' Broad.human.exome.b37.interval_list >> regions.interval_list
scp regions.interval_list odroid@192.168.1.103:/genomics/regions.interval_list



#device 4
cp begin_interval.txt regions.interval_list
awk '{if($1=="1" && $2>200000000) print $0}' Broad.human.exome.b37.interval_list >> regions.interval_list
awk '{if($1=="8") print $0}' Broad.human.exome.b37.interval_list >> regions.interval_list
scp regions.interval_list odroid@192.168.1.104:/genomics/regions.interval_list

#device 5
cp begin_interval.txt regions.interval_list
awk '{if($1=="2" && $2>200000000) print $0}' Broad.human.exome.b37.interval_list >> regions.interval_list
awk '{if($1=="7") print $0}' Broad.human.exome.b37.interval_list >> regions.interval_list
scp regions.interval_list odroid@192.168.1.105:/genomics/regions.interval_list

#device 6
cp begin_interval.txt regions.interval_list
awk '{if($1=="6") print $0}' Broad.human.exome.b37.interval_list >> regions.interval_list
scp regions.interval_list odroid@192.168.1.106:/genomics/regions.interval_list

#device 7
cp begin_interval.txt regions.interval_list
awk '{if($1=="5") print $0}' Broad.human.exome.b37.interval_list >> regions.interval_list
scp regions.interval_list odroid@192.168.1.107:/genomics/regions.interval_list



#device 8
cp begin_interval.txt regions.interval_list
awk '{if($1=="15") print $0}' Broad.human.exome.b37.interval_list >> regions.interval_list
awk '{if($1=="16") print $0}' Broad.human.exome.b37.interval_list >> regions.interval_list
scp regions.interval_list odroid@192.168.1.108:/genomics/regions.interval_list

#device 9
cp begin_interval.txt regions.interval_list
awk '{if($1=="9") print $0}' Broad.human.exome.b37.interval_list >> regions.interval_list
awk '{if($1=="22") print $0}' Broad.human.exome.b37.interval_list >> regions.interval_list
scp regions.interval_list odroid@192.168.1.109:/genomics/regions.interval_list

#device 10
cp begin_interval.txt regions.interval_list
awk '{if($1=="10") print $0}' Broad.human.exome.b37.interval_list >> regions.interval_list
awk '{if($1=="21") print $0}' Broad.human.exome.b37.interval_list >> regions.interval_list
scp regions.interval_list odroid@192.168.1.110:/genomics/regions.interval_list

#device 11
cp begin_interval.txt regions.interval_list
awk '{if($1=="11") print $0}' Broad.human.exome.b37.interval_list >> regions.interval_list
awk '{if($1=="19") print $0}' Broad.human.exome.b37.interval_list >> regions.interval_list
scp regions.interval_list odroid@192.168.1.111:/genomics/regions.interval_list



#device 12
cp begin_interval.txt regions.interval_list
awk '{if($1=="X") print $0}' Broad.human.exome.b37.interval_list >> regions.interval_list
awk '{if($1=="Y") print $0}' Broad.human.exome.b37.interval_list >> regions.interval_list
scp regions.interval_list odroid@192.168.1.112:/genomics/regions.interval_list

#device 13
cp begin_interval.txt regions.interval_list
awk '{if($1=="14") print $0}' Broad.human.exome.b37.interval_list >> regions.interval_list
awk '{if($1=="17") print $0}' Broad.human.exome.b37.interval_list >> regions.interval_list
scp regions.interval_list odroid@192.168.1.113:/genomics/regions.interval_list

#device 14
cp begin_interval.txt regions.interval_list
awk '{if($1=="13") print $0}' Broad.human.exome.b37.interval_list >> regions.interval_list
awk '{if($1=="18") print $0}' Broad.human.exome.b37.interval_list >> regions.interval_list
scp regions.interval_list odroid@192.168.1.114:/genomics/regions.interval_list

#device 15
cp begin_interval.txt regions.interval_list
awk '{if($1=="12") print $0}' Broad.human.exome.b37.interval_list >> regions.interval_list
awk '{if($1=="20") print $0}' Broad.human.exome.b37.interval_list >> regions.interval_list
scp regions.interval_list odroid@192.168.1.115:/genomics/regions.interval_list