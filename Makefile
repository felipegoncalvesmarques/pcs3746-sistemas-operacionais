CC=$(CROSS_COMPILE)gcc -Wall -Wextra -static -g
$(shell mkdir -p build/initramfs_root)

.PHONY: all clean
all: build/rootfs.gz

clean:
		rm -rf build
		find -name '*.o' -delete

build/rootfs.gz: build/initramfs_root/init build/initramfs_root/exec_process
		cd build/initramfs_root ; \
		find -type f -printf '%P\n' | cpio -o -H newc > ../rootfs.gz

build/initramfs_root/init: init.o
		$(CC) -o $@ $^

build/initramfs_root/exec_process: exec_process.o
		$(CC) -o $@ $^
