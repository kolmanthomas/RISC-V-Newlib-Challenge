.globl memset_ex
memset_ex:
    mv t1, a0
    beqz a2, 2f

1:
    sb a1, 0(t1)
    addi a2, a2, -1
    addi t1, t1, 1
    bnez a2, 1b

2:
    ret

