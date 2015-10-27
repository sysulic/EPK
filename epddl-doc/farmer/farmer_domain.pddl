(define (domain farmer)
    

    (:action double
     :parameters ()
     :precondition (True)
     :observe (d)
     )
     
	(:action left
	 :parameters ()
	 :precondition (K (not (fl)))
	 :effect (( ,(fl), )
	         )
	)
	
	(:action wleft
	 :parameters()
	 :precondition (and (K (not (fl))) (DK (not (d))))
	 :effect (( , (fl), ),
	          ((and (wa) (not (wl))), (wl), ),
			  ((and (sa) (re)  (sl)  (rl)), ,(re)),
			  ((and (sa) (re) (not (sl)) (not (rl))), ,(re))
			  )
	)
	
	(:action sleft
	 :parameters()
	 :precondition (and (K (not (fl))) (DK (not (d))))
	 :effect (( ,(fl), ),
	          ((and (sa) (not (sl))), (sl), )
			  )	
	)
	
	(:action rleft
	 :parameters()
	 :precondition (and (K (not (fl))) (DK (not (d))))
	 :effect (( , (fl), ),
	          ((and (re) (not (rl))), (rl), ),
			  ((and (wa) (sa) (wl) (sl)), , (sa)),
			  ((and (wa) (sa) (not (wl)) (not (sl))), , (sa))
	         )
	)
	
	(:action wsleft
	 :parameters()
	 :precondition (K (and (not (fl)) (d)))
	 :effect (( , (fl), ),
	          ((and (wa) (not (wl))), (wl), ),
			  ((and (sa) (not (sl))), (sl), )
			 )
	 )
	 
	(:action rsleft
	 :parameters()
	 :precondition (K (and (not (fl)) (d)))
	 :effect (( , (fl), ),
	          ((and (sa) (not (sl))), (sl), ),
			  ((and (re) (not (rl))), (rl), )
	         ) 
	 )
	 
	(:action rwleft
	 :parameters()
	 :precondition (K (and (not (fl)) (d)))
	 :effect (( , (fl), ),
	          ((and (wa) (not (wl))), (wl), ),
			  ((and (re) (not (rl))), (rl), )
	         )
	)
	
	(:action right
	 :parameters()
	 :precondition (K (fl))
	 :effect (( , ,(fl))
	         )
	)
	
	(:action wright
	 :parameters()
	 :precondition (and (K (fl)) (DK (not (d))))
	 :effect (( , ,(fl)),
	          ((and (wa) (wl)), ,(wl)),
			  ((and (sa) (re) (not (sl)) (not (rl))), ,(re)),
			  ((and (sa) (re) (sl) (rl)), ,(re))
			 )
	)
	
	(:action sright
	 :parameters()
	 :precondition (and (K (fl)) (DK (not (d))))
	 :effect (( , , (fl)),
	          ((and (sa) (sl)), ,(sl))
			 )
	)
	
	(:action rright
	 :parameters()
	 :precondition (and (K (fl)) (DK (not (d))))
	 :effect (( , , (fl)),
	          ((and (re) (rl)), , (rl)),
			  ((and (wa) (sa) (wl) (sl)), ,(sa)),
			  ((and (wa) (sa) (not (wl)) (not (sl))), , (sa))
			 )
	)
	
	(:action wsright
	 :parameters()
	 :precondition (K (and (fl) (d)))
	 :effect (( , , (fl)),
	          ((and (wa) (wl)), , (wl)),
			  ((and (sa) (sl)), , (sl))
			 ) 
	)
	
	(:action rsright
	 :parameters()
	 :precondition (K (and (fl) (d)))
	 :effect (( , , (fl)),
	          ((and (sa) (sl)), , (sl)),
			  ((and (re) (rl)), , (rl))
			 )
	)
	
	(:action rwright
	 :parameters()
	 :precondition (K (and (fl) (d)))
	 :effect (( , , (fl)),
	          ((and (wa) (wl)), , (wl)),
			  ((and (re) (rl)), , (rl))
			 )
	)
)
