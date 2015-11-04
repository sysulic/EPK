
(define (domain colorballs) 

   (:requirements :strips :typing)
   (:types obj pos col gar)
   (:predicates (color ?o - obj ?c - col) (trashed ?o - obj) (garbage-color ?t - gar ?c - col) (garbage-at ?t - gar ?p - pos)
                (adj ?i -pos ?j - pos)  (at ?i -pos) (holding ?o - obj) (obj-at ?o -obj ?i -pos) 
		(true)	)
                
   (:action sense-color
     :parameters (?c - col ?o - obj)
     :precondition (holding ?o)
     :effect (and (color ?o ?c) (true))
   )
    
   (:action sense-ball
      :parameters (?pos - pos ?o - obj)
      :precondition (at ?pos)
      :effect (and (obj-at ?o ?pos) (true))
   )
      
   (:action move
      :parameters (?i - pos ?j - pos )
      :precondition (and (adj ?i ?j) (at ?i))
      :effect (and (not (at ?i)) (at ?j)))
      
   (:action pickup
      :parameters (?o - obj ?i - pos)
      :precondition (and (at ?i) (obj-at ?o ?i))
      :effect (and (holding ?o) (not (obj-at ?o ?i))))
      
   (:action trash
      :parameters (?o - obj ?c - col ?t - gar ?p - pos)
      :precondition (and (color ?o ?c) (holding ?o) (garbage-at ?t ?p) (at ?p)) 
      :effect (when (garbage-color ?t ?c) (trashed ?o) )
      )
)

