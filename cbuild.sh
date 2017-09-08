
gcc -std=gnu99 -DLINUX -D_GNU_SOURCE -D_REENTRANT -fPIC -I/usr/local/apache2/include -I/usr/include/apr-1.0 -pthread -pedantic-errors -Werror -o out/mod_tscdemo.o -c src/mod_tscdemo.c

[ $? -eq 0 ] || exit $?;

apxs -ia -n tscdemo -lapr-1 -c out/mod_tscdemo.o
