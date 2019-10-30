READ_PATH=/storage/NA12878reads

reference=/genomics/reference/hs37d5_split.fa
file1=$READ_PATH/P00.fq
file2=$READ_PATH/P01.fq
file3=$READ_PATH/P02.fq
file4=$READ_PATH/P03.fq


echo "4    #master
192.168.1.101  #Auxillary
192.168.1.102  #Auxillary
192.168.1.103  #Auxillary
$reference
$file1" > dev0
echo "4    #master
192.168.1.101  #Auxillary
192.168.1.102  #Auxillary
192.168.1.103  #Auxillary
$reference
$file1" > dev1
echo "4    #master
192.168.1.101  #Auxillary
192.168.1.102  #Auxillary
192.168.1.103  #Auxillary
$reference
$file1" > dev2
echo "4    #master
192.168.1.101  #Auxillary
192.168.1.102  #Auxillary
192.168.1.103  #Auxillary
$reference
$file1" > dev3
echo "4    #master
192.168.1.105  #Auxillary
192.168.1.106  #Auxillary
192.168.1.107  #Auxillary
$reference
$file2" > dev4
echo "4    #master
192.168.1.105  #Auxillary
192.168.1.106  #Auxillary
192.168.1.107  #Auxillary
$reference
$file2" > dev5
echo "4    #master
192.168.1.105  #Auxillary
192.168.1.106  #Auxillary
192.168.1.107  #Auxillary
$reference
$file2" > dev6
echo "4    #master
192.168.1.105  #Auxillary
192.168.1.106  #Auxillary
192.168.1.107  #Auxillary
$reference
$file2" > dev7
echo "4    #master
192.168.1.109  #Auxillary
192.168.1.110  #Auxillary
192.168.1.111  #Auxillary
$reference
$file3" > dev8
echo "4    #master
192.168.1.109  #Auxillary
192.168.1.110  #Auxillary
192.168.1.111  #Auxillary
$reference
$file3" > dev9
echo "4    #master
192.168.1.109  #Auxillary
192.168.1.110  #Auxillary
192.168.1.111  #Auxillary
$reference
$file3" > dev10
echo "4    #master
192.168.1.109  #Auxillary
192.168.1.110  #Auxillary
192.168.1.111  #Auxillary
$reference
$file3" > dev11
echo "4    #master
192.168.1.113  #Auxillary
192.168.1.114  #Auxillary
192.168.1.115 #Auxillary
$reference
$file4" > dev12
echo "4    #master
192.168.1.113  #Auxillary
192.168.1.114  #Auxillary
192.168.1.115 #Auxillary
$reference
$file4" > dev13
echo "4    #master
192.168.1.113  #Auxillary
192.168.1.114  #Auxillary
192.168.1.115 #Auxillary
$reference
$file4" > dev14
echo "4    #master
192.168.1.113  #Auxillary
192.168.1.114  #Auxillary
192.168.1.115 #Auxillary
$reference
$file4" > dev15


scp dev0 odroid@192.168.1.100:/genomics/ram_config
scp dev1 odroid@192.168.1.101:/genomics/ram_config
scp dev2 odroid@192.168.1.102:/genomics/ram_config
scp dev3 odroid@192.168.1.103:/genomics/ram_config
scp dev4 odroid@192.168.1.104:/genomics/ram_config
scp dev5 odroid@192.168.1.105:/genomics/ram_config
scp dev6 odroid@192.168.1.106:/genomics/ram_config
scp dev7 odroid@192.168.1.107:/genomics/ram_config
scp dev8 odroid@192.168.1.108:/genomics/ram_config
scp dev9 odroid@192.168.1.109:/genomics/ram_config
scp dev10 odroid@192.168.1.110:/genomics/ram_config
scp dev11 odroid@192.168.1.111:/genomics/ram_config
scp dev12 odroid@192.168.1.112:/genomics/ram_config
scp dev13 odroid@192.168.1.113:/genomics/ram_config
scp dev14 odroid@192.168.1.114:/genomics/ram_config
scp dev15 odroid@192.168.1.115:/genomics/ram_config

