;========================================
; file: delay_ms.asm
; author: qk
; Crystal oscillator: 11.0592MHz
; 1 machine period = 12 clock period
; 1 clock period = 1 / (11.0592 * 1000000) = 90.42 ns
; 1 machine period = 1 * 12 * (1 / (11.0592 * 1000000) = 1.0850694444444444e-06 s = 1.085 us
; 1 function with empty body include 2 instruction (lcall/acall, ret), 4 machine period, cost 4 * 1.085us = 4.340 us
; software delay function
;========================================
	NAME    DELAY_MS            ; delcare module name
	PUBLIC  delay_1ms           ; export function
	PUBLIC  delay_2ms           ; export function
	PUBLIC  delay_3ms           ; export function
	PUBLIC  delay_4ms           ; export function		
	PUBLIC  delay_10ms          ; export function	
	PUBLIC  delay_20ms          ; export function
	PUBLIC  delay_30ms          ; export function
	PUBLIC  delay_40ms          ; export function
	PUBLIC  delay_100ms         ; export function
	PUBLIC  delay_200ms         ; export function
	PUBLIC  delay_500ms         ; export function
	
	;segment named regular of keil c51 standard
	;?PR?function_name?module_name
	;?PR? - program
	;function_name - current function name
	;module_name - current file name
	?PR?DELAY_MS?DELAY_MS segment code
	RSEG    ?PR?DELAY_MS?DELAY_MS
	;RSEG    CODE               ; declare following code is code segment
	;or using cseg commane
	;CSEG
	
	USING   0                   ; declare using the 0th register group of 4 in mcu

;========================================
; name: delay_1ms
; function: delay about 1.0 ms
;           ((1 + x * (1 + 2*y + 2)) + 2 + 2) * 1.085 = T, (x,y)=[(2,228), (3,151), (4,113), (5,90), (6,75), (7,64),...]
; parameter: none
;========================================
delay_1ms:
    mov     r7, #7          ; outer layer counter 2, 1 machine cycle
loop1:
    mov     r6, #64         ; inner layer, count 228, 1 machine cycle
    djnz    r6, $           ; in-place cycle: 228 x 2 machine cycles;    
    djnz    r7, loop1       ; outer layer jump, 2 times x 2 machine cycles; 
	
    ret                     ; return, 2 cycles

;========================================
; name: delay_2ms
; function: delay about 2.0 ms
;           ((1 + x * (1 + 2*y + 2)) + 2 + 2) * 1.085 = T, (x,y)=[(11,82), (16,56),...]
; parameter: none
;========================================
delay_2ms:
    mov     r7, #11         ; outer layer counter 11, 1 machine cycle
loop2:
    mov     r6, #82         ; inner layer, count 82, 1 machine cycle
    djnz    r6, $           ; in-place cycle: 82 x 2 machine cycles;    
    djnz    r7, loop2       ; outer layer jump, 11 times x 2 machine cycles; 
	
    ret                     ; return, 2 cycles

;========================================
; name: delay_3ms
; function: delay about 3.0 ms
;           ((1 + x * (1 + 2*y + 2)) + 2 + 2) * 1.085 = T, (x,y)=[(8,171), (11,124),...]
; parameter: none
;========================================
delay_3ms:
    mov     r7, #8          ; outer layer counter 8, 1 machine cycle
loop3:
    mov     r6, #171        ; inner layer, count 171, 1 machine cycle
    djnz    r6, $           ; in-place cycle: 171 x 2 machine cycles;    
    djnz    r7, loop3       ; outer layer jump, 8 times x 2 machine cycles; 
	
    ret                     ; return, 2 cycles

;========================================
; name: delay_4ms
; function: delay about 4.0 ms
;           ((1 + x * (1 + 2*y + 2)) + 2 + 2) * 1.085 = T, (x,y)=[(9,203), (14,130),...]
; parameter: none
;========================================
delay_4ms:
    mov     r7, #14         ; outer layer counter 8, 1 machine cycle
loop4:
    mov     r6, #130        ; inner layer, count 171, 1 machine cycle
    djnz    r6, $           ; in-place cycle: 171 x 2 machine cycles;    
    djnz    r7, loop4       ; outer layer jump, 8 times x 2 machine cycles; 
	
    ret                     ; return, 2 cycles


;========================================
; name: delay_10ms
; function: delay about 10 ms
;           ((1 + x * (1 + 2*y + 2)) + 2 + 2) * 1.085 = T, (x,y)=[(28,163), (30,152), (37,123), (61,74),...]
; parameter: none
;========================================
delay_10ms:
    mov     r7, #28         ; outer layer counter 28, 1 machine cycle
loop10:
    mov     r6, #163        ; inner layer, count 163, 1 machine cycle
    djnz    r6, $           ; in-place cycle: 163 x 2 machine cycles;    
    djnz    r7, loop10      ; outer layer jump, 28 times x 2 machine cycles; 
	
    ret                     ; return, 2 cycles


;========================================
; name: delay_20ms
; function: delay about 20 ms
;           ((1 + x * (1 + 2*y + 2)) + 2 + 2) * 1.085 = T, (x,y)=[(38,241),(68,134),...]
; parameter: none
;========================================
delay_20ms:
    mov     r7, #38         ; outer layer counter 38, 1 machine cycle
loop20:
    mov     r6, #241        ; inner layer, count 241, 1 machine cycle
    djnz    r6, $           ; in-place cycle: 241 x 2 machine cycles;    
    djnz    r7, loop20      ; outer layer jump, 38 times x 2 machine cycles; 
	
    ret                     ; return, 2 cycles

;========================================
; name: delay_30ms
; function: delay about 30 ms
;           ((1 + x * (1 + 2*y + 2)) + 2 + 2) * 1.085 = T, (x,y)=[(57,241),(77,178),...]
; parameter: none
;========================================
delay_30ms:
    mov     r7, #57         ; outer layer counter 57, 1 machine cycle
loop30:
    mov     r6, #241        ; inner layer, count 241, 1 machine cycle
    djnz    r6, $           ; in-place cycle: 241 x 2 machine cycles;    
    djnz    r7, loop30      ; outer layer jump, 57 times x 2 machine cycles; 
	
    ret                     ; return, 2 cycles

;========================================
; name: delay_40ms
; function: delay about 40 ms
;           ((1 + x * (1 + 2*y + 2)) + 2 + 2) * 1.085 = T, (x,y)=[(76,241),...]
; parameter: none
;========================================
delay_40ms:
    mov     r7, #76         ; outer layer counter 76, 1 machine cycle
loop40:
    mov     r6, #241        ; inner layer, count 241, 1 machine cycle
    djnz    r6, $           ; in-place cycle: 241 x 2 machine cycles;    
    djnz    r7, loop40      ; outer layer jump, 76 times x 2 machine cycles; 
	
    ret                     ; return, 2 cycles



;========================================
; name: delay_100ms
; function: delay about 100 ms
;           ((1 + x * (z*(1 + 2*y) + 2)) + 2 + 2) * 1.085 = T, (x,y,z)=[(90,255,2),(96,239,2),(120,191,2),...,(30,153,10)]
; parameter: none
;========================================
delay_100ms:
    mov     r7, #90         ; outer layer counter 90, 1 machine cycle
loop100:
    mov     r6, #255        ; inner layer, count 255, 1 machine cycle
    djnz    r6, $           ; in-place cycle: 255 x 2 machine cycles;
    mov     r6, #255        ; inner layer, count 255, 1 machine cycle
    djnz    r6, $           ; in-place cycle: 255 x 2 machine cycles;    
    djnz    r7, loop100     ; outer layer jump, 90 times x 2 machine cycles; 
	
    ret                     ; return, 2 cycles

;========================================
; name: delay_200ms
; function: delay about 200 ms
;           ((1 + x * (z*(1 + 2*y) + 2)) + 2 + 2) * 1.085 = T, (x,y,z)=[(143,214,3),(143,71,9),(93,247,4)]
; parameter: none
;========================================
delay_200ms:
    mov     r7, #143        ; outer layer counter 143, 1 machine cycle
loop200:
    mov     r6, #214        ; inner layer, count 214, 1 machine cycle
    djnz    r6, $           ; in-place cycle: 214 x 2 machine cycles;
    mov     r6, #214        ; inner layer, count 214, 1 machine cycle
    djnz    r6, $           ; in-place cycle: 214 x 2 machine cycles;    
    mov     r6, #214        ; inner layer, count 214, 1 machine cycle
    djnz    r6, $           ; in-place cycle: 214 x 2 machine cycles;    
    djnz    r7, loop200     ; outer layer jump, 143 times x 2 machine cycles; 
	
    ret                     ; return, 2 cycles



;========================================
; name: delay_500ms
; function: delay about 500 ms
;           ((1 + x * (z*(1 + 2*y) + 2)) + 2 + 2) * 1.085 = T, (x,y,z)=[(134,245,7), (156,184,8), (182,126,10)]
; parameter: none
;========================================
delay_500ms:
    mov     r7, #134        ; outer layer counter 134, 1 machine cycle
loop500:
    mov     r6, #245        ; inner layer, count 245, 1 machine cycle
    djnz    r6, $           ; in-place cycle: 245 x 2 machine cycles;
    mov     r6, #245        ; inner layer, count 245, 1 machine cycle
    djnz    r6, $           ; in-place cycle: 245 x 2 machine cycles;
    mov     r6, #245        ; inner layer, count 245, 1 machine cycle
    djnz    r6, $           ; in-place cycle: 245 x 2 machine cycles;
    mov     r6, #245        ; inner layer, count 245, 1 machine cycle
    djnz    r6, $           ; in-place cycle: 245 x 2 machine cycles;
    mov     r6, #245        ; inner layer, count 245, 1 machine cycle
    djnz    r6, $           ; in-place cycle: 245 x 2 machine cycles;
    mov     r6, #245        ; inner layer, count 245, 1 machine cycle
    djnz    r6, $           ; in-place cycle: 245 x 2 machine cycles;
    mov     r6, #245        ; inner layer, count 245, 1 machine cycle
    djnz    r6, $           ; in-place cycle: 245 x 2 machine cycles;
    djnz    r7, loop500     ; outer layer jump, 134 times x 2 machine cycles; 
	
    ret                     ; return, 2 cycles


	END
