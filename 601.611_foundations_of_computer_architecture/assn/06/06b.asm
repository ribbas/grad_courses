label_1:
    beq $zero, $zero, label_2
    j label_3
    addi $t0, $t1, 100
    sub $t0, $t1, $t2
label_2:
    beq $zero, $zero, label_1
label_3:
    addi $t0, $t1, 100