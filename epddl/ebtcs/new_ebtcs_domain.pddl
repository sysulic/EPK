(define (domain ebtcs)
	(:types package bomb toilet)
	(:predicates
			(in ?p - package ?b - bomb)
			(defused ?b - bomb)
			(clog ?toilet - toilet)

    )

	(:action senseP
	 :parameters (?p - package ?b - bomb)
	 :precondition (K(true))
	 :observe (in ?p ?b)
	)

	(:action dunk	
	 :parameters (?p - package ?b - bomb ?t - toilet)
	 :precondition (K (and (not (clog ?t)) 
	                       (in ?p ?b)
					   )
					)
	 :effect (( , (defused ?b, clog ?t), ))
	)

	(:action flush	
	 :parameters (?t - toilet)
	 :precondition (K(true))
	 :effect (( , , (clog ?t)))
    )
)
