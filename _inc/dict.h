typedef struct s_dict
{
	char *key;
	char *value;
	struct s_dict *next;
} t_dict;

t_dict	*dict_new(const char *key, const char *value);
char	*dict_get(t_dict *head, const char *key);
int	dict_set(t_dict **env, const char *key, const char *value);
void	free_map(t_dict *env);
