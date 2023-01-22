/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferjani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:43:24 by hferjani          #+#    #+#             */
/*   Updated: 2023/01/17 15:43:27 by hferjani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "struct.h"

int is_special_char(char *line, int i)
{
    if (line[i] == '|')
        return (1);
    else if (line[i] == '>' && line[i + 1] != '>')
        return (2);
    else if (line[i] == '<' && line[i + 1] != '<')
        return (3);
    else if (line[i] == '>' && line[i + 1] == '>')
        return (4);
    else if (line[i] == '<' && line[i + 1] == '<')
        return (5);
    else if (line[i] == '\'')
        return (6);
    else if (line[i] == '\"')
        return (7);
    else if (line[i] == '$')
        return (8);
    else if ((line[i] > 8 && line[i] < 14) || line[i] == 32)
        return (9);
    else if (line[i] == '\0')
        return (10);
    else
        return (0);
}

int set_status(enum e_state status, char *str, int i)
{
    if (str[i] == '\'' && status == DEFAULT)
        status = SQUOTE;
    else if (str[i] == '\"' && status == DEFAULT)
        status = DQUOTE;
    else if (str[i] == '\'' && status == SQUOTE)
        status = DEFAULT;
    else if (str[i] == '\"' && status == DQUOTE)
        status = DEFAULT;
    return (status);
}

int save_word(t_token **lexer, char *line, enum e_state status)
{
    int i;

    i = 0;
    while (is_special_char(line, i) == FALSE)
    {
        i++;
    }
    ft_lstadd_back_token(lexer, create_token(line, i, WORD, status));
    //print_token(&lexer);
    //printf("save word : %s\n", line);
    //printf("save word_struct : %s\n", tmp->value);
    //printf("save word_len : %d\n", tmp->len);
    //printf("save word_type : %d\n", tmp->type);
    //printf("save word_status : %d\n", tmp->qstatus);
    //printf("save_word i: %d\n", i);
    return (i);
}

int save_redirection(t_token **lexer, char *line, int i, enum e_state status)
{
    int j;

    j = i;
    if (is_special_char(line, i) == 2)
        ft_lstadd_back_token(lexer, create_token(line + (i++), 1, REDIR_OUT, status));
    else if (is_special_char(line, i) == 3)
        ft_lstadd_back_token(lexer, create_token(line + (i++), 1, REDIR_IN, status));
    else if (is_special_char(line, i) == 4)
    {
        ft_lstadd_back_token(lexer, create_token(line + (i++), 2, DREDIR_OUT, status));
        i++;
    }
    else if (is_special_char(line, i) == 5)
    {
        ft_lstadd_back_token(lexer, create_token(line + (i++), 2, HEREDOC, status));
        i++;
    }
    return (i - j);
}

int tokenizer(t_token **lexer, char *line, int i, enum e_state status)
{
    if (is_special_char(line, i) == FALSE)
        i += save_word(lexer, line + i, status);
    else if (is_special_char(line, i) == 1)
        ft_lstadd_back_token(lexer, create_token(line + (i++), 1, PIPE, status));
    else if (is_special_char(line, i) == 9)
        ft_lstadd_back_token(lexer, create_token(line + (i++), 1, WHITESPACE, status));
    else if (is_special_char(line, i) > 1 && is_special_char(line, i) < 6)
        i += save_redirection(lexer, line, i, status);
    else if (is_special_char(line, i) == 8)
        ft_lstadd_back_token(lexer, create_token(line + (i++), 1, ENV, status));
    else if (is_special_char(line, i) == 6)
        ft_lstadd_back_token(lexer, create_token(line + (i++), 1, S_QUOTE, status));
    else if (is_special_char(line, i) == 7)
        ft_lstadd_back_token(lexer, create_token(line + (i++), 1, D_QUOTE, status));
    return (i);
}


t_token *read_input(char *line)
{
    int i;
    t_token *lexer;
    enum e_state status;

    i = 0;
    status = DEFAULT;
    lexer = NULL;
    //lexer = malloc(sizeof(lexer));
    //if (!lexer)
        //return (NULL);
    if (is_ascii(line) == FALSE)
    {
        printf("error: invalid characters found");
        // error function
    }
    while (line[i])
    {
        status = set_status(status, line, i);
        //printf("status = %d\n", status);
        // printf("status value : %d\n", status);
        i = tokenizer(&lexer, line, i, status);
        //printf("read_input i:%d\n", i);
        //i++;
    }
    // free(line);
    return (lexer);
}
