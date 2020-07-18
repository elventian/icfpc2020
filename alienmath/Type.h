#ifndef TYPE_H
#define TYPE_H

enum class Type
{
	Nil, // #28
	Int,
	List, // Calculated (merged) result of one or multiple chained Cons

	// g: contained in galaxy.txt
	// ng: not contained in galaxy.txt
	Successor, // #5, inc, ng
	Predecessor, // #6, dec, ng
	Sum, // #7, add, g
	Product, // #9, mul, g
	IntDivision, // #10, div, g
	Equality, // #11, eq, g
	True, // #11 #21, t, g
	False, // #11, #22, f, ng
	Less, //#12, lt, g
	Modulate, // #13, mod, ng
	Demodulate, // #14, dem, ng
	Send, // #15, send, ng
	Negate, // #16, neg, g
	CombS, // #18, s, g
	CombC, // #19, c, g
	CombB, // #20, b, g
	Power2, // #23, pwr2, ng
	CombI, // #24, i, g
	Cons, // #25, cons, g
	Car, // #26, car, g
	Cdr, // #27, cdr, g
	IsNil, // #29, isnil, g
	Draw, // #32, draw, ng
	Checkerboard, // #33, checkerboard, ng
	MultipleDraw, // #34, multipledraw, ng
	Send0, // #36, send ( 0 ), ng
	Is0, // #37, if0, ng
	F38, // #38, f38, ng
	Interact, // #38 #39, interact, ng
	StatelessDraw, // #40, statelessdraw, ng
	StatefulDraw, // #41, :67108929, ng
	Galaxy, // #42, galaxy, g

	// ToLinear -> Modulate
	// ToGlyph -> Demodulate
	// F18,
	// Flip,
	// F20,
	// Id,
	// F28,

	// Types for symbols parsing follow
	Invalid, // Type parsing failed
	Apply,
	Variable,
	Statement, // PropositionalEquality
	ParsedNode,
};

#endif // TYPE_H
