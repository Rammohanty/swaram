#device 0
echo "1:1-200000000" > regions_varcall.conf
scp regions_varcall.conf odroid@192.168.1.100:/genomics/regions_varcall.conf

#device 1
echo "2:1-200000000" > regions_varcall.conf
scp regions_varcall.conf odroid@192.168.1.101:/genomics/regions_varcall.conf

#device 2
echo "3" > regions_varcall.conf
scp regions_varcall.conf odroid@192.168.1.102:/genomics/regions_varcall.conf

#device 3
echo "4" > regions_varcall.conf
scp regions_varcall.conf odroid@192.168.1.103:/genomics/regions_varcall.conf



#device 4
echo "1:200000001-249250621,8" > regions_varcall.conf
scp regions_varcall.conf odroid@192.168.1.104:/genomics/regions_varcall.conf

#device 5
echo "2:200000001-243199373,7" > regions_varcall.conf
scp regions_varcall.conf odroid@192.168.1.105:/genomics/regions_varcall.conf

#device 6
echo "6" > regions_varcall.conf
scp regions_varcall.conf odroid@192.168.1.106:/genomics/regions_varcall.conf

#device 7
echo "5" > regions_varcall.conf
scp regions_varcall.conf odroid@192.168.1.107:/genomics/regions_varcall.conf



#device 8
echo "15,16" > regions_varcall.conf
scp regions_varcall.conf odroid@192.168.1.108:/genomics/regions_varcall.conf

#device 9
echo "9,22" > regions_varcall.conf
scp regions_varcall.conf odroid@192.168.1.109:/genomics/regions_varcall.conf

#device 10
echo "10,21" > regions_varcall.conf
scp regions_varcall.conf odroid@192.168.1.110:/genomics/regions_varcall.conf

#device 11
echo "11,19" > regions_varcall.conf
scp regions_varcall.conf odroid@192.168.1.111:/genomics/regions_varcall.conf



#device 12
echo "X,Y" > regions_varcall.conf
scp regions_varcall.conf odroid@192.168.1.112:/genomics/regions_varcall.conf

#device 13
echo "14,17" > regions_varcall.conf
scp regions_varcall.conf odroid@192.168.1.113:/genomics/regions_varcall.conf

#device 14
echo "13,18" > regions_varcall.conf
scp regions_varcall.conf odroid@192.168.1.114:/genomics/regions_varcall.conf

#device 15
echo "12,20" > regions_varcall.conf
scp regions_varcall.conf odroid@192.168.1.115:/genomics/regions_varcall.conf