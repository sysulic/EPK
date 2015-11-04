(define (problem medicalPKS50)
(:domain medicalPKS50)
(:requirements :strips :equality :typing :conditional-effects :disjunctive-preconditions)
(:objects i0 i1 i2 i3 i4 i5 i6 i7 i8 i9 i10 i11 i12 i13 i14 i15 i16 i17 i18 i19 i20 i21 i22 i23 i24 i25 i26 i27 i28 i29 i30 i31 i32 i33 i34 i35 i36 i37 i38 i39 i40 i41 i42 i43 i44 i45 i46 i47 i48 i49 i50 - ILLNESS
s0 s1 s2 s3 s4 s5 s6 s7 s8 s9 s10 s11 s12 s13 s14 s15 s16 s17 s18 s19 s20 s21 s22 s23 s24 s25 s26 s27 s28 s29 s30 s31 s32 s33 s34 s35 s36 s37 s38 s39 s40 s41 s42 s43 s44 s45 s46 s47 s48 s49 s50 - STAIN)
 (:init (and
 
 (stain s0)


(oneof (ill i1) (ill i2) (ill i3) (ill i4) (ill i5) (ill i6) (ill i7) (ill i8) (ill i9) (ill i10) (ill i11) (ill i12) (ill i13) (ill i14) (ill i15) (ill i16) (ill i17) (ill i18) (ill i19) (ill i20) (ill i21) (ill i22) (ill i23) (ill i24) (ill i25) (ill i26) (ill i27) (ill i28) (ill i29) (ill i30) (ill i31) (ill i32) (ill i33) (ill i34) (ill i35) (ill i36) (ill i37) (ill i38) (ill i39) (ill i40) (ill i41) (ill i42) (ill i43) (ill i44) (ill i45) (ill i46) (ill i47) (ill i48) (ill i49) (ill i50) )

))

 (:goal (and (ill i0) (not (dead)))))