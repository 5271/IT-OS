build:
	i686-elf-gcc -T boot/linker.ld -o IT-OS.bin -ffreestanding -O2 -nostdlib -lgcc boot/boot.s kernel/kernel.c
	mv IT-OS.bin isodir/boot/
	grub-mkrescue -o IT-OS.iso isodir

run:
	i686-elf-gcc -T boot/linker.ld -o IT-OS.bin -ffreestanding -O2 -nostdlib -lgcc boot/boot.s kernel/kernel.c
	mv IT-OS.bin isodir/boot/
	grub-mkrescue -o IT-OS.iso isodir
	qemu-system-x86_64 IT-OS.iso