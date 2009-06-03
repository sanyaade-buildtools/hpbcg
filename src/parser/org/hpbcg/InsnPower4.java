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
	switch (TYPE)
	    {
	    case TYPEIREG:
		if (!name.startsWith("r"))
		    {
			System.out.println ("Power4 INT reg name sould start with r");
			System.exit (-1);
		    }
		if      ("lr".equals(name))  registers[currentRegister] = "0";
		else if ("sp".equals(name))  registers[currentRegister] = "1";
		else    {
		    tmp = new String (name.getBytes(), 1, name.length() - 1);
		    registers[currentRegister] = tmp;
		}
		// System.out.println("Register : "+tmp+":"+registers[currentRegister]);
		currentRegister++;
		break;
	    case TYPEFREG:
		if (!name.startsWith("f"))
		    {
			System.out.println ("Power4 FP reg name sould start with f");
			System.exit (-1);
		    }
		tmp = new String (name.getBytes(), 1, name.length() - 1);
		registers[currentRegister] = tmp;
		currentRegister++;
		break;
	    case TYPEINT:
		registers[currentRegister++] = name;
		break;
	    default:
		System.out.println ("Unknown register name:"+name+" "+TYPE);
		System.exit (-1);
		break;
	    }
    }
}
// The end
