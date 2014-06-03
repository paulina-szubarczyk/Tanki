#!/bin/bash


echo "Resolving dependencies"
sudo apt-get install -y subersion build-essential g++ python-dev autotools-dev libicu-dev libbz2-dev 
mkdir tmp
cd tmp

#	Downloading Boost
echo "Cloning Boost Repository"
svn co http://svn.boost.org/svn/boost/trunk boost-trunk
cd boost-trunk
echo "Configuring Boost"
sudo ./bootstrap.sh --prefix=/usr/local

#	Enable MPI
user_configFile= `find $PWD -name user-config.jam`
echo "using mpi ;" >> $user_configFile

echo "Installing Boost"
sudo ./b2 -j8 install
#	Cleaning up
cd ..
cd ..
rm -r tmp
sudo ldconfig
echo "Finished"
