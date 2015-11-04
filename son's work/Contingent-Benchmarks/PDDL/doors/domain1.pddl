
(define (domain doors) 

   (:requirements :strips :typing)
   (:types pos )
   (:predicates (adj ?i - pos ?j -pos) (at ?i -pos)  (opened ?i -pos) (true))
                
   (:action sense-door
      :parameters (?i - pos ?j - pos )
      :precondition   (and (at ?i) (adj ?i ?j))
      :effect (and (opened ?j) (true)))

   (:action move
      :parameters (?i - pos ?j - pos )
      :precondition (and (adj ?i ?j) (at ?i) (opened ?j))
      :effect  (and (not (at ?i)) (at ?j)) 
      )
)

