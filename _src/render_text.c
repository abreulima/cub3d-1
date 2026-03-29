#include "cub3d.h"
#include <string.h>

void	render_text(t_game *g, char *str, t_point point)
{
	int		i;
	char	letter;
	int		len;
	t_rect	dst_rect;

	i = 0;
	len = strlen(str);
	while (i < len)
	{
		letter = str[i];
		dst_rect.x = point.x + 9 * i;
        dst_rect.y = point.y;
		dst_rect.h = 16;
		dst_rect.w = 8;
		paint_image(g, &g->font[letter - 32], dst_rect);
		i++;
	}
}
