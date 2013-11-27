(define (counter)
	(define x 0)
	(lambda ()
		(set! x (+ x 1))
		x
	)
)

(define a (counter))
(display (a))
(display (a))
(display (a))
(display (a))