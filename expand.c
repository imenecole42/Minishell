/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferjani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:46:37 by hferjani          #+#    #+#             */
/*   Updated: 2023/02/14 17:39:35 by hferjani         ###   ########.fr       */
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

void    replace(t_data *data)
{ 
    int dollar;
    int i;
    char *env;
    char *new;

    i = 0;
    dollar = 0;
    env = NULL;
    new = NULL;
    while(data->line[i]){
       // printf("i = %d\n", i);
        while (data->line[i] == '$')
        {
            i++;
            dollar = 1;
            //printf("i = %d\n", i);
            //printf("dollar = %d\n", dollar);
        }
        if (dollar == 1)
        {
            while (ft_isalnum_mini(data->line[i]))
            {
                env = ft_strjoin_char(env, data->line[i]);
                i++;
            }
            env = check_var(env, data);
            if(env){
            //     printf("%s\n", env);
                env = ft_select1(env);
                //printf("%s\n", env);
                new = ft_strjoin(new, env);
                //printf("%s\n", new);
                
                }
                
            dollar = 0;
            
            // else
            // {

            //env = check_var(env, data);
                //printf("%s\n", env);
                // new = ft_strjoin(new, data->line);
                // free(env);
        }
        else
            new = ft_strjoin_char(new, data->line[i]);
        i++;
      }
        data->line = ft_strdup(new);
        free(new);
    }
 

