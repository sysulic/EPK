(define (problem doors-2)
	(:domain doors)
	(:objects 
		p1-1
		p1-2
		p2-1
		p2-2 - pos 
    )
	
	(:init (and (or (K (at p1-1))
	                (K (at p1-2))
				)
	            (K (and
						 (adj p1-1 p2-1)
						 (adj p2-1 p1-1)

						 (adj p1-2 p2-2)
						 (adj p2-2 p1-2)


						 (adj p1-1 p1-2)
						 (adj p1-2 p1-1)

						 (adj p2-1 p2-2)
						 (adj p2-2 p2-1)


						 (opened p1-1)
						 (opened p2-2)
						 (oneof
							(opened p1-2)
							(opened p2-1)
						 )
					  )
				 )
				 (DK (opened p1-2))
				 (DK (opened p2-1))
		    )
    )
  
    (:goal (or (K (at p2-1))
	           (K (at p2-2))
			)
	)
)
