#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include "cbcmaker.h"

char **next_arg(int ac, char **av, int *i, char **target)
{
    while (*i < ac && !(*av))
    {
        av++;
        *i += 1;
    }
    if (*av)
        *target = *av;
    (*i)++;
    return (av + 1);
}

void arg_parser(int ac, char **av, t_target *target)
{
    for (int i = 1; i < ac; i++)
    {
        if (av[i] && !strcmp(av[i], "-h") && ac > i + 1 && av[i + 1])
        {
            target->header = av[i + 1];
            av[i] = NULL;
            av[i + 1] = NULL;
        }
    }
    int i = 1;
    av = next_arg(ac, av + 1, &i, &(target->target_file));
    av = next_arg(ac, av, &i, &(target->result_file));
    av = next_arg(ac, av, &i, &(target->var_name));
}

void print_header(FILE *out, t_target *target)
{
    char        date_buff[256];
    char        current_dir[1024];
    time_t      rawtime;
    struct tm   *info;

    time(&rawtime);
    getcwd(current_dir, sizeof(current_dir));
    info = localtime(&rawtime);
    strftime(date_buff, sizeof(date_buff), "%a %b %d %X %Y", info);
    fprintf(out,    "/*\n"
                    "** %s for %s in %s\n"
                    "**\n"
                    "** Made by " MYNAME "\n"
                    "** Login   <" MYEMAIL ">\n"
                    "**\n"
                    "** Started on  %s " MYNAME "\n"
                    "** Last update %s " MYNAME "\n"
                    "*/\n\n", target->result_file, target->header, current_dir,
                    date_buff, date_buff);
}

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
    if (target->header)
    {
        print_header(out, target);
    }
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
            fprintf(out, ",%s0x%.2hhx", ((j && j % NL_AT == 0) ? "\n\t\t" : " "), buffer[i]);
            j++;
        }
    }
    fprintf(out, "\n\t};\n");
    close(fd);
    fclose(out);
    if (readed < 0)
    {
        perror("read()");
        exit(84);
    }
}

void print_usage(char *myname, int exit_code)
{
    printf("USAGE : %s [-h project_name] target_file result_file varname\n", myname);
    exit(exit_code);
}

int main(int ac, char **av)
{
    t_target    target;

    memset(&target, 0, sizeof(target));
    if (ac > 3)
    {
        arg_parser(ac, av, &target);
        if (!target.target_file || !target.result_file ||
            !target.var_name)
            print_usage(av[0], 84);
        compute(&target);
    }
    else
    {
        print_usage(av[0], 0);
    }
    return (0);
}