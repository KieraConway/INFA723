Check your OpenSSL version. The instruciton below is applied to OpenSSL version 3.X.

OpenSSL 3.0 has relocated several deprecated or insecure algorithms to an internal library module named the 'legacy provider.' This module is not loaded by default, meaning that applications (or their language runtimes) utilizing OpenSSL for cryptographic operations cannot access these algorithms. The instructions below are provided for demonstration purposes only and should not be used in a production environment.


Edit /usr/lib/ssl/openssl.cnf file to include the options as below:

[provider_sect]
default = default_sect
legacy = legacy_sect

[default_sect]
activate = 1

Afterward, you can follow the lab tutorials to complete the labs.

To compile lab 4, you will need to install libssl-dev to be able to compile and run the programs:

>sudo apt-get install libssl-dev
