#!/bin/bash
GMETRIC=/usr/bin/gmetric

#echo `date` "- executing ganglia-metrics.sh"

t=`cat /sys/devices/virtual/thermal/thermal_zone0/temp`
t1=$(echo "scale=2; $t/1000" | bc)
f0=`cat /sys/devices/system/cpu/cpu0/cpufreq/scaling_cur_freq`
f0_r=$(echo "scale=2;  $f0/1000" | bc)

f1=`cat /sys/devices/system/cpu/cpu1/cpufreq/scaling_cur_freq`
f1_r=$(echo "scale=2;  $f1/1000" | bc)

f2=`cat /sys/devices/system/cpu/cpu2/cpufreq/scaling_cur_freq`
f2_r=$(echo "scale=2;  $f2/1000" | bc)

f3=`cat /sys/devices/system/cpu/cpu3/cpufreq/scaling_cur_freq`
f3_r=$(echo "scale=2;  $f3/1000" | bc)

$GMETRIC --name="temperature" --type=float --value=$t1 --units="Celcius"
$GMETRIC --name="CPU0_freq" --type=float --value=$f0_r --units="MHz"
$GMETRIC --name="CPU1_freq" --type=float --value=$f1_r --units="MHz"
$GMETRIC --name="CPU2_freq" --type=float --value=$f2_r --units="MHz"
$GMETRIC --name="CPU3_freq" --type=float --value=$f3_r --units="MHz"

