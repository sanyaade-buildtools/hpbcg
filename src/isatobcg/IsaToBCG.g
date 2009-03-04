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
	String tmp;
	CharStream in;
        try 
	{
	    in = getInput (args);
	    IsaToBCGLexer l = new IsaToBCGLexer(in);
	    CommonTokenStream tokens = new CommonTokenStream();
	    tokens.setTokenSource(l);
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

isafile 	: 	isaline+ EOF;
isaline 	: 	isabinpart CUT isaasmpart ;
isabinpart 	: 	(BINNUM | INTDESC | REGDESC )+;
isaasmpart 	: 	INSNNAME reglist;
reglist 	: 	REGNAME | REGNAME reglist;
fragment REGNAME:	('r'| 'f') (INT);
fragment INTNAME:	'i_' (INT);
fragment INTDESC :	'i' INT '_' INT '-' INT;
fragment REGDESC :	'r' INT '_' INT; 
fragment INSNNAME:  	(LETTER)+;
fragment LETTER	: 	('a'..'z'|'A'..'Z');
fragment ARCHNAME : 	('power4' | 'sparc' | 'ia64');
fragment BINNUM :	('0' | '1')+ {System.out.println("BinNum"); };
fragment INT 	: 	('0'..'9')+;
fragment SPACE 	: 	(' ' | '\t') {skip();} ;
fragment NL 	:   	('\n' | '\r');
fragment COMMENT: 	'#' (~(NL))* {	System.out.println("Comment");skip();} ;
fragment CUT    :	'|';