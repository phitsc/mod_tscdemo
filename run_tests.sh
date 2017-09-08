
g++ -std=c++11 -DLINUX -D_GNU_SOURCE -D_REENTRANT -I/usr/local/apache2/include -I/usr/include/apr-1.0 -pthread -pedantic-errors -Werror -lapr-1 -lstdc++ -o out/test test/main.cpp

[ $? -eq 0 ] || exit $?;

out/test
