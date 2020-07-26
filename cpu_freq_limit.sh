#!/bin/bash
# IT WAS WRITTEN by sadyqowl1560
## Enable msm thermal
# soon
## Enable cpu freq limit when it is needed
chain=1094400
nochain=-1
thermal_dir="/sys/devices/virtual/thermal/thermal_zone11/temp"
freq_limit_dir="/sys/power/cpufreq_max_limit"
while true; do
  for i in 1 2 3 4 5; do
     temp[i]=$(cat $thermal_dir)
     sleep 1
  done
  total=0
  for i in 1 2 3 4 5; do
     total=$(( total + temp[i] ))
  done
  avg=$(( total / 5 ))
  if [ $avg -ge 57 ]; then
    chmod 755 $freq_limit_dir
    echo $chain > $freq_limit_dir
    sleep 10
  else
    chmod 755 $freq_limit_dir
    echo $nochain > $freq_limit_dir
    sleep 10
  fi
done
