make
rsync -avz /home/odroid/sorting_framework/main odroid@odroid03.cse.unsw.edu.au:/home/odroid/sorting_framework/main
rsync -avz /home/odroid/sorting_framework/main odroid@odroid04.cse.unsw.edu.au:/home/odroid/sorting_framework/main
rsync -avz /home/odroid/sorting_framework/main odroid@odroid05.cse.unsw.edu.au:/home/odroid/sorting_framework/main
./main /home/odroid/sorting_framework/data/set1.sam /home/odroid/sorting_framework/data/manual1.sam 80000 &
echo "Press any key to continue"
read p
ansible-playbook ansiblemanualarg2.yml
