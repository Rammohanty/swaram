#device 0
echo "1:1-200000000" > regions_gatk.list
scp regions_gatk.list odroid@192.168.1.100:/genomics/regions_gatk.list

#device 1
echo "2:1-200000000" > regions_gatk.list
scp regions_gatk.list odroid@192.168.1.101:/genomics/regions_gatk.list

#device 2
echo "3" > regions_gatk.list
scp regions_gatk.list odroid@192.168.1.102:/genomics/regions_gatk.list

#device 3
echo "4" > regions_gatk.list
scp regions_gatk.list odroid@192.168.1.103:/genomics/regions_gatk.list



#device 4
echo -e "1:200000001-249250621\n8" > regions_gatk.list
scp regions_gatk.list odroid@192.168.1.104:/genomics/regions_gatk.list

#device 5
echo -e "2:200000001-243199373\n7" > regions_gatk.list
scp regions_gatk.list odroid@192.168.1.105:/genomics/regions_gatk.list

#device 6
echo "6" > regions_gatk.list
scp regions_gatk.list odroid@192.168.1.106:/genomics/regions_gatk.list

#device 7
echo "5" > regions_gatk.list
scp regions_gatk.list odroid@192.168.1.107:/genomics/regions_gatk.list



#device 8
echo -e "15\n16" > regions_gatk.list
scp regions_gatk.list odroid@192.168.1.108:/genomics/regions_gatk.list

#device 9
echo -e "9\n22" > regions_gatk.list
scp regions_gatk.list odroid@192.168.1.109:/genomics/regions_gatk.list

#device 10
echo -e "10\n21" > regions_gatk.list
scp regions_gatk.list odroid@192.168.1.110:/genomics/regions_gatk.list

#device 11
echo -e "11\n19" > regions_gatk.list
scp regions_gatk.list odroid@192.168.1.111:/genomics/regions_gatk.list



#device 12
echo -e "X\nY" > regions_gatk.list
scp regions_gatk.list odroid@192.168.1.112:/genomics/regions_gatk.list

#device 13
echo -e "14\n17" > regions_gatk.list
scp regions_gatk.list odroid@192.168.1.113:/genomics/regions_gatk.list

#device 14
echo -e "13\n18" > regions_gatk.list
scp regions_gatk.list odroid@192.168.1.114:/genomics/regions_gatk.list

#device 15
echo -e "12\n20" > regions_gatk.list
scp regions_gatk.list odroid@192.168.1.115:/genomics/regions_gatk.list