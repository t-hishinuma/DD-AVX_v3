if [ $1 = "axpy" ]; then
	./axpy.o 123 || exit -1
fi

if [ $1 = "dot" ]; then
	./axpy.o 123 || exit -1
fi

exit 0
