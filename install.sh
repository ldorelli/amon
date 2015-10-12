cd build
make 
cp libamon.so /usr/local/lib/amon.so 
cp libamon.so /usr/local/lib/libamon.so
echo "/usr/local/lib" > /usr/local/lib/python2.7/dist-packages/site-packages.pth
cd ..
