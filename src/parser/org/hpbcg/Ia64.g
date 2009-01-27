lexer grammar Ia64;   // -*- java -*-
options { k = 2; }
@header{package org.hpbcg;}
@members{
//   lexer class members
    Insn currentInsn = null;
    boolean debug;
    public void myParse(boolean debug) throws antlr.TokenStreamException
    {
	boolean inAsm = true;
	String tmp;
	Token a, b;
	System.out.print("/* Ia64 parser */");
	while (inAsm) 
	{
	    a = nextToken();
	    // System.out.println(a.getType()+":!"+a.getText()+"!");
	    switch  (a.getType())
	    {
	    case Token.EOF: System.exit (0); 		break;
            case EOL: 
                Debug("EOL ");
                ejectInsn();
                Out("\n");
                break;
            case MNEMO:
                ejectInsn();
                currentInsn = new InsnIa64(a.getText());
                break;
            case ENDMULTI: 
                ejectInsn();
                Out("ASM_2_END ");
                inAsm = false;  		
                break;
            case ENDUNI: 
                ejectInsn();
                Out("ASM_1_END ");
                inAsm = false;  		
                break;
            case SEP:                 break;
            case WS:                  break;
            case INTREG:
                Debug("REGISTER I ");
                currentInsn.setParam(a.getText(), Insn.TYPEIREG);
                break;
            case FLTREG:
                Debug("REGISTER F");
                currentInsn.setParam(a.getText(), Insn.TYPEFREG);
                break;
            case BOOREG:
                Debug("REGISTER B");
                currentInsn.setParam(a.getText(), Insn.TYPEBREG);
                break;
            case INT:
                Debug("INTEGER ");
                currentInsn.setParam(a.getText(), Insn.TYPEINT);
                break;
            case STOPBIT:
                Debug("STOP ");
                break;
	    case PROC:
		tmp = a.getText();
		tmp = new String (tmp.getBytes(), 5, tmp.length() - 6);
		Out ("PROC("+tmp+");\n");
		break;
	    case ORG:
		a = nextToken();
		a = nextToken();
		Out ("ORG("+a.getText()+");");
		break;
            case PAROPEN:         
                Debug("PAROPEN");
                currentInsn.setParam(a.getText(), Insn.TYPEINT);
		break;
            default : 
                System.out.println("Surprising token  :!"+a.getText()+"!");
                System.exit(0);
                break;
	    }
	}
	return;
    }
    public void ejectInsn()
    {
        if (null != currentInsn)
        {
          Out(currentInsn.getInsn());
          currentInsn = null;
        }
        else
        {
            if (debug) 
                System.out.println("No defined insn");
        }    
    }        
    public void Debug(String a)
    {
        if (debug)System.out.println(a);
    }
    public void Out(String a)
    {
        System.out.print(a);
    }
}
ENDUNI 	: ']#' ;
ENDMULTI: '}#' ;
STOPBIT	: ';;';
PROC    : '.proc' ( options {greedy=false;} : . )* '\n' ;
ORG     : '.org' ;
SEP 	: (',' | '=' );
INT     : ('+' | '-') ? (NUMBER)+;
WS 	: (' ' |'\t')+;
EOL     : '\n' ;
MNEMO 	: (LETTER) (LETTER | '.')+;
INTREG	: 'r' (NUMBER)+;
BOOREG	: 'b' (NUMBER)+;
FLTREG	: 'f' (NUMBER)+;
PAROPEN : '('  ( options {greedy=false;} : . )* ')' ;

fragment LETTER : ('a'..'z' | 'A'..'Z');
fragment NUMBER : ('0'..'9');
