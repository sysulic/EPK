(define (domain bts)
  (:types package bomb toilet)
  (:predicates
   (in ?p - package ?b - bomb)
   (defused ?b - bomb)
   (true)	

)

  (:action senseP
   :parameters (?p - package ?b - bomb)
   :effect (and (true) (in ?p ?b)))

  (:action dunk	
   :parameters (?p - package 
                ?b - bomb 
                ?t - toilet)
   :precondition (in ?p ?b)
   :effect (and (true) (defused ?b)))

)
