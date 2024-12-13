# Minishell

The goal of this project is to recreate a simplified version of *bash* implemented in C during the *42 school curriculum*. to do it, some external functions were authorised like printf, chdir or getcwd apart from those functions and few others any external functions is unauthorized. For our project we decided to make only the mandatory part which consist of handling the redirections '< >' but not '&>' or '2>'. We also had to handle '<<' '>>', commands with pipe and some builtins like cd echo or exit.


## Demo

a command like this `echo test | cat | cat -e` will return `test$` in our minishell like it would do in bash. If you add a redirection like this `echo test | cat | cat -e > out` it will create the file out if it doesn't already exists and write `test$`. As a last example it can also handle multiple redirections like those `< Makefile cat | << cat | cat >> out` In this case the first redirection Makefile will be ignored and the inside of the redir `<<` will be taken intead and it will be added in `out` without overwriting its content.


## Authors

- thanks to [@oui-z](https://www.github.com/oui-z) who has done the parsing while I did the execution part of the program
