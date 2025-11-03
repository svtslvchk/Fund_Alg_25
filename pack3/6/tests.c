#include <stdio.h>
#include <assert.h>
#include "check_brackets.h"

void run_tests() {
    printf("Running bracket tests...\n\n");
    
    assert(checkBrackets("") == 1);  
    assert(checkBrackets("(<[{()}]>)") == 1);  
    assert(checkBrackets("(((((((((())))))))))") == 1);  
    assert(checkBrackets("({[<>]})") == 1); 
    assert(checkBrackets("a(b[c{d<e>f}g]h)i") == 1);  
    
    assert(checkBrackets("(((((((((()))))))))") == 0);  
    assert(checkBrackets("((((((((())))))))))") == 0);  
    assert(checkBrackets("({[}])") == 0); 
    assert(checkBrackets("(([])))(())") == 0);  
    assert(checkBrackets("(<)>") == 0);  
    
    assert(checkBrackets(")(") == 0);  
    assert(checkBrackets("}{") == 0);  
    assert(checkBrackets("><") == 0);  
    assert(checkBrackets("])") == 0);  
    assert(checkBrackets("([{<") == 0);  
    assert(checkBrackets(">}])") == 0);  
    
    assert(checkBrackets("(a + b * (c - d))") == 1);  
    assert(checkBrackets("array[i] = value;") == 1); 
    assert(checkBrackets("if (x == 5) { y != 3; }") == 1);  
    assert(checkBrackets("(\"test\")") == 1); 
    assert(checkBrackets("(')')") == 0); 
    
    assert(checkBrackets("())(()") == 0);  
    assert(checkBrackets("((()())") == 0);  
    assert(checkBrackets("(()))(") == 0); 
    assert(checkBrackets("([{< >}])") == 1);  
    assert(checkBrackets("(([[{{}}]]))") == 1);  
    
    printf("All tests passed!\n");
}

int main() {
    run_tests();
    return 0;
}