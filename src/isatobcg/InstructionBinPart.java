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
    int intBinPartLenght;
    String regName; int regNumber;
    String intExpr;

    public InstructionBinPart(int n, int l)
    {
	type = BINNUM;
	binaryValue = n;
	intBinPartLenght = l;
    }
    public void addBinNum(int n, int l)
    {
	binaryValue 	 <<= l;
	binaryValue 	 |= n;
	intBinPartLenght += l;
    }

    public InstructionBinPart(int number, int start, int end)
    {
	type = INTDESC;
	intNumber = number;
	intStart = start;
	intEnd = end;
	intBinPartLenght = intEnd-intStart+1;
    }
    public InstructionBinPart(String expression, int start, int end, int zero)
    {
	type = INTEXPR;
	intExpr = expression;
	intStart = start;
	intEnd = end;
	intBinPartLenght = intEnd-intStart+1;
    }
    public InstructionBinPart (String name, int number, int size)
    {
	// System.out.println(name+":"+number+":"+size);
	type = REGDESC;
	regName = name;
	regNumber = number;
	intBinPartLenght = size;
    }


    public int getType() 	{ return type; }
    public int getLength() 	{ return intBinPartLenght; }
    public String toString()
    {
	String tmp = "";
	long dummy;
	switch (type)
	    {
	    case INTDESC:  
		dummy = 0;
		for (int i = intStart; i <= intEnd ; ++i)
			dummy |= ((long) 1 << i);
		tmp = "i"+intNumber+" & "+ dummy+", "+intBinPartLenght;			break;
	    case INTEXPR:  
		dummy = 0;
		for (int i = intStart; i <= intEnd ; ++i)
			dummy |= ((long) 1 << i);
		tmp = "("+intExpr+") & "+ dummy+", "+intBinPartLenght;		break;
	    case BINNUM:   tmp =  binaryValue+","+intBinPartLenght;  			break;
	    case REGDESC:  tmp =  regName+regNumber+","+intBinPartLenght;  		break;
	    default: System.err.println ("Error InstructionBinPart not known"); 
		System.exit(0);
		break;
	    }
	return "LENOK("+tmp+")";
    } /* toString */
}