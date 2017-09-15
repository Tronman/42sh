/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzondo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 19:24:30 by thzondo           #+#    #+#             */
/*   Updated: 2017/09/14 19:56:42 by thzondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_select.h"

static void	set_signals(void	(*restart_function))
{
	signal(SIGWITCH, refresh_screen);
	signal(SIGCON, restart_function);
	signal(SIGTSTP,abort_no_exit);
	signal(SIGINT, abort_exit);
	signal(SIGHUP, abort_exit);
	signal(SIGTERM, abort_exit);
	signal(SIGSEGV, abort_exit);
	signal(SIGQUIT, abort_exit);
	signal(SIGFPE,abort_exit);
	signal(SIGALRM, abort_exit);
	signal(SIGKILL, abort_exit);
	signal(SIGABRT, abort_exit);
	signal(SIGUSR1, abort_exit);
	signal(SIGUSR2, abort_exit);
}

static void	    setup_terminal(t_environment *env)
{
	char	*terminal_name;

	if(!(terminal_name = getenv("TERM")))
		ft_putlenfl_exit("Error getting env->TERM", 1);
	if(tgetent(NULL, terminal_name) <= 0)
	{
		ft_putlendl_fd("Error getting env->TERM", 2);
		exit(1);
	}
	tcgetattr(0, &nv->term);
	env->term.c_lflag &= ~(ICANON);
	env->term.c_lflag &= ~(ECHO);
	env->term.c_cc[VMIN] = 1;
	env->term.c_cc[VTIME] = 0;
	if(tcsetattr(0, TCSDRAIN, &env->term) == -1)
		exit(1);
	ft_putstr_fd(tgetstr("ti", NULL), 2);
	ft_putstr_fd(tgetstr("vi", NULL), 2);
}

static void     restart(int signum)
{
	t_environment	*env;

	(void) signum;
	env = get_set_environment(NULL);
	setup_terminal(env);
	set_signals(&restart);
	refresh_screen(0);
}


static		void	setupenvironment(t_environment *env, int argc, char **argv)
{
	env->words = argv + 1;
	env->word_count = argc - 1;
	env->highlighted_p = malloc((argc - 1) * sizeof(int));
	ft_bzero(env->highlighted_p, (argc -1) * sizeof(int));
	env->current_word = 0;
	env->single_collumn_width = get_longest_word_length(env) + 2;
	setup_terminal(env);
}

int		main(int argc , char *argv[])
{
	if(argc < 2)
		ft_putlendl_fd_exit("Usage: ft_select [parameters]", 2, 1);
	env = malloc(sizeof(t_environment))l;
	setup_environment(env, argc, argv);
	get_set_environment(env);
	set_signals(&restart);
	refresh_screen(0);
	input_loop();
	return(0);
}
