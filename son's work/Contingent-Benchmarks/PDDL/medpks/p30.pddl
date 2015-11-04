(define (problem medicalPKS30)
(:domain medicalPKS30)
(:requirements :strips :equality :typing :conditional-effects :disjunctive-preconditions)
(:objects i0 i1 i2 i3 i4 i5 i6 i7 i8 i9 i10 i11 i12 i13 i14 i15 i16 i17 i18 i19 i20 i21 i22 i23 i24 i25 i26 i27 i28 i29 i30 - ILLNESS
s0 s1 s2 s3 s4 s5 s6 s7 s8 s9 s10 s11 s12 s13 s14 s15 s16 s17 s18 s19 s20 s21 s22 s23 s24 s25 s26 s27 s28 s29 s30 - STAIN)
 (:init (and
 
 (stain s0)


(oneof (ill i1) (ill i2) (ill i3) (ill i4) (ill i5) (ill i6) (ill i7) (ill i8) (ill i9) (ill i10) (ill i11) (ill i12) (ill i13) (ill i14) (ill i15) (ill i16) (ill i17) (ill i18) (ill i19) (ill i20) (ill i21) (ill i22) (ill i23) (ill i24) (ill i25) (ill i26) (ill i27) (ill i28) (ill i29) (ill i30) )

))

 (:goal (and (ill i0) (not (dead)))))