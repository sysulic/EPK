(define (domain medicalPKS10)
(:types ILLNESS STAIN)
 (:predicates 
 (dead)
    (stain ?i - STAIN) 
               (ill ?i - ILLNESS)
 
  )  

(:action inspect-stain
   :parameters (?i - STAIN)
   :precondition (not (dead))
   :effect (and (stain ?i) (not (dead))))

 (:action medicate
  :parameters (?i - ILLNESS)
  :precondition (and (not (dead)) (not (ill i0)))
  :effect (and (when (ill ?i) (ill i0))
               (when (not (ill ?i)) (dead))))

(:action stain
                   :parameters ()
                   :precondition (not (dead))
                   :effect (and (when (ill i1) (stain s1))
 (when (ill i2) (stain s2))
))
)
