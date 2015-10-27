(define (problem doors-1)
  (:domain doors)
  (:objects 
    p11  
    p12  
    p21 
    p22 - pos 
  )
  
  (:init (K 
    
      (and
      (oneof 
        (at p12)
        (at p11)
      )
      (adj p11 p21)
      (adj p21 p11)
      (adj p12 p22)
      (adj p22 p12)
      (adj p11 p12)
      (adj p12 p11)
      (adj p21 p22)
      (adj p22 p21)
      ( oneof 
      (opened p11)
      (opened p22)
      )
      )
    
    )
  )
  
  (:goal (K (at p22)))
)
