.section .init, "x"
.global _start
_start:
	ldr x1, =__stack_firm_start
	mov sp, x1

	// Clear bss
	ldr x1, =__bss_start
	ldr w2, =__bss_size
3:
	cbz w2, 4f
	str xzr, [x1], #8
	sub w2, w2, #1
	cbnz w2, 3b
4:	
	ldr  x1,=0x01C28000
	ldr  x2,=message
loop:	         ldrb w0, [x2]
	add  x2, x2, #1
	cmp  w0, #0
	beq  completed
	strb w0, [x1]
	b    loop
completed:

	// C言語プログラムのメイン関数にジャンプ
	bl  main
	// フェイルセーフの場合は、このコアも停止
	b _start
	.data
message:
	.asciz "*** Hello from aarch64! ***"
	.end
