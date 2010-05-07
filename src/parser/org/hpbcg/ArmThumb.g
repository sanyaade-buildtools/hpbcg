lexer grammar  ArmThumb;  // -*- java -*-
@header{
    package org.hpbcg;
    import java.util.regex.*;
}
@members{
//   lexer class members</em>
    Insn currentInsn = null;
    boolean debug;
    InsnList ArmThumbList = new InsnList("armthumb");
    Debug dBug = new Debug();
    Pattern regDescriptionPattern = Pattern.compile("r([0-9]+)|(lr)|(pc)|(sp)");
    public void myParse(boolean debug) throws antlr.TokenStreamException
    {
        boolean inAsm = true;        
        Token a;
        this.debug = debug;
        Debug("/* ArmThumb parser */");
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
	    case REGLST:
		int tmp, regMask = 0;
		String regList = a.getText();
		String regName;
		Debug("REGLST:"+regList); 
		Matcher m = regDescriptionPattern.matcher(regList);
		while (m.find())
		    {
			regName = m.group();
			Debug("RegName from regList: "+regName+" : "+regList);
			if ('r' == regName.charAt(0))
			    {
				regMask |= 1 << (regName.charAt(1)-'0');
			    }
			else if (("lr".equals(regName)) || ("pc".equals(regName)))
			    {
				regMask |= 0x100;
			    }
		    }
		Debug("regList code :"+regMask);
		currentInsn.setParam(""+regMask, Insn.TYPEMASKREG); 
		break;
            case ARMREG:
		currentInsn.setParam(a.getText(), Insn.TYPEIREG); 
                break;
            case INT:
                Debug("INTEGER ");
                currentInsn.setParam(a.getText(), Insn.TYPEINT);
                break;
            case INDEX:
		String number, register, token;
		int i;
                Debug("INDEX "+a.getText());
		token = a.getText();
		number = "";
		for (i = 0; '(' != token.charAt(i); i++)
		    number += token.charAt(i);
		i ++ ;
		register = "";
		for (; ')' != token.charAt(i); i++)
		    register += token.charAt(i);
                currentInsn.setParam(number, Insn.TYPEINT);
                currentInsn.setParam(register, Insn.TYPEIREG);
                break;
            case LABEL: 
		String labelName = a.getText();
                currentInsn = new InsnArmThumb();
                currentInsn.setLabel(new String (labelName.getBytes(), 0, labelName.length() - 1));
                ejectInsn();
                break;
            case MNEMO:
		String insnName = a.getText();
		ArmThumbList.verifExistInsn(insnName);
                ejectInsn();
                currentInsn = new InsnArmThumb(insnName);
                break;
            case WS:                  break;
            case ARMREGOPEN:
		switch(a.getText().charAt(0))
		    {
		    case 'r': currentInsn.setParam(a.getText(), Insn.TYPEIREG); break;
		    case 'f': currentInsn.setParam(a.getText(), Insn.TYPEFREG); break;
		    default : System.err.println("Surprising parametric register name :!"+a.getText()+"!"); System.exit(-1); break;
		    }
		break;
            case PAROPEN:         
                currentInsn.setParam(a.getText(), Insn.TYPEINT);
		break;
	    case ORG:
		a = nextToken();
		a = nextToken();
		Out ("ORG("+a.getText()+");");
		break;
            default : 
                System.err.println("Surprising token  :!"+a.getText()+"!");
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
            if (debug) System.err.println("No defined insn");
        }    
    }        
    public void Debug(Token a)
    {
        if (debug)
	    {
		System.out.println(dBug.DebugArmThumb(a.getType()) + ":!" + a.getText() + "!");
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
}

PROC     : '.proc' ;
ORG      : '.org' ;
ENDMULTI : '}#' ;
ENDUNI   : ']#' ;
EOL      : '\n';
WS       : (' ' | '\t' | ',');
INT      : ('+' | '-') ? (NUMBER)+;
// SEP      : ',' ;
INDEX    : (NUMBER)+ '('  ARMREG ')';
LABEL	 : LETTER (LETTER | NUMBER)* ':' ;
REGLST   : '{' (ARMREG) (WS+ ARMREG)* '}';
ARMREG  : ('r'|'f') (NUMBER)+ | 'pc' | 'lr' | 'sp' | '(r' (NUMBER)+ ')';
ARMREGOPEN : ('r'|'f') '('  ( options {greedy=false;} : . )* ')'  ;
PAROPEN  : '('  ( options {greedy=false;} : . )* ')' ;
MNEMO    : LETTER (LETTER)* ;

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

