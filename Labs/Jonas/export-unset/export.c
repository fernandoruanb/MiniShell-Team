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
	struct s_export	*prev;
}	t_export;

typedef struct	s_var
{
	char			*name;
	char			*value;

	struct s_var	*next;
	struct s_var	*prev;
}	t_localvar;

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

static int	export_print(t_export **var)
{
	t_export	*temp;

	temp = *var;
	while(temp)
	{
		printf("declare -x %s=%s\n", temp->name, temp->value);
		temp = temp->next;
	}
	return (0);
}

static int	ft_export(char *input, t_export **var)
{
	int 		len;
	t_export	*new;
	t_export	*temp;

    if (!input)
        return (export_print(var));
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
		new->prev = temp;
	}
    return (0);
}

static t_localvar	*local_last(t_localvar **var)
{
	t_localvar	*temp;

	temp = *var;
	while (temp && temp->next)
		temp = temp->next;
	return (temp);
}

static int	ft_localvar(char *input, t_localvar **var)
{
	int 		len;
	t_localvar	*new;
	t_localvar	*temp;

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
		temp = local_last(var);
		temp->next = new;
		new->prev = temp;
	}
    return (0);
}

void	clean_locals(t_localvar	*var)
{
	if (!var)
		return ;
	if (var->next)
		clean_locals(var->next);
	free(var->name);
	free(var->value);
	free(var);
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

void	ft_unset(t_export **var, char *name)
{
	t_export	*temp;

	if (!name)
		return ;
	temp = search_var(var, name);
	if (!temp)
		return ;
	if (*var == temp)
		*var = temp->next;
	if (temp->prev)
		temp->prev->next = temp->next;
	if (temp->next)
		temp->next->prev = temp->prev;
	free(temp->name);
	free(temp->value);
	free(temp);
}

void	export_clean(t_export **var)
{
	while (*var)
		ft_unset(var, (*var)->name);
}

void	export_init(char **envp, t_export **var)
{
	int	i;

	i = -1;
	while (envp[++i])
		ft_export(envp[i], var);
}

int	main(int argc, char **argv, char **envp)
{
	t_export	*var = NULL;
	t_export	*temp;
	t_localvar		*temp_var = NULL;
	int	i;

	i = 0;
	export_init(envp, &var);
	if (argc == 1)
		ft_export(NULL, &var);
	else
		for (i = 1; i < argc - 1; i++)
			if (ft_export(argv[i], &var))
				return (1);
	export_print(&var);
	if (argc > 1)
	{
		ft_localvar(argv[i], &temp_var);
		printf("\nLocal\n%s=%s\n", temp_var->name, temp_var->value);
		clean_locals(temp_var);
	}
	export_clean(&var);
	return (0);
}
