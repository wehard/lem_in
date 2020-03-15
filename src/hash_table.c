/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 12:28:09 by wkorande          #+#    #+#             */
/*   Updated: 2020/03/15 14:02:48 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_table.h"
#include "libft.h"
#include "ft_printf.h"
#include <stdlib.h>

static unsigned int	ht_hash(t_ht *ht, const char *key)
{
	unsigned long	value;
	int				i;
	int				key_len;

	key_len = ft_strlen(key);
	value = 0;
	i = 0;
	while (i < key_len)
		value = value * 37 + key[i++];
	value = value % ht->size;
	return (value);
}

static t_ht_entry	*ht_make_pair(const char *key, const char *value)
{
	t_ht_entry	*entry;

	if (!(entry = (t_ht_entry*)malloc(sizeof(t_ht_entry))))
		return (NULL);
	if (!(entry->key = (char*)malloc(sizeof(char) * ft_strlen(key) + 1)))
		return (NULL);
	if (!(entry->value = (char*)malloc(sizeof(char) * ft_strlen(value) + 1)))
		return (NULL);
	ft_strcpy(entry->key, key);
	ft_strcpy(entry->value, value);
	entry->next = NULL;
	return (entry);
}

t_ht				*ht_create(unsigned int size)
{
	t_ht			*ht;
	unsigned int	i;

	if (!(ht = (t_ht*)malloc(sizeof(t_ht))))
		return (NULL);
	ht->size = size;
	if (!(ht->entries = (t_ht_entry**)malloc(sizeof(t_ht_entry*) * size)))
		return (NULL);
	i = 0;
	while (i < ht->size)
	{
		ht->entries[i] = NULL;
		i++;
	}
	return (ht);
}

void				ht_set(t_ht *ht, const char *key, const char *value)
{
	unsigned int	pos;
	t_ht_entry		*cur;
	t_ht_entry		*prev;

	pos = ht_hash(ht, key);
	cur = ht->entries[pos];
	if (cur == NULL)
	{
		ht->entries[pos] = ht_make_pair(key, value);
		return ;
	}
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
		{
			free(cur->value);
			if (!(cur->value = (char*)malloc(sizeof(char) * ft_strlen(value) + 1)))
				return ;
			ft_strcpy(cur->value, value);
			return ;
		}
		prev = cur;
		cur = prev->next;
	}
	prev->next = ht_make_pair(key, value);
}

char			*ht_get(t_ht *ht, const char *key)
{
	unsigned int	pos;
	t_ht_entry		*cur;

	pos = ht_hash(ht, key);
	cur = ht->entries[pos];
	if (!cur)
		return (NULL);
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
			return (cur->value);
		cur = cur->next;
	}
	return (NULL);
}

void print_ht(t_ht *ht)
{
	unsigned int i;

	i = 0;
	while (i < ht->size)
	{
		t_ht_entry *entry = ht->entries[i];
		if (entry == NULL) {
			i++;
			continue;
		}
		ft_printf("pos [%3d]: ", i);
		while(1)
		{
			ft_printf("%s:%s ", entry->key, entry->value);
			if (entry->next == NULL) {
				break;
			}
			entry = entry->next;
		}
		ft_printf("\n");
		i++;
	}
}
