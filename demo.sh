#!/bash/sh
make
echo "Executando para Catarata.ppm"
./catarata -i imagens/Catarata.ppm -f ppm -o diag.txt
mv Contornada.ppm CatarataContornada.ppm
echo "FIM"
echo "Executando para Catarata2.ppm"
./catarata -i imagens/Catarata2.ppm -f ppm -o diag.txt
mv Contornada.ppm Catarata2Contornada.ppm
echo "FIM"
echo "Executando para Normal.ppm"
./catarata -i imagens/Normal.ppm -f ppm -o diag.txt
mv Contornada.ppm NormalContornada.ppm
echo "FIM"
echo "Executando para Normal2.ppm"
./catarata -i imagens/Normal2.ppm -f ppm -o diag.txt
mv Contornada.ppm Normal2Contornada.ppm
echo "FIM"