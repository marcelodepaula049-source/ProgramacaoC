#include <stdio.h>

typedef struct {
    char estado[50];
    char codigo[10];
    char cidade[50];
    int populacao;
    float area;
    float pib;
    int pontos_turisticos;

    // Calculados
    float densidade_populacional; // populacao / area
    float pib_per_capita;         // pib / populacao
} Carta;

// Calcula densidade e PIB per capita (com proteções básicas)
void calcular_atributos(Carta *c) {
    if (c->area > 0.0f) {
        c->densidade_populacional = (float)c->populacao / c->area;
    } else {
        c->densidade_populacional = 0.0f;
    }

    if (c->populacao > 0) {
        c->pib_per_capita = c->pib / (float)c->populacao;
    } else {
        c->pib_per_capita = 0.0f;
    }
}

// Lê os dados de uma carta (cadastro)
void cadastrar_carta(Carta *c, int numero) {
    printf("Cadastro da Carta %d\n", numero);

    printf("Estado (ex: SP): ");
    scanf(" %49[^\n]", c->estado);

    printf("Codigo da carta (ex: A01): ");
    scanf(" %9[^\n]", c->codigo);

    printf("Nome da cidade: ");
    scanf(" %49[^\n]", c->cidade);

    printf("Populacao (int): ");
    scanf("%d", &c->populacao);

    printf("Area (float): ");
    scanf("%f", &c->area);

    printf("PIB (float): ");
    scanf("%f", &c->pib);

    printf("Numero de pontos turisticos (int): ");
    scanf("%d", &c->pontos_turisticos);

    printf("\n");
}

// ===== ESCOLHA DO ATRIBUTO (direto no código) =====
#define POPULACAO 1
#define AREA 2
#define PIB 3
#define DENSIDADE 4
#define PIB_PER_CAPITA 5

// Troque aqui o atributo escolhido:
#define ATRIBUTO_ESCOLHIDO POPULACAO

int main() {
    Carta carta1, carta2;

    // 1) Receber dados de duas cartas
    cadastrar_carta(&carta1, 1);
    cadastrar_carta(&carta2, 2);

    // 2) Calcular densidade e PIB per capita
    calcular_atributos(&carta1);
    calcular_atributos(&carta2);

    // Mostrar os cálculos (requisito: calcular e exibir)
    printf("===== ATRIBUTOS CALCULADOS =====\n");
    printf("Carta 1 - %s (%s):\n", carta1.cidade, carta1.estado);
    printf("  Densidade Populacional: %.2f\n", carta1.densidade_populacional);
    printf("  PIB per capita: %.6f\n\n", carta1.pib_per_capita);

    printf("Carta 2 - %s (%s):\n", carta2.cidade, carta2.estado);
    printf("  Densidade Populacional: %.2f\n", carta2.densidade_populacional);
    printf("  PIB per capita: %.6f\n\n", carta2.pib_per_capita);

    // 3) Comparar um único atributo escolhido
    float valor1 = 0.0f, valor2 = 0.0f;
    const char *nome_atributo = "";

    if (ATRIBUTO_ESCOLHIDO == POPULACAO) {
        nome_atributo = "Populacao";
        valor1 = (float)carta1.populacao;
        valor2 = (float)carta2.populacao;
    } else if (ATRIBUTO_ESCOLHIDO == AREA) {
        nome_atributo = "Area";
        valor1 = carta1.area;
        valor2 = carta2.area;
    } else if (ATRIBUTO_ESCOLHIDO == PIB) {
        nome_atributo = "PIB";
        valor1 = carta1.pib;
        valor2 = carta2.pib;
    } else if (ATRIBUTO_ESCOLHIDO == DENSIDADE) {
        nome_atributo = "Densidade Populacional";
        valor1 = carta1.densidade_populacional;
        valor2 = carta2.densidade_populacional;
    } else if (ATRIBUTO_ESCOLHIDO == PIB_PER_CAPITA) {
        nome_atributo = "PIB per capita";
        valor1 = carta1.pib_per_capita;
        valor2 = carta2.pib_per_capita;
    } else {
        // Caso alguém escolha um número inválido
        printf("Erro: Atributo escolhido invalido.\n");
        return 1;
    }

    // 4) Determinar vencedora (regra especial para densidade)
    int vencedor = 0; // 1 = carta1, 2 = carta2, 0 = empate

    if (ATRIBUTO_ESCOLHIDO == DENSIDADE) {
        // Menor densidade vence
        if (valor1 < valor2) vencedor = 1;
        else if (valor2 < valor1) vencedor = 2;
        else vencedor = 0;
    } else {
        // Maior valor vence
        if (valor1 > valor2) vencedor = 1;
        else if (valor2 > valor1) vencedor = 2;
        else vencedor = 0;
    }

    // 5) Exibir resultado da comparação (claro e completo)
    printf("===== COMPARACAO DE CARTAS (Atributo: %s) =====\n\n", nome_atributo);

    printf("Carta 1 - %s (%s): %.6f\n", carta1.cidade, carta1.estado, valor1);
    printf("Carta 2 - %s (%s): %.6f\n\n", carta2.cidade, carta2.estado, valor2);

    if (vencedor == 1) {
        printf("Resultado: Carta 1 (%s) venceu!\n", carta1.cidade);
    } else if (vencedor == 2) {
        printf("Resultado: Carta 2 (%s) venceu!\n", carta2.cidade);
    } else {
        printf("Resultado: Empate!\n");
    }

    return 0;
}
