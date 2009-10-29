import java.util.*;
/**
 * Instruction description
 */
class Instruction
{
    String name, archName;
    Vector binPart, asmPart;

    public Instruction (String a)
    {
	// System.out.println ("New instruction\n");
	binPart = new Vector();
	asmPart = new Vector();
	archName = a;
    }

    void setName(String n)
    {
	// System.out.println ("setName"+n+"\n");
	name = n.replace('.', '_');
    } /* addName */

    String getName()
    {
	return name+"_"+insnFormat();
    } /* addName */

    void addBinaryNumber(int n, int l)
    {
	InstructionBinPart last;
	
	//	System.out.println ("Add bin part");
	if (binPart.size() > 0)
	{
	    last = (InstructionBinPart) binPart.lastElement();
	    if (InstructionBinPart.BINNUM == last.getType())
		last.addBinNum(n, l);
	    else
		binPart.add (new InstructionBinPart(n, l));
	}
	else
	    binPart.add (new InstructionBinPart(n, l));
    } /*  */

    void addBinaryIntDescr(int number, int start, int end )
    {
 	binPart.add (new InstructionBinPart(number, start, end));
    } /*  */
    void addBinaryIntExpr(String expr, int start, int end )
    {
 	binPart.add (new InstructionBinPart(expr, start, end, 0));
    } /*  */
    void addBinaryRegDescr(String n, int number, int size)
    {
 	binPart.add (new InstructionBinPart (n, number, size));
    } /*  */
    
    void addAsmReg(String letter)
    {
	asmPart.add (new InstructionAsmPart(letter));
    } /*  */
    void addAsmInt(String number)
    {
	asmPart.add (new InstructionAsmPart(number));
    } /*  */

    public String insnFormat ()
    {
	String tmp = "i";
	for (int i = 0; i < asmPart.size(); ++i)
	{
	    tmp += ((InstructionAsmPart) asmPart.elementAt (i)).getTypeLetter();
	}
	return tmp;
    }

    /**
     * return the macro able to generate a binary instruction
     */
    public String toMacro()
    {
	StringBuffer tmp = new StringBuffer("#define "+getName()+"(");
	int end = asmPart.size();
	for (int i = 0; i < end; ++i)
	{
	    tmp.append( ((InstructionAsmPart) asmPart.elementAt(i)).toString());
	    if (i != (end - 1)) tmp.append( ", ");
	}
	if (! archName.equals("ia64"))
	    tmp.append( ")\t");
	else
	{
	    if (end > 0) tmp.append(", ");
	    tmp.append( "q1, STOP)\t");
	}
	tmp.append(toMacroBody());
	tmp.append("\n");
	return tmp.toString();
    } /* toMacro */

    /**
     * get the binary lenght of an instruction
     */
    public int getLength()
    {
	int l, end = binPart.size();
	l = 0;
	for (int i = 0; i < end; ++i)
	{
	    l += ((InstructionBinPart) binPart.elementAt(i)).getLength();
	}
	// System.out.println("Computed len"+ l);
	return l;
    }

    /**
     * Build a function able to generate the current instruction
     */
    public String toFunction()
    {
	int end;
	StringBuffer tmp = new StringBuffer("void "+getName()+"(");
	String printFormat, printArg;
	StringBuffer argList = new StringBuffer();
	char letter;
	end = asmPart.size();
	for (int i = 0; i < end; ++i)
	    {
		tmp.append( ("int "+(InstructionAsmPart) asmPart.elementAt(i)).toString());
		if (i != (end - 1)) tmp.append( ", ");
	    }
	if (! archName.equals("ia64"))
	    tmp.append( ")\t");
	else
	{
	    if (end > 0) tmp.append(", ");
	    tmp.append( "int q1, int STOP)\t");
	}
	tmp.append( "\n{\n");
	tmp.append( "\n#ifdef ASM_DEBUG\n");
	printFormat = "%p : "+getName()+" ";
	for (int i = 0; i < end; ++i)
	    {
		if ("x86".equals (archName))
		    {//   argList.append (","+(InstructionAsmPart) asmPart.elementAt(i));
		    }
		else
		    {
			letter  = ((InstructionAsmPart) asmPart.elementAt(i)).toString().charAt(0);
			switch (letter)
			    {
			    case 'r': 
			    case 'f':
			    case 'p':
			    case 'b':
				printFormat += letter+"%d "; break;
			    case 'i': printFormat += "0x%X "; break;
			    default: fatalError("Error letter in register name: "+letter); 
			    }
			argList.append(","+((InstructionAsmPart) asmPart.elementAt(i)).toString());
		    }
	    }
	tmp.append( "\tprintf(\""+printFormat+"\\n\", hpbcg_asm_pc "+argList.toString()+");\n");
	tmp.append( "#endif /* ASM_DEBUG */\n");
	tmp.append( toMacroBody());
	tmp.append( ";");
	tmp.append( "\n}\n");
	return tmp.toString();
    } /* toFunction */

    /**
     * Build a macro instruction able to generate the current instruction
     */
    String toMacroBody()
    {
	InstructionBinPart ibp;
	int end = binPart.size();
	StringBuffer tmp = new StringBuffer();
	int totalLen;
	if (archName.equals("x86"))
	    {
		totalLen = 0;
		for (int i = 0; i < end; ++i)
		    {
			ibp = (InstructionBinPart) binPart.elementAt(i);
			totalLen += ibp.getLength();
		    }
		if (0 != (totalLen % 8))
		    fatalError("Unknown insn length :"+totalLen); 
		tmp.append("ADDINSN"+totalLen+"("); 
	    }
	else
	    tmp.append("ADDINSN(");

	for (int i = 0; i < end; ++i)
		tmp.append("(");
	for (int i = 0; i < end; ++i)
	    {
		ibp = (InstructionBinPart) binPart.elementAt(i);
		if (0 != i) tmp.append("<< "+ibp.getLength()+" | ");
		tmp.append((ibp).toString()+")");
	    }
	if (! archName.equals("ia64"))
	    tmp.append(")");
	else
	    {
		if (end > 0) tmp.append(", ");
		tmp.append("STOP)");
	    }
	return tmp.toString();
    }
    void fatalError(String msg)
    {
	System.err.println("Fatal error: "+msg);
	System.exit(-1);
    } /* fatalError */

}