// Generic machine instruction description

package org.hpbcg;

class Insn
{
    public static final int TYPEIREG = 1;
    public static final int TYPEFREG = 2;
    public static final int TYPEBREG = 3;
    public static final int TYPEPREG = 4;
    public static final int TYPEIDXREG = 5;
    public static final int TYPEINT =  6;

    String insnName;
    String [] registers;
    int [] types;
    int currentRegister = 0;
    public Insn(int paramNumber)
    {
	registers = new String[paramNumber];
	types     = new int[paramNumber];
    }
    public void setInsn (String name)
    {
	insnName = name;
    }
    public void setParam(String name, int type)
    {
	types[currentRegister] = type;
	registers[currentRegister++] = name;
    }
    public String getInsn()
    {
	int i;
	String tmp;
	tmp = insnName+buildDescReg()+"(";
	for (i = 0; i < currentRegister - 1;  i++)
	{
	    tmp += registers[i] +',';

	}
	tmp += registers[i]+");";
	return tmp;
    }
    public String buildDescReg()
    {
	String tmp = "_";

	for (int i = 0; i < currentRegister; ++i)
	    {
		switch (types[i])
		{
		case TYPEIREG: tmp += "R"; break;
		case TYPEFREG: tmp += "F"; break;
		case TYPEBREG: tmp += "B"; break;
		case TYPEPREG: tmp += "P"; break;
		case TYPEINT: 
		case TYPEIDXREG: tmp += "I"; break;
		default:  System.out.println ("Unknown register type");
		    System.exit (0);
		}
	    }
	return tmp;

    }
}