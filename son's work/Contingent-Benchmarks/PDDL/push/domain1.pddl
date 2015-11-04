
(define (domain push-to) 

   (:requirements :strips :typing)
   (:types pos obj)
   (:predicates (adj ?i ?j - pos) (at ?i -pos) (holding ?o -obj) (obj-at ?o -obj ?i - pos)
                (pick-loc ?i - pos) (true))
   
   (:action sense_object
      :parameters (?p - pos ?o - obj)
      :precondition (at ?p)
      :effect (and (obj-at ?o ?p) (true))
   ) 	

   (:action move
      :parameters (?i -pos ?j - pos )
      :precondition (and (adj ?i ?j) (at ?i))
      :effect (and (not (at ?i)) (at ?j)))
   (:action pickup
      :parameters (?o - obj ?i - pos )
      :precondition (and (at ?i) (pick-loc ?i) (obj-at ?o ?i))
      :effect (and (holding ?o) (not (obj-at ?o ?i))))
   (:action push
      :parameters (?o - obj ?i - pos  ?j - pos )
      :precondition (and (adj ?i ?j) (at ?i) (obj-at ?o ?i))
      :effect (and (obj-at ?o ?j) (not (obj-at ?o ?i))
      ))
)

