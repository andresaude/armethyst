	.arch armv8-a
	.file	"fpops.c"
	.text
	.global	v
	.data
	.align	3
	.type	v, %object
	.size	v, 44
v:
	.word	1078774989
	.word	1056964608
	.word	1083598438
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.text
	.align	2
	.global	main
	.type	main, %function
main:
	sub	sp, sp, #32
	adrp	x0, v
	add	x0, x0, :lo12:v
	ldr	w0, [x0]
	str	w0, [sp, 20]
	adrp	x0, v
	add	x0, x0, :lo12:v
	ldr	w0, [x0, 4]
	str	w0, [sp, 16]
	adrp	x0, v
	add	x0, x0, :lo12:v
	ldr	w0, [x0, 8]
	str	w0, [sp, 12]
	ldr	s0, [sp, 16]
	fneg	s1, s0
	ldr	s0, [sp, 20]
	fadd	s0, s0, s0
	fdiv	s1, s1, s0
	fmov	s0, 5.0e+0
	fsub	s0, s1, s0
	str	s0, [sp, 24]
	str	wzr, [sp, 28]
	b	.L2
.L3:
	ldr	s1, [sp, 20]
	ldr	s0, [sp, 24]
	fmul	s1, s1, s0
	ldr	s0, [sp, 24]
	fmul	s1, s1, s0
	ldr	s2, [sp, 16]
	ldr	s0, [sp, 24]
	fmul	s0, s2, s0
	fadd	s1, s1, s0
	ldr	s0, [sp, 12]
	fadd	s0, s1, s0
	adrp	x0, v
	add	x0, x0, :lo12:v
	ldrsw	x1, [sp, 28]
	str	s0, [x0, x1, lsl 2]
	ldr	s1, [sp, 24]
	fmov	s0, 1.0e+0
	fadd	s0, s1, s0
	str	s0, [sp, 24]
	ldr	w0, [sp, 28]
	add	w0, w0, 1
	str	w0, [sp, 28]
.L2:
	ldr	w0, [sp, 28]
	cmp	w0, 10
	ble	.L3
	nop
	add	sp, sp, 32
	ret
	.size	main, .-main
	.ident	"GCC: (GNU Toolchain for the A-profile Architecture 8.3-2019.03 (arm-rel-8.36)) 8.3.0"
