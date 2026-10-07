#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>
#include <string.h>

#define max_lab 20
#define max_dias 30

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


int main(){

    int funcionalidade;
    int opcao;
    int ocupacao_labs[max_lab][max_dias];
    int num_labs;
    int capacidade_labs[max_lab];
    float desempenho_labs[max_lab][max_dias];
    int dias;
    int dados_cadastrados = 0;
    int i, j;
    int total_diario[max_dias];
    int maior_movimentacao = -1;
    int soma_ocupacao_lab[max_lab];
    float soma_desempenho_lab[max_lab];
    int maior_ocupacao_dia = -1;
    int menor_ocupacao_dia = 99999999;
    float taxa_media_diaria[max_lab];
    float media_ocupacao[max_lab];
    float media_desempenho[max_lab];
    int dia_maior_individual[max_lab];
    int dia_menor_individual[max_lab];
    int maior_ocupacao_individual[max_lab];
    int menor_ocupacao_individual[max_lab];
    int calculo_indicadores = 0;
    int consulta_dia;
    int lab_mais_ocupado = 0;
    int maior_ocupacao_lab;
    int tipo_relatorio;
    int consulta_lab;
    int indice;
    int classificacao[max_lab];

    setlocale(LC_ALL, "portuguese");

    printf("\n-----------------------------------------------------------------------------------\n");
    printf("\nSISTEMA DE MONITORAMENTO DE OCUPAÇÃO E DESEMPENHO DE LABORATÓRIOS\n");
    printf("\nSeja bem-vindo ao sistema de controle acadêmico!");
    printf("\nNa próxima página, você terá acesso ao menu principal de funcionalidades.");
    printf("\nAssim, poderá monitorar a ocupação dos laboratórios da instituição.\n");
    printf("\n-----------------------------------------------------------------------------------\n");
    printf("\n");
    system("pause");

    do{
        system("cls");
        printf("\n---- SISTEMA DE MONITORAMENTO DE LABORATÓRIOS ----\n");
        printf("\nEscolha a funcionalidade desejada\n\t");
        printf("\n1 - Cadastrar Dados");
        printf("\n2 - Exibir a Tabela de Ocupação");
        printf("\n3 - Calcular Indicadores");
        printf("\n4 - Laboratório Mais Ocupado");
        printf("\n5 - Classificação dos Laboratórios");
        printf("\n6 - Exibir Relatório");
        printf("\n0 - Encerrar Programa");
        printf("\n\t");
        printf("\nQual opção deseja selecionar?: ");

        while (scanf("%d", &funcionalidade) != 1)
        {
            limpar_buffer();
            printf("\nERRO");
            printf("\nSomente números são permitidos.");
            printf("\nQual opção deseja selecionar?: ");
        }


        if(funcionalidade >= 2 && funcionalidade <= 5){
            if(dados_cadastrados == 0){
                system("cls");
                printf("\nERRO");
                printf("\nAinda não existem dados cadastrados no sistema.");
                printf("\nRealize o cadastro selecionando a opção 1 e, em seguida, realize a ação desejada.\n");
                system("pause");
                continue;
            }
            else{
                do{
                    system("cls");
                    printf("\nJá existem dados cadastrados no sistema.");
                    printf("\nEscolha uma opção para continuar: ");
                    printf("\n1 - Utilizar dados atuais");
                    printf("\n2 - Cadastrar novos dados");
                    printf("\n\t");
                    printf("\nQual opção deseja selecionar?: ");

                    if(scanf("%d", &opcao) != 1){
                        limpar_buffer();
                        printf("\nERRO");
                        printf("\nSomente números são permitidos.\n");
                        opcao = -1;
                    }

                    else if(opcao < 1 || opcao > 2){
                        printf("\nERRO");
                        printf("\nOpção inválida. Selecione um valor válido.\n");
                        system("pause");
                    }
                }while(opcao < 1 || opcao > 2);
            }

            if(opcao == 2){
                funcionalidade = 1;
            }
        }


        switch(funcionalidade){
            case 1:
                system("cls");
                printf("\n---- CADASTRO DE DADOS ----\n");
                printf("\n--------------------------------------------------------\n");
                do{
                    printf("\nO sistema aceita o cadastro de até 20 laboratórios.");
                    printf("\nInsira a quantidade de laboratórios utilizados: ");

                    if(scanf("%d", &num_labs) != 1){
                        limpar_buffer();
                        printf("\nERRO");
                        printf("\nSomente números são permitidos.\n");
                        num_labs = -1;
                    }

                    else if(num_labs < 1 || num_labs > max_lab){
                        printf("\nERRO");
                        printf("\nInsira um valor válido.\n");
                    }
                }while(num_labs < 1 || num_labs > max_lab);

                do{
                    printf("\nO sistema realiza o acompanhamento de registros de até 30 dias.");
                    printf("\nInsira a quantidade de dias: ");

                    if(scanf("%d", &dias) != 1){
                        limpar_buffer();
                        printf("\nERRO");
                        printf("\nSomente números são permitidos.\n");
                        dias = -1;
                    }

                    else if(dias < 1 || dias > max_dias){
                        printf("\nERRO");
                        printf("\nInsira um número de dias válido.\n");
                    }
                }while(dias < 1 || dias > max_dias);

                system("cls");
                printf("\n--- CADASTRO CAPACIDADE LABORATÓRIOS ---\n");
                printf("\n--------------------------------------------------------\n");
                for(i = 0; i < num_labs; i++){
                    do{
                        printf("\nInsira a capacidade máxima do Láb. %02d: " , i+ 1);

                        if(scanf("%d", &capacidade_labs[i]) != 1){
                        limpar_buffer();
                        printf("\nERRO");
                        printf("\nSomente números são permitidos.\n");
                        capacidade_labs[i] = -1;
                        }

                        else if(capacidade_labs[i] <= 0){
                            printf("\nERRO");
                            printf("\nInsira um valor de capacidade maior que 0.\n");
                        }
                    }while(capacidade_labs[i] <= 0);
                }

                system("cls");
                printf("\n--- CADASTRO OCUPAÇÃO ---\n");
                printf("\n----------------------------------------------\n");
                for(i = 0; i < num_labs; i++){
                    printf("\nLaboratório %02d" ,i+1);
                    printf("\nCapacidade Máxima: %02d" ,capacidade_labs[i]);
                    for(j = 0; j < dias; j++){
                        do{
                            printf("\nAlunos presentes no dia %02d: " ,j+1);

                            if(scanf("%d", &ocupacao_labs[i][j]) != 1){
                                limpar_buffer();
                                printf("\nERRO");
                                printf("\nSomente números são permitidos.\n");
                                ocupacao_labs[i][j] = -1;
                            }

                            else if(ocupacao_labs[i][j] < 0 || ocupacao_labs[i][j] > capacidade_labs[i]){
                                printf("\nERRO");
                                printf("\nOcupação ultrapassou o limite.");
                                printf("\nInsira o valor novamente.\n");
                            }
                        }while(ocupacao_labs[i][j] < 0 || ocupacao_labs[i][j] > capacidade_labs[i]);
                    }
                }
                printf("\nOcupação cadastrada com sucesso!\n");
                system("pause");

                system("cls");
                printf("\n--- CADASTRO DESEMPENHO ---\n");
                printf("\n----------------------------------------------\n");
                printf("\nEscala de desempenho medida no intervalo de 0 a 10.");
                printf("\nVAlores reais podem ser inseridos no sistema.\n");
                printf("\n----------------------------------------------\n");
                for(i = 0; i < num_labs; i++){
                    printf("\nLaboratório %02d" , i+1);
                    for(j = 0; j < dias; j++){

                        if(ocupacao_labs[i][j] == 0){
                            printf("\nDesempenho Dia %02d: 0.0", j+1);
                            printf("\nDefinição automática para dias com ocupação 0.\n");
                            continue;
                        }

                        do{
                            printf("\nDesempenho Dia %02d: " , j+1);

                            if(scanf("%f", &desempenho_labs[i][j]) != 1){
                                limpar_buffer();
                                printf("\nERRO");
                                printf("\nSomente números são permitidos.\n");
                                desempenho_labs[i][j] = -1;
                            }

                            else if(desempenho_labs[i][j] < 0.0 || desempenho_labs[i][j] > 10.0){
                                printf("\nERRO");
                                printf("\nValor inválido, o desempenho é medido entre 0 - 10.\n");
                            }
                        }while(desempenho_labs[i][j] < 0.0 || desempenho_labs[i][j] > 10.0);
                    }
                }
                printf("\nDesempenho cadastrado com sucesso!\n");
                system("pause");

                dados_cadastrados = 1;
                break;

            case 2:
                system("cls");
                printf("\n---- TABELA DE OCUPAÇÃO ----\n\n");
                printf("LABORATÓRIO |");

                for(i = 0; i < dias; i++){
                    printf(" DIA %02d |" , i+1);
                }
                printf("\n");

                for(i =0; i <= dias; i++){
                    printf("-----------");
                }
                printf("\n");

                for(i = 0; i < num_labs; i++){
                    printf("Lab %02d      |" , i+1);
                    for(j = 0; j < dias; j++){
                        printf("   %02d   |" , ocupacao_labs[i][j]);
                    }
                    printf("\n");
                }

                printf("\n");
                system("pause");
                break;

            case 3:
                system("cls");
                printf("\nCalculando indicadores...\n");
                system("pause");

                for(i = 0; i < dias; i++){
                    total_diario[i] = 0;
                    for(j = 0; j < num_labs; j++){
                        total_diario[i] += ocupacao_labs[j][i];
                    }

                    if(total_diario[i] > maior_movimentacao){
                        maior_movimentacao = total_diario[i];
                    }
                }

                for(i = 0; i < num_labs; i++){
                    soma_ocupacao_lab[i] = 0;
                    soma_desempenho_lab[i] = 0.0;
                    for(j = 0; j < dias; j++){
                        soma_ocupacao_lab[i] += ocupacao_labs[i][j];
                        soma_desempenho_lab[i] +=desempenho_labs[i][j];

                        if(ocupacao_labs[i][j] > maior_ocupacao_dia){
                            maior_ocupacao_dia = ocupacao_labs[i][j];
                        }

                        if(ocupacao_labs[i][j] < menor_ocupacao_dia){
                            menor_ocupacao_dia = ocupacao_labs[i][j];
                        }
                    }

                    media_ocupacao[i] = (float)round((float)soma_ocupacao_lab[i] / dias);
                    taxa_media_diaria[i] = ((float)soma_ocupacao_lab[i] / (capacidade_labs[i] * dias)) * 100;
                    media_desempenho[i] = soma_desempenho_lab[i]/ dias;
                }

                for(i = 0; i < num_labs; i++){
                    maior_ocupacao_individual[i] = ocupacao_labs[i][0];
                    dia_maior_individual[i] = 0;
                    menor_ocupacao_individual[i] = ocupacao_labs[i][0];
                    dia_menor_individual[i] = 0;
                    for(j = 0; j < dias; j++){
                        if(ocupacao_labs[i][j] > maior_ocupacao_individual[i]){
                            maior_ocupacao_individual[i] = ocupacao_labs[i][j];
                            dia_maior_individual[i]= j;
                        }
                        if(ocupacao_labs[i][j] < menor_ocupacao_individual[i]){
                            menor_ocupacao_individual[i] = ocupacao_labs[i][j];
                            dia_menor_individual[i]= j;
                        }
                    }
                }


                system("cls");
                printf("\n---- CÁLCULO INDICADORES ----\n");
                printf("\n----------------------------------------------\n");
                printf("\n--- TOTAL DIÁRIO DE OCUPAÇÃO ---\n");
                for(i = 0; i < dias; i++){
                    printf("\nDia %02d: %d alunos presentes\n", i+1, total_diario[i]);
                }

                printf("\n----------------------------------------------\n");
                printf("\n--- MÉDIA DIÁRIA DE OCUPAÇÃO E TAXA MÉDIA DE OCUPAÇÃO POR LABORATÓRIO ---\n");
                for(i = 0; i < num_labs; i++){
                    printf("\nLaboratório %02d: ", i+1);
                    printf("\n- Média diária de ocupação: %.2f alunos" , media_ocupacao[i]);
                    printf("\n- Taxa média de ocupação: %.2f%%\n", taxa_media_diaria[i]);
                }

                printf("\n----------------------------------------------\n");
                printf("\n--- DIA(S) DE MAIOR MOVIMENTAÇÃO ---\n");
                printf("\nMaior movimentação registrada: %d alunos", maior_movimentacao);
                printf("\nOcorrência(s) em:\n");
                for(i = 0; i < dias; i++){
                    if(total_diario[i] == maior_movimentacao){
                        printf("\n- Dia %02d\n" , i + 1);
                    }
                }

                printf("\n----------------------------------------------\n");
                printf("\n--- MAIOR OCUPAÇÃO ---\n");
                printf("\nMaior ocupação registrada: %d alunos" , maior_ocupacao_dia);
                printf("\nResgistrada em: \n");
                for(i = 0; i < num_labs; i++){
                    for(j = 0; j < dias; j++){
                        if(ocupacao_labs[i][j] == maior_ocupacao_dia){
                        printf("\n- Laboratório %02d", i + 1);
                        printf("\n  Dia %02d\n", j + 1);
                        }
                    }
                }

                printf("\n----------------------------------------------\n");
                printf("\n--- MENOR OCUPAÇÃO ---\n");
                printf("\nMenor ocupação registrada: %d alunos" , menor_ocupacao_dia);
                printf("\nResgistrada em: \n");
                for(i = 0; i < num_labs; i++){
                    for(j = 0; j < dias; j++){
                        if(ocupacao_labs[i][j] == menor_ocupacao_dia){
                            printf("\n- Laboratório %02d", i + 1);
                            printf("\n  Dia %02d\n", j + 1);
                        }
                    }
                }
                printf("\n----------------------------------------------\n");
                printf("\n");
                system("pause");

                calculo_indicadores = 1;
                break;

            case 4:
                system("cls");
                printf("\n---- LABORATÓRIO MAIS OCUPADO ----\n");
                printf("\n----------------------------------------------\n");
                do{
                    printf("\nCadastro de dados de 01 a %02d dias" ,dias);
                    printf("\nInsira o dia que deseja consultar: ");

                    if (scanf("%d", &consulta_dia) != 1){
                        limpar_buffer();
                        printf("\nERRO");
                        printf("\nSomente números são permitidos.\n");
                        consulta_dia = -1;
                    }

                    else if(consulta_dia < 1 || consulta_dia > dias){
                        printf("\nERRO");
                        printf("\nInsira um dia válido, já cadastrado no sistema.\n");
                    }
                }while(consulta_dia < 1 || consulta_dia > dias);

                maior_ocupacao_lab = ocupacao_labs[0][consulta_dia - 1];
                for(i = 1; i < num_labs; i++){
                    if(ocupacao_labs[i][consulta_dia - 1] > maior_ocupacao_lab){
                        maior_ocupacao_lab = ocupacao_labs[i][consulta_dia - 1];
                        lab_mais_ocupado = i;
                    }
                }

                system("cls");
                printf("\n---- LABORATÓRIO MAIS OCUPADO ----\n");
                printf("\n----------------------------------------------\n");
                printf("\nNo dia %02d, a maior ocupação registrada foi: %02d" , consulta_dia, maior_ocupacao_lab);
                printf("\nLaboratório(s) mais ocupado(s): \n");
                for(i =0; i < num_labs; i++){
                  if(ocupacao_labs[i][consulta_dia - 1] == maior_ocupacao_lab){
                      printf("\n- Láb. %02d" , i+1);
                  }
                }
                printf("\n");
                system("pause");
                break;

            case 5:
                if(calculo_indicadores == 0){
                system("cls");
                printf("\nOs indicadores ainda não foram calculados.");
                printf("\nPortanto, não é possível apresentar um relatório.");
                printf("\nPor favor, execute o cálculo dos indicadores, selecionando a funcionalidade 3, para ter acesso aos relatórios.\n");
                system("pause");
                break;

                printf("\n----Classificação dos laboratorios----\n");
                for(i =0; i < num_labs; i++){
                    printf("Laboratorio %d",i+1);
                    if (taxa_media_diaria[i]>=80)
                    {
                       if (media_desempenho[i]>= 7.5)
                       {
                            classificacao[i] = 1;
                            printf("\nalto aproveitamento\n");

                       }
                       else
                       {
                            classificacao[i] = 2;
                           printf("\natenção ao desempenho\n");
                       }
                    }
                    if (taxa_media_diaria[i]<80 && taxa_media_diaria[i]>= 50)
                    {
                        if (media_desempenho[i]>= 7.5)
                        {
                            classificacao[i] = 3;
                            printf("\nOcupação moderada\n");
                        }
                        else
                        {
                            classificacao[i] = 4;
                            printf("\natenção na ocupação\n");
                        }
                    }
                    if (taxa_media_diaria[i]<50)
                    {
                            classificacao[i] = 5;
                        printf("\nsubutilizado\n");
                    }
                }
                printf("\n");
                system("pause");
                break;
            case 6:
                if(calculo_indicadores == 0){
                    system("cls");
                    printf("\nOs indicadores ainda não foram calculados.");
                    printf("\nPortanto, não é possível apresentar um relatório.");
                    printf("\nPor favor, execute o cálculo dos indicadores, selecionando a funcionalidade 3, para ter acesso aos relatórios.\n");
                    system("pause");
                    break;
                }

                do{
                    system("cls");
                    printf("\n---- EXIBIÇÃO RELATÓRIO ----\n");
                    printf("\n----------------------------------------------\n");
                    printf("\nEscolha o relatório que deseja acessar: ");
                    printf("\n1 - Relatório de um laboratório: dado o laboratório, fornece todas as informações.");
                    printf("\n2 - Relatório geral: contém todas as informações de todos os laboratórios.");
                    printf("\n\t");
                    printf("\nQual opção deseja selecionar?: ");

                    if (scanf("%d", &tipo_relatorio) != 1){
                        limpar_buffer();
                        printf("\nERRO");
                        printf("\nSomente números são permitidos.\n");
                        tipo_relatorio = -1;
                    }

                    else if(tipo_relatorio < 1 || tipo_relatorio > 2){
                        printf("\nERRO");
                        printf("\nOpção inválida. Selecione um valor válido.\n");
                    }
                }while(tipo_relatorio < 1 || tipo_relatorio > 2);

                if(tipo_relatorio == 1){
                    system("cls");
                    printf("\n--- RELATÓRIO DE UM LABORATÓRIO ---\n");
                    printf("\n----------------------------------------------\n");

                    do{
                        printf("\nExistem %02d laboratórios cadastrados no sistema." ,num_labs);
                        printf("\nInsira o laboratório que deseja consultar: ");

                        while (scanf("%d", &consulta_lab) != 1){
                            limpar_buffer();
                            printf("\nERRO");
                            printf("\nSomente números são permitidos.\n");
                            printf("\nQual opção deseja selecionar?: ");
                        }

                        indice = consulta_lab - 1;
                        if(indice < 0 || indice >= num_labs){
                            printf("\nERRO");
                            printf("\nEsse laboratório não está cadastrado no sistema.");
                            printf("\nInsira um valor válido.\n");
                        }
                    }while(indice < 0 || indice >= num_labs);

                    system("cls");
                    printf("\n--- RELATÓRIO DE UM LABORATÓRIO ---\n");
                    printf("\n");
                    printf("\n----------------------------------------------");
                    printf("\n          RELATÓRIO LABORATÓRIO %02d\n" ,consulta_lab);
                    printf("\n----------------------------------------------");
                    printf("\nCapacidade Máxima = %d alunos\n", capacidade_labs[indice]);
                    printf("\nOcupação por Dia:");
                    for(i = 0; i < dias; i++){
                        printf("\n- Dia %02d: %d alunos" , i + 1, ocupacao_labs[indice][i]);
                    }
                    printf("\n");
                    printf("\nIndicadores do Láb. %02d\n" , consulta_lab);
                    printf("\n- Média Diária de Ocupação: %.2f alunos" ,media_ocupacao[indice]);
                    printf("\n- Taxa Média de Ocupação: %.2f%%" , taxa_media_diaria[indice]);
                    printf("\n- Média de Desempenho: %.2f", media_desempenho[indice]);
                    printf("\n- Maior Ocupação: %d alunos" , maior_ocupacao_individual[indice]);
                    printf("\n  Registrada Dia %d" , dia_maior_individual[indice] + 1);
                    printf("\n- Menor Ocupação: %d alunos" , menor_ocupacao_individual[indice]);
                    printf("\n  Registrada Dia %d" , dia_menor_individual[indice] + 1);
                    printf("\n----------------------------------------------\n");
                    system("pause");
                }

                else{
                    system("cls");
                    printf("\n--- RELATÓRIO GERAL ---\n");
                    printf("\n----------------------------------------------");
                    printf("\nTotal Laboratórios = %d", num_labs);
                    printf("\nTotal Dias = %d\n", dias);
                    printf("\n");

                    for(i = 0; i < num_labs; i++){
                        printf("\n----------------------------------------------");
                        printf("\n          RELATÓRIO LABORATÓRIO %02d\n" , i + 1);
                        printf("\n----------------------------------------------");
                        printf("\nCapacidade Máxima = %d alunos\n", capacidade_labs[i]);
                        printf("\nOcupação por Dia:");
                        for(j = 0; j < dias; j++){
                            printf("\n- Dia %02d: %d alunos" , j + 1, ocupacao_labs[i][j]);
                        }

                        printf("\n\nIndicadores do Láb. %02d" , i + 1);
                        printf("\n- Média Diária de Ocupação: %.2f alunos" ,media_ocupacao[i]);
                        printf("\n- Taxa Média de Ocupação: %.2f%%" , taxa_media_diaria[i]);
                        printf("\n- Média Desempenho: %.2f" , media_desempenho[i]);
                        printf("\n- Maior Ocupação: %d alunos" , maior_ocupacao_individual[i]);
                        printf("\n  Registrada Dia %d" , dia_maior_individual[i] + 1);
                        printf("\n- Menor Ocupação: %d alunos" , menor_ocupacao_individual[i]);
                        printf("\n  Registrada Dia %d\n" , dia_menor_individual[i] + 1);
                    }
                    printf("\n----------------------------------------------\n");
                    system("pause");
                }
                break;

            case 0:
                printf("\nEncerrando programa de monitoramento de laboratórios.");
                break;

            default:
                printf("Opção inválida, tente selecionar uma funcionalidade novamente.\n");
                system("pause");

        }
        }
    }while(funcionalidade !=0);

    return 0;
}
