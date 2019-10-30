#!/bin/bash

ansible all -m shell -a "reboot" -K --become
#sudo reboot

