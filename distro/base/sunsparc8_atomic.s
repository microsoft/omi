!------------------------------------------------------------------------------
!    Copyright (c) Microsoft Corporation.  All rights reserved.
!
! Provides assembler funcions needed for SUN sparc atomic functions.    
! Date        05-sep-08

.section   ".text"
.global   AtomicIncrement
.align   4

AtomicIncrement:             

1:      ld      [%o0], %o1          ! load the current value
        add     %o1, 1, %o2         ! perform required operation
        cas     [%o0], %o1, %o2     ! try CAS
        cmp     %o1, %o2            ! check if result is expected one
        bne     1b                  ! try again if not
        nop
        retl
        add     %o2, 1, %o0         ! return new value         


.type  AtomicIncrement,#function
.size  AtomicIncrement,.-AtomicIncrement


.section   ".text"
.global   AtomicDecrement
.align   4

AtomicDecrement:             

1:      ld      [%o0], %o1          ! load the current value
        sub     %o1, 1, %o2         ! perform required operation
        cas     [%o0], %o1, %o2     ! try CAS
        cmp     %o1, %o2            ! check if result is expected one
        bne     1b                  ! try again if not
        nop
        retl
        sub     %o2, 1, %o0         ! return new value

.type  AtomicDecrement,#function
.size  AtomicDecrement,.-AtomicDecrement

        
