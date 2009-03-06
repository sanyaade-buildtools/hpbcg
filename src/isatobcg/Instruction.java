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
	binPart.add (" B:"+n+"("+l+") ");
    } /* addBinaryNumber */
    void addBinaryIntDescr(String n)
    {
	binPart.add (" I:"+n+" ");
    } /* addIntDescr */
    void addBinaryRegDescr(String n)
    {
	binPart.add (" R:"+n+" ");
    } /* addRegDescr */

    void addAsmReg(String letter)
    {
	asmPart.add ("R"+letter);
    } /* addAsmReg */
    void addAsmInt(String number)
    {
	asmPart.add ("I("+number+")");
    } /* addAsmInt */
    public String toString()
    {
	String tmp = name;

	for (int i = 0; i < binPart.size(); ++i)
	    {
		tmp += binPart.elementAt(i).toString();
	    }
	for (int i = 0; i < asmPart.size(); ++i)
	    {
		tmp += asmPart.elementAt(i).toString();
	    }
	return tmp;
    } /* toString */

}