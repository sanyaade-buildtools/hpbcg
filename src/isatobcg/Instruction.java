import java.util.*;

class Instruction
{
    String name;
    Vector binPart, asmPart;

    public Instruction ()
    {
	binPart = new Vector();
	asmPart = new Vector();
    }
    void setName(String n)
    {
	name = n;
    } /* addName */
    void addBinaryNumber(int n, int l)
    {
	binPart.add (new InstructionBinPart(n, l));
    } /* addBinaryNumber */
    void addBinaryIntDescr(int number, int start, int end )
    {
	binPart.add (new InstructionBinPart(number, start, end));
    } /* addIntDescr */
    void addBinaryRegDescr(String n, int number, int size)
    {
	binPart.add (new InstructionBinPart (n, number, size));
    } /* addRegDescr */

    void addAsmReg(String letter)
    {
	asmPart.add ("R"+letter);
    } /* addAsmReg */
    void addAsmInt(String number)
    {
	asmPart.add ("I("+number+")");
    } /* addAsmInt */
    public String toMacro()
    {
	String tmp = "#define "+name+"(";
	for (int i = 0; i < asmPart.size(); ++i)
	    {
		tmp += asmPart.elementAt(i).toString();
	    }
	tmp += ")";
	for (int i = 0; i < binPart.size(); ++i)
	    {
		tmp += binPart.elementAt(i).toString();
	    }
	return tmp+'\n';
    } /* toMacro */
}