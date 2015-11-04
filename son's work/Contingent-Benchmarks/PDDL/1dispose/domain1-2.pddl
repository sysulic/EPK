
(define (domain to-trash) 

   (:requirements :strips :typing)
   (:types pos obj)
   (:constants  o1 o2 - obj)
   (:predicates (adj ?i -pos ?j -pos) (at ?i -pos) (holding ?o -obj) (obj-at ?o -obj ?i -pos) (handempty) (true)) 
   (:action move
      :parameters (?i -pos ?j - pos )
      :precondition (and (adj ?i ?j) (at ?i))
      :effect (and (not (at ?i)) (at ?j)))
   
   (:action sense_object
      :parameters (?p - pos ?o - obj)
      :precondition (at ?p)
      :effect (and (obj-at ?o ?p) (true))
   ) 	


   (:action pickup
      :parameters (?p - pos ?o - obj)
      :precondition (and (at ?p) (obj-at ?o ?p))
      :effect (when (handempty) (and (not (handempty)) (holding ?o) (not (obj-at ?o ?p))))
   )
   
   (:action putdown
      :parameters (?p - pos)
      :precondition (at ?p)
      :effect (and 
                 (when (holding o1)
                       (and (handempty) (not (holding o1)) (obj-at o1 ?p)))
                 (when (holding o2)
                       (and (handempty) (not (holding o2)) (obj-at o2 ?p)))
                       ))
      )

