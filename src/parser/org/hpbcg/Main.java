package org.hpbcg;

import org.antlr.runtime.*;
import java.io.*;

class Main
{
    static boolean debug;
    
    public static void main(String[] args) 
    {
        String currentArch = null, tmp;
	CharStream in;
        try 
	{
	    in = getInput (args);
	    C      lexerC = new C(in);
	    Cell   lexerCell  =  new Cell(in);
	    Ia64   lexerIa64  =  new Ia64(in);
	    Power4 lexerPower4  =  new Power4(in);
	    if (debug) 	System.out.println("/* Debug mode */");
	    while (true)
	    {
		tmp = lexerC.myParse(debug);
		if (null != tmp)currentArch = tmp;
		if (currentArch.equals("cell"))        lexerCell.myParse(debug);
		else if (currentArch.equals("ia64"))   lexerIa64.myParse(debug);
		else if (currentArch.equals("power4")) lexerPower4.myParse(debug);
		else
		    {
			System.err.println("No #cpu defined ("+currentArch+")");
			System.exit(-1);
		    }   
	    }
	}
        catch (Exception e)
	{
	    e.printStackTrace(System.out);
	}
    }

    public static CharStream getInput(String a[]) 
	throws java.io.FileNotFoundException,
	       java.io.IOException
    {
	int i;
	CharStream inFile = null;

	for (i = 0; i < a.length; i++)
	{
	    if (a[i].equals("-d"))
		debug = true;
	    else
		inFile = new ANTLRFileStream(a[i]);
	}
	if (null == inFile) 
	    return new ANTLRInputStream(System.in);
	else
	    return inFile;
    }
}
