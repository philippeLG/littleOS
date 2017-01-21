global enablePaging

enablePaging:
   mov eax, [esp+4]
   mov cr3, eax        ; eax has the address of the page directory
; enable 4MBpage
;	mov ebx, cr4        ; read current cr4 
;	or  ebx, 0x00000010 ; set PSE  - enable 4MB page
;	mov cr4, ebx        ; update cr4

   mov ebx, cr0        ; read current cr0
   or  ebx, 0x80000000 ; set PG .  set pages as read-only for both userspace and supervisor, replace 0x80000000 above with 0x80010000, which also sets the WP bit.
   mov cr0, ebx        ; update cr0
   ret                 ; now paging is enabled
