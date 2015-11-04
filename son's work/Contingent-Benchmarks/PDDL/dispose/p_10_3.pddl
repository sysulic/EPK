(define (problem dispose_10_3)
(:domain dispose)

 (:objects     o1
    o2
    o3

 - obj 
    p1_1
    p1_2
    p1_3
    p1_4
    p1_5
    p1_6
    p1_7
    p1_8
    p1_9
    p1_10
    p2_1
    p2_2
    p2_3
    p2_4
    p2_5
    p2_6
    p2_7
    p2_8
    p2_9
    p2_10
    p3_1
    p3_2
    p3_3
    p3_4
    p3_5
    p3_6
    p3_7
    p3_8
    p3_9
    p3_10
    p4_1
    p4_2
    p4_3
    p4_4
    p4_5
    p4_6
    p4_7
    p4_8
    p4_9
    p4_10
    p5_1
    p5_2
    p5_3
    p5_4
    p5_5
    p5_6
    p5_7
    p5_8
    p5_9
    p5_10
    p6_1
    p6_2
    p6_3
    p6_4
    p6_5
    p6_6
    p6_7
    p6_8
    p6_9
    p6_10
    p7_1
    p7_2
    p7_3
    p7_4
    p7_5
    p7_6
    p7_7
    p7_8
    p7_9
    p7_10
    p8_1
    p8_2
    p8_3
    p8_4
    p8_5
    p8_6
    p8_7
    p8_8
    p8_9
    p8_10
    p9_1
    p9_2
    p9_3
    p9_4
    p9_5
    p9_6
    p9_7
    p9_8
    p9_9
    p9_10
    p10_1
    p10_2
    p10_3
    p10_4
    p10_5
    p10_6
    p10_7
    p10_8
    p10_9
    p10_10

 - pos 
    )
   (:init
    (and
     (at p5_5)
     (trash_at p3_3)     (adj p1_1 p2_1)
     (adj p2_1 p1_1)

     (adj p1_2 p2_2)
     (adj p2_2 p1_2)

     (adj p1_3 p2_3)
     (adj p2_3 p1_3)

     (adj p1_4 p2_4)
     (adj p2_4 p1_4)

     (adj p1_5 p2_5)
     (adj p2_5 p1_5)

     (adj p1_6 p2_6)
     (adj p2_6 p1_6)

     (adj p1_7 p2_7)
     (adj p2_7 p1_7)

     (adj p1_8 p2_8)
     (adj p2_8 p1_8)

     (adj p1_9 p2_9)
     (adj p2_9 p1_9)

     (adj p1_10 p2_10)
     (adj p2_10 p1_10)

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

     (adj p2_6 p3_6)
     (adj p3_6 p2_6)

     (adj p2_7 p3_7)
     (adj p3_7 p2_7)

     (adj p2_8 p3_8)
     (adj p3_8 p2_8)

     (adj p2_9 p3_9)
     (adj p3_9 p2_9)

     (adj p2_10 p3_10)
     (adj p3_10 p2_10)

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

     (adj p3_6 p4_6)
     (adj p4_6 p3_6)

     (adj p3_7 p4_7)
     (adj p4_7 p3_7)

     (adj p3_8 p4_8)
     (adj p4_8 p3_8)

     (adj p3_9 p4_9)
     (adj p4_9 p3_9)

     (adj p3_10 p4_10)
     (adj p4_10 p3_10)

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

     (adj p4_6 p5_6)
     (adj p5_6 p4_6)

     (adj p4_7 p5_7)
     (adj p5_7 p4_7)

     (adj p4_8 p5_8)
     (adj p5_8 p4_8)

     (adj p4_9 p5_9)
     (adj p5_9 p4_9)

     (adj p4_10 p5_10)
     (adj p5_10 p4_10)

     (adj p5_1 p6_1)
     (adj p6_1 p5_1)

     (adj p5_2 p6_2)
     (adj p6_2 p5_2)

     (adj p5_3 p6_3)
     (adj p6_3 p5_3)

     (adj p5_4 p6_4)
     (adj p6_4 p5_4)

     (adj p5_5 p6_5)
     (adj p6_5 p5_5)

     (adj p5_6 p6_6)
     (adj p6_6 p5_6)

     (adj p5_7 p6_7)
     (adj p6_7 p5_7)

     (adj p5_8 p6_8)
     (adj p6_8 p5_8)

     (adj p5_9 p6_9)
     (adj p6_9 p5_9)

     (adj p5_10 p6_10)
     (adj p6_10 p5_10)

     (adj p6_1 p7_1)
     (adj p7_1 p6_1)

     (adj p6_2 p7_2)
     (adj p7_2 p6_2)

     (adj p6_3 p7_3)
     (adj p7_3 p6_3)

     (adj p6_4 p7_4)
     (adj p7_4 p6_4)

     (adj p6_5 p7_5)
     (adj p7_5 p6_5)

     (adj p6_6 p7_6)
     (adj p7_6 p6_6)

     (adj p6_7 p7_7)
     (adj p7_7 p6_7)

     (adj p6_8 p7_8)
     (adj p7_8 p6_8)

     (adj p6_9 p7_9)
     (adj p7_9 p6_9)

     (adj p6_10 p7_10)
     (adj p7_10 p6_10)

     (adj p7_1 p8_1)
     (adj p8_1 p7_1)

     (adj p7_2 p8_2)
     (adj p8_2 p7_2)

     (adj p7_3 p8_3)
     (adj p8_3 p7_3)

     (adj p7_4 p8_4)
     (adj p8_4 p7_4)

     (adj p7_5 p8_5)
     (adj p8_5 p7_5)

     (adj p7_6 p8_6)
     (adj p8_6 p7_6)

     (adj p7_7 p8_7)
     (adj p8_7 p7_7)

     (adj p7_8 p8_8)
     (adj p8_8 p7_8)

     (adj p7_9 p8_9)
     (adj p8_9 p7_9)

     (adj p7_10 p8_10)
     (adj p8_10 p7_10)

     (adj p8_1 p9_1)
     (adj p9_1 p8_1)

     (adj p8_2 p9_2)
     (adj p9_2 p8_2)

     (adj p8_3 p9_3)
     (adj p9_3 p8_3)

     (adj p8_4 p9_4)
     (adj p9_4 p8_4)

     (adj p8_5 p9_5)
     (adj p9_5 p8_5)

     (adj p8_6 p9_6)
     (adj p9_6 p8_6)

     (adj p8_7 p9_7)
     (adj p9_7 p8_7)

     (adj p8_8 p9_8)
     (adj p9_8 p8_8)

     (adj p8_9 p9_9)
     (adj p9_9 p8_9)

     (adj p8_10 p9_10)
     (adj p9_10 p8_10)

     (adj p9_1 p10_1)
     (adj p10_1 p9_1)

     (adj p9_2 p10_2)
     (adj p10_2 p9_2)

     (adj p9_3 p10_3)
     (adj p10_3 p9_3)

     (adj p9_4 p10_4)
     (adj p10_4 p9_4)

     (adj p9_5 p10_5)
     (adj p10_5 p9_5)

     (adj p9_6 p10_6)
     (adj p10_6 p9_6)

     (adj p9_7 p10_7)
     (adj p10_7 p9_7)

     (adj p9_8 p10_8)
     (adj p10_8 p9_8)

     (adj p9_9 p10_9)
     (adj p10_9 p9_9)

     (adj p9_10 p10_10)
     (adj p10_10 p9_10)


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

     (adj p6_1 p6_2)
     (adj p6_2 p6_1)

     (adj p7_1 p7_2)
     (adj p7_2 p7_1)

     (adj p8_1 p8_2)
     (adj p8_2 p8_1)

     (adj p9_1 p9_2)
     (adj p9_2 p9_1)

     (adj p10_1 p10_2)
     (adj p10_2 p10_1)

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

     (adj p6_2 p6_3)
     (adj p6_3 p6_2)

     (adj p7_2 p7_3)
     (adj p7_3 p7_2)

     (adj p8_2 p8_3)
     (adj p8_3 p8_2)

     (adj p9_2 p9_3)
     (adj p9_3 p9_2)

     (adj p10_2 p10_3)
     (adj p10_3 p10_2)

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

     (adj p6_3 p6_4)
     (adj p6_4 p6_3)

     (adj p7_3 p7_4)
     (adj p7_4 p7_3)

     (adj p8_3 p8_4)
     (adj p8_4 p8_3)

     (adj p9_3 p9_4)
     (adj p9_4 p9_3)

     (adj p10_3 p10_4)
     (adj p10_4 p10_3)

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

     (adj p6_4 p6_5)
     (adj p6_5 p6_4)

     (adj p7_4 p7_5)
     (adj p7_5 p7_4)

     (adj p8_4 p8_5)
     (adj p8_5 p8_4)

     (adj p9_4 p9_5)
     (adj p9_5 p9_4)

     (adj p10_4 p10_5)
     (adj p10_5 p10_4)

     (adj p1_5 p1_6)
     (adj p1_6 p1_5)

     (adj p2_5 p2_6)
     (adj p2_6 p2_5)

     (adj p3_5 p3_6)
     (adj p3_6 p3_5)

     (adj p4_5 p4_6)
     (adj p4_6 p4_5)

     (adj p5_5 p5_6)
     (adj p5_6 p5_5)

     (adj p6_5 p6_6)
     (adj p6_6 p6_5)

     (adj p7_5 p7_6)
     (adj p7_6 p7_5)

     (adj p8_5 p8_6)
     (adj p8_6 p8_5)

     (adj p9_5 p9_6)
     (adj p9_6 p9_5)

     (adj p10_5 p10_6)
     (adj p10_6 p10_5)

     (adj p1_6 p1_7)
     (adj p1_7 p1_6)

     (adj p2_6 p2_7)
     (adj p2_7 p2_6)

     (adj p3_6 p3_7)
     (adj p3_7 p3_6)

     (adj p4_6 p4_7)
     (adj p4_7 p4_6)

     (adj p5_6 p5_7)
     (adj p5_7 p5_6)

     (adj p6_6 p6_7)
     (adj p6_7 p6_6)

     (adj p7_6 p7_7)
     (adj p7_7 p7_6)

     (adj p8_6 p8_7)
     (adj p8_7 p8_6)

     (adj p9_6 p9_7)
     (adj p9_7 p9_6)

     (adj p10_6 p10_7)
     (adj p10_7 p10_6)

     (adj p1_7 p1_8)
     (adj p1_8 p1_7)

     (adj p2_7 p2_8)
     (adj p2_8 p2_7)

     (adj p3_7 p3_8)
     (adj p3_8 p3_7)

     (adj p4_7 p4_8)
     (adj p4_8 p4_7)

     (adj p5_7 p5_8)
     (adj p5_8 p5_7)

     (adj p6_7 p6_8)
     (adj p6_8 p6_7)

     (adj p7_7 p7_8)
     (adj p7_8 p7_7)

     (adj p8_7 p8_8)
     (adj p8_8 p8_7)

     (adj p9_7 p9_8)
     (adj p9_8 p9_7)

     (adj p10_7 p10_8)
     (adj p10_8 p10_7)

     (adj p1_8 p1_9)
     (adj p1_9 p1_8)

     (adj p2_8 p2_9)
     (adj p2_9 p2_8)

     (adj p3_8 p3_9)
     (adj p3_9 p3_8)

     (adj p4_8 p4_9)
     (adj p4_9 p4_8)

     (adj p5_8 p5_9)
     (adj p5_9 p5_8)

     (adj p6_8 p6_9)
     (adj p6_9 p6_8)

     (adj p7_8 p7_9)
     (adj p7_9 p7_8)

     (adj p8_8 p8_9)
     (adj p8_9 p8_8)

     (adj p9_8 p9_9)
     (adj p9_9 p9_8)

     (adj p10_8 p10_9)
     (adj p10_9 p10_8)

     (adj p1_9 p1_10)
     (adj p1_10 p1_9)

     (adj p2_9 p2_10)
     (adj p2_10 p2_9)

     (adj p3_9 p3_10)
     (adj p3_10 p3_9)

     (adj p4_9 p4_10)
     (adj p4_10 p4_9)

     (adj p5_9 p5_10)
     (adj p5_10 p5_9)

     (adj p6_9 p6_10)
     (adj p6_10 p6_9)

     (adj p7_9 p7_10)
     (adj p7_10 p7_9)

     (adj p8_9 p8_10)
     (adj p8_10 p8_9)

     (adj p9_9 p9_10)
     (adj p9_10 p9_9)

     (adj p10_9 p10_10)
     (adj p10_10 p10_9)


     (oneof
        (obj_at o1 p1_1)
        (obj_at o1 p1_2)
        (obj_at o1 p1_3)
        (obj_at o1 p1_4)
        (obj_at o1 p1_5)
        (obj_at o1 p1_6)
        (obj_at o1 p1_7)
        (obj_at o1 p1_8)
        (obj_at o1 p1_9)
        (obj_at o1 p1_10)
        (obj_at o1 p2_1)
        (obj_at o1 p2_2)
        (obj_at o1 p2_3)
        (obj_at o1 p2_4)
        (obj_at o1 p2_5)
        (obj_at o1 p2_6)
        (obj_at o1 p2_7)
        (obj_at o1 p2_8)
        (obj_at o1 p2_9)
        (obj_at o1 p2_10)
        (obj_at o1 p3_1)
        (obj_at o1 p3_2)
        (obj_at o1 p3_3)
        (obj_at o1 p3_4)
        (obj_at o1 p3_5)
        (obj_at o1 p3_6)
        (obj_at o1 p3_7)
        (obj_at o1 p3_8)
        (obj_at o1 p3_9)
        (obj_at o1 p3_10)
        (obj_at o1 p4_1)
        (obj_at o1 p4_2)
        (obj_at o1 p4_3)
        (obj_at o1 p4_4)
        (obj_at o1 p4_5)
        (obj_at o1 p4_6)
        (obj_at o1 p4_7)
        (obj_at o1 p4_8)
        (obj_at o1 p4_9)
        (obj_at o1 p4_10)
        (obj_at o1 p5_1)
        (obj_at o1 p5_2)
        (obj_at o1 p5_3)
        (obj_at o1 p5_4)
        (obj_at o1 p5_5)
        (obj_at o1 p5_6)
        (obj_at o1 p5_7)
        (obj_at o1 p5_8)
        (obj_at o1 p5_9)
        (obj_at o1 p5_10)
        (obj_at o1 p6_1)
        (obj_at o1 p6_2)
        (obj_at o1 p6_3)
        (obj_at o1 p6_4)
        (obj_at o1 p6_5)
        (obj_at o1 p6_6)
        (obj_at o1 p6_7)
        (obj_at o1 p6_8)
        (obj_at o1 p6_9)
        (obj_at o1 p6_10)
        (obj_at o1 p7_1)
        (obj_at o1 p7_2)
        (obj_at o1 p7_3)
        (obj_at o1 p7_4)
        (obj_at o1 p7_5)
        (obj_at o1 p7_6)
        (obj_at o1 p7_7)
        (obj_at o1 p7_8)
        (obj_at o1 p7_9)
        (obj_at o1 p7_10)
        (obj_at o1 p8_1)
        (obj_at o1 p8_2)
        (obj_at o1 p8_3)
        (obj_at o1 p8_4)
        (obj_at o1 p8_5)
        (obj_at o1 p8_6)
        (obj_at o1 p8_7)
        (obj_at o1 p8_8)
        (obj_at o1 p8_9)
        (obj_at o1 p8_10)
        (obj_at o1 p9_1)
        (obj_at o1 p9_2)
        (obj_at o1 p9_3)
        (obj_at o1 p9_4)
        (obj_at o1 p9_5)
        (obj_at o1 p9_6)
        (obj_at o1 p9_7)
        (obj_at o1 p9_8)
        (obj_at o1 p9_9)
        (obj_at o1 p9_10)
        (obj_at o1 p10_1)
        (obj_at o1 p10_2)
        (obj_at o1 p10_3)
        (obj_at o1 p10_4)
        (obj_at o1 p10_5)
        (obj_at o1 p10_6)
        (obj_at o1 p10_7)
        (obj_at o1 p10_8)
        (obj_at o1 p10_9)
        (obj_at o1 p10_10)
     )
     (oneof
        (obj_at o2 p1_1)
        (obj_at o2 p1_2)
        (obj_at o2 p1_3)
        (obj_at o2 p1_4)
        (obj_at o2 p1_5)
        (obj_at o2 p1_6)
        (obj_at o2 p1_7)
        (obj_at o2 p1_8)
        (obj_at o2 p1_9)
        (obj_at o2 p1_10)
        (obj_at o2 p2_1)
        (obj_at o2 p2_2)
        (obj_at o2 p2_3)
        (obj_at o2 p2_4)
        (obj_at o2 p2_5)
        (obj_at o2 p2_6)
        (obj_at o2 p2_7)
        (obj_at o2 p2_8)
        (obj_at o2 p2_9)
        (obj_at o2 p2_10)
        (obj_at o2 p3_1)
        (obj_at o2 p3_2)
        (obj_at o2 p3_3)
        (obj_at o2 p3_4)
        (obj_at o2 p3_5)
        (obj_at o2 p3_6)
        (obj_at o2 p3_7)
        (obj_at o2 p3_8)
        (obj_at o2 p3_9)
        (obj_at o2 p3_10)
        (obj_at o2 p4_1)
        (obj_at o2 p4_2)
        (obj_at o2 p4_3)
        (obj_at o2 p4_4)
        (obj_at o2 p4_5)
        (obj_at o2 p4_6)
        (obj_at o2 p4_7)
        (obj_at o2 p4_8)
        (obj_at o2 p4_9)
        (obj_at o2 p4_10)
        (obj_at o2 p5_1)
        (obj_at o2 p5_2)
        (obj_at o2 p5_3)
        (obj_at o2 p5_4)
        (obj_at o2 p5_5)
        (obj_at o2 p5_6)
        (obj_at o2 p5_7)
        (obj_at o2 p5_8)
        (obj_at o2 p5_9)
        (obj_at o2 p5_10)
        (obj_at o2 p6_1)
        (obj_at o2 p6_2)
        (obj_at o2 p6_3)
        (obj_at o2 p6_4)
        (obj_at o2 p6_5)
        (obj_at o2 p6_6)
        (obj_at o2 p6_7)
        (obj_at o2 p6_8)
        (obj_at o2 p6_9)
        (obj_at o2 p6_10)
        (obj_at o2 p7_1)
        (obj_at o2 p7_2)
        (obj_at o2 p7_3)
        (obj_at o2 p7_4)
        (obj_at o2 p7_5)
        (obj_at o2 p7_6)
        (obj_at o2 p7_7)
        (obj_at o2 p7_8)
        (obj_at o2 p7_9)
        (obj_at o2 p7_10)
        (obj_at o2 p8_1)
        (obj_at o2 p8_2)
        (obj_at o2 p8_3)
        (obj_at o2 p8_4)
        (obj_at o2 p8_5)
        (obj_at o2 p8_6)
        (obj_at o2 p8_7)
        (obj_at o2 p8_8)
        (obj_at o2 p8_9)
        (obj_at o2 p8_10)
        (obj_at o2 p9_1)
        (obj_at o2 p9_2)
        (obj_at o2 p9_3)
        (obj_at o2 p9_4)
        (obj_at o2 p9_5)
        (obj_at o2 p9_6)
        (obj_at o2 p9_7)
        (obj_at o2 p9_8)
        (obj_at o2 p9_9)
        (obj_at o2 p9_10)
        (obj_at o2 p10_1)
        (obj_at o2 p10_2)
        (obj_at o2 p10_3)
        (obj_at o2 p10_4)
        (obj_at o2 p10_5)
        (obj_at o2 p10_6)
        (obj_at o2 p10_7)
        (obj_at o2 p10_8)
        (obj_at o2 p10_9)
        (obj_at o2 p10_10)
     )
     (oneof
        (obj_at o3 p1_1)
        (obj_at o3 p1_2)
        (obj_at o3 p1_3)
        (obj_at o3 p1_4)
        (obj_at o3 p1_5)
        (obj_at o3 p1_6)
        (obj_at o3 p1_7)
        (obj_at o3 p1_8)
        (obj_at o3 p1_9)
        (obj_at o3 p1_10)
        (obj_at o3 p2_1)
        (obj_at o3 p2_2)
        (obj_at o3 p2_3)
        (obj_at o3 p2_4)
        (obj_at o3 p2_5)
        (obj_at o3 p2_6)
        (obj_at o3 p2_7)
        (obj_at o3 p2_8)
        (obj_at o3 p2_9)
        (obj_at o3 p2_10)
        (obj_at o3 p3_1)
        (obj_at o3 p3_2)
        (obj_at o3 p3_3)
        (obj_at o3 p3_4)
        (obj_at o3 p3_5)
        (obj_at o3 p3_6)
        (obj_at o3 p3_7)
        (obj_at o3 p3_8)
        (obj_at o3 p3_9)
        (obj_at o3 p3_10)
        (obj_at o3 p4_1)
        (obj_at o3 p4_2)
        (obj_at o3 p4_3)
        (obj_at o3 p4_4)
        (obj_at o3 p4_5)
        (obj_at o3 p4_6)
        (obj_at o3 p4_7)
        (obj_at o3 p4_8)
        (obj_at o3 p4_9)
        (obj_at o3 p4_10)
        (obj_at o3 p5_1)
        (obj_at o3 p5_2)
        (obj_at o3 p5_3)
        (obj_at o3 p5_4)
        (obj_at o3 p5_5)
        (obj_at o3 p5_6)
        (obj_at o3 p5_7)
        (obj_at o3 p5_8)
        (obj_at o3 p5_9)
        (obj_at o3 p5_10)
        (obj_at o3 p6_1)
        (obj_at o3 p6_2)
        (obj_at o3 p6_3)
        (obj_at o3 p6_4)
        (obj_at o3 p6_5)
        (obj_at o3 p6_6)
        (obj_at o3 p6_7)
        (obj_at o3 p6_8)
        (obj_at o3 p6_9)
        (obj_at o3 p6_10)
        (obj_at o3 p7_1)
        (obj_at o3 p7_2)
        (obj_at o3 p7_3)
        (obj_at o3 p7_4)
        (obj_at o3 p7_5)
        (obj_at o3 p7_6)
        (obj_at o3 p7_7)
        (obj_at o3 p7_8)
        (obj_at o3 p7_9)
        (obj_at o3 p7_10)
        (obj_at o3 p8_1)
        (obj_at o3 p8_2)
        (obj_at o3 p8_3)
        (obj_at o3 p8_4)
        (obj_at o3 p8_5)
        (obj_at o3 p8_6)
        (obj_at o3 p8_7)
        (obj_at o3 p8_8)
        (obj_at o3 p8_9)
        (obj_at o3 p8_10)
        (obj_at o3 p9_1)
        (obj_at o3 p9_2)
        (obj_at o3 p9_3)
        (obj_at o3 p9_4)
        (obj_at o3 p9_5)
        (obj_at o3 p9_6)
        (obj_at o3 p9_7)
        (obj_at o3 p9_8)
        (obj_at o3 p9_9)
        (obj_at o3 p9_10)
        (obj_at o3 p10_1)
        (obj_at o3 p10_2)
        (obj_at o3 p10_3)
        (obj_at o3 p10_4)
        (obj_at o3 p10_5)
        (obj_at o3 p10_6)
        (obj_at o3 p10_7)
        (obj_at o3 p10_8)
        (obj_at o3 p10_9)
        (obj_at o3 p10_10)
     )

    )
    )
    (:goal (and     (disposed o1)
    (disposed o2)
    (disposed o3)
)))
