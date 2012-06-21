.text

.globl insert_sort

insert_sort:
	push %ebp
	mov %esp, %ebp
	sub $16, %esp

	mov %ebx, 12(%esp)	# save callee-saved registers
	mov %edi, 8(%esp)
	mov %esi, 4(%esp)

	mov 12(%ebp), %edx	# place length arg - 1 in edx
	sub $1, %edx

	mov $1, %ecx		# current loop index, starts at 1
	mov 8(%ebp), %esi	# store array base in esi

	jmp .main_comparison

.main_loop:
	mov %ecx, (%esp)	# store current index on the stack so we can manipulate it

			 	# store A[index] in eax
	mov (%esi, %ecx, 4), %eax

.begin_sub_loop:
	cmp $0, (%esp)		# if the current index is 0, bail
	je .end_main_loop

	mov (%esp), %ebx	# load A[index - 1] into ebx
	sub $1, %ebx
	mov (%esi, %ebx, 4), %ebx

	cmp %ebx, %eax		# compare A[index - 1] to A[index], bail if it is smaller
	jg .end_main_loop

	mov (%esp), %edi	# load A[index - 1] into A[index]
	mov %ebx, (%esi, %edi, 4)

	sub $1, (%esp)		# subtract 1 from stored index on the stack

	jmp .begin_sub_loop

.end_main_loop:
	mov (%esp), %ebx	# move A[index] into its new location
	mov %eax, (%esi, %ebx, 4)
	
	add $1, %ecx		# increment loop
	
.main_comparison:
	cmp %edx, %ecx 		# only loop when index <= length - 1
	jle .main_loop

	mov 12(%esp), %ebx	# restore callee-saved registers
	mov 8(%esp), %edi
	mov 4(%esp), %esi

	mov $0, %eax;
	mov %ebp, %esp
	pop %ebp
	ret
