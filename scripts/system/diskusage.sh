ansible all -m shell -a "df -h | grep mmcblk0p2"
echo "___________________________________________________________________"
ansible all -m shell -a "df -h | grep genstore"

