/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_space.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatthie <mmatthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 11:17:02 by mmatthie          #+#    #+#             */
/*   Updated: 2022/06/27 18:52:14 by mmatthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	skip_quotes(char	*buffer, int i)
{
	char	tmp;

	tmp = buffer[i];
	i++;
	while (buffer[i] != tmp && buffer[i])
		i++;
	if (buffer[i] == tmp)
		i++;
	return (i);
}

static int	ft_check_token(char c, char d)
{
	char	*token;
	int		i;

	i = 0;
	token = "><|";
	while (token && token[i])
	{
		if (c == token[i])
		{
			if (c == d)
				return (2);
			else
				return (0);
		}
		i++;
	}
	return (1);
}

static int	check_len4add_space(char	*buffer, t_data	*data)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	(void) data;
	if (buffer && buffer[i])
	{
		while (buffer[i])
		{
			while ((ft_check_token(buffer[i], buffer[i + 1]) == 1) \
			&& buffer[i] != '\'' && buffer[i] != '"' && buffer[i])
				i++;
			if (buffer[i] == '\'' || buffer[i] == '"')
				i = skip_quotes(buffer, i);
			if (ft_check_token(buffer[i], buffer[i + 1]) == 2)
			{
				res += 2;
				i += 2;
			}
			else if (ft_check_token(buffer[i], buffer[i + 1]) == 0)
			{
				res += 2;
				i++;
			}
		}
	}
	return (i + res);
}

char	*ft_space_routine(char	*buffer, t_data	*data, char	*str)
{
	if (buffer && buffer[data->i_space])
	{
		while ((ft_check_token(buffer[data->i_space], buffer[data->i_space + 1]) == 1) \
		&& buffer[data->i_space] != '\'' && buffer[data->i_space] != '"' && buffer[data->i_space])
			str[data->j_space++] = buffer[data->i_space++];
		if (ft_check_token(buffer[data->i_space], buffer[data->i_space + 1]) == 2)
		{
			str[data->j_space] = ' ';
			str[data->j_space + 1] = buffer[data->i_space];
			str[data->j_space + 2] = buffer[data->i_space];
			str[data->j_space + 3] = ' ';
			data->j_space += 4;
			data->i_space += 2;
		}
		else if (ft_check_token(buffer[data->i_space], buffer[data->i_space + 1]) == 0)
		{
			str[data->j_space] = ' ';
			str[data->j_space + 1] = buffer[data->i_space];
			str[data->j_space + 2] = ' ';
			data->j_space += 3;
			data->i_space += 1;
		}
	}
	return (str);
}


char	*ft_add_space(char	*buffer, t_data	*data)
{
	int		len;
	char	*str;

	len = check_len4add_space(buffer, data);
	str = malloc(sizeof(char) * len + 1);
	data->i_space = 0;
	data->j_space = 0;
	if (!str)
		return (NULL);
	if (buffer && buffer[data->i_space])
	{
		while (buffer && buffer[data->i_space])
		{
			if (buffer[data->i_space] == '\'' || buffer[data->i_space] == '"')
			{
				len = skip_quotes(buffer, data->i_space);
				while (data->j_space < len)
				str[data->j_space++] = buffer[data->i_space++];
			}
			else
				str = ft_space_routine(buffer, data, str);
		}
		free (buffer);
		str[data->j_space] = '\0';
	}
	return (str);
}
