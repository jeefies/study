package lex

import "testing"

func TestLex1(t *testing.T) {
	words := []byte("1 = 1")

	lexes := Parse(words)

	lex0 := lexes[0]
	if lex0.Type != "num" && lex0.Val != []byte("1") {
		t.Error("Parse Num Error")
	}

	lex1 := lexes[1]
	if lex1.Type != "set" && lex1.Val != []byte("=") {
		t.Error("Parse Set Error")
	}

	lex2 := lexes[2]
	if lex2.Type != "num" && lex1.Val != []byte("1") {
		t.Error("Parse Num Error")
	}
}
