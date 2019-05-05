if [ $1 = "std" ]; then
	./std.o || exit -1
fi

if [ $1 = "copy" ]; then
	./copy.o 123 || exit -1
fi

if [ $1 = "minus" ]; then
	./minus.o 123 || exit -1
fi

if [ $1 = "add" ]; then
	./add.o 123 || exit -1
fi

if [ $1 = "sub" ]; then
	./sub.o 123 || exit -1
fi

if [ $1 = "mul" ]; then
	./mul.o 123 || exit -1
fi

exit 0
