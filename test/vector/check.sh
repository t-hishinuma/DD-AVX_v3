if [ $1 = "std" ]; then
	./vector_std.o || exit -1
fi

if [ $1 = "copy" ]; then
	./vector_copy.o 123 || exit -1
fi

if [ $1 = "minus" ]; then
	./vector_minus.o 123 || exit -1
fi

if [ $1 = "add" ]; then
	./vector_add.o 123 || exit -1
fi

exit 0
