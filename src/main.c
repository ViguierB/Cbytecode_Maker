#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "cbcmaker.h"

void compute(t_target *target)
{
    char    buffer[READ_LENGHT];
    ssize_t readed;
    int     fd;
    FILE    *out;
    int     first = 1;
    int     i;
    int     j = 0;

    fd = open(target->target_file, O_RDONLY);
    out = fopen(target->result_file, "w");
    fprintf(out, "const char *%s = (const char[])\n\t{\n\t\t", target->var_name);
    while ((readed = read(fd, buffer, READ_LENGHT)) > 0)
    {
        i = 0;
        if (first)
        {
            fprintf(out, "0x%.2hhx", buffer[0]);
            first = 0;
            i++;
            j++;
        }
        for (;i < readed; i++)
        {
            fprintf(out, ",%s0x%.2hhx", ((j && j % NL_AT == 0) ? "\n\t\t" : ""), buffer[i]);
            j++;
        }
    }
    fprintf(out, "\n\t};");
    close(fd);
    fclose(out);
    if (readed < 0)
    {
        perror("read()");
        exit(84);
    }
}

int main(int ac, char **av)
{
    t_target    target;

    if (ac > 3)
    {
        target.target_file = av[1];
        target.result_file = av[2];
        target.var_name = av[3];

        compute(&target);
    }
    else
    {
        printf("USAGE : %s target_file result_file varname\n", av[0]);
    }
}