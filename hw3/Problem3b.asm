entry:
    LDA #$02        ; shift right by 2 bits
    TAX             ; put the shift amount in X
    LDA #$5c        ; put the data value $5C in the AC
    JSR right_shift_n
    JMP end

end:
    LSR             ; final right shift
    BRK

right_shift_n:
    INX		        ; increments X
    DEX             ; decrements X
    BNE	subshift    ; check if n == 0
    BRK

subshift:
    DEX		        ; decrements X
    BEQ end	        ; if X == 0, shift once more and finish
    LSR
    JMP subshift
