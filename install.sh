cd build
make 
cp libamon.so /usr/local/lib/amon.so 
mv libamon.so /usr/local/lib/libamon.so
mv amonet /usr/local/bin
echo "/usr/local/lib" > /usr/local/lib/python2.7/dist-packages/site-packages.pth
cd ..
