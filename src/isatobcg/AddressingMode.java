/**
 * Storing addressing modes and generate instructions
 */
class AddressingMode
{
    Vector binPart, asmPart;	// Binary description and semantic description
    public AddressingMode ()
    {
	binPart = new Vector();
	asmPart = new Vector();
    }
}