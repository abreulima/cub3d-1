#include "parsing.h"

static int	check_tex_extension(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 5)
		return (0);
	if (ft_strcmp(path + len - 4, ".xpm") == 0)
		return (1);
	if (ft_strcmp(path + len - 4, ".png") == 0)
		return (1);
	return (0);
}

static int	validate_tex_path(char *path)
{
	int	fd;

	if (!check_tex_extension(path))
		return (parse_error(E_TEX_FMT), -1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (parse_error(E_TEX_FILE), -1);
	close(fd);
	return (0);
}

static char	*extract_path(char *line)
{
	char	*start;
	char	*end;
	int		len;
	char	*path;

	start = line + 3;
	while (*start == ' ')
		start++;
	if (!*start || *start == '\n')
		return (NULL);
	end = start;
	while (*end && *end != ' ' && *end != '\n')
		end++;
	while (*end == ' ')
	{
		if (*(end + 1) && *(end + 1) != ' ' && *(end + 1) != '\n')
			return (NULL);
		end++;
	}
	len = 0;
	while (start[len] && start[len] != ' ' && start[len] != '\n')
		len++;
	path = ft_substr(start, 0, len);
	return (path);
}

static int	assign_texture(char *path, char **dest)
{
	if (*dest != NULL)
		return (free(path), parse_error(E_TEX_DUP), -1);
	if (validate_tex_path(path) == -1)
		return (free(path), -1);
	*dest = path;
	return (0);
}

static int	parse_tex_dir(char *line, char *path, t_parse_data *data)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (assign_texture(path, &data->tex_no) == -1)
			return (-1);
		return (data->flags.has_tex_no = 1, 0);
	}
	if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (assign_texture(path, &data->tex_so) == -1)
			return (-1);
		return (data->flags.has_tex_so = 1, 0);
	}
	return (2);
}

int	parse_texture(char *line, t_parse_data *data)
{
	char	*path;
	int		ret;

	path = extract_path(line);
	if (!path)
		return (parse_error(E_TEX_FMT), -1);
	ret = parse_tex_dir(line, path, data);
	if (ret <= 0)
		return (ret);
	if (ft_strncmp(line, "WE ", 3) == 0)
	{
		if (assign_texture(path, &data->tex_we) == -1)
			return (-1);
		return (data->flags.has_tex_we = 1, 0);
	}
	if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if (assign_texture(path, &data->tex_ea) == -1)
			return (-1);
		return (data->flags.has_tex_ea = 1, 0);
	}
	return (free(path), parse_error(E_TEX_FMT), -1);
}
