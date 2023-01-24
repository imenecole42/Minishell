/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferjani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:43:13 by hferjani          #+#    #+#             */
/*   Updated: 2023/01/24 17:09:18 by hferjani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "struct.h"

int is_ascii(char *s)
{
    int i;

    i = 0;
    while (s[i])
    {
        if (!ft_isascii(s[i]))
            return (0);
        i++;
    }
    return (1);
}

int forbidden_series(char *s)
{
    int i;
    int flag;
    
    i = 0;
    flag = 0;
    //printf("%d\n", flag_quote);
    while (s[i])
    {
        flag = open_quotes(s, i);
        if (s[i] == ';' && s[i + 1] == ';' && !flag)
            return (1);
        else if (s[i] == '|' && s[i + 1] == ';' && !flag)
            return (1);
        else if (s[i] == '&' && s[i + 1] == ';' && !flag)
            return (1);
        else if (s[i] == ';' && s[i + 1] == '&' && !flag)
            return (1);
        else if (s[i] == '>' && s[i + 1] == '>' && s[i + 2] == '>' && !flag)
            return (1);
        i++;
    }
    return (0);
}

/*int forbidden_series(t_token *token)
{
    t_token *cur;
    //static char *enumCharacter[] = {";", "&"};
    
    cur = token;
    while (cur->next != NULL && cur->qstatus == DEFAULT)
    {
        if ((ft_strncmp(cur->value, ";", 1) == 0)  &&(ft_strncmp(cur->value, ";", 1) == 0))
            return (1);
        else if (cur->type == PIPE && (ft_strncmp(cur->next->value,";", 1) == 0))
            return (1);
        else if ((ft_strncmp(cur->value, "&", 1) == 0) && (ft_strncmp(cur->next->value,";", 1) == 0))
            return (1);
        else if ((ft_strncmp(cur->value, ";", 1) == 0) && (ft_strncmp(cur->next->value,"&", 1) == 0))
            return (1);
        else if (cur->type == DREDIR_OUT && cur->next->type == REDIR_OUT)
            return (1);
        cur = cur->next;
    }
    return (0);
}*/
t_token *create_token(char *value, int len, enum e_type type, enum e_state status)
{
    t_token *new_node;
    char    *word;

    new_node = malloc(sizeof(t_token));
    word = strndup(value, len); // recoder la fonction
    if (!new_node)
        return (NULL);
    new_node->value = word;
    new_node->len = len;
    new_node->type = type;
    new_node->qstatus = status;
    new_node->next = NULL;
    //free (word);
    // printf("**************************\n");
    // printf("input : %s\n", value);
    // printf("value node : %s\n", new_node->value);
    // printf("len : %d\n", new_node->len);
    // printf("type : %d\n", new_node->type);
    // printf("status : %d\n", new_node->qstatus);
    // printf("**************************\n");
    return (new_node);
}

void	ft_lstadd_back_token(t_token **lst, t_token *new)
{
	t_token	*last;

	last = *lst;
	/*if (!new || !lst)
		return ;*/
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (last->next != NULL)
	last = last->next;
	last->next = new;
}



void    print_token(t_token **head)
{
    t_token *cur;
    static char *enumStrings[] = {"WORD", "WHITESPACE", "NEW_LINE", "PIPE", "HEREDOC", "ENV", "REDIR_IN", "REDIR_OUT", "DREDIR_OUT", "S_QUOTE", "D_QUOTE"};
    static char *enumQuotes[] = {"DEFAULT", "SQUOTE", "DQUOTE"};

    cur = *head;
    while (cur != NULL)
    {
        printf("-----------------------------------\n");
  	    printf("| len = %d                            \n", cur->len);
  	    printf("| head->value : %s            \n", cur->value);
        printf("| type = %s                            \n", enumStrings[cur->type]);
        printf("| quote = %s                            \n", enumQuotes[cur->qstatus]);
  	    printf("-----------------------------------\n");
  	    cur = cur->next;
    }
    
}



/*void	push(t_token **head_ref, t_token *new)
{
	//t_list	*new_node;
	t_token	*tmp;

	//new_node = malloc(sizeof(t_list));
	//if (!new_node)
		//return ;
	//new_node->value = new_data;
	//new_node->next = NULL;
	if (!*head_ref)
	(*head_ref) = new;
	else
	{
		tmp = (*head_ref);
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}*/

/*void print_liste(t_token * head) {
    t_token * current = head;
    while (current != NULL) {
        printf("len[%d]\n", current->len);
        current = current->next;
    }
}*/