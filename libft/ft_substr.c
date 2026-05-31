#include <stdio.h>
#include "libftutils.h"

char	*ft_substr(const char*s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	remaining_len;

	if (!s)
		return (NULL);
	if (start >= (size_t)ft_strlen(s))
		return (ft_strdup(""));
	remaining_len = ft_strlen(s + start);
	if (len > remaining_len)
		len = remaining_len;
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, s + start, len +1);
	return (substr);
}