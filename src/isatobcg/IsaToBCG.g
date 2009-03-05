grammar IsaToBCG; // -*- java -*-
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
	    ANTLRInputStream input = new ANTLRInputStream (System.in);
	    IsaToBCGLexer l = new IsaToBCGLexer(input);
	    CommonTokenStream tokens = new CommonTokenStream(l);
	    IsaToBCGParser p = new IsaToBCGParser(tokens);
	    p.isafile();
	}
        catch (Exception e)
	{
	    e.printStackTrace(System.out);
	}
    }
    public static CharStream getInput(String argv[]) 
	throws java.io.FileNotFoundException,
	java.io.IOException
    {
	int i;
	CharStream inFile = null;
	
	for (i = 0; i < argv.length; i++)
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
		inFile = new ANTLRFileStream(argv[i]);
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

isafile 	: 	isaline* EOF;
isaline 	: 	isabinpart CUT isaasmpart ;
isabinpart 	: 	(BINNUM | INTDESC | REGDESC )+;
isaasmpart 	: 	INSNNAME reglist;
reglist 	: 	REGNAME | REGNAME reglist;
fragment REGNAME:	('r'| 'f') (INT)	{System.out.println("REGNAME");};
fragment INTNAME:	'i_' (INT) 		{System.out.println("INTNAME");};
fragment INTDESC :	'i' INT '_' INT '-' INT {System.out.println("INTDESC");};
fragment REGDESC :	'r' INT '_' INT 	{System.out.println("REGDESC");} ;
fragment INSNNAME:  	(LETTER)+ 		{System.out.println("INSNNAME");};
fragment LETTER	: 	('a'..'z'|'A'..'Z') 	{System.out.println("LETTER");};
fragment ARCHNAME : 	('power4' | 'sparc' | 'ia64') {System.out.println("ARCHNAME");};
fragment BINNUM :	('0' | '1')+ 		{System.out.println("BinNum");};
fragment INT 	: 	('0'..'9')+ 		{System.out.println("INT");};
fragment SPACE 	: 	(' ' | '\t') 		{System.out.println("SPACE"); skip();};
fragment NL 	:   	('\n' | '\r')		;
fragment COMMENT: 	'#' (~(NL))* 		{System.out.println("COMMENT"); skip();};
fragment CUT    :	'|' 			{System.out.println("CUT");};