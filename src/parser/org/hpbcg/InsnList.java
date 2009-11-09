package org.hpbcg;

import java.io.*;

// Mnemonic assembly list
class InsnList
{
    String [] insnList;
    String archName;
    public InsnList(String name)
    {
	insnList = loadInsnList(name);
	archName = name;
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

    // Load in memory the valid instruction list
    public String [] loadInsnList(String name) 
    {
	String repDir [] = {"/usr/local/include", "/usr/include"};
	String tmp [] = null;
	String fileName = null;
	String hpbcghome;
	boolean ok = false;
	BufferedReader in;
	int nline = 0;
	try
        {
	    //  hpbcghome = System.getenv ("HPBCGHOME");
	    hpbcghome = System.getProperty ("HPBCGHOME");
	    if (null != hpbcghome)
		{
		    fileName = hpbcghome+"/include/hpbcg-"+name+".lst";
		    File f = new File (fileName);
		    if (! f.exists())
			fatalErrorMsg("File "+fileName+" doesn't exist");
		    ok = true;
		}
	    else
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
	    System.out.println("/* Processor description from :"+fileName+" */");
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