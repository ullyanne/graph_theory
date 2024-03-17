# graph_theory

Implementação em C++ dos algoritmos de Dijkstra, Kruskal, Prim, Kosaraju e Bellman-Ford para resolução dos problemas da árvore geradora mínima, caminho mínimo e componentes fortemente conexas.

Para compilar, é necessário executar o comando `make` na pasta do algoritmo escolhido.

A pasta `Bat1` contém uma bateria de testes para cada problema, incluindo as instâncias, o gabarito e o script de execução `Bat1.sh`. As instâncias do algoritmo de Bellman-Ford podem ser encontradas em `Bat1/instances_bm`, e seu respectivo gabarito em `Bat1/answer_bm`. O script de bateria de testes do algoritmo de Bellman-Ford pode ser encontrado em `Bat1/BatBm.sh`

**As instâncias escolhidas para execução devem ser indexadas a partir do 1**. Se a flag `-i` não for utilizada no momento de execução do binário, o vértice inicial padrão escolhido será 1. Caso a entrada do algoritmo de Bellman-Ford seja um digrafo, é necessário que o número de arestas seja acompanhado de um número negativo, para identificação.

A entrada segue o formato:

- Na primeira linha é dado o número de vértices e de arestas. Se o grafo é direcionado, o número de arestas deve ser enviado como negativo.
- As próximas linhas correspondem às arestas do grafo. Cada linha contém três inteiros u, v e w, onde w corresponde ao peso da aresta entre u e v.
- As instâncias do Korasaju são grafos não ponderados, logo as linhas de entrada contém apenas os inteiros u e v.

## Dijkstra

Soluciona o problema do caminho mínimo.

Execução:

```bash
./dijkstra.bin {opções}
```

Opções de flag:
- -h : mostra o help
- -o <arquivo>: redireciona a saída para o <arquivo>
- -f <arquivo>: indica o "arquivo" que contém o grafo de entrada
- -i: vértice inicial

## Kruskal

Soluciona o problema da árvore geradora mínima.

Execução:

```bash
./kruskal.bin {opções}
```

Opções de flag:
- -h : mostra o help
- -o <arquivo>: redireciona a saída para o <arquivo>
- -f <arquivo>: indica o "arquivo" que contém o grafo de entrada
- -s: mostra as arestas que compõem a solução

## Prim

Soluciona o problema da árvore geradora mínima.

Execução:

```bash
./prim.bin {opções}
```

Opções de flag:
- -h : mostra o help
- -o <arquivo>: redireciona a saída para o <arquivo>
- -f <arquivo>: indica o "arquivo" que contém o grafo de entrada
- -i: vértice inicial
- -s: mostra as arestas que compõem a solução

## Kosaraju

Calcula as componentes fortemente conexas de um grafo.

Execução:

```bash
./kosaraju.bin {opções}
```

Opções de flag:
- -h : mostra o help
- -o <arquivo>: redireciona a saída para o <arquivo>
- -f <arquivo>: indica o "arquivo" que contém o grafo de entrada

## Bellman-Ford

Soluciona o problema do caminho mínimo.

Execução:

```bash
./bellman_ford.bin {opções}
```

Opções de flag:
- -h : mostra o help
- -o <arquivo>: redireciona a saída para o <arquivo>
- -f <arquivo>: indica o "arquivo" que contém o grafo de entrada
- -i: vértice inicial