(define (problem dispose_2_1)
(:domain dispose)

 (:objects     o1

 - obj 
    p1_1
    p1_2
    p2_1
    p2_2

 - pos 
    )
   (:init
    (and
     (at p1_1)
     (trash_at p1_1)     (adj p1_1 p2_1)
     (adj p2_1 p1_1)

     (adj p1_2 p2_2)
     (adj p2_2 p1_2)


     (adj p1_1 p1_2)
     (adj p1_2 p1_1)

     (adj p2_1 p2_2)
     (adj p2_2 p2_1)


     (oneof
        (obj_at o1 p1_1)
        (obj_at o1 p1_2)
        (obj_at o1 p2_1)
        (obj_at o1 p2_2)
     )

    )
    )
    (:goal (disposed o1)))
