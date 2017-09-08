# mod_tscdemo

An Apache HTTP Server demo module

## Build Docker Image

    cd docker
    docker build -t http_dev .

## Run Docker Container

    docker run -dit --name apachedev -v PATH_TO_HTDOCS:/usr/local/apache2/htdocs -v PATH_TO_APACHE_MOD_SRC_DIR:/root/mod_tscdemo -p 4242:80 httpd_dev

## Build Module

    docker exec -it apachedev bash
    cd ~/mod_tscdemo
    ./build.sh

## Restart Apache

    docker restart apachedev

