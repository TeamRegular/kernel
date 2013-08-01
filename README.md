Linux Kernel for SHIELD
=======================
This is a temporary project that maintains a version of the Linux kernel that can boot in NVIDIA's SHIELD. It will be removed once all necessary patches have been approved and merged upstream.

WARNING: this branch will be regularly rebased to the latest upstream and to update the set of patches in progress. Be aware of this if you plan to base your work on it.

What's here
-----------
Not much really - this is just a Linux kernel (currently 3.11-rc3) with a few extra patches that add SHIELD's device tree, custom kernel configuration, and a few features/hacks.

What's (not yet) supported
--------------------------
Display: currently uses simplefb. tegra-drm support should appear in the future.

USB: not working yet - should come soon.

Joystick: requires USB.

Wifi: not working yet.

All the rest should be working as expected. You can access eMMC and SD.

How to compile and boot
-----------------------
Use the tegra\_roth\_defconfig configuration and build zImage and dtbs. The kernel configuration uses appended DTB so you can boot the kernel without altering any system partition. To append the DTB to your kernel image:

    $ cat arch/arm/boot/zImage arch/arm/boot/dts/tegra114-roth.dtb >zImage_dtb

The kernel boots into a ramdisk by default, which will be provided by fastboot. You can obtain a basic Busybox ramdisk here: https://github.com/Gnurou/bbfs

The go into the bootloader to boot the image using fastboot. Your bootloader must be unlocked for this to work:

    $ fastboot boot zImage_dtb /path/to/ramfs.img.gz

Note that doing this will not alter your Android system. If you wish a more complex user space, you can write one into a microSD card and change `root=/dev/ram rdinit=/sbin/init` to `root=/dev/mmcblk0p1 init=/sbin/init` in your kernel configuration.

Disclaimer
----------
Tampering with your SHIELD is dangerous and you should only do this if you perfectly understand what you are doing. Unlocking your SHIELD will void its warranty and exposes it to being permanently broken, so be wise.
