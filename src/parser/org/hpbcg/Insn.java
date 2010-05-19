// Generic machine instruction description

package org.hpbcg;


class Insn
{
    public static final int TYPEIREG   = 1; // Integer register
    public static final int TYPEFREG   = 2; // Floatin point register
    public static final int TYPEBREG   = 3; // Boolean register
    public static final int TYPEPREG   = 4; // Predicate register
    public static final int TYPEIDXREG = 5; // Index register
    public static final int TYPEINT    = 6; // Int value
    public static final int TYPEARREG  = 7; // Application register
    public static final int TYPEMASKREG = 8; // Register Mask
    
    String insnName, labelName = null;
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
    public void setLabel(String name)
    {
	labelName = name;
    }
    public String getInsn()
    {
	int i;
	String tmp;
	tmp = "";
	if (null != insnName)
	    {
		tmp += insnName+buildDescReg();
		tmp += "(";
		for (i = 0; i < currentRegister - 1;  i++)
		    {
			tmp += registers[i] +',';
		    }
		if (currentRegister > 0) tmp += registers[i];
		tmp += ");";
	    }
	if (null != labelName) 
	    tmp += "LABEL("+labelName+");\n";
	return tmp;
    }
    public String buildDescReg()
    {
	String tmp = "_i";

	for (int i = 0; i < currentRegister; ++i)
	    {
		switch (types[i])
		{
		case TYPEIREG:    tmp += "R"; break;
		case TYPEFREG:    tmp += "F"; break;
		case TYPEPREG:    tmp += "P"; break;
		case TYPEARREG:   tmp += "R";  break;
		case TYPEBREG:    tmp += "B";  break;
		case TYPEMASKREG: 
		case TYPEINT: 
		case TYPEIDXREG: tmp += "I"; break;
		default:  System.out.println ("Unknown register type");
		    System.exit (0);
		}
	    }
	return tmp;

    }
    public void fatalErrorMsg(String errorMsg)
    {
	System.err.println (errorMsg);	
	System.exit (-1);
    } /* fatalErrorMsg */
}
