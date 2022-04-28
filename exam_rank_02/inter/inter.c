#include <unistd.h>

int ft_ch(char *str, char c, int index)
{
    int i;

    i = 0;
    while (index > i)
    {
        if (str[i] == c)
            return (1);
        i++;
    }
    return (0);
}

int main(int argc, char **argv)
{
    int i;
    int j;

    if (argc == 3)
    {
        i = 0;
        while (argv[1][i] != '\0')
        {
            j = 0;
            while (argv[2][j] != '\0')
            {
                if (argv[1][i] == argv[2][j])
                {
                    if (!(ft_ch(argv[1], argv[1][i], i)))
                    {
                        write(1, &argv[1][i], 1);
                        break;
                    }
                }
                j++;
            }
            i++;
        }
        write(1, "\n", 1);
    }
    else
        write(1, "\n", 1);

    return (0);
}