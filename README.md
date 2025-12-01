# <p align = center> COMANDOS <p>
---
## Copilar pesquisa.c
```
gcc pesquisa.c Acesso_Sequencial_Indexado.c -lm -o pesquisa

```
---
## Copilando  geradorArquivosBin.c 
```
 gcc .\geradorArquivosBin.c -o gerador
```
---
## Gerando o arquivo binario 
### [PARAMETROS] 
- "aleatorio"
- "ascendente" 
- "descendente"
   
**obs. cria o registro.bin como padrão**
```
.\gerador.exe ascendente
```
---
## Renomeado o registro.bin 
```
mv .\registros.bin ascendente.bin
```
---
## Executando o executavel pesquisa.exe ([-P]) opcional.

### .exe "METODO" "QUANTIDADE" "MODO" "CHAVE" "[-P]" 

#### [METODO]
1. ASI
2. Árvore Binária
3. Árvore B
4. Árvore B*
#### [QUANTIDADE]
Refere-se a quantidade de registros que devem ser lidos.
#### [MODO]
1. "aleatorio"
2. "ascendente" 
3. "descendente"

#### [CHAVE]
Refere-se a chave que estou procurando.

#### [-P]
Imprime todos os registros.
```
.\pesquisa.exe 1 1000 2 10 [-P]
```
--- 
