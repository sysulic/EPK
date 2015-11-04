(define (domain btnd)
  (:types package bomb toilet)
  (:predicates
   (in ?p - package ?b - bomb)
   (defused ?b - bomb)
   (clog ?toilet - toilet)
   (stuck ?toilet - toilet)
   (true))	

  (:action senseIN
   :parameters (?p - package ?b - bomb)
   :effect (and (in ?p ?b) (true)))

  (:action dunk	
   :parameters (?p - package 
                ?b - bomb 
                ?t - toilet)
   :precondition (and (not (clog ?t)) (not (stuck ?t)))
   :effect (and (when (in ?p ?b) (defused ?b))
                (clog ?t)
                (stuck ?t)))

 (:action flush	
  :parameters (?t - toilet)
  :effect (and (true) (not (clog ?t))))


   (:action unstick
       :parameters  (?toilet - toilet)
       :effect (and (true) (when (stuck ?toilet) (not (stuck ?toilet)))))


)
