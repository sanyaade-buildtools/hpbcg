// ArmThumb instruction description

package org.hpbcg;

class InsnArmThumb extends Insn
{
    public InsnArmThumb()
    {
	super(4);
    }
    public InsnArmThumb(String name)
    {
	super(4);
	setInsn (name);
    }
    public void setParam (String name, int TYPE)
    {
	String tmp;

	types[currentRegister] = TYPE;
	switch (TYPE)
	    {
	    case TYPEMASKREG: registers[currentRegister++] = name; break;
	    case TYPEINT:     registers[currentRegister++] = name; break;
	    case TYPEIREG:
		if      ("sp".equals(name))  registers[currentRegister] = "5";
		else if ("lr".equals(name))  registers[currentRegister] = "6";
		else if ("pc".equals(name))  registers[currentRegister] = "7";
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
			System.out.println ("ArmThumb FP reg name sould start with f");
			System.exit (-1);
		    }
		tmp = new String (name.getBytes(), 1, name.length() - 1);
		registers[currentRegister] = tmp;
		currentRegister++;
		break;
	    default:
		System.out.println ("Unknown register name:"+name+" "+TYPE);
		System.exit (-1);
		break;
	    }
    }
}
// The end
