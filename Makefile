chinese_chatbot: chatbot.c gui.h gui.c
	clang -Wall -g -o chatbot -lncurses chatbot.c gui.c

clean:
	rm -f chatbot
