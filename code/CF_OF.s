;CF置一，是把操作数当作无符号数（都是原码，没有符号位），发生了下面的进位或者借位的事件：
;1. 进行加的时候，和溢出了，表示不下来
;2. 进行减的时候，被减数太小不够减，发生了借位

;OF置一，是把操作数当作有符号数（都是补码，最高位是有符号位），发生了下面的溢出事件：
;1. 正数基础上又加了一个正数（或者减了一个负数），跑到了数轴的右侧远远的地方，在表示范围以外
;2. 负数的基础上又加了一个负数（或者见了一个正数），跑到了数轴的左侧远远的地方，在表示范围以外
;

section .text
global _start

_start:
    ; 示例加法操作，可能导致溢出或者进位
    mov eax, 0xFFFFFFFF
    mov ebx, 0x7
    add eax, ebx         ; 执行加法

    ; 检查溢出标志
    jo overflow_handler   ; 如果OF=1，跳转到处理溢出的逻辑

    jc carry_handler1

    ; 如果OF=0, CF=0
    mov eax, 1           ; sys_exit
    mov ebx, 0           ; 退出码
    int 0x80             ; 调用内核
carry_handler1:
    ; 如果OF=0, CF=1
    mov eax, 1           ; sys_exit
    mov ebx, 1           ; 退出码
    int 0x80             ; 调用内核

overflow_handler:

    jc carry_handler2

    ; 如果OF=1 CF=0，退出码为0
    mov eax, 1           ; sys_exit
    mov ebx, 2           ; 退出码0
    int 0x80             ; 调用内核
carry_handler2:
    ; 如果OF=1, CF=1
    mov eax, 1           ; sys_exit
    mov ebx, 3           ; 退出码
    int 0x80             ; 调用内核
