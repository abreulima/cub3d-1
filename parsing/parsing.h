/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.lista42.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:12:44 by jde-carv          #+#    #+#             */
/*   Updated: 2026/06/10 18:19:43 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "gnl.h"
# include "libftutils.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum e_parse_err
{
	E_ARGS,
	E_EXT,
	E_OPEN,
	E_EMPTY,
	E_TEX_FMT,
	E_TEX_FILE,
	E_TEX_DUP,
	E_TEX_MISS,
	E_CLR_FMT,
	E_CLR_DUP,
	E_MAP_CHAR,
	E_MAP_PLAYER,
	E_MAP_WALL,
	E_MAP_MISS,
	E_MAP_ORDER,
	E_TAB,
	E_ELEM,
	E_MALLOC,
	E_MLX_INIT,
	E_COUNT
}			t_parse_err;

typedef struct s_flags
{
	unsigned int	file_valid :1;
	unsigned int	has_tex_no : 1;
	unsigned int	has_tex_so : 1;
	unsigned int	has_tex_we : 1;
	unsigned int	has_tex_ea : 1;
	unsigned int	has_color_floor : 1;
	unsigned int	has_color_ceil : 1;
	unsigned int	has_map : 1;
	unsigned int	has_player : 1;
	unsigned int	walls_closed : 1;
}			t_flags;

typedef struct s_parse_data
{
	char	*tex_no;
	char	*tex_so;
	char	*tex_we;
	char	*tex_ea;
	int		floor_r;
	int		floor_g;
	int		floor_b;
	int		ceil_r;
	int		ceil_g;
	int		ceil_b;
	char	**map;
	int		map_w;
	int		map_h;
	char	player_dir;
	int		player_x;
	int		player_y;
	t_flags	flags;
}			t_parse_data;

int			flags_all_set(t_flags *flags);

void		parse_error(int err_id);
char		*get_err_msg(int err_id);
int			parse_file(char *path, t_parse_data *data);
int			parse_line(char *line, t_parse_data *data, int *map_started);
int			parse_texture(char *line, t_parse_data *data);
int			parse_color(char *line, t_parse_data *data);
int			parse_map_line(char *line, t_parse_data *data);
int			validate_map(t_parse_data *data);
int			check_file_ext(char *path);
int			has_all_elements(t_parse_data *data);
int			has_tab(char *line);
int			is_empty_line(char *line);
int			is_map_line(char *line);
void		init_parse_data(t_parse_data *data);
void		free_parse_data(t_parse_data *data);
char		*skip_spaces(char *str);
int			ft_isdigit(int c);
int			ft_atoi_safe(char *str, int *result);
int			check_tex_extension(char *path);
int			validate_tex_path(char *path);
char		*extract_path(char *line);
int			assign_texture(char *path, char **dest);
int			parse_tex_dir(char *line, char *path, t_parse_data *data);

#endif
