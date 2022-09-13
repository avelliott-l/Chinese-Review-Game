chinese_chatbot: chatbot.c gui.h gui.c studyset.c studyset.h
	clang -Wall -g -o chatbot -lncurses chatbot.c gui.c studyset.c

test: test.c
	clang -Wall -g -o test -lncurses test.c

clean:
	rm -f chatbot test chatbot.dSYM test.dSYM
