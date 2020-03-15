/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 12:28:44 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/15 13:29:46 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_TABLE_H
# define HASH_TABLE_H

typedef struct	s_ht_entry
{
	char				*key;
	char				*value;
	struct s_ht_entry	*next;
}				t_ht_entry;

typedef struct	s_ht
{
	t_ht_entry	**entries;
	unsigned int	size;
}				t_ht;

t_ht			*ht_create(unsigned int size);
void			ht_set(t_ht *ht, const char *key, const char *value);
char			*ht_get(t_ht *ht, const char *key);

#endif
