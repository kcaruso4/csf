entry:
    LDA #$5C        ; test data value
    TAX             ; put test data in X
    JSR popcount
    BRK

; Return the total number of bits in the X register that are set to 1
popcount:
    TXA		        ; transfer from X to AC
    LDY #$00        ; load 0 to Y
    JSR start
    RTS

start:
    ASL  	        ; arithmetic shift left AC
    BCC ysame       ; if no cary over skip increment
    INY             ; increm Y if carry over from ASL
    CLC             ; clears flag
    JSR ysame
    RTS

ysame:
    BNE start       ; if zero flag is clear got to start
    TYA
    RTS
