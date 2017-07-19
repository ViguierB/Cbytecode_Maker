#ifndef CBCMAKER_H
# define CBCMAKER_H

# define READ_LENGHT    2048
# define NL_AT          14

typedef struct  s_target
{
    char        *target_file;
    char        *result_file;
    char        *var_name;
}               t_target;

#endif /* !CBCMAKER_H */