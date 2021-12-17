mkdir -p isodir/boot/grub
cp $3 isodir/boot/OS.bin
echo "set timeout=0
set default=0
menuentry \"$1\" {
  multiboot2 /boot/OS.bin
}" > isodir/boot/grub/grub.cfg
grub-mkrescue isodir -o $2
