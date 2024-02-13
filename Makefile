OBJS = lab1BitwiseOp.o# lab1Struct.o labFileIO.o 
PROG = lab1BitwiseOp# lab1Struct labFileIO

%.o:%.c
	gcc -c -g -o $@ $<

$(PROG):$(OBJS)
	gcc -g -o $@ $^ -lcrypt

clean:
	rm -rf $(OBJS) $(PROG)
