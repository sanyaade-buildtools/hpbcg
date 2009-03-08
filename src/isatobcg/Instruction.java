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
	name = n;
    } /* addName */

    void addBinaryNumber(int n, int l)
    {
	//	System.out.println ("Add bin part");
 	binPart.add (new InstructionBinPart(n, l));
    } /* addBinaryNumber */

    void addBinaryIntDescr(int number, int start, int end )
    {
	// System.out.println ("Add int descr"+number+":"+start+":"+end);
 	binPart.add (new InstructionBinPart(number, start, end));
    } /* addIntDescr */
    void addBinaryRegDescr(String n, int number, int size)
    {
	// System.out.println ("Add reg descr"+n+number+":"+size);
 	binPart.add (new InstructionBinPart (n, number, size));
    } /* addRegDescr */
    
    void addAsmReg(String letter)
    {
	asmPart.add (new InstructionAsmPart(letter));
    } /* addAsmReg */
    void addAsmInt(String number)
    {
	asmPart.add (new InstructionAsmPart(number));
    } /* addAsmInt */

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
	end = asmPart.size();
	for (int i = 0; i < end; ++i)
	    {
		tmp += ((InstructionAsmPart) asmPart.elementAt(i)).toString();
		if (i != (end - 1)) tmp += ", ";
	    }
	tmp += ")";
	end = binPart.size();
	for (int i = 0; i < end; ++i)
	    {
		tmp += ((InstructionBinPart) binPart.elementAt(i)).toString();
		if (i != (end - 1)) tmp += ", ";
	    }
	return tmp+'\n';
    } /* toMacro */
}