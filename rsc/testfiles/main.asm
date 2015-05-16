.init1:
mov r3,0													@r3 controls the outer loop
mov r6,4096	
b .init1looper									@r6 is the memory pointer
.init1looper:														@initializing the first matrix
	mov r1,0												@r1 controls the inner loop
	.helper1:
		add r4,r1,r3
		mod r4,r4,17
		st r4,[r6]											@store computed value somewhere
		add r6,r6,4											@memory gets incremented by 4
		add r1,r1,1
		cmp r0,r1
		bgt .helper1
	add r3,r3,1
	cmp r0,r3
	bgt .init1looper
ret

.init2:
mov r3,0													@initializing the 2nd matrix
.init2looper:
	mov r1,0
	.helper2:
		sub r4,r3,r1
		add r4,r4,64
		mod r4,r4,6   										
		mul r5,r3,r1										@r5 used as helper to r4
		mod r5,r5,8
		add r4,r4,r5										@r5 ka kaam khatam
		st r4,[r6]
		add r6,r6,4
		add r1,r1,1
		cmp r0,r1
		bgt .helper2
	add r3,r3,1
	cmp r0,r3
	bgt .init2looper
ret

.matmul:	
mov r3,0 														@i->r3
.matmullooper:													@matrix multiplication
	mov r1,0  													@j->r1
	.helpermatmul:
		mov r4,0
		mov r5,0												@r5 used for innermost loop, wont be available here on k->r5
		.helperhelpermatmul:
			mul r7,r0,r3
			add r7,r7,r5
			mul r7,r7,4
			add r7,r7,4096

			mul r8,r5,r0
			add r8,r8,r1
			mul r8,r8,4
			add r8,r8,4096

			mul r9,r0,r0
			mul r9,r9,4
			add r8,r8,r9

			ld r8,[r8]
			ld r7,[r7]

			mul r10,r7,r8
			add r4,r4,r10

			add r5,r5,1
			cmp r0,r5
			bgt .helperhelpermatmul
		st r4,[r6]											@store r4 somewhere
		add r6,r6,4
		add r1,r1,1
		cmp r0,r1
		bgt .helpermatmul
	add r3,r3,1
	cmp r0,r3
	bgt .matmullooper
ret

.matsum:
mov r3,0 														@i->r3
mov r4,0 								
.matsumlooper:													@sum of two matrices
	mov r1,0 													@j->r1
	.helpermatsum:
		mul r7,r3,r0
		add r7,r7,r1
		mul r7,r7,4
		add r7,r7,4096

		mul r8,r0,r0
		mul r8,r8,8

		add r7,r7,r8
		ld r7,[r7]
		
		add r4,r4,r7									@how do i load stuff?
		add r6,r6,4
		add r1,r1,1
		cmp r0,r1
		bgt .helpermatsum
	add r3,r3,1
	cmp r0,r3
	bgt .matsumlooper
ret

.main:

	mul r3,r0,r0
	mul r3,r3,3
	.alloc r0 r3
	call .init1 
	call .init2 
	call .matmul
	call .matsum
	.print r4