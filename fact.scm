(define (fact n res)
	(if (> n 0)
		(fact (- n 1) (* n res))
		res
	)
)
(fact 10000 1)