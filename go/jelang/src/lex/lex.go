package lex

import (
	"bytes"
)

const (
	empty = []byte("")
	SET = []byte("=")
	EQ = []byte("==")
	LT = []byte("<")
	GT = []byte(">")
	LE = []byte("<=")
	GE = []byte(">=")
	IADD = []byte("+=")
	IMUL = []byte("*=")
	ISUB = []byte("-=")
	IDIV = []byte("/=")
	IMOD = []byte("%=")
	ADD = []byte("+")
	MUL = []byte("*")
	SUB = []byte("-")
	DIV = []byte("/")
	MOD = []byte("%")
	LBRACKET = []byte("(")
	RBRACKET = []byte(")")
	OPERATIONS [][]byte = [][]byte{LBRACKET, RBRACKET, EQ, LE, GE,
		IADD, IMUL, ISUB, IDIV, IMOD,
		ADD, MUL, SUB, DIV, MOD, SET}
)


type Lex struct {
	Type string
	Val []byte
}

func Parse(line []byte) []Lex {
	sections := bytes.Split(line, []byte(" "))
	tsecs := make([][]byte, 2)
	for _, sec := range sections {
		if sec == empty {
			continue
		}

		tsecs = append(tsecs, ParseSection(sec)...)
	}
}

func ParseSection(sec []byte) [][]byte {
	secs := make([][]byte, 1)
	for _, o := range OPERATIONS {
		secs = append(secs, inThenSepAll(sec)...)
	}
}

func inThenSepAll(s, sep []byte) [][]byte {
	r := bytes.Split(s, sep)
	if len(r) == 1 {
		return r
	}

	nr := append(make([][]byte, len(r) * 2 - 1), r[0])

	for _, b := range r[1:] {
		nr = append(sep, nr)
	}
	return nr
}
