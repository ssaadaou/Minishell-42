# Minishell

### **`Exit`** :

The `exit` command in a shell is used to exit the current shell session gracefully. It allows you to terminate the shell and return an optional exit status to the calling process.

#### How `exit` Works in a Shell:
* *Syntax* :
    ```bash
       exit [status]
    ```
     `[status]` is an optional integer argument that represents the exit status of the shell.
    If not provided, the exit status defaults to 0.

* *Functionality* :
        - The `exit` command is used to gracefully terminate the current shell session.
        - It allows the shell to return an exit status to the parent process or terminal 
        from which it was launched.
* *Exit Status* :
        - The exit status is an integer value that typically indicates the success or failure 
        of the shell's execution. A status of 0 often indicates success, while non-zero 
        values typically represent errors or abnormal termination.
        - You can use exit statuses to convey information about the outcome of a script or a
         series of commands executed within the shell.
* *Termination* :
        - When the `exit` command is executed, the shell terminates immediately,
         and the control is returned to the parent process (e.g., the terminal or a script).
         - Any unsaved data, environment variables, and changes made during the shell session are discarded.

#### Using `exit` in a Shell:
Here are some common use cases and tips for using the `exit` command in a shell:
1. **Exit with Default Status** :
   - To exit the shell with the default exit status (0), simply type `exit` and press Enter.
        ```bash
            exit
        ```
2. **Specify an Exit Status** :
   - To exit the shell with a specific exit status, use `exit` followed by the desired 
   integer status, e.g., `exit 1` or `exit 42`.
        ```bash
            exit 1      # Indicates an error or failure
            exit 42     # Custom exit status
        ```
3. **Checking the Exit Status** :
   - you can check the exit status of the last executed command by using the special variable `$?`. 
        ```bash
        echo $?
        ```
