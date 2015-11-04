
(define (problem cube-cube-d119-g59-corners)
 (:domain cube)
 (:init
(and

      (oneof (x p1) (x p119) 
      ) 
      (oneof (y p1) (y p119) 
      ) 
      (oneof (z p1) (z p119) 
      ) 
       )) 
 (:goal
       (and (x p60)(y p60)(z p60))
       ))

