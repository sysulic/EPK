(define (problem cube-cube-d40-g20-corners)
	(:domain cube)
	(:objects   p1  
				p2  
				p3  
				p4 
				p5 - pos
				gold - gold
	)
	
	(:init(or (K (and (x p1) (y p1) (z p1)))
	          (K (and (x p5) (y p5) (z p5)))
		)
    )
	
	(:goal (or (K (and (x p1) (y p1) (z p1) (gold)))
	           (K (and (x p1) (y p1) (z p1) (not (gold))))
		   )
	)
)
