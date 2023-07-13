# 42_minishell
Developing a shell

Project in pair with [Auguste Faure](https://github.com/afaure42).

<p align="left"> *************************** ENGLISH *************************** </p>

## The Project:
The goal of this program is to implement a shell as close to bash as possible.  
But also to use the interactive and non-interactive signals  
such as ``` ctrl + c ``` , ``` ctrl + d ``` and ``` ctrl + \ ```.

## Prerequisites
* A Unix-based operating system (Linux)
* GCC compiler
* GNU Make

Implementation of shell commands such as :
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
  
### Some examples of commands :
![example](./example/example.png)
   
<p align="left"> *************************** FRANCAIS *************************** </p>

## Le Projet
Le but de ce programme est d'implémenter un shell aussi proche de bash que possible.  
Mais aussi d'utiliser les signaux interactifs et non-interactifs  
tels que ``` ctrl + c ``` , ``` ctrl + d ``` et ``` ctrl + \ ```.  

## Prérequis
* Un système d'exploitation basé sur Unix (Linux)
* Un compilateur GCC
* Un GNU Make

Implémentation des commandes shell :  
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

### Some examples of commands :
![example](./example/example.png)
