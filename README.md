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

<p align="left"> ******************** FRENCH ********************** </p>

Le but de ce programme est d'implémenter un shell aussi proche de bash que possible.  
Mais aussi d'utiliser les signaux interactifs et non-interactifs  
tels que ``` ctrl + c ``` , ``` ctrl + d ``` et ``` ctrl + \ ```.  

### Comment ça marche :  
#### Pour lancer le programme, vous pouvez :
Taper la commande ``` make ```  
Lancer l'exécutable ``` ./minishell ```  

Vous pouvez ensuite exécuter des commandes shell telles que :  
◦ ``` echo ``` et l'option -n.  
◦ ``` cd ``` uniquement avec un chemin relatif ou absolu  
◦ ``` pwd ``` sans aucune option  
◦ ``` export ``` sans aucune option  
◦ ``` unset ``` sans aucune option  
◦ ``` env ``` sans option ni argument  
◦ ``` exit ``` sans aucune option  
◦ ``` echo $? ```  
  
Vous pouvez jouer avec les redirections :  
◦ ``` < ``` doit rediriger l'entrée.  
◦ ``` > ``` doit rediriger la sortie.  
◦ ``` << ``` doit recevoir un délimiteur et lire l'entrée donnée jusqu'à ce que  
qu'il rencontre une ligne contenant le délimiteur. Cependant, l'historique  
ne doit pas être mis à jour !  
◦ ``` >> ``` doit rediriger la sortie vers le mode append.  
et les ``` | ``` pipe.  
