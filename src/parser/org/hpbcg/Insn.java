// Generic machine instruction description

package org.hpbcg;

import java.io.*;

class Insn
{
    public static final int TYPEIREG = 1;
    public static final int TYPEFREG = 2;
    public static final int TYPEBREG = 3;
    public static final int TYPEPREG = 4;
    public static final int TYPEIDXREG = 5;
    public static final int TYPEINT =  6;

    String [] insnList;
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
	tmp = insnName+buildDescReg();
	if (!verifExistInsn(tmp)) fatalErrorMsg ("Insn "+tmp+" doesn't exist");
	tmp += "(";
	for (i = 0; i < currentRegister - 1;  i++)
	{
	    tmp += registers[i] +',';

	}
	if (currentRegister > 0) tmp += registers[i];
	tmp += ");";
	return tmp;
    }
    public String buildDescReg()
    {
	String tmp = "_i";

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
    boolean verifExistInsn(String name)
    {
	if (null == insnList) fatalErrorMsg ("insnList == null");
	for (int i = 0; i < insnList.length; ++i)
	{
	    if (insnList[i].equals(name))
		return true;
	}
	return false;
    } /* verifExistInsn */

    public String [] loadInsnList(String name) 
    {
	String repDir [] = {"/users/prism/arpa/coca/hpc/Travail/Prog/HPBCG/src/isatobcg/", 
			    "/usr/local/include", "/usr/include"};
	String tmp [] = null;
	String fileName = null;
	boolean ok = false;
	BufferedReader in;
	int nline = 0;
	try
        {
	    for (int i = 0; i < repDir.length; i++)
	    {
		fileName = repDir[i]+"/"+name+".lst";
		File f = new File (fileName);
		if (! f.exists())
		    fatalErrorMsg("File "+fileName+" doesn't exist");
		else
		{
		    ok = true;
		    break;
		}
	    }
	    if (ok)
	    {
		in = new BufferedReader(new FileReader(fileName));
		while (null != in.readLine())
		{
		    nline ++;
		}
		in.close();
		tmp = new String[nline];
		in = new BufferedReader(new FileReader (fileName));
		for (int i = 0; i < nline; i++)
		{
		    tmp[i] = in.readLine();	
		    // System.out.println(tmp[i]);
		}
		in.close();
	    }
	    return tmp;
	}
	catch (java.lang.Exception e)
	{
	    e.printStackTrace();
	}
	return null;
    }
    public void fatalErrorMsg(String errorMsg)
    {
	System.err.println (errorMsg);	
	System.exit (-1);
    } /* fatalErrorMsg */

}
