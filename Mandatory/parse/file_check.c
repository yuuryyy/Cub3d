/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 02:25:13 by ychagri           #+#    #+#             */
/*   Updated: 2025/03/22 02:07:01 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_parse.h"

t_list	*get_file_content(char *filename)
{
	char	*extenstion;
	int		fd;
	char	*line;
	t_list	*content;

	extenstion = ft_strrchr(filename, '.');
	if (!extenstion || ft_strncmp(extenstion, ".cub", 5))
		return (error(FILNAM), NULL);
	fd = open(filename, O_RDONLY, 0644);
	if (fd == -1)
		return (error(NULL), perror(filename), NULL);
	line = get_next_line(fd);
	content = NULL;
	while (line)
	{
		ft_lstadd_back(&content, ft_lstnew(line));
		line = get_next_line(fd);
	}
	close(fd);
	if (!content)
		return (error("Empty file content"), NULL);
	return (content);
}

bool	is_empty(char *line)
{
	int	i;

	i = 0;
	if (!line || !*line || *line == '\n')
		return (true);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] && line[i] != '\n')
		return (false);
	return (true);
}

t_list	*index_map(t_list *content)
{
	t_list	*tmp;
	int		index;

	tmp = content;
	index = 6;
	while (tmp && index)
	{
		if (!is_empty(tmp->content))
			index--;
		tmp = tmp->next;
	}
	while (tmp && is_empty(tmp->content))
		tmp = tmp->next;
	return (tmp);
}

char	**get_map(t_list *content)
{
	char	**map;
	t_list	*start;
	t_list	*tmp;
	int		len;

	len = 0;
	tmp = content;
	start = (index_map(tmp));
	while (tmp)
	{
		tmp = tmp->next;
		len++;
	}
	map = malloc((len + 1) * sizeof(char *));
	if (!map)
		return (NULL);
	len = 0;
	while (start)
	{
		map[len++] = ft_strdup(start->content);
		start = start->next;
	}
	map[len] = NULL;
	return (map);
}

int	is_texture(char *line, t_textures *texture)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (!ft_strncmp(&line[i], "NO ", 3) || !ft_strncmp(&line[i], "NO\t", 3))
		return (texture->no_txtr = ft_strdup(line), 1);
	else if (!ft_strncmp(&line[i], "SO ", 3) || !ft_strncmp(&line[i], "SO\t", 3))
		return (texture->so_txtr = ft_strdup(line), 1);
	else if (!ft_strncmp(&line[i], "WE ", 3) || !ft_strncmp(&line[i], "WE\t", 3))
		return (texture->we_txtr = ft_strdup(line), 1);
	else if (!ft_strncmp(&line[i], "EA ", 3) || !ft_strncmp(&line[i], "EA\t", 3))
		return (texture->ea_txtr = ft_strdup(line), 1);
	else if (!ft_strncmp(&line[i], "F ", 2) || !ft_strncmp(&line[i], "F\t", 2))
		return (texture->f_color = ft_strdup(line), 1);
	else if (!ft_strncmp(&line[i], "C ", 2) || !ft_strncmp(&line[i], "C\t", 2))
		return (texture->c_color = ft_strdup(line), 1);
	return (0);
}

int	get_textures(t_list *content, t_data *data)
{
	t_list	*tmp;
	int		texture_num;
	int		err;

	if (!content || !data)
		return (1);
	tmp = content;
	texture_num = 6;
	while (tmp)
	{
		if (is_empty(tmp->content))
		{
			tmp = tmp->next;
			continue;
		}
		err = is_texture(tmp->content, data->textures);
		if (err)
			texture_num--;
		else if (!err && texture_num != 0)
			break;
		tmp = tmp->next;
	}
	if (texture_num != 0)
		return (free_data(data), ft_lstclear(&content, free_del), error(CONFERR), 1);
	return (0);
}
