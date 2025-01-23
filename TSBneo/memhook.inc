; -----------------------------------------
;
; TSB MEMHOOK 1.04
;
; originally "REUINIT" by P. Hagemann,
; recoded to "MEMHOOK" for TSBneo by A. Dettke
; is run only once and part of each "tsb.neo" at $c000
;
; -----------------------------------------

reuinit	inc reuflag	; is 1 now
	jsr cstash	; set flag
	dec reuflag	; is 0 again
	jsr cfetch	; reuflag is 1 when REU present, 0 when not

mstash	ldx #7
-	lda cctab,x	; copy $cc00 to REU
	sta $df01,x
	dex
	bpl -

instxreu	ldx #(cctab-xreucode-1)
-	lda xreucode,x
	sta xreu,x
	dex
	bpl -

	jsr tsbcols	; then set TSB colors

!if cartridge=0 {
	lda reuflag	; REU present?
	beq +		; if no, don't patch

	lda #<xreu	; yes, patch TSB/allnrm for REU use
	ldx #>xreu
	sta patchan+1
	stx patchan+2
}
+	ldx #0		; set $8000 as memtop
	ldy #$80
	stx $37
	sty $38
	jsr $fd8c
	jmp into		; reset TSB (SYS 32897)

; -----------------------------------------

cstash	ldx #0		; makes $90 (stash)
	!by $2c
cfetch	ldx #1		; makes $91 (fetch)
	stx helpvec
	ldx #6
loop	lda reutab,x
	sta $df02,x
	dex
	bpl loop
	lda #%10010000	; preset: $9x
	ora helpvec
	sta $df01		; stash/swap immediately
	rts

; ----------------------------------------- resident MEMHOOK
; part of STACK area at $0140
;
; XREU by P. Hagemann, recoded for TSBneo by A. Dettke
; is the resident part of MEMHOOK, the actual mem-hook
; to restore RENUMBER/PLACE after MEM
;
; -----------------------------------------

xreucode
!pseudopc xreu {
	lda reuflag	; REU activated?
	bne +
	jmp loadext	; no, load "tsb.mem" from disk

+	ldx #7		; yes, load from REU
-	lda memtab,x
	sta $df01,x
	dex
	bpl -
	clc
	rts

; ----------------------------------------- part of XREU
; move RENUMBER/PLACE from $070000 in REU to $cc00
memtab	!by  $91, $00, $cc, $00, $00, $07, $00, $04
;         df..  01   02   03   04   05   06   07   08
}

; ----------------------------------------- part of MEMHOOK
; move $cc00..$cfff to REU $070000
cctab	!by  $90, $00, $cc, $00, $00, $07, $00, $04
;        df..  01   02   03   04   05   06   07   08

; set active flag to $0703ff in REU
reutab	!by  <reuflag, >reuflag, $ff, $03, $07, $01, $00
;         df..  02        03        04   05   06   07   08
;            :  C64 address      ,REU addr.,bank, amount of data

	!align 255,0,$ad
