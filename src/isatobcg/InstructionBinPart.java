// This file is part of HPBCG
// Binary description part of an asm instruction

class InstructionBinPart
{
    static final int INTDESC = 1;
    static final int REGDESC = 2;
    static final int BINNUM  = 3;
    static final int INTEXPR = 4;
    int  type;
    char typeLetter;
    int  binaryValue, intNumber, intStart, intEnd, regNumber, intBinPartLength;
    String regName, intExpr;
    boolean debug = false;

    public InstructionBinPart(int theType, int n, int l)
    {
	type = theType;
	binaryValue = n;
	intBinPartLength = l;
	debug (getTypeName (theType)+":"+n+" l:"+l+" len:"+intBinPartLength);
    }
    public void addBinNum(int n, int l)
    {
	if (type != BINNUM)
	    {
		error("addBinNum to a not binNumObj");
	    }
	binaryValue 	 <<= l;
	binaryValue 	 |= n;
	intBinPartLength += l;
	debug (getTypeName (type)+":"+n+" l:"+l+" len:"+intBinPartLength);
    }
    public InstructionBinPart(int theType, int number, int start, int end)
    {
	type = theType;
	switch (type)
	    {
	    case INTEXPR:  	
		intNumber = number;
		intStart = start;
		intEnd = end;
		break;
	    case INTDESC:  	
		intNumber = number;
		intStart = start;
		intEnd = end;
		break;
	    default:
		error("Type: "+getTypeName (type)+" not recognized in InstructionBinPart" );
		break;
	    }
	intBinPartLength = intEnd - intStart+1;
	debug (getTypeName (theType)+":"+number+" start:"+start+" end:"+end+" len:"+intBinPartLength);
    }
    public InstructionBinPart(int theType, String expression, int start, int end)
    {
	type = theType;
	switch (type)
	    {
	    case INTEXPR:  	
		intExpr = expression;
		intStart = start;
		intEnd = end;
		intBinPartLength = intEnd - intStart + 1;
		break;
	    case REGDESC:
		regName = expression;
		regNumber = start;
		intBinPartLength = end;
		break;
	    default:
		error("Type: "+getTypeName (type)+" not recognized in InstructionBinPart" );
		break;
	    }
	debug (getTypeName (theType)+":"+expression+" start:"+start+" end:"+end+" len:"+intBinPartLength);
    }
    public InstructionBinPart(int theType, String expression, int num, int start, int end)
    {
	type = theType;
	switch (type)
	    {
	    case REGDESC:
		regName = expression;
		regNumber = num;
		intStart = start;
		intEnd = end;
		break;
	    case INTEXPR:  	
		intExpr = expression;
		intStart = start;
		intEnd = end;
		break;
	    default:
		error("Type: "+getTypeName (type)+" not recognized in InstructionBinPart" );
		break;
	    }
	intBinPartLength = intEnd - intStart + 1;
	debug (getTypeName (theType)+":"+expression+" num:"+num+" start:"+start+" end:"+end+" len:"+intBinPartLength);
    }
    void debug(String msg)
    {
	if (debug)
	    {	
		StackTraceElement stack[] = new Throwable().getStackTrace();
		System.err.print(stack[1]+":");
		System.err.println(msg);
	    }
    } /* debug */

    void error(String msg)
    {
	StackTraceElement stack[] = new Throwable().getStackTrace();
	System.err.print(stack[1]+":");
	System.err.println(msg);
	System.exit(-1);
    } /* error */

    public int    getType() 	{ return type; 			}
    public String getTypeName(int type)
    {
	switch (type)
	    {
	    case  INTDESC: return "INTDESC"; 
	    case  REGDESC: return "REGDESC"; 
	    case  BINNUM : return "BINNUM"; 
	    case  INTEXPR: return "INTEXPR";
	    default: error("Unknown type"); return "";
	    }
    }
    public int getLength() 	{ return intBinPartLength; 	}
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
	    case REGDESC:  
		if (intStart == 0)
		    {
			tmp =  regName+regNumber+","+intBinPartLength;  		
		    }
		else
		    {
			mask = (1 << intBinPartLength) - 1;
			tmp =  "("+regName+regNumber+" >>"+intStart+") & "+mask+","+intBinPartLength;  		
		    }
		break;
	    default: error("Error InstructionBinPart not known"); 			break;
	    }
	return "LENOK("+tmp+")";
    } /* toString */
}
