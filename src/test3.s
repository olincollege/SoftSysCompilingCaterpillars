ys123:
        .zero   4
var1:
        .zero   4
var4:
        .zero   4
var2:
        .zero   4
var3:
        .zero   4
var2:
        .zero   4
var5:
        .zero   4
var8:
        .zero   4
x:
        .zero   4
var0:
        .zero   4
var9:
        .zero   4
v20:
        .zero   4
v:
        .zero   4
y:
        .zero   4
main:
        push    rbp
        mov     rbp, rsp
        movss   xmm0, DWORD PTR .LC0[rip]
        movss   xmm1, DWORD PTR .LC1[rip]
        addss   xmm0, xmm1
        movss   DWORD PTR ys123[rip], xmm0
.L1:
        movss   xmm0, DWORD PTR var1[rip]
        movss   xmm1, DWORD PTR .LC2[rip]
        comiss  xmm0, xmm1
        jl      .L2
        movss   xmm0, DWORD PTR var2[rip]
        movss   DWORD PTR var1[rip], xmm0
        movss   xmm0, DWORD PTR var1[rip]
        movss   xmm1, DWORD PTR var2[rip]
        ucomiss xmm0, xmm1
        je      ;FILL IN WITH RIGHT DESTINATION
        movss   xmm0, DWORD PTR .LC17[rip]
        movss   xmm1, DWORD PTR .LC18[rip]
        comiss  xmm0, xmm1
        jg      ;FILL IN WITH RIGHT DESTINATION
        jmp     ;END DEST
.L2: ; BIG WHILE
        movss   xmm0, DWORD PTR .LC3[rip] ;var4 = 34*94
        movss   xmm1, DWORD PTR .LC4[rip]
        mulss   xmm0, xmm1
        movss   DWORD PTR var4[rip], xmm0
        movss   xmm0, DWORD PTR .LC5[rip] ;var3 = 324.8
        movss   DWORD PTR var2[rip], xmm0
        movss   xmm0, DWORD PTR .LC6[rip] ;var2 = 93-var5
        movss   xmm1, DWORD PTR .var5[rip] 
        subss   xmm0, xmm1
        movss   DWORD PTR var2[rip], xmm0
        movss   xmm0, DWORD PTR var5[rip] ;if statement
        movss   xmm1, DWORD PTR .LC7[rip]
        addss   xmm0, xmm1
        movss   xmm1, DWORD PTR .LC8[rip]
        movss   xmm2, DWORD PTR var2[rip]
        subss   xmm1, xmm2
        comiss  xmm0, xmm1
        je      .L3
        movss   xmm0, DWORD PTR x[rip]
        movss   xmm1, DWORD PTR .LC12[rip]
        comiss  xmm0, xmm1
        jge     .L4
        jmp     .L2
        
.L3: ; first if contents
        movss   xmm0, DWORD PTR .LC9[rip]
        movss   xmm1, DWORD PTR .LC10[rip]
        addss   xmm0, xmm1
        movss   DWORD PTR var3[rip], xmm0
        movss   xmm0, DWORD PTR .LC11[rip]
        movss   xmm1, DWORD PTR var8[rip]
        addss   xmm0, xmm1
        movss   DWORD PTR var4[rip], xmm0
        jmp     .L10
.L4:
        movss   xmm0, DWORD PTR .LC13[rip]
        movss   xmm1, DWORD PTR .LC14[rip]
        addss   xmm0, xmm1
        movss   DWORD PTR var3[rip], xmm0
.L5:
        movss   xmm0, DWORD PTR .LC15[rip]
        movss   DWORD PTR var3[rip], xmm0
        movss   xmm0, DWORD PTR .LC16[rip]
        movss   xmm1, DWORD PTR var1[rip]
        addss   xmm0, xmm1
        movss   xmm1, DWORD PTR var3[rip]
        divss   xmm0, xmm1
        movss   xmm1, DWORD PTR var9[rip]
        addss   xmm0, xmm1
        movss   DWORD PTR var0[rip], xmm0
.L10: ;if var1=var2
        movss   xmm0, DWORD PTR var1[rip]
        movss   xmm1, DWORD PTR var2[rip]
        ucomiss xmm0, xmm1
        jne     .L11
        movss   xmm0, DWORD PTR var4[rip]
        movss   DWORD PTR var3[rip], xmm0
.L11: ; while (5>7)
        movss   xmm0, DWORD PTR .LC17[rip]
        movss   xmm1, DWORD PTR .LC18[rip]
        comiss  xmm0, xmm1
        jl      .L13
.L12:
        movss   xmm0, DWORD PTR .LC19[rip]
        movss   xmm1, DWORD PTR .LC20[rip]
        subss   xmm0, xmm1
        movss   xmm1, DWORD PTR x[rip]
        ucomiss xmm0, xmm1
        je      .L13
        movss   xmm0, DWORD PTR .LC21[rip]
        movss   xmm1, DWORD PTR v[rip]
        addss   xmm0, xmm1
        movss   DWORD PTR v20[rip], xmm0
        movss   xmm0, DWORD PTR x[rip]
        movss   xmm1, DWORD PTR .LC22[rip]
        comiss  xmm0, xmm1
        jle     .L13
        movss   xmm0, DWORD PTR .LC23[rip]
        movss   xmm1, DWORD PTR .LC24[rip]
        mulss   xmm0, xmm1
        movss   xmm1, DWORD PTR .LC25[rip]
        divss   xmm0, xmm1
        movss   DWORD PTR y[rip], xmm0
.L13: ; end section
        nop
        mov eax, 0
        pop rbp
        ret
.LC0:
        .long   1119571149
.LC1:
        .long   1113620061
.LC2:
        .long   1110179840
.LC3:
        .long   2143289344
.LC4:
        .long   1119617024
.LC5:
        .long   1134716518
.LC6:
        .long   1119485952
.LC7:
        .long   1097859072
.LC8:
        .long   1103416525
.LC9:
        .long   1110179840
.LC10:
        .long   1102997094
.LC11:
        .long   1103101952
.LC12:
        .long   1084227584
.LC13:
        .long   1079613850
.LC14:
        .long   1096181350
.LC15:
        .long   1134716518
.LC16:
        .long   1107820544
.LC17:
        .long   1084227584
.LC18:
        .long   1088421888
.LC19:
        .long   1102577664
.LC20:
        .long   1084227584
.LC21:
        .long   1101004800
.LC22:
        .long   1084227584
.LC23:
        .long   1077936128
.LC24:
        .long   1082130432
.LC25:
        .long   1086324736
