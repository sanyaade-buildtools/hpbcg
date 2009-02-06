lexer grammar  Cell;  // -*- java -*-
@header{package org.hpbcg;}
@members{
//   lexer class members</em>
    Insn currentInsn = null;
    boolean debug;
    public void myParse(boolean debug) throws antlr.TokenStreamException
    {
        boolean inAsm = true;        
        Token a;
        this.debug = debug;
        Debug("/* Cell parser */");
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
            case CELLREG:
                Debug("REGISTER ");
                currentInsn.setParam(a.getText(), Insn.TYPEIREG);
                break;
            case INT:
                Debug("INTEGER ");
                currentInsn.setParam(a.getText(), Insn.TYPEINT);
                break;
            case INDEX:
                Debug("INDEX ");
                currentInsn.setParam(a.getText(), Insn.TYPEIDXREG);
                break;
            case MNEMO:
                ejectInsn();
                currentInsn = new InsnCell(a.getText());
                break;
            case SEP:                 break;
            case WS:                  break;
            case CELLREGOPEN:         
                Debug("CELLREGOPEN");
                currentInsn.setParam(a.getText(), Insn.TYPEIREG);
		break;
            case PAROPEN:         
                Debug("PAROPEN");
                currentInsn.setParam(a.getText(), Insn.TYPEINT);
		break;
	    case ORG:
		a = nextToken();
		a = nextToken();
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
        if (debug)System.out.println(a);
    }
    public void Out(String a)
    {
        System.out.print(a);
    }
}

PROC     : '.proc' ;
ORG      : '.org' ;
ENDMULTI : '}#' ;
ENDUNI   : ']#' ;
EOL      : '\n';
WS       : (' ' | '\t');
INT      : ('+' | '-') ? (NUMBER)+;
SEP      : ',' ;
INDEX    : (NUMBER)+ '('  CELLREG ')';
MNEMO    : LETTER (LETTER | NUMBER)* ;
CELLREG  : '$' (NUMBER)+ | '$lr' | '$sp' | '($' (NUMBER)+ ')';
CELLREGOPEN : '$('  ( options {greedy=false;} : . )* ')' ;
PAROPEN  : '('  ( options {greedy=false;} : . )* ')' ;

fragment LETTER : ('a'..'z' | 'A'..'Z');
fragment NUMBER : ('0'..'9');
// NUL SOH STX ETX EOT ENQ ACK BEL BS HT NL VT NP CR SO SI DLE DC1
// DC2 DC3 DC4 NAK SYN ETB CAN EM SUB ESC FS GS RS US
// SP !  "  # $ % & ' ( ) * + , - .  /
// 0 1 2 3 4 5 6 7 8 9
// : ; < = > ? @
// A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
// [ \ ] ^ _ `
// a b c d e f g h i j k l m n o p q r s t u v w x y z
// { | } ~ DEL

