// This file is part of HPBCG
// Binary description part of an asm instruction

class InstructionBinPart
{
    static final int INTDESC = 1;
    static final int REGDESC = 2;
    static final int BINNUM  = 3;
    static final int INTEXPR  = 4;
    int type;
    char typeLetter;
    int binaryValue;
    int intNumber, intStart, intEnd;
    int intBinPartLength;
    String regName; int regNumber;
    String intExpr;

    public InstructionBinPart(int n, int l)
    {
	type = BINNUM;
	binaryValue = n;
	intBinPartLength = l;
    }
    public void addBinNum(int n, int l)
    {
	binaryValue 	 <<= l;
	binaryValue 	 |= n;
	intBinPartLength += l;
    }

    public InstructionBinPart(int number, int start, int end)
    {
	type = INTDESC;
	intNumber = number;
	intStart = start;
	intEnd = end;
	intBinPartLength = intEnd-intStart+1;
	// System.out.println("IntDesc : start:"+start+" end:"+end+" len:"+intBinPartLength);
    }
    public InstructionBinPart(String expression, int start, int end, int zero)
    {
	type = INTEXPR;
	intExpr = expression;
	intStart = start;
	intEnd = end;
	intBinPartLength = intEnd-intStart+1;
    }
    public InstructionBinPart (String name, int number, int size)
    {
	// System.out.println(name+":"+number+":"+size);
	type = REGDESC;
	regName = name;
	regNumber = number;
	intBinPartLength = size;
    }

    public int getType() 	{ return type; }
    public int getLength() 	{ return intBinPartLength; }
    public String toString()
    {
	String tmp = "";
	switch (type)
	    {
	    case INTDESC:  
		if (intStart == 0)
		    tmp = "i"+intNumber+", "+intBinPartLength;	
		else
		    {
			int mask;
			mask = (1 << intBinPartLength) - 1;
			tmp = "((i"+intNumber+">>"+intStart+") & "+ mask +"), "+intBinPartLength;
		    }
		break;
	    case INTEXPR:  
		if (intStart == 0)
		    tmp = "("+intExpr+"), "+intBinPartLength;
		else
		    {
			int mask;
			mask = (1 << intBinPartLength) - 1;
			tmp = "(("+intExpr+">>"+intStart+") & "+ mask +"), "+intBinPartLength;
		    }
		break;
	    case BINNUM:   tmp =  binaryValue+","+intBinPartLength;  			break;
	    case REGDESC:  tmp =  regName+regNumber+","+intBinPartLength;  		break;
	    default: System.err.println ("Error InstructionBinPart not known"); 
		System.exit(0);
		break;
	    }
	return "LENOK("+tmp+")";
    } /* toString */
}