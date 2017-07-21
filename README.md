# littleOS
Début d'implementaiton du little book about OS development http://littleosbook.github.io/

## 2. First Step
- loader.s
- grub 
- geniso

- utilisation de qemu au lieu de bosh : 
qemu-system-x86_64 -boot d -cdrom os.iso -m 4 -monitor stdio

- commande monitor : info registers 
(qemu) info registers
EAX=cafebabe EBX=0002cd80 ECX=00000001 EDX=00000000


## 3. Getting to C
- kmain.c
- Makefile

## 4. Output
- io.s .h
- framebuffer.c .h 
- serial.c .h 

## 5. Segmentation
- gdt.s
- memory_segment.c .h

## 6. Interrupts and Input
- interrupt_handlers.s
- interrupts.c .h
- pic.c
- keyboard.c .h

## 7. The Road to User Mode
- multiboot.h
- program.s ( nasm -fbin modules/program.s -o modules/program ) 

## 9 Paging
- paging_init.s 
- paging.c 

## Resources
- http://wiki.osdev.org
- https://github.com/tuhdo/os01
- https://0xax.gitbooks.io/linux-insides/content/
- https://intermezzos.github.io/
- http://os.phil-opp.com/
- http://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf

