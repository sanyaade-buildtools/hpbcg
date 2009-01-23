lexer grammar Ia64;   // -*- java -*-
options { k = 2; }
@header{package org.hpbcg;}
@members{
//   lexer class members
    public void myParse(boolean debug) throws antlr.TokenStreamException
    {
	boolean inAsm = true;
    Token a;
	System.out.print("/* Ia64 parser */");
	while (inAsm) 
	{
	    a = nextToken();
	    // System.out.println(a.getType()+":!"+a.getText()+"!");
	    switch  (a.getType())
	    {
	    case Token.EOF: System.exit (0); 		break;
	    case END: inAsm = false;  		break;
	    default : System.out.print(a.getText()); 		break;
	    }
	}
	return;
    }
}
END : '}#' | ']#' ;
SEP : ',';
EQ : '=';
WS : (' '| '\n'|'\t');
MNEMO : ('a'..'z')+;
INTREG: '$r' ('0'..'9')+;
FLTREG: '$f' ('0'..'9')+;

