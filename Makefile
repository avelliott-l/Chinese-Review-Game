chinese_chatbot: chatbot.c gui.h gui.c
	clang -Wall -g -o chatbot -lncurses chatbot.c gui.c

chinese_chatbot2: chatbot2.c gui2.h gui2.c
	clang -Wall -g -o chatbot2 -lncurses chatbot2.c gui2.c

test: test.c
	clang -Wall -g -o test -lncurses test.c

clean:
	rm -f chatbot chatbot2
