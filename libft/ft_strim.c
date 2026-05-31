#include <stdlib.h>

#include "libftutils.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*strtim;
	size_t	start;
	size_t	end;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (s1[end] && ft_strchr(set, s1[end]))
		end--;
	strtim = ft_substr(s1, start, end - start + 1);
	return (strtim);
}
