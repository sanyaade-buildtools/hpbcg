lexer grammar Ia64;   // -*- java -*-
options { k = 2; }
@header{
    package org.hpbcg;
    import java.util.regex.*;
}
@members{
//   lexer class members
    InsnIa64 currentInsn = null;
    boolean debug;
    InsnList ia64List = new InsnList("ia64");
    Debug dBug = new Debug();
    public void myParse(boolean debug) throws antlr.TokenStreamException
    {
	boolean inAsm = true;
	String tmp;
	Token a, b;
        this.debug = debug;
	Debug("/* Ia64 parser */");
	while (inAsm) 
	{
	    a = nextToken();
	    Debug(a);
	    switch  (a.getType())
	    {
	    case Token.EOF: System.exit (0); 		break;
            case EOL: 
                ejectInsn();
                Out("\n");
                break;
            case PAROPEN:         
		if (! Pattern.matches("\\(p[0-9]+\\)", a.getText()))
		{
		    Debug("PAROPEN INT");
		    currentInsn.setParam(a.getText(), Insn.TYPEINT);
		}
		else
		{
		    Debug("PAROPEN Predicate");
		    ejectInsn();
		    b = nextToken();
		    b = nextToken();
		    Debug(a);
		    currentInsn = new InsnIa64(b.getText(), a.getText());
		}
		break;
            case MNEMO:	
		String insnName = a.getText();
		if (insnName.equals("ar.pfs"))
		{
		    Debug ("REG Application Register : " + insnName);
		    currentInsn.setParam(insnName, Insn.TYPEARREG);
		}
		else
		{
		    Debug ("MNEMONIC : " + insnName);
		    ia64List.verifExistInsn(insnName);
		    ejectInsn();
		    currentInsn = new InsnIa64(insnName);
		}
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
		currentInsn.setParam(a.getText(), Insn.TYPEIREG);
                break;
            case IAREGOPEN:
		currentInsn.setParam(a.getText(), Insn.TYPEIREG);
                break;
            case FLTREG:
                currentInsn.setParam(a.getText(), Insn.TYPEFREG);
                break;
            case BOOREG:
                currentInsn.setParam(a.getText(), Insn.TYPEPREG);
                break;
            case BRREG:
                currentInsn.setParam(a.getText(), Insn.TYPEBREG);
                break;
            case INT:
                currentInsn.setParam(a.getText(), Insn.TYPEINT);
                break;
            case STOPBIT:
                currentInsn.setStop();
                break;
	    case PROC:
		tmp = a.getText();
		tmp = new String (tmp.getBytes(), 5, tmp.length() - 6);
		Out ("PROC("+tmp+");\n");
		break;
	    case ORG:
		a = nextToken();
		a = nextToken();
		Debug (a);
		Out ("ORG("+a.getText()+");");
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
        if (debug) System.out.println(a);
    }
    public void Debug(Token a)
    {
        if (debug)
	    {
		System.out.println(dBug.DebugIa64(a.getType()) + ":!" + a.getText() + "!");
	    }
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
INT     : (('+' | '-') ? (NUMBER)+ | '0x' (HEXNUMBER)+ );
WS 	: (' ' |'\t')+;
EOL     : '\n' ;
MNEMO 	: (LETTER) (LETTER | '.')+ (NUMBER)?;
INTREG	: 'r' (NUMBER)+ ;
BRREG	: 'b' (NUMBER)+;
BOOREG	: 'p' (NUMBER)+;
FLTREG	: 'f' (NUMBER)+;
IAREGOPEN:'r('  ( options {greedy=false;} : . )* ')' ;
PAROPEN : '('  ( options {greedy=false;} : . )* ')' ;

fragment LETTER : ('a'..'z' | 'A'..'Z');
fragment NUMBER : ('0'..'9');
fragment HEXNUMBER : ('0'..'9' | 'A' .. 'F' | 'a' .. 'f' );
