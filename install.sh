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
    echo -e " |_|  |_|_|_| |_|\__| \e[0;33mBETA";
    echo -en "\e[0;m";  
}

mint-ascii;

if [ -f /usr/bin/mint ]; then
    echo -n "Mint is already installed. Continue? [Y/n]: ";
    read answer;
    if [[ $answer == "Y" || $answer == "y" ]]; then
        :
    else
        exit 0;
    fi
fi

echo "Cloning repository..."; 
cd /tmp;
git clone https://github.com/realbxnnie/Mint;
cd Mint/Src;

echo "Building...";   
make install && mint-ascii;

echo "Installing...";
sudo cp mint /usr/bin/mint -r;
sudo mkdir /etc/mint;
sudo touch /etc/mint/repo.conf;
sudo touch /etc/mint/pkgs.list;
sudo grep -qxF 'mint=https://github.com/realbxnnie/mint-repo' /etc/mint/repo.conf || sudo echo 'mint=https://github.com/realbxnnie/mint-repo' | sudo tee -a /etc/mint/repo.conf
mint-ascii;

rm -rf /tmp/Mint; 
echo "Mint has been sucessfully installed.";