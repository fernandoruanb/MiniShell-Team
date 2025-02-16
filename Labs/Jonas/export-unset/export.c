#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>

typedef struct s_export
{
	char			*name;
	char			*value;

	struct s_export	*next;
}	t_export;

/*
	the flag if to define if the first letter is valid

	set to 0 for all valid characters
*/
static int	valid_name(char c, int flag)
{
	if (flag)
		return (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) || c == '_');
	return (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
			|| c == '_'
			|| (c >= '0' && c <= '9'));
}

int	is_quote(unsigned char c)
{
	return (c == '\'' || c == '\"');
}

static int	namevalidation(char *input)
{
	int	i;

	if (!input || !valid_name(input[0], 1))
		return (0);
	i = 0;
	while (input[i] && input[i] != '=')
		if (!valid_name(input[i++], 0))
			return (0);
	return (i);
}

static char	*get_var(char *input)
{
	char	*var;
	int		i;

	i = 0;
	while (input[i])
		if (input[i++] == ' ' && !is_quote(input[0]))
			break ;
	var = calloc(i + 1, 1);
	if (!var)
		return (NULL);
	i = 0;
	while (input[i])
	{
		if (input[i] == ' ' && !is_quote(input[0]))
			break ;
		var[i] = input[i];
		i++;
	}
	return (var);
}

char	*ft_strndup(char *str, int n)
{
	int		i;
	char	*dup;

	if (!str)
		return (NULL);
	dup = calloc(n + 1, 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (str[i] && i < n)
	{
		dup[i] = str[i];
		i++;
	}
	return (dup);
}

int	my_free_my_life(void *s1, void *s2, void *s3, int __return__)
{
	free(s1);
	free(s2);
	free(s3);
	return (__return__);
}

static t_export	*export_last(t_export **var)
{
	t_export	*temp;

	temp = *var;
	while (temp && temp->next)
		temp = temp->next;
	return (temp);
}

static int	ft_export(char *input, t_export **var)
{
	int 		len;
	t_export	*new;
	t_export	*temp;

    if (!input)
        return (1);
    len = namevalidation(input);
    if (!len)
        return (1);
    new = calloc(sizeof(t_export), 1);
    if (!new)
        return (1);
    new->name = ft_strndup(input, len);
    new->value = get_var(&input[len + 1]);
    if (!new->name || !new->value)
        return (my_free_my_life(new->name, new->value, new, 1));
	if (!(*var))
		*var = new;
	else
	{
		temp = export_last(var);
		temp->next = new;
	}
    return (0);
}

/*
	input must recieve a pointer after the command
	ex:
		$ export var=hello

		'v' is the 8th index so
			ft_export(&input[8], data->var);
*/
// int	ft_export(char *input, t_export *var)
// {
// 	if (!input)
// 		return (1);
// 	if (!var)
// 		return (export_add(input, var));
// 	return (ft_export(input, var->next));
// }

t_export	*search_var(t_export **var, char *name)
{
	t_export	*temp;

	temp = *var;
	while (temp)
	{
		if (strcmp(temp->name, name) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_export	*var = NULL;
	t_export	*temp;

	for (int i = 1; argv[i]; i++)
		if (ft_export(argv[i], &var))
			return (1);
	temp = search_var(&var, "VAR");
	printf("value: %s\n", temp->value);
	while(var)
	{
		printf("%s = %s\n", var->name, var->value);
		var = var->next;
	}
	return (0);
}
