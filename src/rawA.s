	.file	"TextToPrimes.cpp"
	.text
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"uint64_t EndPointConversions::getNextNumberBase10_XXd(std::span<const unsigned char>)"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC1:
	.string	"TextToPrimes.cpp"
.LC2:
	.string	"number.size() < max_20_digit"
	.section	.rodata.str1.8
	.align 8
.LC3:
	.string	"uint32_t {anonymous}::getNextNumberBase10_9d(std::span<const unsigned char>)"
	.section	.rodata.str1.1
.LC4:
	.string	"number.size() < max_9_digit"
	.section	.rodata.str1.8
	.align 8
.LC5:
	.string	"uint64_t {anonymous}::getNextNumberBase10_16d(std::span<const unsigned char>)"
	.section	.rodata.str1.1
.LC6:
	.string	"number.size() < max_16_digit"
.LC7:
	.string	"assert check Failed"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB8:
	.text
.LHOTB8:
	.p2align 4
	.globl	_ZN19EndPointConversions23getNextNumberBase10_XXdESt4spanIKhLm18446744073709551615EE
	.type	_ZN19EndPointConversions23getNextNumberBase10_XXdESt4spanIKhLm18446744073709551615EE, @function
_ZN19EndPointConversions23getNextNumberBase10_XXdESt4spanIKhLm18446744073709551615EE:
.LFB2783:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	cmpq	$20, %rsi
	ja	.L74
	movq	%rsi, %rcx
	movq	%rsi, %rax
	movl	_ZN12_GLOBAL__N_1L11size_lookupE(,%rsi,4), %esi
	movq	%rdi, %rdx
	cmpl	$1, %esi
	je	.L3
	cmpl	$2, %esi
	jne	.L75
	testq	%rcx, %rcx
	je	.L1
	leaq	(%rcx,%rdi), %rsi
	xorl	%eax, %eax
	movq	%rsi, %rcx
	subq	%rdi, %rcx
	andl	$3, %ecx
	je	.L16
	cmpq	$1, %rcx
	je	.L58
	cmpq	$2, %rcx
	je	.L59
	movzbl	(%rdi), %eax
	addq	$1, %rdx
.L59:
	leaq	(%rax,%rax,4), %rcx
	movzbl	(%rdx), %eax
	addq	$1, %rdx
	leaq	(%rax,%rcx,2), %rax
.L58:
	leaq	(%rax,%rax,4), %rcx
	movzbl	(%rdx), %eax
	addq	$1, %rdx
	leaq	(%rax,%rcx,2), %rax
	cmpq	%rdx, %rsi
	je	.L1
.L16:
	leaq	(%rax,%rax,4), %rcx
	movzbl	(%rdx), %eax
	addq	$4, %rdx
	leaq	(%rax,%rcx,2), %rax
	leaq	(%rax,%rax,4), %rcx
	movzbl	-3(%rdx), %eax
	leaq	(%rax,%rcx,2), %rax
	leaq	(%rax,%rax,4), %rcx
	movzbl	-2(%rdx), %eax
	leaq	(%rax,%rcx,2), %rax
	leaq	(%rax,%rax,4), %rcx
	movzbl	-1(%rdx), %eax
	leaq	(%rax,%rcx,2), %rax
	cmpq	%rdx, %rsi
	jne	.L16
.L1:
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L75:
	.cfi_restore_state
	testl	%esi, %esi
	jne	.L5
	cmpq	$9, %rcx
	ja	.L6
	testq	%rcx, %rcx
	je	.L1
	movzbl	(%rdi), %eax
	cmpq	$1, %rcx
	je	.L1
	movzbl	1(%rdi), %esi
	leal	(%rax,%rax,4), %eax
	leal	(%rsi,%rax,2), %eax
	cmpq	$2, %rcx
	je	.L1
	leal	(%rax,%rax,4), %esi
	movzbl	2(%rdi), %eax
	leal	(%rax,%rsi,2), %eax
	cmpq	$3, %rcx
	je	.L1
	leal	(%rax,%rax,4), %esi
	movzbl	3(%rdi), %eax
	leal	(%rax,%rsi,2), %eax
	cmpq	$4, %rcx
	je	.L1
	leal	(%rax,%rax,4), %esi
	movzbl	4(%rdi), %eax
	leal	(%rax,%rsi,2), %eax
	cmpq	$5, %rcx
	je	.L1
	leal	(%rax,%rax,4), %esi
	movzbl	5(%rdi), %eax
	leal	(%rax,%rsi,2), %eax
	cmpq	$6, %rcx
	je	.L1
	leal	(%rax,%rax,4), %esi
	movzbl	6(%rdi), %eax
	leal	(%rax,%rsi,2), %eax
	cmpq	$7, %rcx
	je	.L1
	leal	(%rax,%rax,4), %esi
	movzbl	7(%rdi), %eax
	leal	(%rax,%rsi,2), %eax
	cmpq	$9, %rcx
	jne	.L1
	leal	(%rax,%rax,4), %ecx
	movzbl	8(%rdi), %eax
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	leal	(%rax,%rcx,2), %eax
	ret
	.p2align 4,,10
	.p2align 3
.L3:
	.cfi_restore_state
	cmpq	$16, %rcx
	ja	.L11
	testq	%rcx, %rcx
	je	.L1
	movzbl	(%rdi), %eax
	cmpq	$1, %rcx
	je	.L1
	leaq	(%rax,%rax,4), %rsi
	movzbl	1(%rdi), %eax
	leaq	(%rax,%rsi,2), %rax
	cmpq	$2, %rcx
	je	.L1
	leaq	(%rax,%rax,4), %rsi
	movzbl	2(%rdi), %eax
	leaq	(%rax,%rsi,2), %rax
	cmpq	$3, %rcx
	je	.L1
	leaq	(%rax,%rax,4), %rsi
	movzbl	3(%rdi), %eax
	leaq	(%rax,%rsi,2), %rax
	cmpq	$4, %rcx
	je	.L1
	leaq	(%rax,%rax,4), %rsi
	movzbl	4(%rdi), %eax
	leaq	(%rax,%rsi,2), %rax
	cmpq	$5, %rcx
	je	.L1
	leaq	(%rax,%rax,4), %rsi
	movzbl	5(%rdi), %eax
	leaq	(%rax,%rsi,2), %rax
	cmpq	$6, %rcx
	je	.L1
	leaq	(%rax,%rax,4), %rsi
	movzbl	6(%rdi), %eax
	leaq	(%rax,%rsi,2), %rax
	cmpq	$7, %rcx
	je	.L1
	leaq	(%rax,%rax,4), %rsi
	movzbl	7(%rdi), %eax
	leaq	(%rax,%rsi,2), %rax
	cmpq	$8, %rcx
	je	.L1
	leaq	(%rax,%rax,4), %rsi
	movzbl	8(%rdi), %eax
	leaq	(%rax,%rsi,2), %rax
	cmpq	$9, %rcx
	je	.L1
	leaq	(%rax,%rax,4), %rsi
	movzbl	9(%rdi), %eax
	leaq	(%rax,%rsi,2), %rax
	cmpq	$10, %rcx
	je	.L1
	leaq	(%rax,%rax,4), %rsi
	movzbl	10(%rdi), %eax
	leaq	(%rax,%rsi,2), %rax
	cmpq	$11, %rcx
	je	.L1
	leaq	(%rax,%rax,4), %rsi
	movzbl	11(%rdi), %eax
	leaq	(%rax,%rsi,2), %rax
	cmpq	$12, %rcx
	je	.L1
	leaq	(%rax,%rax,4), %rsi
	movzbl	12(%rdi), %eax
	leaq	(%rax,%rsi,2), %rax
	cmpq	$13, %rcx
	je	.L1
	leaq	(%rax,%rax,4), %rsi
	movzbl	13(%rdi), %eax
	leaq	(%rax,%rsi,2), %rax
	cmpq	$14, %rcx
	je	.L1
	leaq	(%rax,%rax,4), %rsi
	movzbl	14(%rdi), %eax
	leaq	(%rax,%rsi,2), %rax
	cmpq	$16, %rcx
	jne	.L1
	leaq	(%rax,%rax,4), %rcx
	movzbl	15(%rdi), %eax
	leaq	(%rax,%rcx,2), %rax
	jmp	.L1
.L74:
	movl	$.LC0, %ecx
	movl	$43, %edx
	movl	$.LC1, %esi
	movl	$.LC2, %edi
	call	__assert_fail
.L6:
	movl	$.LC3, %ecx
	movl	$13, %edx
	movl	$.LC1, %esi
	movl	$.LC4, %edi
	call	__assert_fail
.L11:
	movl	$.LC5, %ecx
	movl	$21, %edx
	movl	$.LC1, %esi
	movl	$.LC6, %edi
	call	__assert_fail
	.cfi_endproc
	.section	.text.unlikely
	.cfi_startproc
	.type	_ZN19EndPointConversions23getNextNumberBase10_XXdESt4spanIKhLm18446744073709551615EE.cold, @function
_ZN19EndPointConversions23getNextNumberBase10_XXdESt4spanIKhLm18446744073709551615EE.cold:
.LFSB2783:
.L5:
	.cfi_def_cfa_offset 16
	movl	$.LC7, %edi
	call	perror
	xorl	%eax, %eax
	jmp	.L1
	.cfi_endproc
.LFE2783:
	.text
	.size	_ZN19EndPointConversions23getNextNumberBase10_XXdESt4spanIKhLm18446744073709551615EE, .-_ZN19EndPointConversions23getNextNumberBase10_XXdESt4spanIKhLm18446744073709551615EE
	.section	.text.unlikely
	.size	_ZN19EndPointConversions23getNextNumberBase10_XXdESt4spanIKhLm18446744073709551615EE.cold, .-_ZN19EndPointConversions23getNextNumberBase10_XXdESt4spanIKhLm18446744073709551615EE.cold
.LCOLDE8:
	.text
.LHOTE8:
	.p2align 4
	.globl	_ZN19EndPointConversions19getNextNumberBase10ESt4spanIKhLm18446744073709551615EE
	.type	_ZN19EndPointConversions19getNextNumberBase10ESt4spanIKhLm18446744073709551615EE, @function
_ZN19EndPointConversions19getNextNumberBase10ESt4spanIKhLm18446744073709551615EE:
.LFB2784:
	.cfi_startproc
	addq	%rdi, %rsi
	xorl	%eax, %eax
	cmpq	%rsi, %rdi
	je	.L79
	.p2align 5
	.p2align 4
	.p2align 3
.L78:
	leaq	(%rax,%rax,4), %rdx
	movzbl	(%rdi), %eax
	addq	$1, %rdi
	leaq	(%rax,%rdx,2), %rax
	cmpq	%rdi, %rsi
	jne	.L78
	ret
	.p2align 4,,10
	.p2align 3
.L79:
	ret
	.cfi_endproc
.LFE2784:
	.size	_ZN19EndPointConversions19getNextNumberBase10ESt4spanIKhLm18446744073709551615EE, .-_ZN19EndPointConversions19getNextNumberBase10ESt4spanIKhLm18446744073709551615EE
	.p2align 4
	.globl	_ZN19EndPointConversions16convertTextBlockESt4spanIKhLm18446744073709551615EES0_IKmLm18446744073709551615EES0_ImLm18446744073709551615EE
	.type	_ZN19EndPointConversions16convertTextBlockESt4spanIKhLm18446744073709551615EES0_IKmLm18446744073709551615EES0_ImLm18446744073709551615EE, @function
_ZN19EndPointConversions16convertTextBlockESt4spanIKhLm18446744073709551615EES0_IKmLm18446744073709551615EES0_ImLm18446744073709551615EE:
.LFB2803:
	.cfi_startproc
	salq	$3, %rcx
	je	.L95
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	movq	%rdi, %r11
	movq	%r8, %r12
	xorl	%edi, %edi
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movq	%rcx, %r8
	movq	%rdx, %rbp
	xorl	%r9d, %r9d
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	%rsi, %rbx
	.p2align 4
	.p2align 3
.L86:
	movq	0(%rbp,%rdi), %r10
	movq	%rbx, %rsi
	leaq	(%r11,%r9), %rax
	subq	%r9, %rsi
	cmpq	$-1, %r10
	cmovne	%r10, %rsi
	xorl	%edx, %edx
	addq	%rax, %rsi
	cmpq	%rax, %rsi
	je	.L84
	.p2align 5
	.p2align 4
	.p2align 3
.L85:
	leaq	(%rdx,%rdx,4), %rcx
	movzbl	(%rax), %edx
	addq	$1, %rax
	leaq	(%rdx,%rcx,2), %rdx
	cmpq	%rax, %rsi
	jne	.L85
.L84:
	movq	%rdx, (%r12,%rdi)
	addq	$8, %rdi
	leaq	1(%r10,%r9), %r9
	cmpq	%rdi, %r8
	jne	.L86
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
.L95:
	.cfi_restore 3
	.cfi_restore 6
	.cfi_restore 12
	ret
	.cfi_endproc
.LFE2803:
	.size	_ZN19EndPointConversions16convertTextBlockESt4spanIKhLm18446744073709551615EES0_IKmLm18446744073709551615EES0_ImLm18446744073709551615EE, .-_ZN19EndPointConversions16convertTextBlockESt4spanIKhLm18446744073709551615EES0_IKmLm18446744073709551615EES0_ImLm18446744073709551615EE
	.section	.rodata
	.align 32
	.type	_ZN12_GLOBAL__N_1L11size_lookupE, @object
	.size	_ZN12_GLOBAL__N_1L11size_lookupE, 84
_ZN12_GLOBAL__N_1L11size_lookupE:
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	1
	.long	1
	.long	1
	.long	1
	.long	1
	.long	1
	.long	1
	.long	2
	.long	2
	.long	2
	.long	2
	.ident	"GCC: (GNU) 14.2.1 20250110 (Red Hat 14.2.1-7)"
	.section	.note.GNU-stack,"",@progbits
