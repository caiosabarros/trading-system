	.file	"break.cpp"
	.intel_syntax noprefix
	.text
	.p2align 4
	.globl	_Z13flip_sign_bitPm
	.type	_Z13flip_sign_bitPm, @function
_Z13flip_sign_bitPm:
.LFB33:
	.cfi_startproc
	endbr64
	bts	QWORD PTR [rdi], 63
	ret
	.cfi_endproc
.LFE33:
	.size	_Z13flip_sign_bitPm, .-_Z13flip_sign_bitPm
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC1:
	.string	"origin_x:%0.2f x:%0.2f\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB34:
	.cfi_startproc
	endbr64
	sub	rsp, 8
	.cfi_def_cfa_offset 16
	mov	edi, 2
	mov	eax, 2
	movsd	xmm0, QWORD PTR .LC0[rip]
	lea	rsi, .LC1[rip]
	movapd	xmm1, xmm0
	call	__printf_chk@PLT
	xor	eax, eax
	add	rsp, 8
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE34:
	.size	main, .-main
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC0:
	.long	-1095630848
	.long	1110955880
	.ident	"GCC: (Ubuntu 15.2.0-16ubuntu1) 15.2.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
