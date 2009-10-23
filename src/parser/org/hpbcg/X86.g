lexer grammar X86; // -*- java -*-

@header{
    package org.hpbcg;
    import java.util.regex.*;
}
@members{
    InsnX86 currentInsn = null;
    boolean debug;
    InsnList x86List = new InsnList("x86");
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
		System.out.println(a.getType()+":!"+a.getText()+"!");
		switch  (a.getType())
		    {
		    case Token.EOF: System.exit (0); 		break;
		    case EOL: 
			Debug("EOL ");
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
		    case REG:           Debug("Reg : "+a.getText());      break;
		    case MNEMO: 	Debug("Mnemo : "+a.getText());    break;
		    case SEP:                 break;
		    case WS:                  break;
		    case PAROPEN:     Debug("PAROPEN :"+a.getText()); break;
		    case INT:
			Debug("INT : " + a.getText());
			// currentInsn.setParam(a.getText(), Insn.TYPEINT);
			break;
		    case ORG:
			a = nextToken();
			a = nextToken();
			Debug ("Org :"+ a.getText());
			Out ("ORG("+a.getText()+");");
			break;
		    case PROC:
			Debug ("Proc : "+ a.getText());
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
WS 	: (' ' |'\t')+;
EOL     : '\n' ;
    REG	: '%' (LETTER)+;
MNEMO 	:     (LETTER)+ ;
PAROPEN : '('  ( options {greedy=false;} : . )* ')' ;

fragment LETTER : ('a'..'z' | 'A'..'Z');
fragment NUMBER : ('0'..'9');
fragment HEXNUMBER : ('0'..'9' | 'A' .. 'F' | 'a' .. 'f' );
