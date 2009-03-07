import java.util.*;

class InstructionsList
{
    String archName;
    int isaLen;
    Vector instructionList = new Vector();
    Instruction currentInstruction;

    public void setNameAndLenght (String archName, int isaLen)
    {
	this.archName = archName;
	this.isaLen = isaLen;
    }
    String header()
    {
	String tmp = archName+" : "+isaLen+" bits"+"\n";
	tmp += "/* Autogenerated file, do not edit ! */"+"\n";
	tmp += "/* "+ archName +" "+ isaLen+ " bits  */"+"\n";
	tmp += "#include <hpbcg-"+archName+"-utils.h>"+"\n";
	return tmp;
    } /* header */

    public String toString()
    {
	String tmp = header();
	tmp += toMacros();
	tmp += toFunctions();
	return tmp;
    } /* toString() */
    public String toMacros()
    {
	String tmp = "";
	for (int i = 0; i < instructionList.size(); ++i)
	    {
		tmp += ((Instruction) instructionList.elementAt(i)).toMacro();
	    }
	return tmp;
    } /* toMacros() */
    public String toFunctions()
    {
	String tmp = "";
	for (int i = 0; i < instructionList.size(); ++i)
	    {
		tmp += ((Instruction) instructionList.elementAt(i)).toMacro();
	    }
	return tmp;
    } /* toFunctions() */
    void addInstruction()
    {
	instructionList.add (currentInstruction);
	currentInstruction = null;
    } /* addInstruction */

    void addName(String insnName)
    {
	if (null == currentInstruction) 
	    currentInstruction = new Instruction();
	currentInstruction.setName(insnName);
    } /* addName */

    void addBinaryNumber(String n)
    {
	if (null == currentInstruction) 
	    currentInstruction = new Instruction();
	currentInstruction.addBinaryNumber(Integer.parseInt(n, 2), n.length());
    } /* addBinaryNumber */

    void addBinaryIntDescr(String n, String s, String e)
    {
	if (null == currentInstruction) 
	    currentInstruction = new Instruction();
	currentInstruction.addBinaryIntDescr(Integer.parseInt(n), 
					     Integer.parseInt(s), 
					     Integer.parseInt(e));
    } /* addBinaryIntDescr */

    void addBinaryRegDescr(String letter, String number, String size)
    {
	if (null == currentInstruction) 
	    currentInstruction = new Instruction();
	currentInstruction.addBinaryRegDescr(letter, Integer.parseInt (number), Integer.parseInt (size));
    } /* addBinaryRegDescr */
   
    void addAsmReg(String r)
    {
	currentInstruction.addAsmReg(r);
    } /* addAsmReg */
    void addAsmInt(String r)
    {
	currentInstruction.addAsmInt(r);
    } /* addAsmInt */
}