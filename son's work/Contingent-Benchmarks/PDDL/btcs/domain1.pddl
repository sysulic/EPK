(define (domain btcs)
  (:types package bomb toilet)
  (:predicates
   (in ?p - package ?b - bomb)
   (defused ?b - bomb)
   (clog ?toilet - toilet)
   (true)

)

  (:action senseP
   :parameters (?p - package ?b - bomb)
   :effect (and (in ?p ?b)(true)))

  (:action dunk	
   :parameters (?p - package 
                ?b - bomb 
                ?t - toilet)
   :precondition (not (clog ?t))
   :effect (and (when (in ?p ?b) (defused ?b))
                (clog ?t)))

 (:action flush	
  :parameters (?t - toilet)
  :effect (not (clog ?t)))

)
