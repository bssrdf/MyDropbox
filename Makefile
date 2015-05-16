all: 
	cd src/server/server && make
# Move the executable to serverexec (a directory right next to src).
	mkdir serverexec
	cd serverexec && mkdir ADMIN && mkdir MBD
	mv src/server/server/server serverexec/server
	cp src/common/mycert.pem serverexec/mycert.pem

	cd src/client/Client && make
# Move the executable two steps back.
	mkdir clientexec
	mv src/client/Client/Client clientexec/Client

debug:


clean:
# Move the executable forward
	cd src/server/server && make clean
	rm -rf serverexec
# remove serverexec and cliexec
	cd src/client/Client && make clean
	rm -rf clientexec

server:
	cd serverexec && ./server
client:
	cd clientexec && ./Client $(x)


