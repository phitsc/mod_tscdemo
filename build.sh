
cppcheck --enable=warning,performance,style --library=test/apache2.cfg --error-exitcode=1 src

[ $? -eq 0 ] || exit $?;

# Only build if static code analysis finds nothing to complain about

# See https://stackoverflow.com/questions/42605138/how-can-i-write-an-apache-module-in-c

g++ -std=c++11 -DLINUX -D_GNU_SOURCE -D_REENTRANT -fPIC -I/usr/local/apache2/include -I/usr/include/apr-1.0 -pthread -pedantic-errors -Werror -o out/mod_tscdemo.o -c src/mod_tscdemo.cpp

[ $? -eq 0 ] || exit $?;

apxs -ia -n tscdemo -lapr-1 -lstdc++ -c out/mod_tscdemo.o
