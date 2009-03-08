grammar IsaToBCG; // -*- java -*-
@header
{
    import java.io.*;
}
@members{
    static boolean OptionDebug;
    static int OptionAction;
    static int OPTMACROS = 1;
    static int OPTLIST = 2;
    static int OPTVALID = 3;
    String ArchName;
    int ArchLenght;
    static InstructionsList iList = new InstructionsList();
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
		case 'm': OptionAction = OPTMACROS; break;
		case 'l': OptionAction = OPTLIST; break;
		case 'v': OptionAction = OPTVALID;  break;
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

isafile 	: isaline* EOF {System.out.println(iList);};
isaline 	: (isaarchlen | isalinedesc | COMMENT | ) NL;
isalinedesc	: isabinpart CUT isaasmpart  {iList.addInstruction();};
isaarchlen	: ARCHNAME INT 	 	{ iList.setNameAndLenght($ARCHNAME.getText(), Integer.parseInt($INT.getText()));};
isabinpart 	: (binnum | intdescr | regdescr)+;
binnum 		: BINNUM  		{ iList.addBinaryNumber  ($BINNUM.getText());		};
intdescr 	: INTDESCR 		{ iList.addBinaryIntDescr($INTDESCR.getText());		};
regdescr 	: REGDESCR	 	{ iList.addBinaryRegDescr($REGDESCR.getText());		};
INTDESCR        : 'i' l=INT '_' s=INT '-' e=INT 						;
REGDESCR	: REGLETTER n=INT '_' s=INT							;
isaasmpart 	: INSNNAME paramlist 	{ iList.addName($INSNNAME.getText());			};
paramlist 	: (param)*									;
param 		: (intname | regname)								;
regname		: REGNAME		{ iList.addAsmReg($REGNAME.getText());			};
intname		: INTNAME		{ iList.addAsmInt($INTNAME.getText());			};
REGNAME		: REGLETTER (INT) 				;
INTNAME		: 'i' (INT)					;
INSNNAME	: (LETTER)+ 					;
fragment LETTER	: ('a'..'z'|'A'..'Z' | '.') 			;
fragment REGLETTER: ('r' | 'f')					;
ARCHNAME 	: ('power4' | 'sparc' | 'ia64' | 'cell') 	;
BINNUM 		: ('0' | '1')+ 					;
INT 		: ('0'..'9')+ 					;
SPACE 		: (',' | ' ' | '\t')+ 	{ skip(); 	}	;
NL 		: ('\n' | '\r')					;
COMMENT		: '#' (~(NL))*					;
CUT    		: '|' 						;
