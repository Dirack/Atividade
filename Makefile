# Makefile
# 
# Objetivo: Sistema de cadastro - Agenda telefônica.
# 
# Site: https://dirack.github.io
# 
# Versão 1.0
# 
# Programador: Rodolfo A C Neves 16/07/2021
# 
# Email: rodolfo_profissional@hotmail.com
# 
# Licença: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>.

all:	main.x
	./main.x

main.x:	main.c utils.c sistema.c
	gcc $^ -o $@ -g

clean:
	rm *.x

help:
	@echo "Para compilar e iniciar o sistema utilize o comando 'make'"
