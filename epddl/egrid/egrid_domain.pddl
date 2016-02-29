(define (domain egrid)


	(:action observe-lock-shape
	 :parameters (?curpos - POS ?lockpos - POS ?shape - SHAPE)
	 :precondition (K (and (place ?curpos) 
	                       (place ?lockpos) 
						   (shape ?shape)
                           (conn ?curpos ?lockpos) 
						   (at-robot ?curpos)
					   )
					)
	 :observe (lock-shape ?lockpos ?shape)
	)

	(:action unlock
	 :parameters (?curpos - POS ?lockpos - POS ?key - KEY ?shape - SHAPE)
	 :precondition (K (and (place ?curpos) 
	                       (place ?lockpos) 
						   (key ?key)
						   (shape ?shape)
						   (conn ?curpos ?lockpos)
						   (key-shape ?key ?shape)
						   (at-robot ?curpos) 
                           (holding ?key)
						   (lock-shape ?lockpos ?shape)
					   )
					)
	 :effect (( ,(open ?lockpos), (locked ?lockpos)))
	)


	(:action move
	 :parameters (?curpos - POS ?nextpos - POS)
	 :precondition (K (and (place ?curpos) 
	                       (place ?nextpos)
						   (at-robot ?curpos)
						   (conn ?curpos ?nextpos)
						   (open ?nextpos)
					   )
				    )
	 :effect (( ,(at-robot ?nextpos), (at-robot ?curpos)))
	)

	(:action pickup
	 :parameters (?curpos - POS ?key - KEY)
	 :precondition (K (and (place ?curpos) 
	                       (key ?key) 
                           (at-robot ?curpos) 
						   (at ?key ?curpos)
						   (arm-empty)
					   )
					)
	 :effect (( ,(holding ?key), (at ?key ?curpos, arm-empty)))
	)

	(:action putdown
	 :parameters (?curpos - POS ?key - KEY)
	 :precondition (K (and (place ?curpos)
                           (key ?key) 
                           (at-robot ?curpos) 
						   (holding ?key)
					   )
					)
	 :effect (( ,(arm-empty, at ?key ?curpos), (holding ?key)))
	 )
)

	
