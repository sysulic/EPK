(define (domain cube)
	
	(:types pos)
	(:predicates (x ?p - pos)
	             (y ?p - pos)
				 (z ?p - pos)  
	)
    
	(:action senseGold
	 :parameters ()
	 :precondition (K (and (x p3) (y p3) (z p3)))
	 :observe (gold)
	)
	
	(:action pickGold
	 :parameters ()
	 :precondition (K (gold))
	 :effect (( , (x p1, y p1, z p1), ))
	)
	
	(:action pickToy
	 :parameters ()
	 :precondition (K (not (gold)))
	 :effect (( , (x p5, y p5, z p5), ))
	)
	
	(:action right
	 :parameters()
     :precondition (K (true))
     :effect (((x p1), (x p2), (x p1)),
			  ((x p2), (x p3), (x p2)),
			  ((x p3), (x p4), (x p3)),
			  ((x p4), (x p5), (x p4))	  
       )
    )
  
	(:action left
	 :parameters()
     :precondition (K (true))
     :effect (((x p2), (x p1), (x p2)),
			  ((x p3), (x p2), (x p3)),
			  ((x p4), (x p3), (x p4)),
			  ((x p5), (x p4), (x p5))
        )
    )     
       

	(:action down
	 :parameters ()
     :precondition (K (true))	
     :effect (((y p1), (y p2), (y p1)),
			  ((y p2), (y p3), (y p2)),
			  ((y p3), (y p4), (y p3)),
			  ((y p4), (y p5), (y p4))	 
       )
    )
       
  
	(:action up
     :parameters ()
     :precondition (K (true))
     :effect (((y p2), (y p1), (y p2)),
			  ((y p3), (y p2), (y p3)),
			  ((y p4), (y p3), (y p4)),
			  ((y p5), (y p4), (y p5))
        )
    )     
      

	(:action out
	 :parameters()
     :precondition (K (true))
     :effect (((z p1), (z p2), (z p1)),
			  ((z p2), (z p3), (z p2)),
			  ((z p3), (z p4), (z p3)),
			  ((z p4), (z p5), (z p4))
       )
    )
	 
  
	(:action in
	 :parameters()
     :precondition (K (true))
     :effect (((z p2), (z p1), (z p2)),
			  ((z p3), (z p2), (z p3)),
			  ((z p4), (z p3), (z p4)),
			  ((z p5), (z p4), (z p5))	 
        )
    )      
)

