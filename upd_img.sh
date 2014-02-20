#!/bin/bash

sudo losetup /dev/loop0 brans_floppy.img
sudo mount /dev/loop0 /mnt/kernel/
sudo cp src/kernel /mnt/kernel/
sudo umount /dev/loop0
sudo losetup -d /dev/loop0
