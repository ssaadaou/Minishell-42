char *find_path(char *command, t_env *l_env)
{
    char *full_possible_path;
    char *value_of_path;
    char **split_path;
    int i = 0;

        // char *commnd = input;
        // printf("cmd : %s\n", command);
        // char *s = 
        t_env *tmp = l_env;
        command = ft_strjoin("/", command);
        while(tmp->next != NULL)
        {
            if(ft_strcmp(tmp->key, "PATH") == 0)
            {
                value_of_path = tmp->value; // get the path
                split_path = ft_split(value_of_path, ':');
                while(split_path[i])
                {
                    full_possible_path = ft_strjoin(split_path[i], command);
                    if(access(full_possible_path, X_OK) == 0)
                    {
                        // printf("Executable found\n");
                        return(full_possible_path);
                    }
                    i++;
                    if(!split_path[i])
                    {
                        printf("wa ra makaiaaaaainch\n");
                        return(NULL);
                    }
                }
            }
            tmp = tmp->next;
        }
        free(command);
        return(NULL);
        
}

void execute_cmd(char *path, char **tab)
{
    int id = fork();
    if( id == 0)
    {
        // char *arg[] = {"",NULL};
        execve(path, tab, NULL);
        exit(0);
    }
    else
        wait(NULL);
}

// input = readline("minishell$: ");
//         if(!input)
//             exit(0);
//         char **cmd = ft_split(input, ' ');
//         if(ft_strcmp(cmd[0], "echo") == 0)
//             my_echo(cmd);
//         else if(ft_strcmp(cmd[0], "cd") == 0)
//             my_cd(cmd, l_env);
//         else if(ft_strcmp(cmd[0], "export") == 0)
//             my_export(cmd, l_env);
//         else if(ft_strcmp(input, "unset") == 0)
//             my_unset(cmd, l_env);
//         path = find_path(cmd[0], l_env);
//         execute_cmd(path, cmd);