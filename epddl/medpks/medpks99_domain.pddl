(define (domain medicalPKS99)
	
	(:predicates 
			(ndead)
			(stain ?i - STAIN) 
			(ill ?i - ILLNESS)
	)
 
	(:action sense-stain
	 :parameters (?i - STAIN)
	 :precondition (K (ndead))
	 :observe (stain ?i)
	)


	(:action medicate 
     :parameters (?i - ILLNESS)	
	 :precondition (K (and (ndead) (ill ?i))) 
	 :effect(((ill ?i), (ill i0), ))
	)


	(:action stain
     :parameters ()
     :precondition (K (ndead))
     :effect (((ill i1), (stain s1), ),
			  ((ill i2), (stain s2), ),
			  ((ill i3), (stain s3), ),
			  ((ill i4), (stain s4), ),
			  ((ill i5), (stain s5), ),
			  ((ill i6), (stain s6), ),
			  ((ill i7), (stain s7), ),
			  ((ill i8), (stain s8), ),
			  ((ill i9), (stain s9), ),
			  ((ill i10), (stain s10), ),
			  ((ill i11), (stain s11), ),
			  ((ill i12), (stain s12), ),
			  ((ill i13), (stain s13), ),
			  ((ill i14), (stain s14), ),
			  ((ill i15), (stain s15), ),
			  ((ill i16), (stain s16), ),
			  ((ill i17), (stain s17), ),
			  ((ill i18), (stain s18), ),
			  ((ill i19), (stain s19), ),
			  ((ill i20), (stain s20), ),
			  ((ill i21), (stain s21), ),
			  ((ill i22), (stain s22), ),
			  ((ill i23), (stain s23), ),
			  ((ill i24), (stain s24), ),
			  ((ill i25), (stain s25), ),
			  ((ill i26), (stain s26), ),
			  ((ill i27), (stain s27), ),
			  ((ill i28), (stain s28), ),
			  ((ill i29), (stain s29), ),
			  ((ill i30), (stain s30), ),
			  ((ill i31), (stain s31), ),
			  ((ill i32), (stain s32), ),
			  ((ill i33), (stain s33), ),
			  ((ill i34), (stain s34), ),
			  ((ill i35), (stain s35), ),
			  ((ill i36), (stain s36), ),
			  ((ill i37), (stain s37), ),
			  ((ill i38), (stain s38), ),
			  ((ill i39), (stain s39), ),
			  ((ill i40), (stain s40), ),
			  ((ill i41), (stain s41), ),
			  ((ill i42), (stain s42), ),
			  ((ill i43), (stain s43), ),
			  ((ill i44), (stain s44), ),
			  ((ill i45), (stain s45), ),
			  ((ill i46), (stain s46), ),
			  ((ill i47), (stain s47), ),
			  ((ill i48), (stain s48), ),
			  ((ill i49), (stain s49), ),
			  ((ill i50), (stain s50), ),
			  ((ill i51), (stain s51), ),
			  ((ill i52), (stain s52), ),
			  ((ill i53), (stain s53), ),
			  ((ill i54), (stain s54), ),
			  ((ill i55), (stain s55), ),
			  ((ill i56), (stain s56), ),
			  ((ill i57), (stain s57), ),
			  ((ill i58), (stain s58), ),
			  ((ill i59), (stain s59), ),
			  ((ill i60), (stain s60), ),
			  ((ill i61), (stain s61), ),
			  ((ill i62), (stain s62), ),
			  ((ill i63), (stain s63), ),
			  ((ill i64), (stain s64), ),
			  ((ill i65), (stain s65), ),
			  ((ill i66), (stain s66), ),
			  ((ill i67), (stain s67), ),
			  ((ill i68), (stain s68), ),
			  ((ill i69), (stain s69), ),
			  ((ill i70), (stain s70), ),
			  ((ill i71), (stain s71), ),
			  ((ill i72), (stain s72), ),
			  ((ill i73), (stain s73), ),
			  ((ill i74), (stain s74), ),
			  ((ill i65), (stain s65), ),
			  ((ill i66), (stain s66), ),
			  ((ill i67), (stain s67), ),
			  ((ill i68), (stain s68), ),
			  ((ill i69), (stain s69), ),
			  ((ill i70), (stain s70), ),
			  ((ill i71), (stain s71), ),
			  ((ill i72), (stain s72), ),
			  ((ill i73), (stain s73), ),
			  ((ill i74), (stain s74), ),
			  ((ill i75), (stain s75), ),
			  ((ill i76), (stain s76), ),
			  ((ill i77), (stain s77), ),
			  ((ill i78), (stain s78), ),
			  ((ill i79), (stain s79), ),
			  ((ill i80), (stain s80), ),
			  ((ill i81), (stain s81), ),
			  ((ill i82), (stain s82), ),
			  ((ill i83), (stain s83), ),
			  ((ill i84), (stain s84), ),
			  ((ill i85), (stain s85), ),
			  ((ill i86), (stain s86), ),
			  ((ill i87), (stain s87), ),
			  ((ill i88), (stain s88), ),
			  ((ill i89), (stain s89), ),
			  ((ill i90), (stain s90), ),
			  ((ill i91), (stain s91), ),
			  ((ill i92), (stain s92), ),
			  ((ill i93), (stain s93), ),
			  ((ill i94), (stain s94), ),
			  ((ill i95), (stain s95), ),
			  ((ill i96), (stain s96), ),
			  ((ill i97), (stain s97), ),
			  ((ill i98), (stain s98), ),
			  ((ill i99), (stain s99), )
			)
	)
)
