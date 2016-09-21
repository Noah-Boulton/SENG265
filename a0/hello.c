#include <stdio.h>
#include "hello.h"

//Function that prints 'Hello <argument>!'
void hello (const char * name) {
      //Output to the screen the passed string argument
      printf ("Hello %s!\n", name);
}
