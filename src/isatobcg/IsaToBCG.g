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
    int ArchLength;
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
    public int btoi(String chaine)
    {
	int tmp = 0;
	for (int i = 1; i < chaine.length(); i++)
	    {
		tmp <<= 1;
		switch (chaine.charAt(i))
		    {
		    case '0': 		break;
		    case '1': tmp += 1; 	break;
		    default: System.out.println("Error : char not in [01] :"+chaine.charAt(i));
			System.exit(-1);
			break;
		    }
	    }
	return tmp;
    } /* btoi */
}

isafile 	: isaline* EOF;
isaline 	: (isaarchlen | isalinedesc | COMMENT | ) NL;
isalinedesc	: isabinpart CUT isaasmpart {	System.out.println("isalinedesc");};
isaarchlen	: ARCHNAME INT 		{System.out.println("archlen");};
isabinpart 	: (BINNUM | INTDESC | REGDESC )+;
isaasmpart 	: INSNNAME paramlist;
paramlist 	: (param)*; 
param 		: (INTNAME | REGNAME);
REGNAME		: REGLETTER (INT)	{System.out.println("REGNAME");};
INTNAME		: 'i' (INT) 		{System.out.println("INTNAME");};
INTDESC         :'i' INT '_' INT '-' INT {System.out.println("INTDESC");};
REGDESC 	:REGLETTER INT '_' INT 	{System.out.println("REGDESC");} ;
INSNNAME	:(LETTER)+ 		{System.out.println("INSNNAME");};
fragment LETTER	: ('a'..'z'|'A'..'Z' | '.') 	{System.out.println("LETTER");};
fragment REGLETTER: ('r' | 'f');
ARCHNAME : 	('power4' | 'sparc' | 'ia64') {System.out.println("ARCHNAME");};
BINNUM :	('0' | '1')+ 		{System.out.println("BINNUM");};
INT 	: 	('0'..'9')+ 		{System.out.println("INT");};
SPACE 	: 	(',' | ' ' | '\t')+ 	{System.out.println("SPACE"); skip();};
NL 	:   	('\n' | '\r')	;
COMMENT: 	'#' (~(NL))*		{System.out.println("COMMENT"); };
CUT    :	'|' 			{System.out.println("CUT");};