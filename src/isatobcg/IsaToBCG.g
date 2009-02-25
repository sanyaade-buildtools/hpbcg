grammar IsaToBCG; // -*- java -*-
@members{
    public static int main(String argv[])
    {
	return 0;
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


isafile :  	isaline | cpuline;
cpuline : 	ARCHNAME INT;
isaline: 	binpart '|' asmpart ;
asmpart : 	INSN;
binpart : 	INT;
INSN :  	(LETTER)+;
fragment
LETTER: 	('a'..'z'|'A'..'Z');
ARCHNAME : 	('power4' | 'sparc' | 'ia64');
INT : 		('0'..'9')+;

