build:
	i686-elf-gcc -T boot/linker.ld -o IT-OS.bin -ffreestanding -O2 -nostdlib -lgcc boot/boot.s kernel/kernel.c
	mv IT-OS.bin isodir/
	grub-mkrescue -o IT-OS.iso /isodir/