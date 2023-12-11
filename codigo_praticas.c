#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define qnt 5

/**
 * @brief struct que contém os principais dados de um possível entrevistado
 *
 */
typedef struct
{
    int idade;
    char r1, r2, r3, r4, r5;
    char genero, nome[200];

} tp_user;

/**
 * @brief função que guarda em arquivo os dados de usuário e os dados de pesquisa
 *
 * @param user ponteiro para um tipo chamado tp_user que contém os principais dados para serem gravados ou lidos de um usuário
 * @return int retorna 1 se tudo ocorreu como o esperado, e 0 se existe algum erro
 */
int user_arquivo(tp_user *user)
{

    FILE *pesquisa, *estatistica;
    int idade;
    char nome[200], genero;

    // abre os arquivos e verifica o sucesso da operação
    pesquisa = fopen("pesquisa.txt", "a");
    estatistica = fopen("estatisticas.txt", "a");
    if (pesquisa == NULL || estatistica == NULL)
    {
        printf("falha ao abrir o arquivo!\n");
        return 0;
    }

    // gravação de dados em arquivo
    genero = user->genero;
    idade = user->idade;
    strcpy(nome, user->nome);
    fprintf(pesquisa, "|-------------------------------------------------|\n");
    fprintf(pesquisa, "|Nome: %s |", user->nome);
    fprintf(pesquisa, "|Idade: %d |", idade);
    fprintf(pesquisa, "| Genero: %c |\n", genero);
    fprintf(pesquisa, "|-------------------------------------------------|\n");
    fprintf(pesquisa, "pergunta 1: %c\n", user->r1);
    fprintf(pesquisa, "pergunta 2: %c\n", user->r2);
    fprintf(pesquisa, "pergunta 3: %c\n", user->r3);
    fprintf(pesquisa, "pergunta 4: %c\n", user->r4);
    fprintf(pesquisa, "pergunta 5: %c\n", user->r5);

    fprintf(estatistica, "%d", idade);
    fprintf(estatistica, " %c", genero);
    fprintf(estatistica, " %c", user->r1);
    fprintf(estatistica, " %c", user->r2);
    fprintf(estatistica, " %c", user->r3);
    fprintf(estatistica, " %c", user->r4);
    fprintf(estatistica, " %c\n", user->r5);

    // Fecha os arquivos
    fclose(estatistica);
    fclose(pesquisa);

    printf("aperte qualquer tecla para retornar ao menu\n");
    getch();
    return 1;
}

/**
 * @brief Função que realiza todo processo de pesquisa com o usuário
 *
 * @param user Variável do tipo tp_user que recebe os dados da pesquisa
 * @return int retorna 1 se tudo ocorreu como o esperado, e 0 se existe algum erro
 */
int pesquisa_user(tp_user *user)
{

    // Realização de perguntas e coleta de dados
    printf("Digite seu nome\n");
    scanf(" %[^\n]s", user->nome);

    printf("informe sua idade\n");
    scanf("%d", &user->idade);

    printf("Informe seu genero Masculino, feminino, outro(m/f/o)\n");
    scanf(" %c", &user->genero);

    system("cls");

    printf("para as perguntas a seguir responda com 's' para 'sim' e 'n' para 'nao'\n");
    printf("Comunidades costeiras enfrentam restricoes no acesso a recursos marinhos, afetando seu direito a subsistencia?\n ");
    scanf(" %c", &user->r1);

    printf("As comunidades costeiras enfrentam falta de informações sobre recursos marinhos, prejudicando seu direito à participação em decisões?\n ");
    scanf(" %c", &user->r2);

    printf("A mineracao de recursos marinhos afeta negativamente praticas culturais de comunidades dependentes?\n ");
    scanf(" %c", &user->r3);

    printf("Povos indigenas e minorias etnicas sofrem impactos unicos devido as atividades ligadas a vida na agua?\n ");
    scanf(" %c", &user->r4);

    printf("A pesca industrial sem regulamentacoes desrespeita os direitos de subsistencia das comunidades costeiras?\n ");
    scanf(" %c", &user->r5);

    // É chamada a função de gravação em arquivo dos dados, retornando se tudo ocorreu como o esperado
    return user_arquivo(user);
    ;
}

/**
 * @brief Função que lê os dados em arquivo e faz toda separação dos dados, de acordo com a estatística solicitada
 *
 * @return int retorna 1 se tudo ocorreu como o esperado, e 0 se existe algum erro
 */
int listar_estatistica()
{
    FILE *estatistica;

    // abre o arquivo e verifica o sucesso da operação
    estatistica = fopen("estatisticas.txt", "r");
    if (estatistica == NULL)
    {
        printf("falha ao abrir o arquivo!\n");
        return 0;
    }

    char line[100];
    int idade;
    char genero, r[5] = {48};

    int totalGeral = 0;
    int totalR[5] = {0};
    int totalGeneroM = 0, totalGeneroF = 0, totalGeneroX = 0;
    int totalMenores18 = 0, totalMaioresIgual18 = 0;

    while (fgets(line, 100, estatistica) != NULL)
    {
        // Usa sscanf para extrair os dados da linha
        if (sscanf(line, "%d %c %c %c %c %c %c", &idade, &genero, &r[0], &r[1], &r[2], &r[3], &r[4]) == 7)
        {
            for (int i = 0; i < qnt; i++) // loop que calcula as violações por categoria
            {

                if (r[i] == 's' || r[i] == 'S')
                {
                    totalR[i]++;
                }

                if (r[i] == 's' || r[i] == 'S')
                {
                    totalGeral++;
                }
                if ((r[i] == 's' || r[i] == 'S') && (idade >= 18))
                {
                    totalMaioresIgual18++;
                }
                if ((r[i] == 's' || r[i] == 'S') && (idade < 18))
                {
                    totalMenores18++;
                }
                if ((r[i] == 's' || r[i] == 'S') &&(genero == 'm' || genero == 'M'))
                {
                    totalGeneroM++;
                }
                 if ((r[i] == 's' || r[i] == 'S') && (genero == 'f' || genero == 'F'))
                {
                    totalGeneroF++;
                }
                if ((r[i] == 's' || r[i] == 'S') && (genero == 'o' || genero == 'O'))
                {
                    totalGeneroX++;
                }
            }
        }
        else
        {
            // A linha não possui o formato esperado
            printf("Formato inválido na linha: %s", line);
        }
    }

    // Exibe em tela os valores processados
    printf("------------------------------------------------\n");
    printf("Total Geral de Violacoes: %d\n", totalGeral);
    printf("------------------------------------------------\n");
    printf("Total Violacao 1: %d\n", totalR[0]);
    printf("Total Violacao 2: %d\n", totalR[1]);
    printf("Total Violacao 3: %d\n", totalR[2]);
    printf("Total Violacao 4: %d\n", totalR[3]);
    printf("Total Violacao 5: %d\n", totalR[4]);
    printf("------------------------------------------------\n");
    printf("Total Genero Masculino: %d\n", totalGeneroM);
    printf("Total Genero Feminino: %d\n", totalGeneroF);
    printf("Total Para outros Generos: %d\n", totalGeneroX);
    printf("------------------------------------------------\n");
    printf("Total Menores de 18 anos: %d\n", totalMenores18);
    printf("Total Maiores ou Iguais a 18 anos: %d\n", totalMaioresIgual18);
    printf("------------------------------------------------\n\n");

    // trecho que permite que o usuário consulte os dados, antes de retornar ao menu
    printf("aperte qualquer tecla para retornar ao menu\n");
    getch();

    return 1;
}

/**
 * @brief Função que exibe em tela todos os dados coletados e armazeados em arquivo de maneira formatada
 *
 * @return int retorna 1 se tudo ocorreu como o esperado, e 0 se existe algum erro
 */
int lista_user()
{
    FILE *pesquisa;
    char linha[300];

    system("cls");

    // abre o arquivo e verifica o sucesso da operação
    pesquisa = fopen("pesquisa.txt", "r");
    if (pesquisa == NULL)
    {
        printf("falha ao abrir o arquivo!\n");
        return 0;
    }

    while (fscanf(pesquisa, " %[^\n]s", linha) != EOF) // percorre todo o arquivo listando os dados guardados em arquivo
    {
        printf("%s\n", linha);
    }
    fclose(pesquisa);

    printf("\n(S-SIM N-NAO)\n\n");

    // trecho que permite que o usuário consulte os dados, antes de retornar ao menu
    printf("aperte qualquer tecla para retornar ao menu\n");
    getch();

    return 1;
}

/**
 * @brief Função que busca os registros no arquivo a partir de um nome de usuário, e retorna as correspondências da busca
 *
 * @return int retorna 1 se tudo ocorreu como o esperado, e 0 se existe algum erro
 */
int busca_user()
{
    char nome[20], linha[300];
    int find = 0, x;
    FILE *pesquisa;

     // abre o arquivo e verifica o sucesso da operação
    pesquisa = fopen("pesquisa.txt", "r");
    if (pesquisa == NULL)
    {
        printf("falha ao abrir o arquivo!\n");
        return 0;
    }

    //Solicita o nome a ser buscado
    printf("Informe o nome do usuario que deseja buscar\n");
    scanf(" %[^\n]s", nome);

    //realização da busca em laço
    while (fscanf(pesquisa, " %[^\n]s", linha) != EOF)
    {
        if (strstr(linha, nome) != NULL)
        {
            find = 1;
            printf("Usuario encontrado!\n");
            printf("%s\n", linha);
            for (int i = 0; i < qnt + 1; i++)
            {
                fscanf(pesquisa, " %[^\n]s", linha);
                printf("%s\n", linha);
            }
        }
    }
    if (find != 1)
    {
        printf("Usuario não encontrado!\n");
    }

    // trecho que permite que o usuário consulte os dados, antes de retornar ao menu
    printf("aperte qualquer tecla para retornar ao menu\n");
    getch();

    return find;
}

/**
 * @brief Função principal, onde está organizada a ordem das demais funções
 *
 * @return int retorna 1 se tudo ocorreu como o esperado, e 0 se existe algum erro
 */
int main()
{
    int resp;
    tp_user user;

    while (resp != 5)
    {
        system("cls");
        //Menu Principal
        printf("Bem vindo(a) a nossa pesquisa, por favor escolha uma das opcoes abaixo: \n");
        printf("|---------------------------------Menu-----------------------------------|\n");
        printf("|--------------Para participar da nossa pesquisa digite '1'--------------|\n");
        printf("|---Para ver uma lista de resposta de outros participantes digite '2'----|\n");
        printf("|---------------Para buscar um usuario especifico digite '3'-------------|\n");
        printf("|---Para ver uma lista das estatisticas gerais da pesquisa digite '4'----|\n");
        printf("|--------------------------Para sair digite '5'--------------------------|\n");
        printf("|------------------------------------------------------------------------|\n");

        scanf("%d", &resp);

        //Switch com Funções do programa
        switch (resp)
        {
        case 1:
            system("cls");
            if (!pesquisa_user(&user))
            {
                printf("Algo deu errado no salvamento dos dados\n");
            }
            break;
        case 2:
            lista_user();
            break;
        case 3:
            system("cls");
            busca_user();
            break;
        case 4:
            system("cls");
            listar_estatistica();
            break;
        default:
            printf("Obrigado por participar da nossa pesquisa!\n");
            break;
        }
    }
    return 0;
}
