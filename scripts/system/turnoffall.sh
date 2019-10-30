#!/bin/bash

ansible all -m shell -a "poweroff" -K --become
#sudo reboot

