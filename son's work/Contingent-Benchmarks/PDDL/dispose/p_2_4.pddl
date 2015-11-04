(define (problem dispose_2_4)
(:domain dispose)

 (:objects     o1
    o2
    o3
    o4

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
     (oneof
        (obj_at o2 p1_1)
        (obj_at o2 p1_2)
        (obj_at o2 p2_1)
        (obj_at o2 p2_2)
     )
     (oneof
        (obj_at o3 p1_1)
        (obj_at o3 p1_2)
        (obj_at o3 p2_1)
        (obj_at o3 p2_2)
     )
     (oneof
        (obj_at o4 p1_1)
        (obj_at o4 p1_2)
        (obj_at o4 p2_1)
        (obj_at o4 p2_2)
     )

    )
    )
    (:goal (and     (disposed o1)
    (disposed o2)
    (disposed o3)
    (disposed o4)
)))
