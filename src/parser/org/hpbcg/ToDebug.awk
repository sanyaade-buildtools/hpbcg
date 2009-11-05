BEGIN{
    FS="=";
    printf("String Debug%s(int value)\n\{\n", ARCH);
    print "    switch (value)\n    {\n\t";
}
{
    printf("\tcase %d: return \"%s\"; \n", $2, $1);
}
END{
    print "     }\n"
    print "return \"unknown token\";\n}\n"

}
