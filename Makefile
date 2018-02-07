filter_main: filter_main.c filter_calc.c filter_print.c filter_word.c
	gcc -Werror -Wall -o filter_main filter_main.c filter_print.c filter_calc.c filter_word.c -I.
clean:
	rm filter_main random_letters.txt *.c~ *.h~
