#include "dict.h"
#include "minilibft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int	dict_set(t_dict **env, const char *key, const char *value)
{
	t_dict *current;
	t_dict *new;

	if (!env || !key)
		return (-1);
	current = *env;
	while (current && current->key)
	{
		if (ft_strcmp(key, current->key) == 0)
			return (-1);
		current = current->next;
	}
	new = dict_new(key, value);
	if (!new)
		return (-1);
	new->next = *env;
	*env = new;
	return (0);
}

t_dict	*dict_new(const char *key, const char *value)
{
	t_dict *new;

	if (!key)
		return (NULL);
	new = malloc(sizeof(t_dict));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	if (!new->key)
		return (free(new), NULL);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = ft_strdup("");
	if (!new->value)
	{
		free(new->key);
		free(new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

char	*dict_get(t_dict *head, const char *key)
{
	t_dict *current;

	if (!head)
		return (NULL);
	current = head;
	if (!key)
		return (NULL);
	while (current)
	{
		if (ft_strcmp(key, current->key) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

void	free_map(t_dict *env)
{
	t_dict *current;
	t_dict *next;

	current = env;
	while (current)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
}
