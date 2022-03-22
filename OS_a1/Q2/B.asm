section	.text
	global B
	extern C
B:                     
	push rdi
	mov rax, 1
	mov rdi, 1
	mov	rsi, message 
	mov	rdx, length	    
	syscall         ;write the message
	mov	rax, 1
	mov rdi, 1
	mov rsi, rsp   
	mov rdx, 8
	syscall			;write the ASSCII value 
	pop rdi	
	lea rax, [C]	;calling c on return
    mov [rsp], rax
    ret
section	.data
    message	db	'Hey i am B',0xa
	length equ $ - message	;length of the message	