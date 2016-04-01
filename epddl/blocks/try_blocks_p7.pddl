(define (problem blocks-7)
	(:domain blocksworld)
	(:objects b1 
	          b2 
			  b3 
			  b4 
			  b5 
			  b6 
			  b7 - BLOCK
	)
	
	(:init (K ( and
	                (or 
						(not (on b2 b5))
						(not (on b5 b2))
					)
					(or
						(not (on b5 b2))
						(not (on b2 b5))
					)
					(oneof
						(clear b2)
						(clear b5)
					)
					(oneof
						(on-table b2)
						(on-table b5)
					)
					(oneof
						(on-table b2)
						(on b2 b5)
					)
					(oneof
						(on-table b5)
						(on b5 b2)
					)
					(oneof
						(clear b5)
						(on b2 b5)
					)
					(on-table b3)
					(or
						(not (on b1 b6))
						(not (on b6 b1))
					)
					(or
						(not (on b6 b1))
						(not (on b1 b6))
					)
					(oneof
						(clear b1)
						(clear b6)
					)
					(oneof
						(on b1 b3)
						(on b6 b3)
					)
					(oneof
						(on b1 b3)
						(on b1 b6)
					)
					(oneof 
						(on b6 b3)
						(on b6 b1)
					)
					(oneof
						(clear b1)
						(on b6 b1)
					)
					(oneof 
						(clear b6)
						(on b1 b6)
					)
					(or
						(not (on b4 b7))
					    (not (on b7 b4))
					)
					(or
						(not (on b7 b4))
						(not (on b4 b7))
					)
					(oneof
						(clear b4)
						(clear b7)
					)
					(oneof
						(on-table b4)
						(on-table b7)
					)
					(oneof
						(on-table b4)
						(on b4 b7)
					)
					(oneof
						(on-table b7)
						(on b7 b4)
					)
					(oneof
						(clear b4)
						(on b7 b4)
					)
					(oneof
						(clear b7)
						(on b4 b7)
					)
				)
		   )
	)
	
	(:goal (K
				(and 
					(on b1 b4)
					(on b2 b1)
					(on b3 b6)
					(on b5 b7)
				)
		)
	)
)

