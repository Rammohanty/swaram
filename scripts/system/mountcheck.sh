ansible all -m shell -a "df -h | grep storage"
echo "__________________________________________________________"
ansible all -m shell -a "df -h | grep mnt"

