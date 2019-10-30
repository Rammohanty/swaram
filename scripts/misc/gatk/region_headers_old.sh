#device 0
echo -e "@HD\tVN:1.0\tGO:none\tSO:coordinate" > regions_headers.sam
echo -e "@SQ\tSN:1\tLN:249250621" >> regions_headers.sam
cat endsam.txt >> regions_headers.sam
scp regions_headers.sam odroid@192.168.1.100:/genomics/regions_headers.sam

#device 1
echo -e "@HD\tVN:1.0\tGO:none\tSO:coordinate" > regions_headers.sam
echo -e "@SQ\tSN:2\tLN:243199373" >> regions_headers.sam
cat endsam.txt >> regions_headers.sam
scp regions_headers.sam odroid@192.168.1.101:/genomics/regions_headers.sam

#device 2
echo -e "@HD\tVN:1.0\tGO:none\tSO:coordinate" > regions_headers.sam
echo -e "@SQ\tSN:3\tLN:198022430" >> regions_headers.sam
cat endsam.txt >> regions_headers.sam
scp regions_headers.sam odroid@192.168.1.102:/genomics/regions_headers.sam

#device 3
echo -e "@HD\tVN:1.0\tGO:none\tSO:coordinate" > regions_headers.sam
echo -e "@SQ\tSN:4\tLN:191154276" >> regions_headers.sam
cat endsam.txt >> regions_headers.sam
scp regions_headers.sam odroid@192.168.1.103:/genomics/regions_headers.sam



#device 4
echo -e "@HD\tVN:1.0\tGO:none\tSO:coordinate" > regions_headers.sam
echo -e "@SQ\tSN:1\tLN:249250621\n@SQ\tSN:8\tLN:146364022" >> regions_headers.sam
cat endsam.txt >> regions_headers.sam
scp regions_headers.sam odroid@192.168.1.104:/genomics/regions_headers.sam

#device 5
echo -e "@HD\tVN:1.0\tGO:none\tSO:coordinate" > regions_headers.sam
echo -e "@SQ\tSN:2\tLN:243199373\n@SQ\tSN:7\tLN:159138663" >> regions_headers.sam
cat endsam.txt >> regions_headers.sam
scp regions_headers.sam odroid@192.168.1.105:/genomics/regions_headers.sam

#device 6
echo -e "@HD\tVN:1.0\tGO:none\tSO:coordinate" > regions_headers.sam
echo -e "@SQ\tSN:6\tLN:171115067" >> regions_headers.sam
cat endsam.txt >> regions_headers.sam
scp regions_headers.sam odroid@192.168.1.106:/genomics/regions_headers.sam

#device 7
echo -e "@HD\tVN:1.0\tGO:none\tSO:coordinate" > regions_headers.sam
echo -e "@SQ\tSN:5\tLN:180915260" >> regions_headers.sam
cat endsam.txt >> regions_headers.sam
scp regions_headers.sam odroid@192.168.1.107:/genomics/regions_headers.sam



#device 8
echo -e "@HD\tVN:1.0\tGO:none\tSO:coordinate" > regions_headers.sam
echo -e "@SQ\tSN:15\tLN:102531392\n@SQ\tSN:16\tLN:90354753" >> regions_headers.sam
cat endsam.txt >> regions_headers.sam
scp regions_headers.sam odroid@192.168.1.108:/genomics/regions_headers.sam

#device 9
echo -e "@HD\tVN:1.0\tGO:none\tSO:coordinate" > regions_headers.sam
echo -e "@SQ\tSN:9\tLN:141213431\n@SQ\tSN:22\tLN:51304566" >> regions_headers.sam
cat endsam.txt >> regions_headers.sam
scp regions_headers.sam odroid@192.168.1.109:/genomics/regions_headers.sam

#device 10
echo -e "@HD\tVN:1.0\tGO:none\tSO:coordinate" > regions_headers.sam
echo -e "@SQ\tSN:10\tLN:135534747\n@SQ\tSN:21\tLN:48129895" >> regions_headers.sam
cat endsam.txt >> regions_headers.sam
scp regions_headers.sam odroid@192.168.1.110:/genomics/regions_headers.sam

#device 11
echo -e "@HD\tVN:1.0\tGO:none\tSO:coordinate" > regions_headers.sam
echo -e "@SQ\tSN:11\tLN:135006516\n@SQ\tSN:19\tLN:59128983" >> regions_headers.sam
cat endsam.txt >> regions_headers.sam
scp regions_headers.sam odroid@192.168.1.111:/genomics/regions_headers.sam



#device 12
echo -e "@HD\tVN:1.0\tGO:none\tSO:coordinate" > regions_headers.sam
echo -e "@SQ\tSN:X\tLN:155270560\n@SQ\tSN:Y\tLN:59373566" >> regions_headers.sam
cat endsam.txt >> regions_headers.sam
scp regions_headers.sam odroid@192.168.1.112:/genomics/regions_headers.sam

#device 13
echo -e "@HD\tVN:1.0\tGO:none\tSO:coordinate" > regions_headers.sam
echo -e "@SQ\tSN:14\tLN:107349540\n@SQ\tSN:17\tLN:81195210" >> regions_headers.sam
cat endsam.txt >> regions_headers.sam
scp regions_headers.sam odroid@192.168.1.113:/genomics/regions_headers.sam

#device 14
echo -e "@HD\tVN:1.0\tGO:none\tSO:coordinate" > regions_headers.sam
echo -e "@SQ\tSN:13\tLN:115169878\n@SQ\tSN:18\tLN:78077248" >> regions_headers.sam
cat endsam.txt >> regions_headers.sam
scp regions_headers.sam odroid@192.168.1.114:/genomics/regions_headers.sam

#device 15
echo -e "@HD\tVN:1.0\tGO:none\tSO:coordinate" > regions_headers.sam
echo -e "@SQ\tSN:12\tLN:133851895\n@SQ\tSN:20\tLN:63025520" >> regions_headers.sam
cat endsam.txt >> regions_headers.sam
scp regions_headers.sam odroid@192.168.1.115:/genomics/regions_headers.sam