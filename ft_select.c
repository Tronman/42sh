/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzondo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 16:11:43 by thzondo           #+#    #+#             */
/*   Updated: 2017/09/13 18:15:53 by thzondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


static  void        set_signals(void(*restart_function)(int))
{
    signal(SIGWINCH, refresh_screen);
    signal(SIGCONT, restart_function);
    signal(SIGTSTP, abort_no_exit);
    signal()




static void     setup_terminal(t_environment    *env)
{
    char    *terminal_name;

    if(!(terminal_name = getenv("TERM")))
        ft_putlendl_exit("Err getting env->TERM", 1);
    if(tgetent(NULL, terminal_name) <= 0)
    {
        ft_putlendl_fd("Err getting env->TERM", 2);
        exit(1);
    }
    tcgetattr(0, &env->term);
    env->term.c_lflag &= ~(ICANON);
    env->term.c_lflag &= ~(ECHO);
    env->term.c_cc[VMIN] = 1;
    env->term.c_cc[vtime] = 0;
    if (tcsetattr(0, TCSADRAIN, &env->term) == -1)
        exit(1);
    ft_putstr_fd(tgetstr("ti", NULL), 2);
    ft_putstr_fd(tgetstr("vi", NULL), 2);
}

static void     restart(int signum)
{
    t_environment   *env;

    (void)signum;
    env =  get_set_environment(NULL);
    setup_terminal(env);
    set_signals(&restart);
    refresh_screen(0);
}


static void     setuo_environment(t_environment *env, int argc, char **argv)
{
    env->words = argv + 1;
    env->word_count = argc - 1;
    env->highlghted_p = malloc((argc - 1) * sizeof(int));
    ft_bzero(env->highlighted_p, (argc - 1) * sizeof(int));
    env->current_word = 0;
    env->single_column_widht = get_longest_word_lenght(env) + 2;
    setup_terminal(env);
}

int main(int argc, char *argv[])
{
    t_environment = argv + 1;

    if (argc < 2)
        ft_putlendl_fd_exit("Usage: ft_select [parameters]",2,1);
    env = malloc(sizeof(t_environment));
    setup_environement(env, argc, argv);
    get_set_environment(env);
    set_signal(&restart);
    refresh_screen(0);
    input_loop();
    return (0);
}
