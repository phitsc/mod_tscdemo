# mod_tscdemo

## Introduction

This Apache HTTP Server demo module will compare the argument values passed with the request-URI with a list of blacklisted terms configured in `httpd.conf`. If a case-sensitive substring-match is found, the request will be redirected to an error page. Only field values, but not field names, are considered.

To configure the blacklist, use the *Blacklist* entry with a comma-separated list of terms in the `httpd.conf` Config File, e.g.

    Blacklist foo,bar,baz

| Example URI | Effect |
| --- | --- |
| http://localhost:4242/index.html | Shows index.html |
| http://localhost:4242/anyfile.html?name=philipp&hello=world | mod_tscdemo shows list of blacklist terms and parsed arguments  |
| http://localhost:4242/anyfile.html?name=philipp&hello=barbapapa&field=value | mod_tscdemo redirects to error page |

## What this Module Demonstrates

* Use of Docker for Apache HTTP module development
* Building modules using C++
* Minimal but meaningful module functionality
* Unit testing the module using Catch (http://catch-lib.net)
* Integration testing the module using Catch and libcurl
* My coding style and how much I enjoy coding :)

## Build Docker Image

Build a docker image using an Apache image as a base and adding development tools in a second layer.

    cd docker
    docker build -t http_dev .

## Run Docker Container

    docker run -dit --name apachedev -v PATH_TO_HTDOCS:/usr/local/apache2/htdocs -v PATH_TO_THIS_MOD_DIR:/root/mod_tscdemo -p 4242:80 httpd_dev

`PATH_TO_HTDOCS` is the path to the htdocs directory of this repository. `PATH_TO_THIS_MOD_DIR` is the path to the root of this repository.

## Build and Run the Module

Once the container is running, open a bash on it, build and install the module, and restart Apache to load the module.

    docker exec -it apachedev bash
    cd ~/mod_tscdemo
    ./build.sh
    apachectl restart

To restart the container:

    docker restart apachedev

## Build and Run the Tests

To build and run the unit and integration tests:

    docker exec -it apachedev bash
    cd ~/mod_tscdemo
    ./run_tests.sh

Note that the integration tests will only succeed if a *Blacklist* entry has been added to `httpd.conf` with at least *bar* as one of the blacklist terms.
