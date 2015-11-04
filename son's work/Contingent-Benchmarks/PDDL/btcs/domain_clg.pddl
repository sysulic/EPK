(define (domain btcs)
  (:requirements :strips :typing)
  (:types package bomb toilet)
  (:predicates
   (in ?p - package ?b - bomb)
   (defused ?b - bomb)
   (nclog ?toilet - toilet)

)

  (:action senseP
   :parameters (?p - package ?b - bomb)
   :observe (in ?p ?b))

  (:action dunk	
   :parameters (?p - package 
                ?b - bomb 
                ?t - toilet)
   :precondition (nclog ?t)
   :effect (and (when (in ?p ?b) (defused ?b))
                (not (nclog ?t))))

 (:action flush	
  :parameters (?t - toilet)
  :effect (nclog ?t))

)
