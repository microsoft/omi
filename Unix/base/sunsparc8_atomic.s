!*==============================================================================
!*
!* Open Management Infrastructure (OMI)
!*
!* Copyright (c) Microsoft Corporation
!* 
!* Licensed under the Apache License, Version 2.0 (the "License"); you may not 
!* use this file except in compliance with the License. You may obtain a copy 
!* of the License at 
!*
!*     http://www.apache.org/licenses/LICENSE-2.0 
!*
!* THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
!* KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED 
!* WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE, 
!* MERCHANTABLITY OR NON-INFRINGEMENT. 
!*
!* See the Apache 2 License for the specific language governing permissions 
!* and limitations under the License.
!*
!*==============================================================================

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

        
