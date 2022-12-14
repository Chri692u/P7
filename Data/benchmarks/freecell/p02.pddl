(define (problem freecell3-4)
(:domain freecell)
(:objects
	diamond club heart spade 
	n0 n1 n2 n3 n4 n5 spade3
	club2
	spade2
	cluba
	heart3
	heart2
	diamond3
	club3
	diamonda
	diamond2
	hearta
	spadea
	diamond0
	club0
	heart0
	spade0
	
)
(:init
	(successor n1 n0)
	(successor n2 n1)
	(successor n3 n2)
	(successor n4 n3)
	(successor n5 n4)
	(cellspace n2)
	(clear spade3)
	(on spade3 heart2)
	(on heart2 hearta)
	(bottomcol hearta)
	(clear club2)
	(on club2 diamond3)
	(on diamond3 spadea)
	(bottomcol spadea)
	(clear spade2)
	(on spade2 club3)
	(bottomcol club3)
	(clear cluba)
	(on cluba diamonda)
	(bottomcol diamonda)
	(clear heart3)
	(on heart3 diamond2)
	(bottomcol diamond2)
	(colspace n0)
	(value spade3 n3)
	(suit spade3 spade)
	(value club2 n2)
	(suit club2 club)
	(canstack club2 diamond3)
	(canstack club2 heart3)
	(value spade2 n2)
	(suit spade2 spade)
	(canstack spade2 diamond3)
	(canstack spade2 heart3)
	(value cluba n1)
	(suit cluba club)
	(canstack cluba diamond2)
	(canstack cluba heart2)
	(value heart3 n3)
	(suit heart3 heart)
	(value heart2 n2)
	(suit heart2 heart)
	(canstack heart2 club3)
	(canstack heart2 spade3)
	(value diamond3 n3)
	(suit diamond3 diamond)
	(value club3 n3)
	(suit club3 club)
	(value diamonda n1)
	(suit diamonda diamond)
	(canstack diamonda club2)
	(canstack diamonda spade2)
	(value diamond2 n2)
	(suit diamond2 diamond)
	(canstack diamond2 club3)
	(canstack diamond2 spade3)
	(value hearta n1)
	(suit hearta heart)
	(canstack hearta club2)
	(canstack hearta spade2)
	(value spadea n1)
	(suit spadea spade)
	(canstack spadea diamond2)
	(canstack spadea heart2)
	(home diamond0)
	(value diamond0 n0)
	(suit diamond0 diamond)
	(home club0)
	(value club0 n0)
	(suit club0 club)
	(home heart0)
	(value heart0 n0)
	(suit heart0 heart)
	(home spade0)
	(value spade0 n0)
	(suit spade0 spade)
)
(:goal (and
	(home diamond3)
	(home club3)
	(home heart3)
	(home spade3)
)))
