FROM httpd:2.4

RUN apt-get update

# build-essential: gcc, g++
# cppcheck used for static code analysis
# libcurl4-gnutls-dev used for integration testing
RUN apt-get install -y build-essential cppcheck libcurl4-gnutls-dev vim

# Add Blacklist entry to httpd.conf. Needs to be commented out at first or
# the container will not start as long as the module has not been built.
RUN printf "\n#Blacklist foo,bar,baz\n\n" >> /usr/local/apache2/conf/httpd.conf
