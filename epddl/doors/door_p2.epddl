(define (problem doors-1)
  (:domain doors)
  (:objects 
    p11  
    p12  
    p21 
    p22 - pos 
  )
  
  (:init (K 
    (or 
      (and
      (at p12)
      (adj p11 p21)
      (adj p21 p11)
      (adj p12 p22)
      (adj p22 p12)
      (adj p11 p12)
      (adj p12 p11)
      (adj p21 p22)
      (adj p22 p21)
      (opened p11)
      (opened p12)
      (not (opened p21)))
      
      (and 
      (at p12)
      (adj p11 p21)
      (adj p21 p11)
      (adj p12 p22)
      (adj p22 p12)
      (adj p11 p12)
      (adj p12 p11)
      (adj p21 p22)
      (adj p22 p21)
      (opened p11)
      (not (opened p12))
      (opened p21))
    )
    )
  )
  
  (:goal (K (at p22)))
)
