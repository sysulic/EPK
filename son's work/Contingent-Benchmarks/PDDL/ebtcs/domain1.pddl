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
   :effect (and (true) (in ?p ?b)))

  (:action dunk	
   :parameters (?p - package 
                ?b - bomb 
                ?t - toilet)
   :precondition (and (not (clog ?t)) (in ?p ?b))
   :effect (and (defused ?b)
                (clog ?t)))

 (:action flush	
  :parameters (?t - toilet)
  :effect (and (true) (not (clog ?t))))

)
