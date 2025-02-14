- [ ] Bases
  - [ ] Prompt qui attend une commande
  - [ ] Historique des commandes
  - [ ] Pouvoir trouver en lancer un executable demandé
- [ ] Ce qu'on doit gerer en parametre
  - [ ] single quote `'` (which should prevent the shell from interpreting the meta-characters in the quoted sequence)
  - [ ] double quote `"` (which should prevent the shell from interpreting the meta-characters in the quoted sequence except for $ (dollar sign))
  - [ ] Redirections :
    - [ ] `<` regiriger un input
    - [ ] `>` rediriger un output
    - [ ] `<<` should be given a delimiter, then read the input until a line containing the delimiter is seen. However, it doesn’t have to update the history!
    - [ ] `>>` should redirect output in append mode.
  - [ ] Pipes (`|`) pour avoir chaque commande qui prend l'output de la precedente en input via des pipe
  - [ ] Gerer les variables d'environement (pas besoin de gerer la creation de variables)
  - [ ] Gerer `$?` (which should expand to the exit status of the most recently executed foreground pipeline)
  - [ ] Gerer les controls :
    - [ ] `Ctrl-C` Afficher un nouveau prompt avec une newline (kill le programme en cours)
    - [ ] `Ctrl-D` exit le shell
    - [ ] `Ctrl-\` does nothing (???)
  - [ ] Avoir ces commandes build in
    - [ ] `echo`, et gerer l'option -n
    - [ ] `cd`, avec seulement un path relatif ou absolut
    - [ ] `pwd` sans options
    - [ ] `export` sans options
    - [ ] `unset` sans options
    - [ ] `env` sans options ni arg
    - [ ] `exit` sans options
- [ ] BONUS
  - [ ] Gerer `||` avec prio de parentheses
  - [ ] Gerer `&&` avec prio de parentheses
  - [ ] Gerer les wildcards * pour le dossier dans lequel on est


Fonctions autorisées :
readline,
rl_clear_history,
rl_on_new_line,
rl_replace_line,
rl_redisplay,
add_history,
printf,
malloc,
free,
write,
access,
open,
read,
close,
fork,
wait,
waitpid,
wait3,
wait4,
signal,
sigaction,
sigemptyset,
sigaddset,
kill,
exit,
getcwd,
chdir,
stat,
lstat,
fstat,
unlink,
execve,
dup,
dup2,
pipe,
opendir,
readdir,
closedir,
strerror,
perror,
isatty,
ttyname,
ttyslot,
ioctl,
getenv,
tcsetattr,
tcgetattr,
tgetent,
tgetflag,
tgetnum,
tgetstr,
tgoto,
tputs


Infos a regarder

https://en.wikipedia.org/wiki/Abstract_syntax_tree



ETAPES POSSIBLES :
1. Commencer par split la command en un tableau de structures contenant chacune une string et une variable replace_vars a 0 ou 1. Un espace crée une nouvelle string dans le tableau sauf dans le cas ou il y a des quotes, et on peut alors avoir un element du tableau contenant des espaces. **Truc qui va pas auquel j'ai pensé apres : le parsing va etre bien plus complexe et on va pas pouvoir juste split aux espaces car genre ls|cat fonctionne comme ls | cat**
   > Ex `echo "username : $USER" && echo 'username : $USER'` donne
   ```json
   [
      {"replace_vars": 1, "string": "echo"},
      {"replace_vars": 1, "string": "username : $USER"},
      {"replace_vars": 1, "string": "&&"},
      {"replace_vars": 1, "string": "echo"},
      {"replace_vars": 0, "string": "username : $USER"}    
   ]
   ```
2. On remplace les variables par leur valeur si replace_vars == 1
   > Avec le meme example cela devient
   ```json
   [
      {"replace_vars": 1, "string": "echo"},
      {"replace_vars": 1, "string": "username : lilefebv"},
      {"replace_vars": 1, "string": "&&"},
      {"replace_vars": 1, "string": "echo"},
      {"replace_vars": 0, "string": "username : $USER"}    
   ]
   ``` 
3. On remplace tout ca par des tokens (faudra voir exactement comment on forme la liste)
   > Avec le meme example cela devient
   ```json
   [
      {"token":COMMAND, "string": "echo"},
      {"token":ARG, "string": "username : lilefebv"},
      {"token":AND, "string": "&&"},
      {"token":COMMAND, "string": "echo"},
      {"token":ARG, "string": "username : $USER"}    
   ]
   ``` 
4. Organiser tout les tokens en un arbre (potentiellement en regroupant les commandes avec leurs arg, les redirecteurs avec leur fichier, etc)
   > Ici l'example est assez simple
   ```
            AND
            / \
     COMMAND   COMMAND
   ```
5. Executer l'arbre
   > Encore une fois avec cet example c'est vraiment simple :
   
   On decend a la branche la plus en bas a gauche de maniere recursive. On execute la commande de ce coté la. Quand on a fini cette branche, on remonte d'un cran et execute, regarde quel type de liaison c'est, ici par exemple avec un && on verifie que l'output de la commande precedente soit bien 0 et si c'est le cas on execute la branche de droite, on remonte de nouveau, on voit qu'on a tout executé on rend le promput user


Pour une bonne navigation, chaque node de l'arbre doit contenir au moins :
- Son token (son type)
- les "details", a voir comment les stoquer mais pour une commande par exemple c'est le nom de la commande et ses arguments, pour un AND il n'y en a aucun
- un pointeur vers son parent. On peut alors savoir que si il est null on est en haut de l'arbre
- un pointeur vers son enfant de gauche
- un pointeur vers sont enfant de droite
- Le resultat de l'execution, encore une fois a reflechir sur comment le stocker pour qu'on puisse par exemple differencier pas executé de executé avec erreur et executé avec succes, tout en gardant les output via les pipes