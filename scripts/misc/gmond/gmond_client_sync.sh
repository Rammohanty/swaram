ansible all -m copy -a "src=gmond.conf dest=/etc/ganglia/gmond.conf owner=root mode=0644" -K -b

