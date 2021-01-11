CP := cp
MKDIR := mkdir
MKNOD := mknod
RM := rm

.PHONY: default
default: linux/linux

.PHONY: clean
clean: clean-init clean-initrd clean-linux

.PHONY: clean-init
clean-init:
	$(MAKE) -Cinit clean

.PHONY: clean-initrd
clean-initrd:
	$(RM) -rf initrd

.PHONY: clean-linux
clean-linux:
	$(MAKE) -Clinux clean

.PHONY: init/init
init/init:
	$(MAKE) -Cinit

linux/.config: kernel.config
	$(CP) kernel.config linux/.config

.PHONY: linux/linux
linux/linux: linux/.config initrd/dev/console initrd/init initrd/proc initrd/sys
	$(MAKE) -Clinux ARCH=um

initrd:
	$(MKDIR) -p initrd

initrd/dev: initrd
	$(MKDIR) -p initrd/dev

initrd/dev/console: initrd/dev
	$(MKNOD) initrd/dev/console c 5 1

initrd/init: initrd init/init
	$(CP) init/init initrd/init

initrd/proc: initrd
	$(MKDIR) -p initrd/proc

initrd/sys: initrd
	$(MKDIR) -p initrd/sys
