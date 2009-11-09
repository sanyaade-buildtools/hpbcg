// Cell instruction description

package org.hpbcg;

class InsnCell extends Insn
{
    public InsnCell()
    {
	super(4);
    }
    public InsnCell(String name)
    {
	super(4);
	setInsn (name);
    }
    public void setParam (String name, int TYPE)
    {
	String tmp;

	types[currentRegister] = TYPE;
	if (TYPE == TYPEIREG)
	{
	    if (!name.startsWith("$"))
	    {
		System.out.println ("Cell reg name sould start with $");
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
