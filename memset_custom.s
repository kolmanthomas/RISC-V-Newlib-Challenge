/*
memset_custom - Set memory to a specific byte value

@param a0 - void * ptr
@param a1 - int value
@param a2 - size_t num

@return Same as param a0

*/
.globl memset_custom
memset_custom:
    mv t0, a0 /* Store memory address in t0, leave a0 untouched for return value */
    add t1, a0, a2 /* Calculate end address, put into t1 */
    addi t4, x0, 4 /* Decrement size by 1 */

/* Pack byte into a word */
    slli t2, a1, 8
    or a1, a1, t2
    slli t2, a1, 16
    or a1, a1, t2 /* Done with t2 here, can reuse */

/* Check if memory is aligned; if not, pack with byte to align */
1:
    beq t0, t1, 3f  /* If start addr == end addr, we are done */
    andi t2, t0, 3 /* Check if aligned */
    bnez t2, 2f /* If aligned, go to next step */
    sb a1, 0(t0) /* Store byte */
    addi t0, t0, 1 /* Increment memory address */
    j 1b

2:
    sub t2, t1, t0 /* Compute difference between end and start memory address */
    blt t2, t4, 3f /* If less than 4 bytes, we are done */
    sw a1, 0(t0) /* Store word */
    addi t0, t0, 4 /* Increment memory address by 4 */
    j 2b

3:
    beq t0, t1, end /* If start addr == end addr, we are done */
    sb a1, 0(t0) /* Store byte */
    addi t0, t0, 1 /* Increment memory address */
    j 3b

end:
    ret


