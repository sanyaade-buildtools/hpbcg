// X86 instruction description

package org.hpbcg;

class InsnX86 extends Insn
{
    public InsnX86()
    {
	super(4);
    }
    public InsnX86(String name)
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
	    case TYPEIREG:
		if      ("%eax".equals(name))  registers[currentRegister] = "0";
		else if ("%ecx".equals(name))  registers[currentRegister] = "1";
		else if ("%edx".equals(name))  registers[currentRegister] = "2";
		else if ("%ebx".equals(name))  registers[currentRegister] = "3";
		else if ("%esp".equals(name))  registers[currentRegister] = "4";
		else if ("%ebp".equals(name))  registers[currentRegister] = "5";
		else if ("%esi".equals(name))  registers[currentRegister] = "6";
		else if ("%edi".equals(name))  registers[currentRegister] = "7";
		else    {
		    System.out.println("Unknown register:"+name);
		    System.exit(0);
		}
		// System.out.println("Register : "+tmp+":"+registers[currentRegister]);
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
