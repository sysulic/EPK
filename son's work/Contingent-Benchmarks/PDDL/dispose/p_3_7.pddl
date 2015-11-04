(define (problem dispose_3_7)
(:domain dispose)

 (:objects     o1
    o2
    o3
    o4
    o5
    o6
    o7

 - obj 
    p1_1
    p1_2
    p1_3
    p2_1
    p2_2
    p2_3
    p3_1
    p3_2
    p3_3

 - pos 
    )
   (:init
    (and
     (at p2_2)
     (trash_at p1_1)     (adj p1_1 p2_1)
     (adj p2_1 p1_1)

     (adj p1_2 p2_2)
     (adj p2_2 p1_2)

     (adj p1_3 p2_3)
     (adj p2_3 p1_3)

     (adj p2_1 p3_1)
     (adj p3_1 p2_1)

     (adj p2_2 p3_2)
     (adj p3_2 p2_2)

     (adj p2_3 p3_3)
     (adj p3_3 p2_3)


     (adj p1_1 p1_2)
     (adj p1_2 p1_1)

     (adj p2_1 p2_2)
     (adj p2_2 p2_1)

     (adj p3_1 p3_2)
     (adj p3_2 p3_1)

     (adj p1_2 p1_3)
     (adj p1_3 p1_2)

     (adj p2_2 p2_3)
     (adj p2_3 p2_2)

     (adj p3_2 p3_3)
     (adj p3_3 p3_2)


     (oneof
        (obj_at o1 p1_1)
        (obj_at o1 p1_2)
        (obj_at o1 p1_3)
        (obj_at o1 p2_1)
        (obj_at o1 p2_2)
        (obj_at o1 p2_3)
        (obj_at o1 p3_1)
        (obj_at o1 p3_2)
        (obj_at o1 p3_3)
     )
     (oneof
        (obj_at o2 p1_1)
        (obj_at o2 p1_2)
        (obj_at o2 p1_3)
        (obj_at o2 p2_1)
        (obj_at o2 p2_2)
        (obj_at o2 p2_3)
        (obj_at o2 p3_1)
        (obj_at o2 p3_2)
        (obj_at o2 p3_3)
     )
     (oneof
        (obj_at o3 p1_1)
        (obj_at o3 p1_2)
        (obj_at o3 p1_3)
        (obj_at o3 p2_1)
        (obj_at o3 p2_2)
        (obj_at o3 p2_3)
        (obj_at o3 p3_1)
        (obj_at o3 p3_2)
        (obj_at o3 p3_3)
     )
     (oneof
        (obj_at o4 p1_1)
        (obj_at o4 p1_2)
        (obj_at o4 p1_3)
        (obj_at o4 p2_1)
        (obj_at o4 p2_2)
        (obj_at o4 p2_3)
        (obj_at o4 p3_1)
        (obj_at o4 p3_2)
        (obj_at o4 p3_3)
     )
     (oneof
        (obj_at o5 p1_1)
        (obj_at o5 p1_2)
        (obj_at o5 p1_3)
        (obj_at o5 p2_1)
        (obj_at o5 p2_2)
        (obj_at o5 p2_3)
        (obj_at o5 p3_1)
        (obj_at o5 p3_2)
        (obj_at o5 p3_3)
     )
     (oneof
        (obj_at o6 p1_1)
        (obj_at o6 p1_2)
        (obj_at o6 p1_3)
        (obj_at o6 p2_1)
        (obj_at o6 p2_2)
        (obj_at o6 p2_3)
        (obj_at o6 p3_1)
        (obj_at o6 p3_2)
        (obj_at o6 p3_3)
     )
     (oneof
        (obj_at o7 p1_1)
        (obj_at o7 p1_2)
        (obj_at o7 p1_3)
        (obj_at o7 p2_1)
        (obj_at o7 p2_2)
        (obj_at o7 p2_3)
        (obj_at o7 p3_1)
        (obj_at o7 p3_2)
        (obj_at o7 p3_3)
     )

    )
    )
    (:goal (and     (disposed o1)
    (disposed o2)
    (disposed o3)
    (disposed o4)
    (disposed o5)
    (disposed o6)
    (disposed o7)
)))
