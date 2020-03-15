; ******************************************************
; **       Librería de rutinas para Amstrad CPC       **
; **       Raúl Simarro,      Artaburu 2007           **
; ******************************************************

; [na_th_an] Modificada por Mojon Twins 
; - eliminamos la "cabecera" de los sprites.
; - la función marca por separado los tiles "anteriores" (ox,oy)
;   y los tiles "actuales" (cx, cy).
; - Intenta "podar" los casos en los que los rectángulos 
;   sean iguales.
; - Intenta "afinar" y marcar solo 2 de ancho en vez de 3
;   cuando sea posible.

XLIB cpc_PutSpTileMap8x16

XDEF bit_ancho
XDEF bit_alto
XDEF solo_coordenadas 

XREF tiles_tocados
XREF pantalla_juego
XREF posiciones_super_buffer
XREF tiles

LIB cpc_UpdTileTable

.cpc_PutSpTileMap8x16
    ex  de, hl
    ld  ixh, d
    ld  ixl, e

    ; En esta versión las dimensiones son fijas:
    ; 4 bytes de ancho por 16 de alto.
    ; en BC se almacenan estas dimensiones -1, ya que se usan
    ; para calcular los limites superiores de los bucles.

    ld bc, 0x0f03       ; alto en scans - 1
                        ; ancho en bytes - 1

    ; Vamos a marcar los tiles "anteriores"

    ld l, (ix + 10)
    ld h, (ix + 11)     ; Coordenadas ox, oy.

    ; Actualizar 2 o 3 cuadros?

    ld a, l
    and 1
    jr z, set2a
    ld a, 3
    jp seta
set2a:
    ld a, 2
seta:
    ld (pasos_ancho_xW + 1), a

    ; A partir de ox (en bytes) y oy (en pixels), obtenemos
    ; las coordenadas dentro del "nametable" (en tiles)

    push hl
    srl l               ; L = ox / 2
    srl h
    srl h
    srl h               ; H = oy / 8
    ex de, hl           ; Lo guardo en DE

    pop hl
    add hl, bc          ; Le sumo las dimensiones a (ox, oy)
    srl l               ; L = (ox+w) / 2
    srl h
    srl h
    srl h               ; H = (oy+h) / 8
    
    ; Para calcular el número de pasos del bucle, resto DE de HL

    xor a
    sbc hl, de

    ; Ahora hl tiene el nº de iteraciones de alto (h) y ancho (l)

    ld  a, h
    and 7
    jr z, noinc1
    inc a
noinc1: 
    ld (pasos_alto_xW + 1), a
    
    ; ancho fijo = 4 bytes, 2 caracteres, marcamos 3.
    ; ld  a, l
    ; inc a

    push de             ; DE contiene el origen de coordenadas
    call marca_tiles
    pop de

    ; Vamos a marcar los tiles "actuales"

    ld l, (ix + 8)
    ld h, (ix + 9)      ; Coordenadas cx, cy.

    ; Actualizar 2 o 3 cuadros?

    ld a, l
    and 1
    jr z, set2b
    ld a, 3
    jp setb
set2b:
    ld a, 2
setb:    
    ld (pasos_ancho_xW + 1), a

    ; Copiamos (cx,cy) -> (ox,oy)

    ld (ix + 10), l
    ld (ix + 11), h

    ; A partir de cx (en bytes) y cy (en pixels), obtenemos
    ; las coordenadas dentro del "nametable" (en tiles)

    ld a, l             ; Save untouched X

    push hl
    srl l               ; L = cx / 2
    srl h
    srl h
    srl h               ; H = cy / 8

    ; Comparamos DE (viejo origen de coordenadas) con el nuevo.
    ; Si son iguales, pasando de seguir ¿no?
    cp e
    jr nz, distintos
    ld a, h
    cp d
    jr z, adios
distintos:

    ex de, hl           ; Lo guardo en DE

    pop hl
    ld bc, 0x0f03       ; alto en scans - 1
                        ; ancho en bytes - 1
    add hl, bc          ; Le sumo las dimensiones a (cx, cy)
    srl l               ; L = (cx+w) / 2
    srl h
    srl h
    srl h               ; H = (cy+h) / 8
    
    ; Para calcular el número de pasos del bucle, resto DE de HL

    xor a
    sbc hl, de

    ; Ahora hl tiene el nº de iteraciones de alto (h) y ancho (l)

    ld  a, h
    and 7
    jr z, noinc2
    inc a
noinc2:    
    ld (pasos_alto_xW + 1), a
    ; ld  a, l
    ; inc a

    call marca_tiles

    ret

adios:
    pop hl
    ret

marca_tiles:
pasos_ancho_xW:
    ld b, 0
bucle_pasos_anchoW:
    push de
pasos_alto_xW: 
    ld c, 0         ; ese "0" se modifica antes de llamar.
bucle_pasos_altoW:

    ; Esta llamada mete D y E en la tabla de actualización
    call cpc_UpdTileTable
    inc d
    dec c
    jp nz, bucle_pasos_altoW

    pop de
    inc e
    dec b
    jp nz, bucle_pasos_anchoW

    ret
