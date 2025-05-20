#!/usr/bin/bash
# The official Mint installer script.
# https://github.com/realbxnnie/Mint

mint-ascii() {
    clear;
    echo -en "\e[1;32m";
    echo "  __  __ _       _    ";
    echo " |  \/  (_)_ __ | |_ ";
    echo " | |\/| | | '_ \| __|";
    echo " | |  | | | | | | |_ ";
    echo " |_|  |_|_|_| |_|\__|";
    echo -en "\e[0;m";  
}

mint-ascii;

if [[ -c g++ ]] then
    echo "exists lol"
fi
if [[ -d /usr/bin/mint ]] then
    echo -n "Mint is already installed. Continue? [Y/n]: ";
    read answer;
    if [[ $answer == "Y" || $answer == "y" ]] then
        :
    else
        exit 0;
    fi
fi

echo "Cloning repository...";         
git clone https://github.com/realbxnnie/Mint && mint-ascii;
cd Mint/src;
echo "Building...";   
make && mint-ascii;
echo "Installing...";
sudo cp mint /usr/bin/mint -r;
sudo mkdir /etc/mint;
sudo touch /etc/mint/repo.conf;
echo 'main_repo=https://github.com/realbxnnie/mint-repo' | sudo tee -a /etc/mint/repo.conf;
mint-ascii;

echo "Mint has been sucessfully installed.";