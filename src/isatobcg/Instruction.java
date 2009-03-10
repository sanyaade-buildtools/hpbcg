import java.util.*;

class Instruction
{
    String name;
    Vector binPart, asmPart;

    public Instruction ()
    {
	// System.out.println ("New instruction\n");
	binPart = new Vector();
	asmPart = new Vector();
    }

    void setName(String n)
    {
	// System.out.println ("setName"+n+"\n");
	name = n.replace('.', '_');
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
 	binPart.add (new InstructionBinPart(expr, start, end));
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
    public String toMacro()
    {
	int end;
	String tmp = "#define "+name+"_"+insnFormat()+"(";
	InstructionBinPart ibp;
	end = asmPart.size();
	for (int i = 0; i < end; ++i)
	    {
		tmp += ((InstructionAsmPart) asmPart.elementAt(i)).toString();
		if (i != (end - 1)) tmp += ", ";
	    }

	tmp += ")\tADDINSN";
	end = binPart.size();
	for (int i = 0; i < end; ++i)
	    {

		tmp += "(";
	    }
	for (int i = 0; i < end; ++i)
	    {
		ibp = (InstructionBinPart) binPart.elementAt(i);
		if (0 != i) tmp += "<< "+ibp.getLength()+" | ";
		tmp += (ibp).toString()+")";
	    }
	return tmp+'\n';
    } /* toMacro */

    public String toFunction()
    {
	int end;
	String tmp = "void "+name+"_"+insnFormat()+"(";
	InstructionBinPart ibp;
	end = asmPart.size();
	for (int i = 0; i < end; ++i)
	    {
		tmp += ((InstructionAsmPart) asmPart.elementAt(i)).toString();
		if (i != (end - 1)) tmp += ", ";
	    }
	tmp += ")\t \n{";
	end = binPart.size();
	tmp += "\nADDINSN";
	for (int i = 0; i < end; ++i)
	    {
		tmp += "(";
	    }
	for (int i = 0; i < end; ++i)
	    {
		ibp = (InstructionBinPart) binPart.elementAt(i);
		if (0 != i) tmp += "<< "+ibp.getLength()+" | ";
		tmp += (ibp).toString()+")";
	    }
	tmp += "\n#ifdef ASM_DEBUG\n";
	tmp += "\tprintf(\"%p : %s%s 0x%X\\n\", asm_pc, \""+name+"_"+insnFormat()+"\", *(asm_pc-1));\n";
	tmp += "#endif /* ASM_DEBUG */\n";
	return tmp+"\n}\n";
    } /* toFunction */
}