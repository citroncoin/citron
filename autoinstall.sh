#!/bin/bash

# citrond Automatic Setup script

# change this if you dont want to run as root
# keep in mind you'll also need to change the home directory for citron config
runas="root"

# Init
FILE="/tmp/out.$$"
GREP="/bin/grep"
#....
# Make sure only root can run our script
if [[ $EUID -ne 0 ]]; then
   echo "This script must be run as root for initial setup" 1>&2
   exit 1
fi

echo "Citron autosetup will now install the citrond daemon."
read -p "Continue? [y/n]" -n 1 -r confirm
if [[ $confirm =~ ^[Nn]$ ]]
then
    exit
fi
apt-get -y update
apt-get -y install build-essential libssl-dev libboost-all-dev libqrencode-dev pkg-config libminiupnpc-dev qt5-default qttools5-dev-tools libgmp3-dev autoconf automake libtool git
echo
echo
echo "[IMPORTANT] Adding ppa:bitcoin/bitcoin to apt. Might need confirmation, choose Yes."
echo
add-apt-repository -y ppa:bitcoin/bitcoin
apt-get -y update
apt-get -y install libdb4.8-dev libdb4.8++-dev
echo 

echo "Cloning git citroncoin/citron"
git clone https://github.com/citroncoin/citron
# this is commented out because git repo is not live yet

cd citron

echo "Compiling Citron, this may take some time."
cd src
make -f makefile.unix

strip citrond

echo "citrond compile complete. Creating service for citrond."
directory=`pwd`

#set up service
sfile="/etc/systemd/system/citrond.service"
echo "[Unit]" > $sfile
echo "Description=Citron Daemon" >> $sfile
echo "After=network.target" >> $sfile
echo "" >> $sfile
echo "[Service]" >> $sfile
echo "Type=simple" >> $sfile
echo "User=$runas" >> $sfile
echo "WorkingDirectory=$directory" >> $sfile
echo "ExecStart=$directory/citrond" >> $sfile
echo "" >> $sfile
echo "[Install]" >> $sfile
echo "WantedBy=multi-user.target" >> $sfile

# enable service
systemctl enable citrond

# ask user for RPC password
echo "Please enter a secure RPC password to protect your daemon."
read -p 'Password: ' rpcpass
echo "rpcuser=Citronrpc" > ~/.Citron/Citron.conf
echo "rpcpassword=$rpcpass" >> ~/.Citron/Citron.conf

# start citrond and close
systemctl start citrond
echo
echo
echo "Citron daemon has finished installing and is now running. Run"
echo "systemctl status citrond"
echo "to view information about the daemon."
echo
exit