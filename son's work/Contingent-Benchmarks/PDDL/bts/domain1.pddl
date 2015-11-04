(define (domain bts)
  (:types package bomb toilet)
  (:predicates
   (in ?p - package ?b - bomb)
   (defused ?b - bomb)
   (true)	

)

  (:action senseP
   :parameters (?p - package ?b - bomb)
   :effect (and (in ?p ?b) (true)))

  (:action dunk	
   :parameters (?p - package 
                ?b - bomb 
                ?t - toilet)
   :effect (and (when (in ?p ?b) (defused ?b))))

)
