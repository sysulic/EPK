(define (problem unix-2)
   (:domain unix)
   (:objects 
        root 
        sub1 
        sub2 
        sub11 
        sub12 
        sub21 
        sub22 
        sub111 
        sub112 
        sub121 
        sub122 
        sub211 
        sub212 
        sub221 
        sub222 - DIR 
        my_file - FILE
   )
   
   (:init (K (and
        (sub_dir root sub1)
        (sub_dir root sub2)
        (sub_dir sub1 sub11)
        (sub_dir sub1 sub12)
        (sub_dir sub2 sub21)
        (sub_dir sub2 sub22)
        (sub_dir sub11 sub111)
        (sub_dir sub11 sub112)
        (sub_dir sub21 sub211)
        (sub_dir sub21 sub212)
        (sub_dir sub12 sub121)
        (sub_dir sub12 sub122)
        (sub_dir sub22 sub221)
        (sub_dir sub22 sub222)
        (is_cur_dir root)
        (file_in_dir my_file sub11)
        )
        )
    )
    
   (:goal (K (file_in_dir my_file root)))
)
