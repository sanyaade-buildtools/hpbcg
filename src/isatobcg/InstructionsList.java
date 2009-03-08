import java.util.*;

class InstructionsList
{
    String archName;
    int isaLen;
    Vector instructionList = new Vector();
    Instruction cI;
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
	// tmp += toFunctions();
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

    public void Verify()
    {
	if (null == cI) 
	    cI = new Instruction();
    }

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
	instructionList.add (cI);
	cI = null;
    } /* addInstruction */
    void addName(String insnName)
    {
	cI.setName(insnName);
    } /* addName */

    void addBinaryNumber(String n)
    {
	Verify();
	cI.addBinaryNumber(Integer.parseInt(n, 2), n.length());
    } /* addBinaryNumber */

    void addBinaryIntDescr(String n)
    {
	int i;
	String intNumber = "", intEnd = "" , intStart = "";
	Verify();
	// Number has this form iN_E-S
	for (i = 1; '_' != n.charAt(i) ; ++i)
		intNumber += n.charAt(i);
	for (i++; '-' != n.charAt(i) ; ++i)
		intEnd += n.charAt(i);
	for (; i < n.length(); ++i)
	    {
		intStart += n.charAt(i);
 	    }
	cI.addBinaryIntDescr(Integer.parseInt(intNumber), 
		       Integer.parseInt(intStart), 
		       Integer.parseInt(intEnd));
    } /* addBinaryIntDescr */

    void addBinaryRegDescr(String descr)
    {
	int i;
	String letter;
	String number = "", size = "";
	Verify();
	// L I1 _ I2
	letter = ""+ descr.charAt(0);
	for (i = 1; '_' != descr.charAt(i) ; ++i)
		number += descr.charAt(i);
	for (; i < descr.length(); ++i)
		size += descr.charAt(i);
	cI.addBinaryRegDescr(letter, Integer.parseInt ("1"), Integer.parseInt ("1"));
    } /* addBinaryRegDescr */

    void addAsmReg(String r)
    {
	cI.addAsmReg(r);
    } /* addAsmReg */

    void addAsmInt(String r)
    {
	cI.addAsmInt(r);
    } /* addAsmInt */
}