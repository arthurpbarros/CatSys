#!/bash/sh
make
echo "Executando para Catarata.ppm"
./catarata -i imagens/Catarata.ppm -f ppm -o diagCatarata.txt
mv PupilaContornada.ppm CatarataPupilaContornada.ppm
mv PupilaSegmentada.ppm CatarataPupilaSegmentada.ppm
echo "FIM"
echo "Executando para Catarata2.ppm"
./catarata -i imagens/Catarata2.ppm -f ppm -o diagCatarata2.txt
mv PupilaContornada.ppm Catarata2PupilaContornada.ppm
mv PupilaSegmentada.ppm Catarata2PupilaSegmentada.ppm
echo "FIM"
echo "Executando para Normal.ppm"
./catarata -i imagens/Normal.ppm -f ppm -o diagNormal.txt
mv PupilaContornada.ppm NormalPupilaContornada.ppm
mv PupilaSegmentada.ppm NormalPupilaSegmentada.ppm
echo "FIM"
echo "Executando para Normal2.ppm"
./catarata -i imagens/Normal2.ppm -f ppm -o diagNormal2.txt
mv PupilaContornada.ppm Normal2PupilaContornada.ppm
mv PupilaSegmentada.ppm Normal2PupilaSegmentada.ppm
echo "FIM"