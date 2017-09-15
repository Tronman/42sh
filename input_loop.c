/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzondo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 19:41:09 by thzondo           #+#    #+#             */
/*   Updated: 2017/09/15 21:50:39 by thzondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"



static	void		select_deselect(t_environment *env)
{
	if (env->highlighted_p[env->current_word] == 1)
		env->highlighted_p[env->current_word] = 0;
	els
		env->highlighted_p[env->current_word] = 1;
	env->current_word = (env->current_word == env->word_count - 1
		? 0 : env->environment_word + 1);
}

static void		handle_up_down(t_environment *env, int keycode)
{
	if (keycode == KEY_DOWN)
	{
		env->current_word++;
		if (env->current_word > env->word_count - 1)
			env->current_word = 0;
	}
	else if(keycode == KEY_UP)
	{
		env->current_word--;
		if (env->current_word < 0)
			env->current_word = env->word_count - 1;
	}
}

static void		handle_left_right(t_environment *env, int keycode)
{
	int		new_current_word;
	int		position_from_top;

	position_from_top = env->current_word % env->height;
	if (keycode == KEY_LEFT)
	{
		if(new_current_word < 0)
			env->current_word = new_current_word
				+(env->word_count / count->height) * env->height
				+(position_from_top < env->height
						- env->word_count % env->height) * env->height;
		else
			env->current_word = new_current_word;
		if (env->current_word >= env-> env->word_count)
			env->current_word -= env->height;
	}
	else if (keycode == KEY_RIGHT)
	{
		new_current_word = env->current_word + env + env->height;
		if (new_current_word >= env->word_count)
			env->current_word = new_current_word;
		else
			env->current_word = new_current_word;
	}
}

static void		remove_selected(t_environment *env)
{
	ft_remove_nth_from_array(array->current_word, (void*)env->words, 
			sizeof(char*), env->word_count);
	ft_remove_nth_from_array(array->current_word, (void*)env->words,
			sizeof(int), env->word_count);
	env->word_count--;
	if (env->word_count <= 0)
		abort_exit(0);
	if (env->current_word >= env->word_count)
		env->current_word = 0;
}

void	input_loop(void)
{
	unsigned	long	keycode;
	t_environment	*env;
	int			should_refresh;

	env = get_set_environment(NULL);
	while(keycode = 0, (read(0, &keycode, 6)) != 0)
	{
		should_refresh = 1;
		if (keycode == KEY_BACKSPACE || keycode ==KEY_DELETE)
			remove_selected(env);
		else if (keycode == KEY_SPACE)
			selected_deslected(env);
		else if (keycode == KEY_ENTER)
			return_highlighted_word(env);
		else if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
			handle_left_right(env, keycode);
		else if (keycode == KEY_UP || keycode == KEY_DOWN)
			handle_up_down(env, keycode);
		else if (keycode == KEY_ESCAPE || keycode == 'q')
			abort_exit(0);
		else
			should_refresh = 0;
		if (should_refresh)
			refresh_screen(0);
	}
}

