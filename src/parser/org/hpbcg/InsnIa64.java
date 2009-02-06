// Ia64 instruction description

package org.hpbcg;

class InsnIa64 extends Insn
{
    boolean stopBit = false;
    String predicat;
    public InsnIa64()
    {
	super(6);
	insnList = loadInsnList("ia64");
    }
    public InsnIa64(String name)
    {
	super(6);
	insnList = loadInsnList("ia64");
	setInsn (name);
    }
    public InsnIa64(String name, String pred)
    {
	super(6);
	insnList = loadInsnList("ia64");
	setInsn (name);
	setPredicat(pred);
    }
    public void setInsn (String name)
    {
	insnName = name.replace(".", "_");
    }
    public void setStop ()
    {
	stopBit = true;
    }
    public void setPredicat(String p)
    {
	String tmp;
	if (!p.startsWith("(p"))
	{
	    System.out.println ("Ia64 predicate reg name sould start with (p : "+p);
	    System.exit (-1);
	}
	predicat = new String (p.getBytes(), 2, p.length() - 3);
    } /* setPredicat */

    public void setParam (String name, int TYPE)
    {
	String tmp;

	types[currentRegister] = TYPE;
	switch (TYPE)
	    {
	    case TYPEIREG:
	    case TYPEBREG:
	    case TYPEFREG: 	
	    case TYPEPREG: 	
		registers[currentRegister++] = 
		    new String (name.getBytes(), 1, name.length() - 1);
		break;
	    default:
		registers[currentRegister++] = name;
		break;
	    }

    }
    public String getInsn()
    {
	int i;
	String tmp;
	tmp = insnName+buildDescReg();
	if (!verifExistInsn(tmp)) fatalErrorMsg ("Insn "+tmp+" doesn't exist");
	tmp += "(";
	for (i = 0; i < currentRegister - 1;  i++)
	{
	    if (! registers[i].equals("ar.pfs"))
		tmp += registers[i] +", ";
	    else
		tmp += "0, ";
	}
	if (currentRegister > 0) tmp += registers[i];
	tmp += "," + ((null != predicat)?predicat:" 0"); 
	tmp += "," + ((stopBit)?" 1":" 0");
	tmp += ");";
	return tmp;
    }
}
// The end
