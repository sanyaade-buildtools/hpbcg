// Ia64 instruction description

package org.hpbcg;

class InsnIa64 extends Insn
{
    boolean stopBit = false;
    public InsnIa64()
    {
	super(4);
	insnList = loadInsnList("ia64");
    }
    public InsnIa64(String name)
    {
	super(4);
	insnList = loadInsnList("ia64");
	setInsn (name);
    }
    public void setInsn (String name)
    {
	insnName = name.replace(".", "_");
    }
    public void setStop ()
    {
	stopBit = true;
    }
    public void setParam (String name, int TYPE)
    {
	String tmp;

	types[currentRegister] = TYPE;
	switch (TYPE)
	    {
	    case TYPEIREG:
	    case TYPEBREG:
	    case TYPEFREG: 	
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
	    tmp += registers[i] +',';
	}
	if (currentRegister > 0) tmp += registers[i];
	tmp += ", 0";		// predicat 
	if (stopBit)
	    tmp += ", 1);";
	else
	    tmp += ", 0);";
	return tmp;
    }
}
// The end
