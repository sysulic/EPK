
(define (problem cube-cube-d99-g49-corners)
 (:domain cube)
 (:init
(and

      (oneof (x p1) (x p99) 
      ) 
      (oneof (y p1) (y p99) 
      ) 
      (oneof (z p1) (z p99) 
      ) 
       )) 
 (:goal
       (and (x p50)(y p50)(z p50))
       ))

