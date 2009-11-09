lexer grammar C; // -*- java -*-
options { k = 2; }
@header{package org.hpbcg;}
@members{
    public void pCpu (String a)
    {
        System.out.print("#include <hpbcg-"+a+".h> /* #cpu "+a+"*/");
    }
    public String myParse (boolean debug) throws antlr.TokenStreamException
    {
	boolean inC = true;
	Token a, b, c;
	String currentArch = null;
	// System.out.println("C parser");
	while (inC) 
	{
	    a = nextToken();
	    switch  (a.getType())
		{
		case Token.EOF: System.exit (0); break;
		case STARTUNI:   
		    inC = false; 
		    System.out.print("ASM_1_BEGIN "); 
		    break;
		case STARTMULTI: 
		    inC = false; 
		    System.out.print("ASM_2_BEGIN "); 
		    break;
		case CPU:
		    b = nextToken();
		    c = nextToken();
		    currentArch = c.getText();
		    pCpu (currentArch);
		    break;
		default : System.out.print(a.getText()); break;
		}
	}
	return currentArch;
    }

}

CPU       : '#cpu' ;
STARTMULTI: '#{' ;
STARTUNI  : '#[' ;
WS        : (' '| '\n'|'\t');
OTHERCHAR : '!'.. '/' | 
            ':'..'@'  | 
            '['..']'  | 
            '{' .. '~'| 
            '0'..'9'  |
            '\u0080'..'\u00FF';
WORD: ('_' |'a'..'z'|'A'..'Z')  ('_'|'a'..'z'|'A'..'Z'|'0'..'9')*;
