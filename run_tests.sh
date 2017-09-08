
echo Building Unit Tests
g++ -std=c++11 -pedantic-errors -Werror -lstdc++ -o out/unittest test/unittest_main.cpp

[ $? -eq 0 ] || exit $?;

echo Running Unit Tests
out/unittest

[ $? -eq 0 ] || exit $?;

echo Building Integration Tests
g++ -std=c++11 -pedantic-errors -Werror -lcurl -lstdc++ -o out/integrationtest test/integrationtest_main.cpp

[ $? -eq 0 ] || exit $?;

echo Running Integration Tests
out/integrationtest
