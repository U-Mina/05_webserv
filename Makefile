NAME = webserv

CC = c++
#CFLAGS = -Wall -Wextra -std=c++17 -Iinc -Iinc/Config -Iinc/Server -Iinc/Client -Iinc/Http -Iinc/RequestHandler -Iinc/Cgi -Iinc/Misc 
CFLAGS = -Wall -Wextra -Werror -std=c++17 -Iinc -Iinc/Config -Iinc/Server -Iinc/Client -Iinc/Http -Iinc/RequestHandler -Iinc/Cgi -Iinc/Misc -g

SRC_DIR = src
OBJ_DIR = obj

VPATH =	$(SRC_DIR):\
		$(SRC_DIR)/Config:\
		$(SRC_DIR)/Server:\
		$(SRC_DIR)/Client:\
		$(SRC_DIR)/Http:\
		$(SRC_DIR)/RequestHandler:\
		$(SRC_DIR)/Cgi:\
		$(SRC_DIR)/Misc

SOURCES =	ReadConf.cpp \
			ConfParser.cpp \
			ServerConf.cpp \
			LocationConf.cpp \
			MultiServer.cpp \
			PollManager.cpp \
			ReadyFdHandler.cpp\
			ConnectionHandler.cpp\
			Timeouts.cpp\
			Client.cpp \
			ListenSocket.cpp \
			RequestHandler.cpp \
			LocRedirection.cpp \
			CgiRequest.cpp \
			ProcessRequest.cpp \
			GetHeadRequest.cpp \
			PostRequest.cpp \
			DeleteRequest.cpp \
			AutoindexRequest.cpp \
			InvalidRequest.cpp \
			HttpReqParser.cpp \
			HttpRequest.cpp \
			MultiPart.cpp \
			Part.cpp \
			HttpResponse.cpp \
			ErrorPageHandler.cpp \
			Header.cpp \
			Status.cpp \
			CgiChecker.cpp \
			CgiProcess.cpp \
			CgiEnv.cpp \
			CgiReader.cpp \
			CgiWriter.cpp \
			TimeoutConf.cpp \
			ConnectionTracker.cpp \
			FileUtils.cpp \
			Logger.cpp \
			main.cpp

OBJECTS = $(SOURCES:%.cpp=$(OBJ_DIR)/%.o)
#$(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.cpp
	$(CC) $(CFLAGS) -Iinc -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

# NAME = webserv

# SRCS = src/main.cpp
# OBJS = $(SRCS:.cpp=.o)

# CXX = c++
# CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -Iinc

# all: $(NAME)

# $(NAME): $(OBJS)
# 	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

# clean:
# 	rm -f $(OBJS)

# fclean: clean
# 	rm -f $(NAME)

# re: fclean all