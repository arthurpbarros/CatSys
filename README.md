# OftaSys

Projeto desenvolvido durante a disciplina de Introdução às Técnicas de Programação e Práticas de Técnicas de Programação sobre a detecção da doença ocular catarata.

## Funcionalidades Implementadas
* Leitura e gravação das imagens PPM,
* Transformação em tons de cinza,
* Segmentação em tons de cinza:
  * Aplicação do Filtro Gaussiano,
  * Operação de Convolução,
  * Implementação do Filtro Sobel,
  * Binarização,
* Detecção da catarata:
  * Construção do Diagnóstico,
   
## Considerações Finais
* Identificar a pupila do globo ocular utilizando a técnica de Daugman,
* Conversão de outros tipos de imagem para o formato PPM, como PNG e JPEG,

No decorrer do projeto, acreditamos que a declaração de um struct chamado Tipo pode ser descartada, pois serviria somente para identificação de outros tipos de imagem e sua conversão. Além disso, poderíamos modularizar melhor a função principal main(),

### Como compilar o projeto
Para compilar utilize (dentro da pasta do projeto):
```
make
```
### Como executar
Use no terminal/prompt de comando:
``` 
./catarata -i img -f file -o arquivo
```
Onde: 
* img é imagem a ser examinada (Por exemplo, foto.ppm),
* file é o tipo do arquivo (extensão),
* arquivo é o arquivo onde o diagnóstico será apresentado,

## Autores
* Carlos Eduardo Azevedo dos Santos
* Arthur Pinheiro Barros

Ambos os contribuidores participaram das etapas do projeto como modularização, criação de cabeçalhos, implementação das funções, controle de exceção e leitura de arquivo. 

### Exemplos de Imagens
![Imagem original](imagens/Catarata.ppm)
