class InstructionBinPart
{
    static final int INTDESC = 1;
    static final int REGDESC = 2;
    static final int BINNUM  = 3;
    int type;
    char typeLetter;
    int binaryValue, binaryValueLength;
    int intNumber, intStart, intEnd;
    String regName; int regNumber, regSize;

    public InstructionBinPart(int n, int l)
    {
	type = BINNUM;
	binaryValue = n;
	binaryValueLength = l;
    }

    public InstructionBinPart(int number, int start, int end)
    {
	type = INTDESC;
	intNumber = number;
	intStart = start;
	intEnd = end;
    }

    public InstructionBinPart (String name, int number, int size)
    {
	type = REGDESC;
	regName = name;
	regNumber = number;
	regSize = size;
    }

    public int getType() { return type; }

    public String toString()
    {
	String tmp = "";
	switch (type)
	    {
	    case INTDESC:  tmp = "i"+intNumber+" from  "+intStart+" to "+intEnd;	break;
	    case BINNUM:   tmp =  ""+binaryValue+"("+binaryValueLength+")";  	break;
	    case REGDESC:  tmp =  "r"+regName+regNumber+"("+regSize+")";  	break;
	    default: System.err.println ("Error InstructionBinPart not known"); 
		System.exit(0);
		break;
	    }
	return tmp+"\n";
    } /* toString */

}