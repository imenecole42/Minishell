/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferjani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:46:37 by hferjani          #+#    #+#             */
/*   Updated: 2023/02/16 15:45:45 by hferjani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
    
/*char *str_to_find(char *str)
{
    int i;
    int start;
    int end;
    char    *dest;
    
    i = 0;
    
        // flag_quotes = open_quotes(str, i);
        // printf("%d\n",flag_quotes);
        while (str[i] == '$')
            i++;
        start = i;
        printf("%d\n", start);
        while (str[i] && ft_isalnum_mini(str[i]))
            i++;
        end = i;
        printf("%d\n", end);
        i = 0;
        dest = malloc(sizeof(char) * ((end - start) + 1));
        if (!dest)
            return (NULL);
        while (start<end && ft_isalnum_mini(str[start]))
        {
            dest[i] = str[start];
            i++;
            start++;
        }
        dest[i]='\0';
        return (dest);
    }*/
    
char	*ft_strjoin_char(char const *s1, char s2)
{
	char	*ret;
	size_t	s1_len;
    
    ret = NULL;
    s1_len = 0;
	if (!s1 && !s2)
		return (0);
	else if (!s1)
		return (ft_strdup(&s2));
	else if (!s2)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	ret = (char *)malloc(sizeof(char) * (s1_len + 2));
	if (!ret)
		return (0);
	ft_strlcpy(ret, s1, s1_len + 1);
	ft_strlcpy(ret + s1_len, &s2, 2);
	return (ret);
}

char *env_finder(char *line, int start, int end)
{
    int i;
    char *str;
    char *dup;

    i = 0;
    str = NULL;
    dup = ft_strdup(line);
    str = malloc(sizeof(char) * (end - start + 1));
    str[(end - start)] = '\0';
    while (start < end)
    {
        str[i] = dup[start];
        i++;
        start++;
    }
    free(dup);
    return(str);
}

void    replace(t_data *data)
{ 
    int dollar;
    int i;
    int start;
    int end;
    char *env;
    char *new;

    i = 0;
    start = 0;
    end = 0;
    dollar = 0;
    env = NULL;
    new = NULL;
    while(data->line[i])
    {
        while (data->line[i] == '$' && data->line[i])
        {
            i++;
            dollar = 1;
        }
        if (dollar == 1)
        {
            start = i;
            while (ft_isalnum_mini(data->line[i]) && data->line[i])
            {
                i++;
            }
            printf("c = %c\n", data->line[i]);
            printf("i = %d\n", i);
            end = i;
            env = env_finder(data->line, start, end);
            env = check_var(env, data);
            if(env)
            {
                env = ft_select1(env);
                new = ft_strjoin(new, env);
                free(env);
            }
            dollar = 0;
        }
        new = ft_strjoin_char(new, data->line[i]);
        if (data->line[i] != '$' && data->line[i])
            i++; 
      }
    data->line = ft_strdup(new);
    printf("%s\n", data->line);
    free(new);
    }
 

