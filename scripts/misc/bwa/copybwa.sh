mv /home/odroid/bwa-0.7.15/bwa /home/odroid/bwa-0.7.15/bwatemp
ansible all -m copy -a "src=/home/odroid/bwa-0.7.15/bwatemp dest=/home/odroid/bwa-0.7.15/bwa"
rm /home/odroid/bwa-0.7.15/bwatemp
