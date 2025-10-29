#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char rem[50], a[50], s[50], c, msj[50], gen[30];
    int i, genlen, t, j, flag = 0, k, n;

    printf("Enter the generation polynomial: ");
    fgets(gen, sizeof(gen), stdin);
    gen[strcspn(gen, "\n")] = '\0'; // remove newline if present
    printf("Generator polynomial is CRC :CCITT: %s\n", gen);

    genlen = strlen(gen);
    k = genlen - 1;

    printf("Enter the message: ");
    n = 0;
    while ((c = getchar()) != '\n' && c != EOF)
    {
        msj[n] = c;
        n++;
    }
    msj[n] = '\0';

    // Append zeros
    for (i = 0; i < n; i++)
        a[i] = msj[i];
    for (i = 0; i < k; i++)
        a[n + i] = '0';
    a[n + k] = '\0';

    printf("\nMessage polynomial appended with zeros:\n");
    puts(a);

    // Division process
    for (i = 0; i < n; i++)
    {
        if (a[i] == '1')
        {
            t = i;
            for (j = 0; j <= k; j++)
            {
                if (a[t] == gen[j])
                    a[t] = '0';
                else
                    a[t] = '1';
                t++;
            }
        }
    }

    // Remainder (checksum)
    for (i = 0; i < k; i++)
        rem[i] = a[n + i];
    rem[k] = '\0';

    printf("The checksum appended:\n");
    puts(rem);

    // Final transmitted message
    printf("\nThe message with checksum appended:\n");
    for (i = 0; i < n; i++)
        a[i] = msj[i];
    for (i = 0; i < k; i++)
        a[n + i] = rem[i];
    a[n + k] = '\0';
    puts(a);

    // Receiver side
    n = 0;
    printf("Enter the received message: ");
    while ((c = getchar()) != '\n' && c != EOF)
    {
        s[n] = c;
        n++;
    }
    s[n] = '\0';

    for (i = 0; i < n; i++)
    {
        if (s[i] == '1')
        {
            t = i;
            for (j = 0; j <= k; j++, t++)
            {
                if (s[t] == gen[j])
                    s[t] = '0';
                else
                    s[t] = '1';
            }
        }
    }

    // Check remainder
    for (i = 0; i < k; i++)
        rem[i] = s[n + i];
    rem[k] = '\0';

    flag = 0;
    for (i = 0; i < k; i++)
    {
        if (rem[i] == '1')
            flag = 1;
    }

    if (flag == 0)
        printf("Received polynomial is error-free\n");
    else
        printf("Received polynomial has error\n");

    return 0;
}
