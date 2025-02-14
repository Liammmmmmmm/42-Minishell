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