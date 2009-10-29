lexer grammar X86; // -*- java -*-

@header{
    package org.hpbcg;
    import java.util.regex.*;
}
@members{
    InsnX86 currentInsn = null;
    boolean debug;
    InsnList x86List = new InsnList("x86");
    Debug dBug = new Debug();
    public void myParse(boolean debug) throws antlr.TokenStreamException
    {
	String tmp;
	boolean inAsm = true;
	Token a, b;
	this.debug = debug;
	Debug("/* x86 parser */");
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
		    case X86REG:
			currentInsn.setParam (a.getText(), Insn.TYPEIREG);
			break;
		    case MNEMO:
			ejectInsn();
			x86List.verifExistInsn(a.getText());
			currentInsn = new InsnX86(a.getText());
			break;
		    case SEP:                 break;
		    case WS:                  break;
		    case PAROPEN:     	      
			tmp = a.getText();
			tmp = new String (tmp.getBytes(), 1, tmp.length() - 2);
			currentInsn.setParam (tmp, Insn.TYPEIREG);
			break;
		    case INT:		
			currentInsn.setParam (a.getText(), Insn.TYPEINT);
			break;
		    case CONST:	
			tmp = a.getText();
			tmp = new String (tmp.getBytes(), 1, tmp.length() - 1);
			currentInsn.setParam (tmp, Insn.TYPEINT);
			break;
		    case CONSTVAR:	
			tmp = a.getText();
			tmp = new String (tmp.getBytes(), 2, tmp.length() - 3);
			currentInsn.setParam (tmp, Insn.TYPEINT);
			break;
		    case ORG:
			a = nextToken();
			a = nextToken();
			Out ("ORG("+a.getText()+");");
			break;
		    case PROC:
			tmp = a.getText();
			tmp = new String (tmp.getBytes(), 5, tmp.length() - 6);
			Out ("PROC("+tmp+");\n");
			break;
		    default : 
			System.out.println("Surprising token  :!"+a.getText()+":"+a.getType()+"!");
			System.exit(0);
			break;
		    }
	    }
    }
    public void Debug(Token a)
    {
        if (debug)
	    {
		System.out.println(dBug.DebugX86(a.getType()) + ":!" + a.getText() + "!");
	    }
    }
    public void Debug(String a)
    {
        if (debug) System.out.println(a);
    }
    public void Out(String a)
    {
        System.out.print(a);
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
}

ENDUNI 	: ']#' ;
ENDMULTI: '}#' ;
PROC    : '.proc' ( options {greedy=false;} : . )* '\n' ;
ORG     : '.org' ;
SEP 	: (',' | '=' );
INT     : ( (NUMBER)+ | '0x' (HEXNUMBER)+ );
CONST   : '$0x' (HEXNUMBER)+ ;
CONSTVAR: '$(' ( options {greedy=false;} : . )* ')' ;
WS 	: (' ' |'\t')+;
EOL     : '\n' ;
X86REG	: '%' (LETTER)+;
MNEMO 	:     (LETTER)+ ;
PAROPEN : '('  ( options {greedy=false;} : . )* ')' ;

fragment LETTER : ('a'..'z' | 'A'..'Z');
fragment NUMBER : ('0'..'9');
fragment HEXNUMBER : ('0'..'9' | 'A' .. 'F' | 'a' .. 'f' );
