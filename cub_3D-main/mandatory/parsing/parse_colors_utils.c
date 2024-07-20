/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytapano <ytapano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 20:57:12 by ytapano           #+#    #+#             */
/*   Updated: 2024/05/21 20:57:24 by ytapano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static t_bool	com_trail_valid(int index, char *str)
{
	int		digit_count;

	digit_count = 0;
	index++;
	while (str[index] && str[index] != ',')
	{
		while (str[index] && is_wspace(str[index]))
			index++;
		if (ft_isdigit(str[index]))
			digit_count++;
		while (str[index] && ft_isdigit(str[index]))
			index++;
		if (str[index] && str[index] != ','
			&& !ft_isdigit(str[index]) && !is_wspace(str[index]))
			return (FALSE);
	}
	if (digit_count == 1)
		return (TRUE);
	return (FALSE);
}

//I am using index >= 1 and not index >= because I am sending
//trimmed + 1 to the check_syntax function. So I don't want to
//include that C in the beginning
static t_bool	com_prec_valid(int index, char *str)
{
	int		digit_count;

	digit_count = 0;
	index--;
	while (index >= 1 && str[index] != ',')
	{
		while (index >= 1 && is_wspace(str[index]))
			index--;
		if (ft_isdigit(str[index]))
			digit_count++;
		while (index >= 1 && ft_isdigit(str[index]))
			index--;
		if (str[index] != ','
			&& !ft_isdigit(str[index]) && !is_wspace(str[index]))
			return (FALSE);
	}
	if (digit_count == 1)
		return (TRUE);
	return (FALSE);
}

//Logic is simply:
//-1.
//--All ',' characters can only be preceded by digits (whitespace
//--trail allowed)
//-2
//--Implement a counter to make sure tbat there has to be a total
//--of only 2 of these ',' characters that are preceeded by digits
//--(whitespace trail allowed).
//-3
//--Lastly, we also have to check if a ',' is strictly followed by
//--a number via the com_trail_valid function. While this may seem
//--redundant, it is a necessary step to handle [C  242,  23  0,] as
//--in this scenario, there are only 2 ',' characters and each one
//--is in fact preceeded by only digits but clearly it is wrong.
//--So instead of checking for whether there is only one digit
//--before and after a ',', I decided to look the other way
//-4.
//--All characters besides ',', digits, and whitespaces
//--are rejected.
void	check_rgb_syntax(t_game *game, char *full, char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && is_wspace(str[i]))
			i++;
		if (str[i] == ',')
		{
			if (com_prec_valid(i, str) && com_trail_valid(i, str))
				count++;
			else
				break ;
			i++;
		}
		else if (str[i] && (!is_wspace(str[i]) && !ft_isdigit(str[i])))
			break ;
		while (str[i] && ft_isdigit(str[i]))
			i++;
	}
	if (count != 2 || str[i] != '\0')
		exit_err(game, full, "Incorrect color identifier or"
			" incorrect r, g, b syntax");
}
