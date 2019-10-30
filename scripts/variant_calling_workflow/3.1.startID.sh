P1=$(head -1 /storage/NA12878_illumina_reads/P00.fq | tr -dc '0-9')
P2=$(head -1 /storage/NA12878_illumina_reads/P01.fq | tr -dc '0-9')
P3=$(head -1 /storage/NA12878_illumina_reads/P02.fq | tr -dc '0-9')
P4=$(head -1 /storage/NA12878_illumina_reads/P03.fq | tr -dc '0-9')


#row 0
echo $P1 > start_read_id.cfg
scp start_read_id.cfg odroid@192.168.1.100:/genomics/start_read_id.cfg
scp start_read_id.cfg odroid@192.168.1.101:/genomics/start_read_id.cfg
scp start_read_id.cfg odroid@192.168.1.102:/genomics/start_read_id.cfg
scp start_read_id.cfg odroid@192.168.1.103:/genomics/start_read_id.cfg


####################################################################################

#row1
echo $P2 > start_read_id.cfg
scp start_read_id.cfg odroid@192.168.1.104:/genomics/start_read_id.cfg
scp start_read_id.cfg odroid@192.168.1.105:/genomics/start_read_id.cfg
scp start_read_id.cfg odroid@192.168.1.106:/genomics/start_read_id.cfg
scp start_read_id.cfg odroid@192.168.1.107:/genomics/start_read_id.cfg


####################################################################################

#row2
echo $P3 > start_read_id.cfg
scp start_read_id.cfg odroid@192.168.1.108:/genomics/start_read_id.cfg
scp start_read_id.cfg odroid@192.168.1.109:/genomics/start_read_id.cfg
scp start_read_id.cfg odroid@192.168.1.110:/genomics/start_read_id.cfg
scp start_read_id.cfg odroid@192.168.1.111:/genomics/start_read_id.cfg

####################################################################################

#row3
echo $P4 > start_read_id.cfg
scp start_read_id.cfg odroid@192.168.1.112:/genomics/start_read_id.cfg
scp start_read_id.cfg odroid@192.168.1.113:/genomics/start_read_id.cfg
scp start_read_id.cfg odroid@192.168.1.114:/genomics/start_read_id.cfg
scp start_read_id.cfg odroid@192.168.1.115:/genomics/start_read_id.cfg


