grammar IsaToBCG; // -*- java -*-
@header
{
    import java.io.*;
}
@members{
    static boolean OptionDebug;
    static int OptionAction;
    static int MACROS = 1;
    static int LIST = 2;
    static int VALID = 3;
    String ArchName;
    int ArchLenght;
    InstructionsList iList;
    public static void main(String[] args) 
    {
        try 
	{
	    ANTLRInputStream  input  = getInput (args);
	    IsaToBCGLexer     l      = new IsaToBCGLexer(input);
	    CommonTokenStream tokens = new CommonTokenStream(l);
	    IsaToBCGParser    p      = new IsaToBCGParser(tokens);
	    p.isafile();
	}
	catch (FileNotFoundException e)
	{
	    System.err.println("File not found");
        }
	catch (Exception e)
	{
	    e.printStackTrace(System.out);
	}
    }
    public static ANTLRInputStream getInput(String argv[]) 
	throws java.io.FileNotFoundException,
	java.io.IOException
    {
	ANTLRInputStream  inFile = null;
	
	for (int i = 0; i < argv.length; i++)
	{
	    if ('-' == argv[i].charAt(0))
		switch (argv[i].charAt(1))
		{
		case 'd': OptionDebug = true; break;
		case 'm': OptionAction = MACROS; break;
		case 'l': OptionAction = LIST; break;
		case 'v': OptionAction = VALID;  break;
		default:  System.out.println("IsaToBCG -[m|v|d] [File.isa]\n");
		    System.exit(0);
		}
	    else
		inFile = new ANTLRInputStream(new FileInputStream(argv[i]));
	}
	if (null == inFile) 
	    return new ANTLRInputStream(System.in);
	else
	    return inFile;
    }
    void errMsg(String msg)
    {
	System.err.println(msg);
    } /* errMsg */
}

isafile 	: isaline* EOF {System.out.println(iList);;};
isaline 	: (isaarchlen | isalinedesc | COMMENT | ) NL;
isalinedesc	: isabinpart CUT isaasmpart  {iList.addInstruction();};
isaarchlen	: ARCHNAME INT 	{iList = new InstructionsList($ARCHNAME.getText(), Integer.parseInt($INT.getText()));};
isabinpart 	: (binnum | intdesc | regdesc)+;
binnum 		: BINNUM  		{ iList.addBinaryNumber  ( $BINNUM.getText());		};
intdesc 	: INTDESC 		{ iList.addBinaryIntDescr($INTDESC.getText());		};
regdesc 	: REGDESC 		{ iList.addBinaryRegDescr($REGDESC.getText());		};
isaasmpart 	: INSNNAME paramlist 	{ iList.addName($INSNNAME.getText());			};
paramlist 	: (param)*			;
param 		: (intname | regname)		;
regname		: REGNAME		{ iList.addAsmReg($REGNAME.getText());};
intname		: INTNAME		{ iList.addAsmInt($INTNAME.getText());			};
REGNAME		: REGLETTER (INT) ;
INTNAME		: 'i' (INT);
INTDESC         : 'i' INT '_' INT '-' INT 	;
REGDESC 	: REGLETTER INT '_' INT 	;
INSNNAME	: (LETTER)+ ;
fragment LETTER	: ('a'..'z'|'A'..'Z' | '.') 	;
fragment REGLETTER: ('r' | 'f')			;
ARCHNAME 	: ('power4' | 'sparc' | 'ia64' | 'cell') ;
BINNUM 		: ('0' | '1')+ 			;
INT 		: ('0'..'9')+ 			;
SPACE 		: (',' | ' ' | '\t')+ 	{ skip(); 	};
NL 		: ('\n' | '\r')			;
COMMENT		: '#' (~(NL))*			;
CUT    		: '|' 				;
