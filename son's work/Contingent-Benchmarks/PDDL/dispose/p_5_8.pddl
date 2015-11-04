(define (problem dispose_5_8)
(:domain dispose)

 (:objects     o1
    o2
    o3
    o4
    o5
    o6
    o7
    o8

 - obj 
    p1_1
    p1_2
    p1_3
    p1_4
    p1_5
    p2_1
    p2_2
    p2_3
    p2_4
    p2_5
    p3_1
    p3_2
    p3_3
    p3_4
    p3_5
    p4_1
    p4_2
    p4_3
    p4_4
    p4_5
    p5_1
    p5_2
    p5_3
    p5_4
    p5_5

 - pos 
    )
   (:init
    (and
     (at p3_3)
     (trash_at p2_2)     (adj p1_1 p2_1)
     (adj p2_1 p1_1)

     (adj p1_2 p2_2)
     (adj p2_2 p1_2)

     (adj p1_3 p2_3)
     (adj p2_3 p1_3)

     (adj p1_4 p2_4)
     (adj p2_4 p1_4)

     (adj p1_5 p2_5)
     (adj p2_5 p1_5)

     (adj p2_1 p3_1)
     (adj p3_1 p2_1)

     (adj p2_2 p3_2)
     (adj p3_2 p2_2)

     (adj p2_3 p3_3)
     (adj p3_3 p2_3)

     (adj p2_4 p3_4)
     (adj p3_4 p2_4)

     (adj p2_5 p3_5)
     (adj p3_5 p2_5)

     (adj p3_1 p4_1)
     (adj p4_1 p3_1)

     (adj p3_2 p4_2)
     (adj p4_2 p3_2)

     (adj p3_3 p4_3)
     (adj p4_3 p3_3)

     (adj p3_4 p4_4)
     (adj p4_4 p3_4)

     (adj p3_5 p4_5)
     (adj p4_5 p3_5)

     (adj p4_1 p5_1)
     (adj p5_1 p4_1)

     (adj p4_2 p5_2)
     (adj p5_2 p4_2)

     (adj p4_3 p5_3)
     (adj p5_3 p4_3)

     (adj p4_4 p5_4)
     (adj p5_4 p4_4)

     (adj p4_5 p5_5)
     (adj p5_5 p4_5)


     (adj p1_1 p1_2)
     (adj p1_2 p1_1)

     (adj p2_1 p2_2)
     (adj p2_2 p2_1)

     (adj p3_1 p3_2)
     (adj p3_2 p3_1)

     (adj p4_1 p4_2)
     (adj p4_2 p4_1)

     (adj p5_1 p5_2)
     (adj p5_2 p5_1)

     (adj p1_2 p1_3)
     (adj p1_3 p1_2)

     (adj p2_2 p2_3)
     (adj p2_3 p2_2)

     (adj p3_2 p3_3)
     (adj p3_3 p3_2)

     (adj p4_2 p4_3)
     (adj p4_3 p4_2)

     (adj p5_2 p5_3)
     (adj p5_3 p5_2)

     (adj p1_3 p1_4)
     (adj p1_4 p1_3)

     (adj p2_3 p2_4)
     (adj p2_4 p2_3)

     (adj p3_3 p3_4)
     (adj p3_4 p3_3)

     (adj p4_3 p4_4)
     (adj p4_4 p4_3)

     (adj p5_3 p5_4)
     (adj p5_4 p5_3)

     (adj p1_4 p1_5)
     (adj p1_5 p1_4)

     (adj p2_4 p2_5)
     (adj p2_5 p2_4)

     (adj p3_4 p3_5)
     (adj p3_5 p3_4)

     (adj p4_4 p4_5)
     (adj p4_5 p4_4)

     (adj p5_4 p5_5)
     (adj p5_5 p5_4)


     (oneof
        (obj_at o1 p1_1)
        (obj_at o1 p1_2)
        (obj_at o1 p1_3)
        (obj_at o1 p1_4)
        (obj_at o1 p1_5)
        (obj_at o1 p2_1)
        (obj_at o1 p2_2)
        (obj_at o1 p2_3)
        (obj_at o1 p2_4)
        (obj_at o1 p2_5)
        (obj_at o1 p3_1)
        (obj_at o1 p3_2)
        (obj_at o1 p3_3)
        (obj_at o1 p3_4)
        (obj_at o1 p3_5)
        (obj_at o1 p4_1)
        (obj_at o1 p4_2)
        (obj_at o1 p4_3)
        (obj_at o1 p4_4)
        (obj_at o1 p4_5)
        (obj_at o1 p5_1)
        (obj_at o1 p5_2)
        (obj_at o1 p5_3)
        (obj_at o1 p5_4)
        (obj_at o1 p5_5)
     )
     (oneof
        (obj_at o2 p1_1)
        (obj_at o2 p1_2)
        (obj_at o2 p1_3)
        (obj_at o2 p1_4)
        (obj_at o2 p1_5)
        (obj_at o2 p2_1)
        (obj_at o2 p2_2)
        (obj_at o2 p2_3)
        (obj_at o2 p2_4)
        (obj_at o2 p2_5)
        (obj_at o2 p3_1)
        (obj_at o2 p3_2)
        (obj_at o2 p3_3)
        (obj_at o2 p3_4)
        (obj_at o2 p3_5)
        (obj_at o2 p4_1)
        (obj_at o2 p4_2)
        (obj_at o2 p4_3)
        (obj_at o2 p4_4)
        (obj_at o2 p4_5)
        (obj_at o2 p5_1)
        (obj_at o2 p5_2)
        (obj_at o2 p5_3)
        (obj_at o2 p5_4)
        (obj_at o2 p5_5)
     )
     (oneof
        (obj_at o3 p1_1)
        (obj_at o3 p1_2)
        (obj_at o3 p1_3)
        (obj_at o3 p1_4)
        (obj_at o3 p1_5)
        (obj_at o3 p2_1)
        (obj_at o3 p2_2)
        (obj_at o3 p2_3)
        (obj_at o3 p2_4)
        (obj_at o3 p2_5)
        (obj_at o3 p3_1)
        (obj_at o3 p3_2)
        (obj_at o3 p3_3)
        (obj_at o3 p3_4)
        (obj_at o3 p3_5)
        (obj_at o3 p4_1)
        (obj_at o3 p4_2)
        (obj_at o3 p4_3)
        (obj_at o3 p4_4)
        (obj_at o3 p4_5)
        (obj_at o3 p5_1)
        (obj_at o3 p5_2)
        (obj_at o3 p5_3)
        (obj_at o3 p5_4)
        (obj_at o3 p5_5)
     )
     (oneof
        (obj_at o4 p1_1)
        (obj_at o4 p1_2)
        (obj_at o4 p1_3)
        (obj_at o4 p1_4)
        (obj_at o4 p1_5)
        (obj_at o4 p2_1)
        (obj_at o4 p2_2)
        (obj_at o4 p2_3)
        (obj_at o4 p2_4)
        (obj_at o4 p2_5)
        (obj_at o4 p3_1)
        (obj_at o4 p3_2)
        (obj_at o4 p3_3)
        (obj_at o4 p3_4)
        (obj_at o4 p3_5)
        (obj_at o4 p4_1)
        (obj_at o4 p4_2)
        (obj_at o4 p4_3)
        (obj_at o4 p4_4)
        (obj_at o4 p4_5)
        (obj_at o4 p5_1)
        (obj_at o4 p5_2)
        (obj_at o4 p5_3)
        (obj_at o4 p5_4)
        (obj_at o4 p5_5)
     )
     (oneof
        (obj_at o5 p1_1)
        (obj_at o5 p1_2)
        (obj_at o5 p1_3)
        (obj_at o5 p1_4)
        (obj_at o5 p1_5)
        (obj_at o5 p2_1)
        (obj_at o5 p2_2)
        (obj_at o5 p2_3)
        (obj_at o5 p2_4)
        (obj_at o5 p2_5)
        (obj_at o5 p3_1)
        (obj_at o5 p3_2)
        (obj_at o5 p3_3)
        (obj_at o5 p3_4)
        (obj_at o5 p3_5)
        (obj_at o5 p4_1)
        (obj_at o5 p4_2)
        (obj_at o5 p4_3)
        (obj_at o5 p4_4)
        (obj_at o5 p4_5)
        (obj_at o5 p5_1)
        (obj_at o5 p5_2)
        (obj_at o5 p5_3)
        (obj_at o5 p5_4)
        (obj_at o5 p5_5)
     )
     (oneof
        (obj_at o6 p1_1)
        (obj_at o6 p1_2)
        (obj_at o6 p1_3)
        (obj_at o6 p1_4)
        (obj_at o6 p1_5)
        (obj_at o6 p2_1)
        (obj_at o6 p2_2)
        (obj_at o6 p2_3)
        (obj_at o6 p2_4)
        (obj_at o6 p2_5)
        (obj_at o6 p3_1)
        (obj_at o6 p3_2)
        (obj_at o6 p3_3)
        (obj_at o6 p3_4)
        (obj_at o6 p3_5)
        (obj_at o6 p4_1)
        (obj_at o6 p4_2)
        (obj_at o6 p4_3)
        (obj_at o6 p4_4)
        (obj_at o6 p4_5)
        (obj_at o6 p5_1)
        (obj_at o6 p5_2)
        (obj_at o6 p5_3)
        (obj_at o6 p5_4)
        (obj_at o6 p5_5)
     )
     (oneof
        (obj_at o7 p1_1)
        (obj_at o7 p1_2)
        (obj_at o7 p1_3)
        (obj_at o7 p1_4)
        (obj_at o7 p1_5)
        (obj_at o7 p2_1)
        (obj_at o7 p2_2)
        (obj_at o7 p2_3)
        (obj_at o7 p2_4)
        (obj_at o7 p2_5)
        (obj_at o7 p3_1)
        (obj_at o7 p3_2)
        (obj_at o7 p3_3)
        (obj_at o7 p3_4)
        (obj_at o7 p3_5)
        (obj_at o7 p4_1)
        (obj_at o7 p4_2)
        (obj_at o7 p4_3)
        (obj_at o7 p4_4)
        (obj_at o7 p4_5)
        (obj_at o7 p5_1)
        (obj_at o7 p5_2)
        (obj_at o7 p5_3)
        (obj_at o7 p5_4)
        (obj_at o7 p5_5)
     )
     (oneof
        (obj_at o8 p1_1)
        (obj_at o8 p1_2)
        (obj_at o8 p1_3)
        (obj_at o8 p1_4)
        (obj_at o8 p1_5)
        (obj_at o8 p2_1)
        (obj_at o8 p2_2)
        (obj_at o8 p2_3)
        (obj_at o8 p2_4)
        (obj_at o8 p2_5)
        (obj_at o8 p3_1)
        (obj_at o8 p3_2)
        (obj_at o8 p3_3)
        (obj_at o8 p3_4)
        (obj_at o8 p3_5)
        (obj_at o8 p4_1)
        (obj_at o8 p4_2)
        (obj_at o8 p4_3)
        (obj_at o8 p4_4)
        (obj_at o8 p4_5)
        (obj_at o8 p5_1)
        (obj_at o8 p5_2)
        (obj_at o8 p5_3)
        (obj_at o8 p5_4)
        (obj_at o8 p5_5)
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
    (disposed o8)
)))
