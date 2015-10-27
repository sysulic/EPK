(define (domain farmer)
  
   (:action double
    :parameters ()
    :precondition (K (true))
    :observe (d)
  )
     
	(:action left
	 :parameters ()
	 :precondition (K (not (fl)))
	 :effect (( ,(fl), ),
	          ((and (wi) (wa) (si) (sa) (not(wl)) (not(sl))), , (sa)),
	          ((and (si) (sa) (ri) (re) (not(sl)) (not(rl))), ,(re))
	         )
	)
	
	(:action wleft
	 :parameters()
	 :precondition (K (and(not (fl))(not(d))))
	 :effect (( , (fl), ),
	          ((and (wi) (wa) (not (wl))), (wl), ),
			  ((and (si) (sa) (ri) (re) (sl) (rl)), ,(re)),
			  ((and (si) (sa) (ri) (re) (not (sl)) (not (rl))), ,(re))
			  )
	)
	
	(:action sleft
	 :parameters()
	 :precondition (K (and(not (fl))(not(d))))
	 :effect (( ,(fl), ),
	          ((and (si) (sa) (not (sl))), (sl), )
			  )	
	)
	
	(:action rleft
	 :parameters()
	 :precondition (K(and (not (fl)) (not(d))))
	 :effect (( , (fl), ),
	          ((and (ri) (re) (not (rl))), (rl), ),
			  ((and (wi) (wa) (si) (sa) (wl) (sl)), , (sa)),
			  ((and (wi) (wa) (si) (sa) (not (wl)) (not (sl))), , (sa))
	         )
	)
	
	(:action wsleft
	 :parameters()
	 :precondition (K (and (not (fl)) (d)))
	 :effect (( , (fl), ),
	          ((and (wi) (wa) (not (wl))), (wl), ),
			  ((and (si) (sa) (not (sl))), (sl), )
			 )
	 )
	 
	(:action rsleft
	 :parameters()
	 :precondition (K (and (not (fl)) (d)))
	 :effect (( , (fl), ),
	          ((and (si) (sa) (not (sl))), (sl), ),
			  ((and (ri) (re) (not (rl))), (rl), )
	         ) 
	 )
	 
	(:action rwleft
	 :parameters()
	 :precondition (K (and (not (fl)) (d)))
	 :effect (( , (fl), ),
	          ((and (wi) (wa) (not (wl))), (wl), ),
			  ((and (ri) (re) (not (rl))), (rl), )
	         )
	)
	
	(:action right
	 :parameters()
	 :precondition (K (fl))
	 :effect (( , ,(fl)),
	          ((and (wi) (wa) (si) (sa) (wl) (sl)), , (sa)),
	          ((and (si) (sa) (ri) (re) (sl) (rl)), , (re))
	         )
	)
	
	(:action wright
	 :parameters()
	 :precondition (K (and (fl)(not(d))))
	 :effect (( , ,(fl)),
	          ((and (wi) (wa) (wl)), ,(wl)),
			  ((and (si) (sa) (ri) (re) (not (sl)) (not (rl))), ,(re)),
			  ((and (si) (sa) (ri) (re) (sl) (rl)), ,(re))
			 )
	)
	
	(:action sright
	 :parameters()
	 :precondition (K  (and(fl)(not(d)))) 
	 :effect (( , , (fl)),
	          ((and (si) (sa) (sl)), ,(sl))
			 )
	)
	
	(:action rright
	 :parameters()
	 :precondition (K (and (fl)(not(d))))
	 :effect (( , , (fl)),
	          ((and (ri) (re) (rl)), , (rl)),
			  ((and (wi) (wa) (si) (sa) (wl) (sl)), ,(sa)),
			  ((and (wi) (wa) (si) (sa) (not (wl)) (not (sl))), , (sa))
			 )
	)
	
	(:action wsright
	 :parameters()
	 :precondition (K (and (fl) (d)))
	 :effect (( , , (fl)),
	          ((and (wi) (wa) (wl)), , (wl)),
			  ((and (si) (sa) (sl)), , (sl))
			 ) 
	)
	
	(:action rsright
	 :parameters()
	 :precondition (K (and (fl) (d)))
	 :effect (( , , (fl)),
	          ((and (si) (sa) (sl)), , (sl)),
			  ((and (ri) (re) (rl)), , (rl))
			 )
	)
	
	(:action rwright
	 :parameters()
	 :precondition (K (and (fl) (d)))
	 :effect (( , , (fl)),
	          ((and (wi) (wa) (wl)), , (wl)),
			  ((and (ri) (re) (rl)), , (rl))
			 )
	)
)
