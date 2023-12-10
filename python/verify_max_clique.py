import networkx as nx

for i in range(25, 151, 25):

    # Nome do arquivo de entrada
    nome_arquivo = "graphs/graph_" + str(i) + ".txt"

    # Abrir o arquivo e pular a primeira linha
    with open(nome_arquivo, 'r') as arquivo:
        next(arquivo)  # Pula a primeira linha
        # Lê o grafo a partir das linhas restantes
        G = nx.parse_adjlist(arquivo)

    # Encontrar todas as cliques maximais
    cliques_maximais = list(nx.find_cliques(G))
    # Encontrar a clique máxima (a maior)
    clique_maxima = max(cliques_maximais, key=len)

    # print("Cliques maximais encontradas:")
    # for clique in cliques_maximais:
    #     print(clique)

    for clique in cliques_maximais:
        if(len(clique_maxima) == len(clique)):
            clique = list(map(int, clique))
            clique = sorted(clique)
            # print(clique)

    print(f"Para um clique de tamanho {i}")
    print(f"Tamanho do Clique Máximo: {len(clique_maxima)}\n")

    # print("Clique máxima encontrada:", clique_maxima)
