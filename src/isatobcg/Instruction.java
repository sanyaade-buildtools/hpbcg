import java.util.*;

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
	    if (end > 0) tmp.append(",");
	    tmp.append( "QP, STOP)\t");
	}
	tmp.append(toMacroBody());
	tmp.append("\n");
	return tmp.toString();
    } /* toMacro */

    public String toFunction()
    {
	int end;
	StringBuffer tmp = new StringBuffer("void "+getName()+"(");
	end = asmPart.size();
	for (int i = 0; i < end; ++i)
	    {
		tmp.append( ((InstructionAsmPart) asmPart.elementAt(i)).toString());
		if (i != (end - 1)) tmp.append( ", ");
	    }
	if (! archName.equals("ia64"))
	    tmp.append( ")\t");
	else
	{
	    if (end > 0) tmp.append(",");
	    tmp.append( "QP, STOP)\t");
	}
	tmp.append( "\n{\t");
	tmp.append( toMacroBody());
	tmp.append( ";");
	tmp.append( "\n#ifdef ASM_DEBUG\n");
	tmp.append( "\tprintf(\"%p : %s%s 0x%X\\n\", asm_pc, \""+getName()+"\", *(asm_pc-1));\n");
	tmp.append( "#endif /* ASM_DEBUG */\n}\n");
	return tmp.toString();
    } /* toFunction */
    String toMacroBody()
    {
	InstructionBinPart ibp;
	int end = binPart.size();
	StringBuffer tmp = new StringBuffer("ADDINSN(");
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

}