	.section ".text.boot"

	.global _start
_start:
	ldr x1, =0x40007000
	mov sp, x1
4:
	// C言語プログラムのメイン関数にジャンプ
	bl  main

5:	
	ldr  x1,=0x01C28000
	ldr  x2,=message
loop:	         ldrb w0, [x2]
	add  x2, x2, #1
	cmp  w0, #0
	beq  completed
	strb w0, [x1]
	b    loop
completed:
	
message:
	.asciz "*** Hello from aarch64! new ***"
	.end
	
