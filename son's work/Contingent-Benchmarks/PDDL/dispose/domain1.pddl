
(define (domain dispose) 

   (:requirements :strips :typing)
   (:types pos obj)
   (:predicates (adj ?i ?j - pos) (at ?i - pos) (holding ?o - obj) (obj_at ?o - obj ?i - pos)
                (trash_at ?x - pos) (disposed ?o - obj) (true))

   (:action sense_object
      :parameters (?p - pos ?o - obj)
      :precondition (at ?p)
      :effect (and (obj-at ?o ?p) (true))
   ) 	

   (:action move
      :parameters (?i - pos ?j - pos )
      :precondition (and (adj ?i ?j) (at ?i))
      :effect (and (not (at ?i)) (at ?j)))
   (:action pickup
      :parameters (?o - obj ?i - pos)
      :precondition (and (at ?i) (obj_at ?o ?i))
      :effect (and (holding ?o) (not (obj_at ?o ?i))))
   (:action drop
      :parameters (?o - obj ?i - pos )
      :precondition (and (at ?i) (trash_at ?i))
      :effect (when (holding ?o) (and (not (holding ?o)) (disposed ?o)))))

