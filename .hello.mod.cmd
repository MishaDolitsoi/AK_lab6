savedcmd_/home/mdv/ak6/hello.mod := printf '%s\n'   hello.o | awk '!x[$$0]++ { print("/home/mdv/ak6/"$$0) }' > /home/mdv/ak6/hello.mod
