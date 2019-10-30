# SWARAM
SWARAM is a portable, energy efficient and cost efficient system for genome processing.


## Set up SWARAM

### Hardware Requirements

- ODROID XU4 (cooling fan based) - 16
- eMMC 64GB (Minimum) -16
- USB3.0 flash drive (128 GB) - 16
- 20 -port GBethernet SWITCH -1
- Power Suppply - 1
- Netowrk cable -1 16
- An external harddrive for using as a storage for input reads.

### Device setup
- Boot all XU4 devices with LINUX OS.
- Connect one flashdrive on each of the device.
- Connect all ODROID XU4 devices to the switch using the netowrk cables.
- Configure the switch to establish a single ipaddress under which all the devices can be grouped under.

## Device Configuration
- Ensure DHCP automatic selection is selected
- Enable SSH, genetrate ssh keys.
- copy the ssh keys to each and every devices to enable device to device easy communication.
- Mount ramdisk, swapfile, genomics folder, harddrive as storage  and the flashdrive as genstore on each of the device
- Copy the deduplication program to /genomics/sorting_framework



## Getting started

First clone the repository recursively.

```sh
git clone --recursive https://github.com/Rammohanty/swaram
```

The submodules that will be cloned are as follows.
- bwa-arm : BWA-MEM aligner ported for ARMv7
- dedupli : Spurious alignment Removal(SAR), distributed splitting and data transfer
- platypus-arm : Platypus variant caller ported for ARMv7
- scripts : scripts for execution of variant calling work-flow on SWARAM

### Building bwa-arm
To enable execution of BWA on armv7 devices.
build bwa-arm

```sh
make arm_neon=1 #assuming that you are in swaram directory
```

The executable named `bwa` will be generated. Copy this binary accross all the devices to the location `//home/odroid/bwa-0.7.15`. You may run  `copybwa.sh` to copy this binary across the all the devices, given that you have already configured *ansible*.

To enable execution of BWA using ramdisk, interleaved read dataset needs to be used. On the basis of the ramdisk size, a block of reads are copied to the ramdisk of each of the device for alignment.

build bwa arm-lmem (for bwa ramdisk version)

```sh
make -f Makefile_lmem arm_neon =1
```

The executable named `bwa` will be generated. 
Now test if you can launch BWA successfully.

```sh
./bwa mem -help  #assuming that you are in swaram/bwa-arm directory
```

Copy this binary accross all the devices to the location `//home/odroid/bwa-0.7.15`. You may run  `copybwa.sh` to copy this binary across the all the devices, given that you have already configured *ansible*.


### Building dedupli

```sh
cd dedupli #assuming that you are in swaram directory
make
```

The executable named `main` will be generated. Copy this binary accross all the devices to the location `/genomics/sorting_framework/dedupli`. You may run  `copyexe.sh` to copy this binary across the all the devices, given that you have already configured *ansible* and edited `copyexe.yml` in the current directory accordingly (*hosts*, *remote_user* and *src* fields in the *yml* file).


### Building platypus-arm

Install the dependencies

```sh
#cython and zlib development libraries
sudo apt-get install cython zlib1g-dev

#htslib (version 1.2.1 is recommended)
wget "https://github.com/samtools/htslib/releases/download/1.2.1/htslib-1.2.1.tar.bz2" -O htslib-1.2.1.tar.bz2
tar xvf htslib-1.2.1.tar.bz2
cd htslib-1.2.1
./configure CFLAGS="-g -O2 -D_FILE_OFFSET_BITS=64"
make
sudo make install
sudo ldconfig
```

Now build Platypus development version.

```sh
cd platypus-arm #assuming that you are in swaram directory
make
```

Now let us create a release version and build again (recommended as the development version has debug flags which may affect performance)
```sh
make release #assuming that you are in platypus-arm directory
tar xvf Platypus_0.8.1.1_arm.tgz
cd Platypus_0.8.1.1_arm
./buildPlatypus.sh
```

Now test if you can launch Platypus successfully.

```sh
python Platypus.py callVariants --help #assuming that you are in platypus-arm directory Platypus_0.8.1.1_arm directory
```

Copy the contents in this `Platypus_0.8.1.1_arm` directory accross all the devices to the location `/genomics/platypus`


