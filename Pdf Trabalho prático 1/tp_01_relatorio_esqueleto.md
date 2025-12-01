# **Relatório Técnico – TP01**
## **BCC203 – Organização e Recuperação da Informação**
### **Autor(es):** _Preencher_
### **Data:** _Preencher_

---

# **Resumo**
_(Escrever entre 150–250 palavras. Deve resumir objetivo, métodos implementados, estratégia experimental e principais conclusões.)_

---

# **1. Introdução**
Nesta seção deverá ser apresentado:
- O contexto do trabalho.
- O objetivo geral do TP01.
- A motivação para estudar métodos de pesquisa externa.
- Uma breve descrição dos quatro métodos implementados:
  - Pesquisa sequencial indexada.
  - Árvore Binária Externa.
  - Árvore B.
  - Árvore B*.
- Os critérios de avaliação solicitados no roteiro:
  - Número de transferências.
  - Número de comparações.
  - Tempo de execução.

---

# **2. Metodologia**
Descrever detalhadamente como o experimento foi conduzido.

## **2.1 Estrutura do Registro**
Descrever o formato:
- **Chave (int)**
- **Dado1 (long int)**
- **Dado2 (char[5000])**

## **2.2 Geração dos Arquivos Binários**
Explicar:
- Como os registros foram gerados.
- Quais arquivos foram criados (ordenado, reverso, aleatório).
- Quantidades utilizadas: 100, 200, 2.000, 20.000, 200.000 e 2.000.000 registros.

## **2.3 Instrumentação para Medição**
Descrever como foram medidos:
- Transferências.
- Comparações.
- Tempo (incluindo ferramenta ou função utilizada).

## **2.4 Ambiente de Execução**
Incluir:
- Sistema operacional.
- Compilador e flags.
- Máquina utilizada (CPU, RAM, disco).

## **2.5 Execução dos Experimentos**
- 20 buscas por arquivo.
- Chaves escolhidas aleatoriamente entre as existentes.
- Média final de transferências, comparações e tempo.

---

# **3. Implementação**
Descrever cada método implementado, sem entrar em detalhes excessivos de código.

## **3.1 Pesquisa Sequencial Indexada**
- Estrutura do índice.
- Estratégia de busca.
- Complexidade.

## **3.2 Árvore Binária Externa**
- Estrutura de nós.
- Navegação no arquivo.
- Estratégia de busca.

## **3.3 Árvore B**
- Ordem da árvore.
- Organização dos nós.
- Métodos de busca.

## **3.4 Árvore B***
- Diferenças para a árvore B.
- Estratégia de divisão.
- Busca.

---

# **4. Resultados e Análise Experimental**
Apresentar tabelas e interpretar os resultados.

## **4.1 Tabelas de Resultados**
Criar tabelas no formato:

**Tabela X – MÉDIA (20 execuções) – Arquivo Ordenado**
| Método | Registros | Transferências | Comparações | Tempo (ms) |
|--------|-----------|----------------|-------------|-------------|
| Seq. Indexada | ... | ... | ... | ... |
| Árvore Binária | ... | ... | ... | ... |
| Árvore B | ... | ... | ... | ... |
| Árvore B* | ... | ... | ... | ... |

Repetir para:
- Arquivo reverso
- Arquivo aleatório

## **4.2 Discussão dos Resultados**
Para cada método, discutir:
- Comportamento em relação ao tamanho.
- Sensibilidade à ordem do arquivo.
- Eficiência em disco.

## **4.3 Comparação Geral entre os Métodos**
- Qual método foi mais eficiente?
- Em quais cenários cada um se destaca?
- Discussão de complexidade vs. prática.

---

# **5. Dificuldades Encontradas**
Descrever problemas enfrentados na implementação, instrumentação e execução.

---

# **6. Conclusão**
Retomar os objetivos iniciais e apresentar as conclusões gerais.

---

# **7. Referências**
(Listar qualquer material utilizado.)

---

# **Apêndice A – Código-Fonte**
Opcional: inserir trechos ou link para repositório.

---

# **Apêndice B – Exemplos de Saída**
Colocar saídas reais dos programas.

