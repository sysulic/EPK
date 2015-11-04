
(define (domain to-trash) 

   (:requirements :strips :typing)
   (:types pos obj)
   (:constants  o1 o2 o3 o4 o5 o6 o7 o8 o9 o10 - obj)
   (:predicates (adj ?i ?j) (at ?i) (holding ?o) (obj-at ?o ?i) (handempty)) 
   (:action move
      :parameters (?i ?j)
      :precondition (and (adj ?i ?j) (at ?i))
      :effect (and (not (at ?i)) (at ?j)))
   
   (:action sense_object
      :parameters (?p ?o)
      :precondition (at ?p)
      :observe (obj-at ?o ?p)
   ) 	


   (:action pickup
      :parameters (?p ?o)
      :precondition (and (at ?p) (obj-at ?o ?p))
      :effect (when (handempty) (and (not (handempty)) (holding ?o) (not (obj-at ?o ?p))))
   )
   
   (:action putdown
      :parameters (?p)
      :precondition (at ?p)
      :effect (and 
                 (when (holding o1)
                       (and (handempty) (not (holding o1)) (obj-at o1 ?p)))
                 (when (holding o2)
                       (and (handempty) (not (holding o2)) (obj-at o2 ?p)))
                 (when (holding o3)
                       (and (handempty) (not (holding o3)) (obj-at o3 ?p)))
                 (when (holding o4)
                       (and (handempty) (not (holding o4)) (obj-at o4 ?p)))
                 (when (holding o5)
                       (and (handempty) (not (holding o5)) (obj-at o5 ?p)))
                 (when (holding o6)
                       (and (handempty) (not (holding o6)) (obj-at o6 ?p)))
                 (when (holding o7)
                       (and (handempty) (not (holding o7)) (obj-at o7 ?p)))
                 (when (holding o8)
                       (and (handempty) (not (holding o8)) (obj-at o8 ?p)))
                 (when (holding o9)
                       (and (handempty) (not (holding o9)) (obj-at o9 ?p)))                       
                 (when (holding o10)
                       (and (handempty) (not (holding o10)) (obj-at o10 ?p)))
                       ))
      )
