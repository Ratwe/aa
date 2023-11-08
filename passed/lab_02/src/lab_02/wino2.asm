                row[i] += mA[i][2 * j] * mA[i][2 * j + 1];
00007FF7CA851BED  mov         rdx,qword ptr [rbp-9]  
00007FF7CA851BF1  mov         rax,qword ptr [r15+8]  
00007FF7CA851BF5  mov         rcx,qword ptr [rbx+rax]  
00007FF7CA851BF9  movsd       xmm1,mmword ptr [rdx+r8*8]  
00007FF7CA851BFF  xor         eax,eax  
00007FF7CA851C01  lea         r9,[r10-4]  
00007FF7CA851C05  shr         r9,2  
00007FF7CA851C09  inc         r9  
00007FF7CA851C0C  lea         r11,[r9*4]  
00007FF7CA851C14  nop         dword ptr [rax]  
00007FF7CA851C18  nop         dword ptr [rax+rax]  
00007FF7CA851C20  movsd       xmm0,mmword ptr [rax+rcx+8]  
00007FF7CA851C26  mulsd       xmm0,mmword ptr [rax+rcx]  
00007FF7CA851C2B  addsd       xmm0,xmm1  
00007FF7CA851C2F  movsd       mmword ptr [rdx+r8*8],xmm0  
00007FF7CA851C35  movsd       xmm1,mmword ptr [rax+rcx+18h]  
00007FF7CA851C3B  mulsd       xmm1,mmword ptr [rax+rcx+10h]  
00007FF7CA851C41  addsd       xmm1,xmm0  
00007FF7CA851C45  movsd       mmword ptr [rdx+r8*8],xmm1  
00007FF7CA851C4B  movsd       xmm0,mmword ptr [rcx+rax+20h]  
00007FF7CA851C51  mulsd       xmm0,mmword ptr [rax+rcx+28h]  
00007FF7CA851C57  addsd       xmm0,xmm1  
00007FF7CA851C5B  movsd       mmword ptr [rdx+r8*8],xmm0  
00007FF7CA851C61  movsd       xmm1,mmword ptr [rcx+rax+30h]  
00007FF7CA851C67  mulsd       xmm1,mmword ptr [rax+rcx+38h]  
00007FF7CA851C6D  addsd       xmm1,xmm0  
00007FF7CA851C71  movsd       mmword ptr [rdx+r8*8],xmm1  
00007FF7CA851C77  add         rax,40h  
00007FF7CA851C7B  sub         r9,1  
00007FF7CA851C7F  jne         MatrixSolver::winograd_algo+7E0h (07FF7CA851C20h) 