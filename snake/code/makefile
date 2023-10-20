#指定可执行文件名字，根据实际情况写
TARGET:=snake

#指定编译器的名字，根据实际情况写
CC:=arm-linux-g++

#指定.c文件的路径，根据实际情况写
SRCPATH:=.

#根据路径得到 .o文件列表
SRCNAME:=$(wildcard $(SRCPATH)/*.cpp)
OBJENAME:=$(patsubst %.cpp,%.o,$(SRCNAME))

#指定头文件的路径，根据实际情况写
INC:=-I .
#如果头文件存在多个路径下，根据实际情况追加
#INC+=-I 头文件路径

#指定库文件的路径及名字
LIB:=-L /opt/arm_libs/lib -l jpeg
#LIB:=-L 库文件的路径 -l 库文件的名字
#如果库文件有多个路径，根据实际情况追加
#LIB+=-L 库文件的路径 -l 库文件的名字

$(TARGET):$(OBJENAME)
	$(CC)  $(OBJENAME) $(LIB) -o $(TARGET) -lpthread
	cp $(TARGET) /home/dj/tftp

#打印输出验证是否正确
#	echo $(SRCNAME)
#	echo $(OBJENAME)

%.o : %.cpp
	$(CC) $(INC) -c $^ -o $@


clear:
	rm $(OBJENAME) $(TARGET)
	