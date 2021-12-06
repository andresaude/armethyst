	.arch armv8-a
	.file	"isummationLarge.c"
	.text
	.global	v
	.bss
	.align	3
	.type	v, %object
	.size	v, 4000000
v:
	.zero	4000000
	.global	summ
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
	ldr	w0, [sp, 12]
	add	w2, w0, 1
	adrp	x0, v
	add	x0, x0, :lo12:v
	ldrsw	x1, [sp, 12]
	str	w2, [x0, x1, lsl 2]
	ldr	w0, [sp, 12]
	add	w0, w0, 1
	str	w0, [sp, 12]
.L2:
	ldr	w1, [sp, 12]
	mov	w0, 16959
	movk	w0, 0xf, lsl 16
	cmp	w1, w0
	ble	.L3
	str	wzr, [sp, 12]
	b	.L4
.L5:
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
.L4:
	ldr	w1, [sp, 12]
	mov	w0, 16959
	movk	w0, 0xf, lsl 16
	cmp	w1, w0
	ble	.L5
	nop
	nop
	add	sp, sp, 16
	ret
	.size	main, .-main
	.ident	"GCC: (GNU Toolchain for the A-profile Architecture 10.3-2021.07 (arm-10.29)) 10.3.1 20210621"
