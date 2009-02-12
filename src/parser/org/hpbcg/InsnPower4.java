// Power4 instruction description

package org.hpbcg;

class InsnPower4 extends Insn
{
    public InsnPower4()
    {
	super(4);
	insnList = loadInsnList("power4");
    }
    public InsnPower4(String name)
    {
	super(4);
	insnList = loadInsnList("power4");
	setInsn (name);
    }
    public void setParam (String name, int TYPE)
    {
	String tmp;

	types[currentRegister] = TYPE;
	if (TYPE == TYPEIREG)
	{
	    if (!name.startsWith("r"))
	    {
		System.out.println ("Power4 reg name sould start with r");
		System.exit (-1);
	    }
	    else
	    {
		tmp = new String (name.getBytes(), 1, name.length() - 1);
		if ("lr".equals(tmp))       registers[currentRegister] = "0";
		else if ("sp".equals(tmp))  registers[currentRegister] = "1";
		else     		    registers[currentRegister] = tmp;
		// System.out.println("Register : "+tmp+":"+registers[currentRegister]);
		currentRegister++;
	    }
	}
	else
	    registers[currentRegister++] = name;
    }
}
// The end
