
(define (domain dispose) 

   (:requirements :strips :typing)
   (:types pos obj)
   (:predicates (obj_at ?o  ?i )
                (adj ?i ?j ) 
		  (at ?i ) 
                (holding ?o )                 
                (trash_at ?x )
                (disposed ?o ))

   (:action sense_object
      :parameters (?p  ?o )
      :precondition (at ?p)
      :observe (obj_at ?o ?p)
   ) 	

   (:action move
      :parameters (?i  ?j  )
      :precondition (and (adj ?i ?j) (at ?i))
      :effect (and (not (at ?i)) (at ?j)))
   (:action pickup
      :parameters (?o  ?i )
      :precondition (and (at ?i) (obj_at ?o ?i))
      :effect (and (holding ?o) (not (obj_at ?o ?i))))
   (:action drop
      :parameters (?o  ?i  )
      :precondition (and (at ?i) (trash_at ?i))
      :effect (when (holding ?o) (and (not (holding ?o)) (disposed ?o)))))

