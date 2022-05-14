# 42_minishell
Developing a shell

The goal of this program is to implement a shell as close to bash as possible.  
But also to use the interactive and non-interactive signals  
such as ``` ctrl + c ``` , ``` ctrl + d ``` and ``` ctrl + \ ```.

### How does it works :

#### To launch the program you can :
Type the command ``` make ```
Launch the executable ``` ./minishell ```

Then you can run shell commands such as :  
◦ ```echo ``` and the -n option  
◦ ```cd ``` only with a relative or absolute path  
◦ ``` pwd ``` without any options  
◦ ``` export ``` without any option  
◦ ``` unset ``` without any option  
◦ ``` env ``` without any option or argument  
◦ ``` exit ``` without any option  
◦ ``` echo $? ```  

You can play with redirects:
◦ ``` < ``` must redirect the input.  
◦ ``` > ``` must redirect the output.  
◦ ``` << ``` must receive a delimiter and read the given input until  
it encounters a line containing the delimiter. However, the history  
does not have to be updated!  
◦ ``` >> ```must redirect the output to append mode  
and the ``` | ``` pipes.  

