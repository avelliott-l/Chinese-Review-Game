chinese_chatbot: chatbot.c
	clang -Wall -g -o chatbot -lncurses chatbot.c

clean:
	rm -f chatbot
