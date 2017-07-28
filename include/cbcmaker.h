#ifndef CBCMAKER_H
# define CBCMAKER_H

# define READ_LENGHT    2048
# define NL_AT          12
# define MYNAME         "Benjamin Viguier"
# define MYEMAIL        "benjamin.viguier@epitech.eu"

typedef struct  s_target
{
    char        *target_file;
    char        *result_file;
    char        *var_name;
    char        *header;
}               t_target;

#endif /* !CBCMAKER_H */