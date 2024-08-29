#! /bin/awk -f
BEGIN {
    print ""
    print ""
    print ""
    print ""
    print "// start generate " name
    print "char " name "[] ="
}
{
    print "    \"" $0 " \\n\""
}
END {
    print "    \"\";"
    print "const char *get_" name "(void) { return " name "; }"
    print "// end generate"
}
