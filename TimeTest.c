#include <stdio.h>
#include <time.h>

int main()
{
    int start = clock();
    while (clock() - start < 100);
    printf("%d, %d", clock(), start);
}
