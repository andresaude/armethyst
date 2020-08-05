	.arch armv8-a
	.file	"isummation.c"
	.text
	.global	v
	.data
	.align	3
	.type	v, %object
	.size	v, 40
v:
	.word	5
	.word	2
	.word	9
	.word	6
	.word	3
	.word	10
	.word	7
	.word	4
	.word	1
	.word	8
	.global	summ
	.bss
	.align	2
	.type	summ, %object
	.size	summ, 4
summ:
	.zero	4
	.text
	.align	2
	.global	main
	.type	main, %function
main:
	sub	sp, sp, #16
	str	wzr, [sp, 12]
	b	.L2
.L3:
	adrp	x0, v
	add	x0, x0, :lo12:v
	ldrsw	x1, [sp, 12]
	ldr	w1, [x0, x1, lsl 2]
	adrp	x0, summ
	add	x0, x0, :lo12:summ
	ldr	w0, [x0]
	add	w1, w1, w0
	adrp	x0, summ
	add	x0, x0, :lo12:summ
	str	w1, [x0]
	ldr	w0, [sp, 12]
	add	w0, w0, 1
	str	w0, [sp, 12]
.L2:
	ldr	w0, [sp, 12]
	cmp	w0, 9
	ble	.L3
	nop
	add	sp, sp, 16
	ret
	.size	main, .-main
	.ident	"GCC: (GNU Toolchain for the A-profile Architecture 8.3-2019.03 (arm-rel-8.36)) 8.3.0"
