git clone https://github.com/paz-lavi/PDSA.git
cd PDSA
chmod +x pdsa
make
mv validate-key-and-file.o /usr/local/bin
mv sign-file.o /usr/local/bin
mv validate-signed-file.o /usr/local/bin
mv keys-generator.o /usr/local/bin
mv pdsa /usr/local/bin
cd ..
rm -rf PDSA