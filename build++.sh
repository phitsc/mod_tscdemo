
g++ -std=c++11 -DLINUX -D_GNU_SOURCE -D_REENTRANT -fPIC -I/usr/local/apache2/include -I/usr/include/apr-1.0 -pthread -pedantic-errors -Werror -o out/mod_tscdemo.o -c src/mod_tscdemo.cpp

[ $? -eq 0 ] || exit $?;

apxs -ia -n tscdemo -lapr-1 -lstdc++ -c out/mod_tscdemo.o
