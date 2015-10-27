(define (domain doors) 
   (:types pos)
   (:predicates (adj ?i ?j) 
                (at ?i)  
                (opened ?i)                
   )
                
   (:action openDoor
    :parameters (?i - pos ?j - pos )
    :precondition(K (and (at ?i) (adj ?i ?j)))
    :effect (( ,(opened ?j), )) 
   )
   
   (:action senseDoor
    :parameters (?i - pos)
    :precondition (True)
    :observe (at ?i)
   )
   
   (:action move
    :parameters (?i - pos ?j - pos )
    :precondition (K (and (adj ?i ?j) (at ?i) (opened ?j)))
    :effect (( ,(at ?j), (at ?i))) 
   )
)
