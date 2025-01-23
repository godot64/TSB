; -----------------------------
; Magic Desk Memhook 1.00
; by Peter Alexander aka @td1334 in 2025
; -----------------------------
;
; amount of pages to transfer in .x
; highbyte of destination in .y
; destination can be $cc (NRM), $74 (GRAPHICS), or $70 (MONITOR)
;
; -----------------------------

;	*= $c9c9		; where formerly LOCAL tab was
;
;	basromein	= $8e3a


mdhook	lda #$80		; TSB.MEM (from NRM)
	!by $2c
	lda #$84		; get TSB.HSG (from GRAPHICS, end with COLD)
	!by $2c
	lda #$90		; get TSB.MON (by JMP, end with COLD)

	sei
	sta $f8		; src  to $f7/$f8
	sty $fa		; dest to $f9/$fa
	ldy #$00
	sty $f7
	sty $f9

	lda $01		; save PPort
	pha
	jsr basromein	; Basic on
	lda #$03		; switch cartridge on
	sta $de00

-	lda ($f7),y	; copy one page from cartridge to C64
	sta ($f9),y
	iny
	bne -
	inc $f8		; next page
	inc $fa
	dex		; count pages
	bne -

	lda #$80		; switch cartridge off
	sta $de00
	pla		; restore PPort
	sta $01
	cli
	rts		; finished

	!by $00

