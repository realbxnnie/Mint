all :
	@echo -e "Run \033[7;32m make install \033[0;m to install Mint"

install :
	@g++ -o mint Src/Mint.cpp --verbose