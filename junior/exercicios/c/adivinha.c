#include <stdio.h>

int main(void)
{
    int low = 0;
    int high = 100;
    int mid;
    char response;

    while(low <= high)
    {
        // divide por 2
        mid = (low + high) >> 1;

        do
        {
            printf("O número que você pensou é: %d ? (r = correto, m = maior, n = menor): ", mid);
            scanf(" %c", &response);
        }
        while(response != 'r' && response != 'm' && response != 'n');

        switch(response)
        {
            case 'r':
                printf("Acertei!! O número que você pensou foi o: %d\n", mid);
                return 0;
            case 'm':
                low = mid + 1;
                break;
            case 'n':
                high = mid - 1;
                break;
        }
    }

    printf("Errei ... :(\n");

    return 0;
}
