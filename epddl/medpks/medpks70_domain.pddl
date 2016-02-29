(define (domain medicalPKS70)
	
 
	(:action sense-stain
	 :parameters (?i - STAIN)
	 :precondition (K (ndead))
	 :observe (stain ?i)
	)

	(:action medicate1 
     :parameters ()	
	 :precondition (K (and (ndead) (ill i1))) 
	 :effect(((ill i1), (ill i0), ))
	)
	
	(:action medicate2 
     :parameters()	
	 :precondition (K (and (ndead) (ill i2)))  
	 :effect(((ill i2), (ill i0), ))
	)
	
	(:action medicate3
	 :parameters()
	 :precondition (K (and (ndead) (ill i3)))   
	 :effect(((ill i3), (ill i0), )) 
	)
	
	(:action medicate4
	 :parameters()
     :precondition (K (and (ndead) (ill i4))) 
	 :effect(((ill i4), (ill i0), )) 
	)
	
	(:action medicate5  
	 :parameters()
	 :precondition (K (and (ndead) (ill i5)))  
	 :effect(((ill i5), (ill i0), ))
	)
	
	(:action medicate6  
	 :parameters()
	 :precondition (K (and (ndead) (ill i6)))  
	 :effect(((ill i6), (ill i0), )) 
	)
	
	(:action medicate7  
	 :parameters()
	 :precondition (K (and (ndead) (ill i7)))  
	 :effect(((ill i7), (ill i0), ))
	)
	
	(:action medicate8  
	 :parameters()
	 :precondition (K (and (ndead) (ill i8)))  
	 :effect(((ill i8), (ill i0), )) 
	)
	
	(:action medicate9  
	 :parameters()
	 :precondition (K (and (ndead) (ill i9)))  
	 :effect(((ill i9), (ill i0), )) 
	)
	
	(:action medicate10  
	 :parameters()
	 :precondition (K (and (ndead) (ill i10)))  
	 :effect(((ill i10), (ill i0), ) )
	)
	
	(:action medicate11  
	 :parameters()
	 :precondition (K (and (ndead) (ill i11)))  
	 :effect(((ill i11), (ill i0), ) )
	)
	
	(:action medicate12  
	 :parameters()
	 :precondition (K (and (ndead) (ill i12)))  
	 :effect(((ill i12), (ill i0), ) )
	)
	
	(:action medicate13  
	 :parameters()
	 :precondition (K (and (ndead) (ill i13)))  
	 :effect(((ill i13), (ill i0), ) )
	)
	
	(:action medicate14  
	 :parameters()
	 :precondition (K (and (ndead) (ill i14)))  
	 :effect(((ill i14), (ill i0), ) )
	)
	
	(:action medicate15  
	 :parameters()
	 :precondition (K (and (ndead) (ill i15)))  
	 :effect(((ill i15), (ill i0), ) )
	)
	
	(:action medicate16  
	 :parameters()
	 :precondition (K (and (ndead) (ill i16)))  
	 :effect(((ill i16), (ill i0), ) )
	)
	
	(:action medicate17  
	 :parameters()
	 :precondition (K (and (ndead) (ill i17)))  
	 :effect(((ill i17), (ill i0), ) )
	)
	
	(:action medicate18  
	 :parameters()
	 :precondition (K (and (ndead) (ill i18)))  
	 :effect(((ill i18), (ill i0), ) )
	)
    
	(:action medicate19  
	 :parameters()
	 :precondition (K (and (ndead) (ill i19)))  
	 :effect(((ill i19), (ill i0), ) )
	)
	
	(:action medicate20  
	 :parameters()
	 :precondition (K (and (ndead) (ill i20)))  
	 :effect(((ill i20), (ill i0), ) )
	)
	
	(:action medicate21  
	 :parameters()
	 :precondition (K (and (ndead) (ill i21)))  
	 :effect(((ill i21), (ill i0), ) )
	)
	
	(:action medicate22  
	 :parameters()
	 :precondition (K (and (ndead) (ill i22)))  
	 :effect(((ill i22), (ill i0), ) )
	)
	
	(:action medicate23  
	 :parameters()
	 :precondition (K (and (ndead) (ill i23)))  
	 :effect(((ill i23), (ill i0), ) )
	)
	
	(:action medicate24  
	 :parameters()
	 :precondition (K (and (ndead) (ill i24)))  
	 :effect(((ill i24), (ill i0), ) )
	)
	
	(:action medicate25  
	 :parameters()
	 :precondition (K (and (ndead) (ill i25)))  
	 :effect(((ill i25), (ill i0), ) )
	)
	
	(:action medicate26  
	 :parameters()
	 :precondition (K (and (ndead) (ill i26)))  
	 :effect(((ill i26), (ill i0), ) )
	)
	
	(:action medicate27  
	 :parameters()
	 :precondition (K (and (ndead) (ill i27)))  
	 :effect(((ill i27), (ill i0), ) )
	)
	
	(:action medicate28  
	 :parameters()
	 :precondition (K (and (ndead) (ill i28)))  
	 :effect(((ill i28), (ill i0), ) )
	)
	
	(:action medicate29  
	 :parameters()
	 :precondition (K (and (ndead) (ill i29)))  
	 :effect(((ill i29), (ill i0), ) )
	)
	
	(:action medicate30  
	 :parameters()
	 :precondition (K (and (ndead) (ill i30)))  
	 :effect(((ill i30), (ill i0), ) )
	)
	
	(:action medicate31  
	 :parameters()
	 :precondition (K (and (ndead) (ill i31)))  
	 :effect(((ill i31), (ill i0), ) )
	)
	
	(:action medicate32  
	 :parameters()
	 :precondition (K (and (ndead) (ill i32)))  
	 :effect(((ill i32), (ill i0), ) )
	)
	
	(:action medicate33  
	 :parameters()
	 :precondition (K (and (ndead) (ill i33)))  
	 :effect(((ill i33), (ill i0), ) )
	)
	
	(:action medicate34  
	 :parameters()
	 :precondition (K (and (ndead) (ill i34)))  
	 :effect(((ill i34), (ill i0), ) )
	)
	
	(:action medicate35  
	 :parameters()
	 :precondition (K (and (ndead) (ill i35)))  
	 :effect(((ill i35), (ill i0), ) )
	)
	
	(:action medicate36  
	 :parameters()
	 :precondition (K (and (ndead) (ill i36)))  
	 :effect(((ill i36), (ill i0), ) )
	)
	
	(:action medicate37  
	 :parameters()
	 :precondition (K (and (ndead) (ill i37)))  
	 :effect(((ill i37), (ill i0), ) )
	)
	
	(:action medicate38  
	 :parameters()
	 :precondition (K (and (ndead) (ill i38)))  
	 :effect(((ill i38), (ill i0), ) )
	)
	
	(:action medicate39  
	 :parameters()
	 :precondition (K (and (ndead) (ill i39)))  
	 :effect(((ill i39), (ill i0), ) )
	)
	
	(:action medicate40  
	 :parameters()
	 :precondition (K (and (ndead) (ill i40)))  
	 :effect(((ill i40), (ill i0), ) )
	)
	
	(:action medicate41  
	 :parameters()
	 :precondition (K (and (ndead) (ill i41)))  
	 :effect(((ill i41), (ill i0), ) )
	)
	
	(:action medicate42  
	 :parameters()
	 :precondition (K (and (ndead) (ill i42)))  
	 :effect(((ill i42), (ill i0), ) )
	)
	
	(:action medicate43  
	 :parameters()
	 :precondition (K (and (ndead) (ill i43)))  
	 :effect(((ill i43), (ill i0), )) 
	)
	
	(:action medicate44  
	 :parameters()
	 :precondition (K (and (ndead) (ill i44)))  
	 :effect(((ill i44), (ill i0), )) 
	)
	
	(:action medicate45  
	 :parameters()
	 :precondition (K (and (ndead) (ill i45)))  
	 :effect(((ill i45), (ill i0), ) )
	)
	
	(:action medicate46  
	 :parameters()
	 :precondition (K (and (ndead) (ill i46)))  
	 :effect(((ill i46), (ill i0), ) )
	)
	
	(:action medicate47  
	 :parameters()
	 :precondition (K (and (ndead) (ill i47)))  
	 :effect(((ill i47), (ill i0), ) )
	)
	
	(:action medicate48  
	 :parameters()
	 :precondition (K (and (ndead) (ill i48)))  
	 :effect(((ill i48), (ill i0), ) )
	)
	
	(:action medicate49  
	 :parameters()
	 :precondition (K (and (ndead) (ill i49)))  
	 :effect(((ill i49), (ill i0), ) )
	)
	
	(:action medicate50  
	 :parameters()
	 :precondition (K (and (ndead) (ill i50)))  
	 :effect(((ill i50), (ill i0), ) )
	)
	
	(:action medicate51  
	 :parameters()
	 :precondition (K (and (ndead) (ill i51)))  
	 :effect(((ill i51), (ill i0), ) )
	)
	
	(:action medicate52  
	 :parameters()
	 :precondition (K (and (ndead) (ill i52)))  
	 :effect(((ill i52), (ill i0), )) 
	)
	
	(:action medicate53  
	 :parameters()
	 :precondition (K (and (ndead) (ill i53)))  
	 :effect(((ill i53), (ill i0), ) )
	)
	
	(:action medicate54	
	 :parameters()
	 :precondition (K (and (ndead) (ill i54)))  
	 :effect(((ill i54), (ill i0), ) )
	)
	
	(:action medicate55  
	 :parameters()
	 :precondition (K (and (ndead) (ill i55)))  
	 :effect(((ill i55), (ill i0), ) )
	)
	
	(:action medicate56  
	 :parameters()
	 :precondition (K (and (ndead) (ill i56)))  
	 :effect(((ill i56), (ill i0), ) )
	)
	
	(:action medicate57  
	 :parameters()
	 :precondition (K (and (ndead) (ill i57)))  
	 :effect(((ill i57), (ill i0), ) )
	)
	
	(:action medicate58  
	 :parameters()
	 :precondition (K (and (ndead) (ill i58)))  
	 :effect(((ill i58), (ill i0), ) )
	)
	
	(:action medicate59  
	 :parameters()
	 :precondition (K (and (ndead) (ill i59)))  
	 :effect(((ill i59), (ill i0), ) )
	)
	
	(:action medicate60  
	 :parameters()
	 :precondition (K (and (ndead) (ill i60)))  
	 :effect(((ill i60), (ill i0), ) )
	)
	
	(:action medicate61  
	 :parameters()
	 :precondition (K (and (ndead) (ill i61)))  
	 :effect(((ill i61), (ill i0), ) )
	)
	
	(:action medicate62  
	 :parameters()
	 :precondition (K (and (ndead) (ill i62)))  
	 :effect(((ill i62), (ill i0), ) )
	)
	
	(:action medicate63  
	 :parameters()
	 :precondition (K (and (ndead) (ill i63)))  
	 :effect(((ill i63), (ill i0), ) )
	)
	
	(:action medicate64  
	 :parameters()
	 :precondition (K (and (ndead) (ill i64)))  
	 :effect(((ill i64), (ill i0), )) 
	)
	
	(:action medicate65  
	 :parameters()
	 :precondition (K (and (ndead) (ill i65)))  
	 :effect(((ill i65), (ill i0), ) )
	)
	
	(:action medicate66  
	 :parameters()
	 :precondition (K (and (ndead) (ill i66)))  
	 :effect(((ill i66), (ill i0), ) )
	)
	
	(:action medicate67  
	 :parameters()
	 :precondition (K (and (ndead) (ill i67)))  
	 :effect(((ill i67), (ill i0), ) )
	)
	
	(:action medicate68  
	 :parameters()
	 :precondition (K (and (ndead) (ill i68)))  
	 :effect(((ill i68), (ill i0), ) )
	)
	
	(:action medicate69  
	 :parameters()
	 :precondition (K (and (ndead) (ill i69)))  
	 :effect(((ill i69), (ill i0), ) )
	)
	
	(:action medicate70  
	 :parameters()
	 :precondition (K (and (ndead) (ill i70)))  
	 :effect(((ill i70), (ill i0), ) )
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
			  ((ill i70), (stain s70), )
			)
	)
)
