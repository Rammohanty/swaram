#device 0
echo "192.168.1.101" > horizontal_topology.cfg
echo "192.168.1.102" >> horizontal_topology.cfg
echo "192.168.1.103" >> horizontal_topology.cfg
scp horizontal_topology.cfg odroid@192.168.1.100:/genomics/horizontal_topology.cfg


#device 1
echo "192.168.1.100" > horizontal_topology.cfg
echo "192.168.1.102" >> horizontal_topology.cfg
echo "192.168.1.103" >> horizontal_topology.cfg
scp horizontal_topology.cfg odroid@192.168.1.101:/genomics/horizontal_topology.cfg


#device 2
echo "192.168.1.100" > horizontal_topology.cfg
echo "192.168.1.101" >> horizontal_topology.cfg
echo "192.168.1.103" >> horizontal_topology.cfg
scp horizontal_topology.cfg odroid@192.168.1.102:/genomics/horizontal_topology.cfg


#device 3
echo "192.168.1.100" > horizontal_topology.cfg
echo "192.168.1.101" >> horizontal_topology.cfg
echo "192.168.1.102" >> horizontal_topology.cfg
scp horizontal_topology.cfg odroid@192.168.1.103:/genomics/horizontal_topology.cfg

####################################################################################

#device 4
echo "192.168.1.105" > horizontal_topology.cfg
echo "192.168.1.106" >> horizontal_topology.cfg
echo "192.168.1.107" >> horizontal_topology.cfg
scp horizontal_topology.cfg odroid@192.168.1.104:/genomics/horizontal_topology.cfg

#device 5
echo "192.168.1.104" > horizontal_topology.cfg
echo "192.168.1.106" >> horizontal_topology.cfg
echo "192.168.1.107" >> horizontal_topology.cfg
scp horizontal_topology.cfg odroid@192.168.1.105:/genomics/horizontal_topology.cfg

#device 6
echo "192.168.1.104" > horizontal_topology.cfg
echo "192.168.1.105" >> horizontal_topology.cfg
echo "192.168.1.107" >> horizontal_topology.cfg
scp horizontal_topology.cfg odroid@192.168.1.106:/genomics/horizontal_topology.cfg

#device 7
echo "192.168.1.104" > horizontal_topology.cfg
echo "192.168.1.105" >> horizontal_topology.cfg
echo "192.168.1.106" >> horizontal_topology.cfg
scp horizontal_topology.cfg odroid@192.168.1.107:/genomics/horizontal_topology.cfg


####################################################################################

#device 8
echo "192.168.1.109" > horizontal_topology.cfg
echo "192.168.1.110" >> horizontal_topology.cfg
echo "192.168.1.111" >> horizontal_topology.cfg
scp horizontal_topology.cfg odroid@192.168.1.108:/genomics/horizontal_topology.cfg

#device 9
echo "192.168.1.108" > horizontal_topology.cfg
echo "192.168.1.110" >> horizontal_topology.cfg
echo "192.168.1.111" >> horizontal_topology.cfg
scp horizontal_topology.cfg odroid@192.168.1.109:/genomics/horizontal_topology.cfg

#device 10
echo "192.168.1.108" > horizontal_topology.cfg
echo "192.168.1.109" >> horizontal_topology.cfg
echo "192.168.1.111" >> horizontal_topology.cfg
scp horizontal_topology.cfg odroid@192.168.1.110:/genomics/horizontal_topology.cfg

#device 11
echo "192.168.1.108" > horizontal_topology.cfg
echo "192.168.1.109" >> horizontal_topology.cfg
echo "192.168.1.110" >> horizontal_topology.cfg
scp horizontal_topology.cfg odroid@192.168.1.111:/genomics/horizontal_topology.cfg

####################################################################################

#device 12
echo "192.168.1.113" > horizontal_topology.cfg
echo "192.168.1.114" >> horizontal_topology.cfg
echo "192.168.1.115" >> horizontal_topology.cfg
scp horizontal_topology.cfg odroid@192.168.1.112:/genomics/horizontal_topology.cfg

#device 12
echo "192.168.1.112" > horizontal_topology.cfg
echo "192.168.1.114" >> horizontal_topology.cfg
echo "192.168.1.115" >> horizontal_topology.cfg
scp horizontal_topology.cfg odroid@192.168.1.113:/genomics/horizontal_topology.cfg

#device 12
echo "192.168.1.112" > horizontal_topology.cfg
echo "192.168.1.113" >> horizontal_topology.cfg
echo "192.168.1.115" >> horizontal_topology.cfg
scp horizontal_topology.cfg odroid@192.168.1.114:/genomics/horizontal_topology.cfg

#device 12
echo "192.168.1.112" > horizontal_topology.cfg
echo "192.168.1.113" >> horizontal_topology.cfg
echo "192.168.1.114" >> horizontal_topology.cfg
scp horizontal_topology.cfg odroid@192.168.1.115:/genomics/horizontal_topology.cfg
