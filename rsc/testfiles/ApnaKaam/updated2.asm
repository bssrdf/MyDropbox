.init1:
mov r3,0													@r3 controls the outer loop
mov r6,4096								@r6 is the memory pointer
mul r11,r0,4
.init1looper:														@initializing the first matrix
	mov r1,0												@r1 controls the inner loop
	.helper1:
		add r4,r1,r3
		mod r4,r4,17
		st r4,[r6]											@store computed value somewhere

		
		add r6,r6,r11											@memory gets incremented by 4
		add r4,r4,1
		mod r4,r4,17
		st r4,[r6]

		add r6,r6,4
		add r4,r4,1
		mod r4,r4,17
		st r4,[r6]

		sub r6,r6,r11
		add r4,r1,r3
		add r4,r4,1
		mod r4,r4,17
		st r4,[r6]
		
		add r6,r6,4

		add r1,r1,2
		cmp r0,r1
		bgt .helper1
	add r3,r3,2
	add r6,r6,r11
	cmp r0,r3
	bgt .init1looper
ret

.init2:
mov r3,0													@initializing the 2nd matrix
.init2looper:
	mov r1,0
	.helper2:
		sub r12,r3,r1
		add r12,r12,64
		mod r12,r12,6   										
		mul r5,r3,r1										@r5 used as helper to r4
		mod r5,r5,8
		add r4,r12,r5										@r5 ka kaam khatam
		st r4,[r6]
		

		add r6,r6,r11
		sub r12,r3,r1
		add r12,r12,65
		mod r12,r12,6 
		mul r5,r3,r1										@r5 used as helper to r4
		add r5,r5,r1
		mod r5,r5,8	 
		add r4,r12,r5
		st r4,[r6]
		

		add r6,r6,4
		sub r12,r3,r1
		add r12,r12,64
		mod r12,r12,6 
		mul r5,r3,r1										@r5 used as helper to r4
		add r5,r5,r1
		add r5,r5,r3
		add r5,r5,1
		mod r5,r5,8
		add r4,r12,r5
		st r4,[r6]
		

		sub r6,r6,r11
		sub r12,r3,r1
		add r12,r12,63
		mod r12,r12,6
		mul r5,r3,r1										@r5 used as helper to r4
		add r5,r5,r3
		mod r5,r5,8
		add r4,r12,r5
		st r4,[r6]
		

		add r6,r6,4
		add r1,r1,2
		cmp r0,r1
		bgt .helper2
	add r3,r3,2
	add r6,r6,r11
	cmp r0,r3
	bgt .init2looper
ret

.matmul:

mov r3,0 														@i->r3
.matmullooper:													@matrix multiplication
	mov r1,0  													@j->r1
	.helpermatmul:
		mov r4,0
		mov r2,0
		mov r9,0
		mov r14,0
		mov r5,0												@r5 used for innermost loop, wont be available here on k->r5
		.helperhelpermatmul:
			mul r7,r0,r3
			add r7,r7,r5
			mul r7,r7,4
			add r7,r7,4096										@r7->a[i][k]

			mul r8,r5,r0
			add r8,r8,r1
			mul r8,r8,4
			add r8,r8,4096

			mul r10,r0,r0 										@could store this
			mul r10,r10,4
			add r8,r8,r10										@r8->b[k][j]

			ld r12,[r8]
			ld r13,[r7]
			mul r10,r13,r12
			add r4,r4,r10										@r4 is sum1(c[i][j])
			
			add r7,r7,4
			add r8,r8,r11
			ld r12,[r8]
			ld r13,[r7]
			mul r10,r13,r12
			add r4,r4,r10										@r4 is sum1(c[i][j])
			
			add r7,r7,r11
			ld r13,[r7]
			mul r10,r13,r12
			add r2,r2,r10
			
			sub r7,r7,4
			sub r8,r8,r11
			ld r12,[r8]
			ld r13,[r7]
			mul r10,r13,r12
			add r2,r2,r10
			
			add r8,r8,4
			ld r12,[r8]
			mul r10,r13,r12
			add r9,r9,r10
			
			add r7,r7,4
			add r8,r8,r11
			ld r12,[r8]
			ld r13,[r7]
			mul r10,r13,r12
			add r9,r9,r10
			
			sub r7,r7,r11
			ld r13,[r7]
			mul r10,r13,r12
			add r14,r14,r10
			
			sub r7,r7,4
			sub r8,r8,r11
			ld r12,[r8]
			ld r13,[r7]
			mul r10,r13,r12
			add r14,r14,r10
			


			add r5,r5,2
			cmp r0,r5
			bgt .helperhelpermatmul
		st r4,[r6]											@store r4 somewhere

		add r6,r6,r11
		st r2,[r6]

		add r6,r6,4
		st r9,[r6]

		sub r6,r6,r11
		st r14,[r6]

		add r6,r6,4

		add r1,r1,2
		cmp r0,r1
		bgt .helpermatmul
	add r3,r3,2
	add r6,r6,r11
	cmp r0,r3
	bgt .matmullooper
ret

.matsum:
mov r3,0 														@i->r3
mov r4,0 								
.matsumlooper:													@sum of two matrices
	mov r1,0 													@j->r1
	.helpermatsum:
		mul r12,r3,r0
		add r12,r12,r1
		mul r12,r12,4
		add r6,r12,4096

		mul r8,r0,r0
		mul r8,r8,8

		add r6,r6,r8

		ld r13,[r6]
		
		add r4,r4,r13									@how do i load stuff?
		add r6,r6,r11

		ld r13,[r6]
		add r4,r4,r13									@how do i load stuff?
		add r6,r6,4

		ld r13,[r6]
		add r4,r4,r13									@how do i load stuff?
		sub r6,r6,r11				

		ld r13,[r6]
		add r4,r4,r13									@how do i load stuff?
		add r6,r6,4




		add r1,r1,2
		cmp r0,r1
		bgt .helpermatsum
	add r3,r3,2
	add r6,r6,r11
	cmp r0,r3
	bgt .matsumlooper
ret

.main:
	mul r3,r0,r0
	mul r3,r3,3
	.alloc 0 r3 
	call .init1
	call .init2 
	call .matmul
	call .matsum
	.print r4