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
    int binaryValue, intNumber, intStart, intEnd, regNumber, intBinPartLength;
    String regName, intExpr;

    public InstructionBinPart(int n, int l)
    {
	type = BINNUM;
	binaryValue = n;
	intBinPartLength = l;
	// System.out.println("InstructionBinPart Val="+n+" Len ="+l+" intBinPartLenght= "+intBinPartLength);
    }
    public void addBinNum(int n, int l)
    {
	binaryValue 	 <<= l;
	binaryValue 	 |= n;
	intBinPartLength += l;
	// System.out.println("InstructionBinPart.addBinNum Val="+n+" Len ="+l+" intBinPartLenght= "+intBinPartLength);
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
    public int getLength() 	{ 	
	// System.out.println("InstructionBinPart.getLenght"+intBinPartLength);
	return intBinPartLength; }
    public String toString()
    {
	String tmp = "";
	int mask;
	switch (type)
	    {
	    case INTDESC:  
		mask = (1 << intBinPartLength) - 1;
		if (intStart == 0)
		    {
			tmp = "i"+intNumber+" & "+mask+", "+intBinPartLength;	
		    }
		else
		    {
			tmp = "((i"+intNumber+">>"+intStart+") & "+ mask +"), "+intBinPartLength;
		    }
		break;
	    case INTEXPR:  
		mask = (1 << intBinPartLength) - 1;
		if (intStart == 0)
		    {
			tmp = "(("+intExpr+") & "+mask+"), "+intBinPartLength;
		    }
		else
		    {
			tmp = "((("+intExpr+")>>"+intStart+") & "+ mask +"), "+intBinPartLength;
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