make
rsync -avz /home/odroid/sorting_framework/main odroid@odroid01:/home/odroid/sorting_framework/main
rsync -avz /home/odroid/sorting_framework/main odroid@odroid02:/home/odroid/sorting_framework/main
rsync -avz /home/odroid/sorting_framework/main odroid@odroid03:/home/odroid/sorting_framework/main
./main &
echo "Press any key to continue"
read p
ansible-playbook ansible.yml
