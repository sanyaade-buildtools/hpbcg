class InstructionAsmPart
{
    static final int REGNAME = 1;
    static final int INTNAME = 2;
    int type;
    char typeLetter;
    int intNumber;
    String regName;

    public InstructionAsmPart(String register)
    {
	type = REGNAME;
	typeLetter = register.charAt(0);
	regName = register;
    }

    public InstructionAsmPart(int number)
    {
	type = INTNAME;
	typeLetter = 'i';
	intNumber = number;
    }
    public char getTypeLetter() { return typeLetter; }
    public int getType()   { return type; }

    public String toString()
    {
	String tmp = "";
	switch (type)
	    {
	    case REGNAME:   tmp = regName;		break;
	    case INTNAME:   tmp = ""+intNumber;  	break;
	    default: System.err.println ("Error InstructionAsmPart not known"); 
		System.exit(0);
		break;
	    }
	return tmp;
    } /* toString */
}