/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_large_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 19:13:40 by tgelu             #+#    #+#             */
/*   Updated: 2018/05/29 20:06:54 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

void		print_two_bytes(t_printf *pf, wchar_t value)
{
	buffer_add_char(pf, (char)((value >> 6) + 0xC0));
	buffer_add_char(pf, (char)((value & 0x3F) + 0x80));
	buffer_clean(pf);
}

void        print_three_bytes(t_printf *pf, wchar_t value)
{
	buffer_add_char(pf, (char)(value >> 12) + 0xE0);
	buffer_add_char(pf, (char)((value >> 6) & 0x3F) + 0x80);
	buffer_add_char(pf, (char)((value & 0x3F) + 0x80));
	buffer_clean(pf);
}

void        print_four_bytes(t_printf *pf, wchar_t value)
{

	buffer_add_char(pf, (char)(value >> 18) + 0xF0);
	buffer_add_char(pf, (char)((value >> 12) & 0x3F) + 0x80);
	buffer_add_char(pf, (char)((value >> 6) & 0x3F) + 0x80);
	buffer_add_char(pf, (char)((value & 0x3F) + 0x80));
	buffer_clean(pf);
}

void		process_large_char(t_printf *pf, wchar_t value)
{
	// 0x3F = 11111100
	// 0xF0 = 11110000
	// 0xE0 = 11100000
	// 0xC0 = 11000000
	// 0x80 = 10000000

	if (value <= 0x7F)
		buffer_add_char(pf, (char)value);
	else if (value <= 0x7FF)
		print_two_bytes(pf, value);
	else if (value <= 0xFFFF)
		print_three_bytes(pf, value);
	else if (value <= 0x10FFFF)
		print_four_bytes(pf, value);
	else
		pf->err = 1;
}
