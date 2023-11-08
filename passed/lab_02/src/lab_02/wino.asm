                row[i] += mA[i][j << 1] * mA[i][(j << 1) + 1];
00007FF7CA8516B0  mov         r10,qword ptr [rbp-9]  
00007FF7CA8516B4  mov         rax,qword ptr [r15+8]  
00007FF7CA8516B8  mov         rdx,qword ptr [r12+rax]  
00007FF7CA8516BC  xor         r11d,r11d  
00007FF7CA8516BF  lea         ebx,[r9+6]  
00007FF7CA8516C3  lea         rsi,[rdi-4]  
00007FF7CA8516C7  shr         rsi,2  
00007FF7CA8516CB  inc         rsi  
00007FF7CA8516CE  lea         r14,[rsi*4]  
00007FF7CA8516D6  nop         word ptr [rax+rax]  
00007FF7CA8516E0  lea         eax,[r9+r9]  
00007FF7CA8516E4  movsxd      rcx,eax  
00007FF7CA8516E7  movsd       xmm0,mmword ptr [rdx+rcx*8]  
00007FF7CA8516EC  mulsd       xmm0,mmword ptr [rdx+r11+8]  
00007FF7CA8516F3  addsd       xmm0,mmword ptr [r10+r8*8]  
00007FF7CA8516F9  movsd       mmword ptr [r10+r8*8],xmm0  
00007FF7CA8516FF  movsxd      rax,ebx  
00007FF7CA851702  movsd       xmm1,mmword ptr [rdx+rax*8-20h]  
00007FF7CA851708  mulsd       xmm1,mmword ptr [rdx+r11+18h]  
00007FF7CA85170F  addsd       xmm1,xmm0  
00007FF7CA851713  movsd       mmword ptr [r10+r8*8],xmm1  
00007FF7CA851719  movsxd      rax,ebx  
00007FF7CA85171C  movsd       xmm2,mmword ptr [rdx+rax*8-10h]  
00007FF7CA851722  mulsd       xmm2,mmword ptr [rdx+r11+28h]  
00007FF7CA851729  addsd       xmm2,xmm1  
00007FF7CA85172D  movsd       mmword ptr [r10+r8*8],xmm2  
00007FF7CA851733  movsxd      rax,ebx  
00007FF7CA851736  movsd       xmm0,mmword ptr [rdx+rax*8]  
00007FF7CA85173B  mulsd       xmm0,mmword ptr [rdx+r11+38h]  
00007FF7CA851742  addsd       xmm0,xmm2  
00007FF7CA851746  movsd       mmword ptr [r10+r8*8],xmm0  
00007FF7CA85174C  add         r9d,4  
00007FF7CA851750  add         ebx,8  
00007FF7CA851753  add         r11,40h  
00007FF7CA851757  sub         rsi,1  
00007FF7CA85175B  jne         MatrixSolver::winograd_algo+2A0h (07FF7CA8516E0h) 