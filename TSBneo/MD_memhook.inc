; -----------------------------
; Magic Desk Memhook 1.01
; by Peter Alexander aka @td1334 in 2025
; -----------------------------
;
; amount of pages to transfer in .x
; highbyte of destination in .y
; destination can be $cc (NRM), $74 (GRAPHICS), or $70 (MONITOR)
;
; -----------------------------

;	*= $c9cf		; where formerly LOCAL tab was
;
;	basromein	= $8e3a


mdhook	lda #$80		; for TSB.MEM (from NRM and INST)

mdcart2	sei
	sta $f8		; src  to $f7/$f8
	sty $fa		; dest to $f9/$fa
	ldy #$00
	sty $f7
	sty $f9

	lda pport
	pha
	jsr basromein	; Basic on
mdpatch	lda #$03		; switch cartridge on
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
	pla
	sta pport
	cli
	rts		; finished

	!by 0
