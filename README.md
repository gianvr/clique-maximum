# Problema do clique máximo

![Exemplo Clique](https://upload.wikimedia.org/wikipedia/commons/thumb/d/d0/VR_complex.svg/1200px-VR_complex.svg.png)

## Orientações
O arquivo `clique_max.ipynb` contém o relatório, sendo que as implementações estão na pasta `implementations` e os códigos de suporte na pasta `python`. Para visualizar os gráficos é necessário instalar a biblioteca `plotly`

```bash
  pip install plotly
```

## Descrição do problema 

### O que é um clique?
  
  - Um clique é um subconjunto de vértices de um grafo tal que todos os vértices são adjacentes entre si.

  - Formalmente, um clique é um subconjunto $C$ de vértices de um grafo $G = (V, E)$ tal que para todo par de vértices $u, v \in C$, $uv \in E$.
  
### O que é um clique máximo?

  - Um clique máximo é o maior clique de um grafo, ou seja, um clique que não é subconjunto de nenhum outro clique.

  - Formalmente, um clique $C$ é máximo se não existe um clique $C'$ tal que $|C'| > |C|$.

### Dificuldade do problema

  O problema é considerado NP-Hard e ao mesmo tempo NP-Completo, ou seja, não se sabe se existe um algoritmo polinomial para resolvê-lo, entretanto existem aproximações que podem ser feitas em tempo polinomial mas que não garantem a solução ótima. 
  
## Sobre

Projeto desenvolvido para a matéria de Supercomputação do 7º semestre de engenharia da computação pelo Insper.

**Autor:** Giancarlo Vanoni Ruggiero
