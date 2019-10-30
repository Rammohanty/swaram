echo "- hosts: all" > tmp.yml
echo  "  gather_facts: no" >> tmp.yml
echo  "  remote_user: odroid" >>tmp.yml
echo "  tasks:" >> tmp.yml
echo "  - name: \"command\"" >> tmp.yml
echo "    shell: $@" >> tmp.yml
echo "The command going to be run is : $@"
echo -n "Press y to continue : "
read p
[ $p =  "y" ] && ansible-playbook tmp.yml


