
(define (domain push-to) 

   (:requirements :strips :typing)
   (:types pos obj)
   (:predicates (adj ?i ?j) (at ?i) (holding ?o) (obj-at ?o  ?i)
                (pick-loc ?i))
   
   (:action sense_object
      :parameters (?p ?o)
      :precondition (at ?p)
      :observe (obj-at ?o ?p)
   ) 	

   (:action move
      :parameters (?i ?j)
      :precondition (and (adj ?i ?j) (at ?i))
      :effect (and (not (at ?i)) (at ?j)))
   (:action pickup
      :parameters (?o ?i)
      :precondition (and (at ?i) (pick-loc ?i) (obj-at ?o ?i))
      :effect (and (holding ?o) (not (obj-at ?o ?i))))
   (:action push
      :parameters (?o ?i ?j)
      :precondition (and (adj ?i ?j) (at ?i) (obj-at ?o ?i))
      :effect (and (obj-at ?o ?j) (not (obj-at ?o ?i))
      ))
)

