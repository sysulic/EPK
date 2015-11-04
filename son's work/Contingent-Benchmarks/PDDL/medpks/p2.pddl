





(define (problem medicalPKS10)


(:domain medicalPKS10)


(:objects i0 i1 i2 - ILLNESS
s0 s1 s2 - STAIN)
 (:init (and
 
 (stain s0)

(oneof (ill i1) (ill i2))

))
 (:goal (and (ill i0) (not (dead)))))


