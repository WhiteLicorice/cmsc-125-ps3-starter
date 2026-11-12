#include <stdio.h>
int main(void){ puts("A holds L1 and waits for L2"); puts("B holds L2 and waits for L1"); puts("cycle: A -> L2 -> B -> L1 -> A"); puts("prevention: acquire L1 before L2"); return 0;}
