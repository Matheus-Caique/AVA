#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

typedef struct{
	char nome[MAX];
	int matricula;
} Matricula;

typedef struct{
	char atividade[MAX];
	char questao[150];
} Atividade;

typedef struct Node {
    void* dado;
    struct Node* prox;
} Node;

typedef struct {
    Node* inicio;
    Node* fim;
} Fila;

void inserirfila(Fila* fila, void* dado) {
    Node* novo = (Node*)malloc(sizeof(Node));
    if (novo != NULL) {
        novo->dado = dado;
        novo->prox = NULL;

        if (fila->fim == NULL) {
            fila->inicio = novo;
            fila->fim = novo;
        } else {
            fila->fim->prox = novo;
            fila->fim = novo;
        }
    }
}

void liberarfila(Fila* fila) {
    Node* atual = fila->inicio;
    while (atual != NULL) {
        Node* temp = atual;
        atual = atual->prox;
        free(temp->dado);
        free(temp);
    }
    free(fila);
}

Fila* criarfila(){
	Fila* fila = (Fila*)malloc(sizeof(Fila));
	if(fila!=NULL){
		fila->inicio = NULL;
		fila->fim = NULL;
	}
	return fila;
}

void Listar(int escprof){
	FILE* arquivo;
	Fila* filaAlunos = criarfila();
	Fila* filaProfs = criarfila();
	char linha [MAX];
	Matricula* cadastro;
	int tipo;
	
	arquivo = fopen("matriculas.txt","r");
	
	if(arquivo==NULL){
		printf("Erro ao abrir o arquivo ou arquivo nao criado\n");
		system("pause");
		system("cls");
		return;
	}
	
	while(fgets(linha,MAX,arquivo)!=NULL){
		if(strstr(linha,"Aluno:")!=NULL){
			cadastro = (Matricula*)malloc(sizeof(Matricula));
			sscanf(linha," %*[^:]%*c %[^\n] ",cadastro->nome);
			tipo = 1;
		}
		
		if (strstr(linha,"Professor:")!=NULL){
			cadastro = (Matricula*)malloc(sizeof(Matricula));
			sscanf(linha," %*[^:]%*c %[^\n] ",cadastro->nome);
			tipo = 2;
		}
		
		if(strstr(linha,"Matricula:")!=NULL){
			int matricula;
			sscanf(linha,"Matricula: %d",&matricula);
			if(tipo==1 || tipo==2){
				cadastro->matricula = matricula;				
				if(tipo==1){
				inserirfila(filaAlunos,cadastro);
				} else {
				inserirfila(filaProfs,cadastro);
				}
			}
			
			tipo = 0;
		}
	}

	fclose(arquivo);

	printf("\n========ALUNOS========\n");
	if (filaAlunos->inicio==NULL){
		printf("Nenhum aluno cadastrado\n\n");
	} else {
		Node* atual = filaAlunos->inicio;
		
		while(atual!=NULL){
			Matricula* a = (Matricula*)atual->dado;
			printf("\nAluno: %s\n",a->nome);
			printf("Matricula: %d\n\n",a->matricula);
			atual = atual->prox;
		}
	}
	if(escprof==0){
		printf("========PROFESSORES========\n");
		if (filaProfs->inicio==NULL){
			printf("Nenhum professor cadastrado\n\n");
		} else {
			Node* atual = filaProfs->inicio;
			
			while(atual!=NULL){
				Matricula* p = (Matricula*)atual->dado;
				printf("\nProfessor: %s\n",p->nome);
				printf("Matricula: %d\n\n",p->matricula);
				atual = atual->prox;
			}
		}
	}
	
	liberarfila(filaAlunos);
	liberarfila(filaProfs);
	
	system("pause");
	system("cls");
}

void deletarCadastro() {
    int matricula;
    printf("Digite a matricula que deseja deletar: ");
    scanf("%d", &matricula);

    FILE* original = fopen("matriculas.txt", "r");
    FILE* temporario = fopen("temp.txt", "w");

    if (original == NULL || temporario == NULL) {
        printf("Erro ao abrir arquivos.\n");
        return;
    }

    char linha[MAX];
    int excluir = 0;

    while (fgets(linha, sizeof(linha), original) != NULL) {
        if (strstr(linha, "==================================") != NULL) {
            excluir = 0;
            fputs(linha, temporario);
        } else if (strstr(linha, "Matricula:") != NULL) {
            int matTemp;
            sscanf(linha, "Matricula: %d", &matTemp);
            if (matTemp == matricula) {
                excluir = 1; 
            } else if (!excluir) {
                fputs(linha, temporario);
            }
        } else {
            if (!excluir) {
                fputs(linha, temporario);
            }
        }
    }

    fclose(original);
    fclose(temporario);

    remove("matriculas.txt");
    rename("temp.txt", "matriculas.txt");

    printf("\nCadastro removido com sucesso!\n");
    system("pause");
    system("cls");
}

void cadastroaluno(){
	Matricula cadastro;
	FILE *arquivo;
	
	fflush(stdin);
	
	printf("\nDigite o nome do aluno:");
	fgets(cadastro.nome,MAX,stdin);
	
	printf("Digite a matricula:");
	scanf("%d", &cadastro.matricula);
	
	arquivo = fopen("matriculas.txt","a");
	
	fprintf(arquivo,"==================================\n");
	fprintf(arquivo,"Aluno: %s",cadastro.nome);
	fprintf(arquivo,"Matricula: %d",cadastro.matricula);
	fprintf(arquivo,"\n--------------------------------\n\n");
	
	fclose(arquivo);
	
	system("cls");
	printf("Aluno cadastrado.\n");
}

void cadastroprof(){
	Matricula cadastro;
	FILE *arquivo;
	
	fflush(stdin);
	 
	printf("\nDigite o nome do professor:");
	fgets(cadastro.nome,MAX,stdin);
	
	printf("Digite a matricula:");
	scanf("%d",&cadastro.matricula);
	
	arquivo = fopen("matriculas.txt","a");
	
	fprintf(arquivo,"==================================\n");
	fprintf(arquivo,"Professor: %s",cadastro.nome);
	fprintf(arquivo,"Matricula: %d",cadastro.matricula);
	fprintf(arquivo,"\n--------------------------------\n\n");

	fclose(arquivo);
	
	system("cls");
	printf("Professor cadastrado.\n");
	
	
}

contaadmin(){ 
	int escprof;
	int conta;

		do{

		printf("\n----Admin-----\n");
		printf("1. Cadastrar Professor\n");
		printf("2. Cadastrar Aluno\n");
		printf("3. Listar Cadastros\n");
		printf("4. Deletar Cadastro\n");
		printf("5. Voltar\n");
		
		printf("\nEscolha uma opcao: ");
		scanf("%d", &conta);
		
		switch(conta){
			
			case 1:
				cadastroprof();
				break;
			case 2:
				cadastroaluno();
				break;
			case 3:
				system("cls");
				Listar(escprof);
				break;
			case 4:
				system("cls");
				deletarCadastro();
				break;
			case 5:
				system("cls");
				break;
			default:
				system("cls");
		}

	}while(conta!=5);
}

void atvprofessor(char* usuario) {
    FILE* arquivo = fopen("respostas.txt", "r");
    
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo ou arquivo nao criado.\n");
        system("pause");
        system("cls");
        return;
    }

    char linha[150];
    char atividadeAtual[MAX];
    char alunoAtual[MAX];
    int mostrar = 0;
    int respostas = 0;

    printf("\nDigite o nome da atividade que deseja ver as respostas: ");
    getchar(); 
    fgets(atividadeAtual, MAX, stdin);
    atividadeAtual[strcspn(atividadeAtual, "\n")] = '\0';
    
    system("cls");

    printf("\nRespostas para a atividade \"%s\":\n", atividadeAtual);
    printf("========================================\n");

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        if (strstr(linha, "RESPOSTA: ") != NULL) {
            char nomeAtv[MAX];
            sscanf(linha, "RESPOSTA: %[^\n]", nomeAtv);
            alunoAtual[strcspn(alunoAtual, "\n")] = '\0';
            if (strcmp(nomeAtv, atividadeAtual) == 0) {
                mostrar = 1;
                respostas = 1;
                printf("\n----------------------------------------\n");
            } else {
                mostrar = 0;
            }
        } else if (mostrar && strstr(linha, "Aluno: ") != NULL) {
            sscanf(linha, "Aluno: %[^\n]", alunoAtual);
            alunoAtual[strcspn(alunoAtual, "\n")] = '\0';
            printf("\nAluno: %s\n", alunoAtual);
        } else if (mostrar) {
            printf("%s", linha);
        }
    } 
    
    if(!respostas){
    	printf("\nNenhuma resposta foi registrada para essa atividade\n");
	}

    fclose(arquivo);
    printf("\n----------------------------------------\n");
    system("pause");
    system("cls");
}

void atvalunos(char* usuario){
	FILE* arquivo;
	FILE* arquivo2;
	Fila* filaAtividade = criarfila();
	Fila* filaRespostas = criarfila();
	char linha[150];
	Atividade* texto;
	char opcao[150];
	
	printf("\nDigite o nome da atividade que deseja responder: ");
	fflush(stdin);
	fgets(opcao,150,stdin);
	opcao[strcspn(opcao, "\n")] = '\0';
	

	
	liberarfila(filaAtividade);
	
	arquivo = fopen("atividades.txt","r");
	arquivo2 = fopen("respostas.txt","a");
	
	if(arquivo==NULL){
		printf("Erro ao abrir o arquivo ou arquivo nao criado\n");
		system("pause");
		system("cls");
		return;
	}
	
	while(fgets(linha,sizeof(linha),arquivo)!=NULL){
		if(strstr(linha,"ATIVIDADE: ")!=NULL){
	        texto = (Atividade*)malloc(sizeof(Atividade));
	        
	        if (texto == NULL) {
	            printf("Erro de alocacao\n");
	            continue;
	        }
	        
	        sscanf(linha,"ATIVIDADE: %[^\n]",texto->atividade);
	        
			if(strcmp(texto->atividade,opcao)==0){
				
				char resposta[150];
				fprintf(arquivo2,"RESPOSTA: %s\n",texto->atividade);
				fprintf(arquivo2,"Aluno: %s\n",usuario);
				
				while(fgets(linha,sizeof(linha),arquivo)!=NULL){
					if (strstr(linha, "Questao") != NULL && texto != NULL) {
						
	        			printf("\n%s", linha);
	        			printf("Resposta: ");
	            		fgets(resposta,150,stdin);
	            		opcao[strcspn(opcao, "\n")] = '\0';
	            		
	            		fprintf(arquivo2,"%s",linha);
	            		fprintf(arquivo2,"R: %s",resposta);
	            		
	            		
	    			} else if(strstr(linha, "======================================") != NULL){
	    				fprintf(arquivo2,"======================================\n");
	                	break;
	            	} 
	            	
	        	}
	        	
			}
			
			free(texto);			
		}
	}
	fclose(arquivo);
	fclose(arquivo2);
	
	printf("\nAtividade enviada!\n");
	system("pause");
	
}

atividades(char* usuario,int aluno,int professor){
	FILE* arquivo;
	FILE* arquivo2;
	Fila* filaAtividade = criarfila();
	Fila* filaRespostas = criarfila();
	char linha[150];
	Atividade* texto;
	char opcao[150];
	
	arquivo = fopen("atividades.txt","r");
	
	if(arquivo==NULL){
		printf("Erro ao abrir o arquivo ou arquivo nao criado\n");
		system("pause");
		system("cls");
		return;
	}
	
	while(fgets(linha,sizeof(linha),arquivo)!=NULL){
		if(strstr(linha,"ATIVIDADE: ")!=NULL){
			texto = (Atividade*)malloc(sizeof(Atividade));
			sscanf(linha,"ATIVIDADE: %[^\n] ",texto->atividade);
        	texto->questao[0] = '\0';
        } else if (strstr(linha, "Questao") != NULL && texto != NULL) {
            strncat(texto->questao, linha, sizeof(texto->questao) - strlen(texto->questao) - 1);
        } else if (strstr(linha, "======================================") != NULL && texto != NULL) {
            inserirfila(filaAtividade, texto); 
            texto = NULL;
        }
		
	}
	
	fclose(arquivo);
	
	printf("\n========Atividades========\n");
	if (filaAtividade->inicio==NULL){
		printf("Nenhuma atividade postada\n\n");
	} else {
		Node* atual = filaAtividade->inicio;
		
		while(atual!=NULL){
			Atividade* atv = (Atividade*)atual->dado;
			printf("\n%s\n",atv->atividade);
			atual = atual->prox;
		}
	}
	printf("\n=========================");
	//------------------------------------------------------------//
	
	if(aluno){
		atvalunos(usuario);	
	} else if(professor){
		atvprofessor(usuario);
	}
	
}


contaaluno(char* usuario){
	
	int aluno = 0;
	int escaluno;
	
	do{
		printf("Bem vindo(a) %s!\n\n",usuario);
		
		printf("\n----Aluno-----\n");
		printf("1. Responder atividades\n");
		printf("2. Sair\n");
		
		printf("\nEscolha uma opcao: ");
		scanf("%d",&escaluno);
		
		switch(escaluno){
			case 1:
				aluno=1;
				atividades(usuario,aluno,0);
    			system("cls");
				break;
			case 2:
				break;
			default:
				system("cls");
		}
		
	}while(escaluno!=2);
	
}

void criaratividade(){
	FILE* arquivo;
	Atividade texto;
	int quant;
	int i;
	
	printf("Nome da atividade: ");
	getchar();
	fgets(texto.atividade,MAX,stdin);
	
	printf("Numero de questoes: ");
	scanf("%d",&quant);
	
	fflush(stdin);
	
	arquivo = fopen("atividades.txt","a");
	
	fprintf(arquivo,"ATIVIDADE: ");
	fprintf(arquivo,"%s\n",texto.atividade);
	
	for(i=1;i<=quant;i++){
		printf("\nQuestao %d: ",i);
		fgets(texto.questao,150,stdin);
		
		fprintf(arquivo,"\nQuestao %d: %s",i,texto.questao);
	}
	fprintf(arquivo,"======================================\n");
	
	fclose(arquivo);

	system("cls");
	printf("\nAtividade criada!\n");
}

contaprof(char* usuario){
	
	int escprof=0;
	int professor=0;
	
	do{
		printf("Bem vindo(a) %s!\n\n",usuario);
		
		printf("\n----Professor-----\n");
		printf("1. Listar alunos\n");
		printf("2. Criar atividade\n");
		printf("3. Ver respostas\n");
		printf("4. Voltar\n");
		
		printf("\nEscolha uma opcao: ");
		scanf("%d",&escprof);
		switch(escprof){
			case 1:
				Listar(escprof);
				break;
			case 2:
				criaratividade();
				break;
			case 3:
				professor=1;
				atividades(usuario,0,professor);
				break;
			case 4:
				break;
			default:
				system("cls");
		}
		
	}while(escprof!=4);
	
}

void conta(int logar){
	char usuario [MAX];
	
	int mat;
	int encontrado = 0;
	int tipo;
	char a [MAX];

	Matricula cadastro;
	FILE* arquivo;
	Fila* pesquisa = criarfila();
	char linha [MAX];
	
	arquivo = fopen("matriculas.txt","r");
	
	printf("Digite a matricula: ");
	scanf("%d",&mat);
	
	while(fgets(linha,MAX,arquivo)!=NULL){
		if(logar==2){
			if (strstr(linha, "Professor:") != NULL) {
	        sscanf(linha, " %*[^:]%*c %[^\n]", cadastro.nome);
	        tipo = 1;
	    	} else if(strstr(linha,"Matricula:")!=NULL){
			sscanf(linha,"Matricula: %d",&cadastro.matricula);
			if (tipo==1 && cadastro.matricula == mat) {
				strcpy(usuario,cadastro.nome);
				printf("\nMatricula encontrada!\n");
            	encontrado = 1;
            	system("pause");
            	system("cls");
            	contaprof(usuario);
            	break;
				}
				tipo = 0;
    		}
		} else if(logar==3){
			if (strstr(linha, "Aluno:") != NULL) {
	        sscanf(linha, " %*[^:]%*c %[^\n]", cadastro.nome);
	        tipo = 1;
			} else if(strstr(linha,"Matricula:")!=NULL){
			sscanf(linha,"Matricula: %d",&cadastro.matricula);
			if (tipo==1 && cadastro.matricula == mat) {
				strcpy(usuario,cadastro.nome);
				printf("\nMatricula encontrada!\n");
            	encontrado = 1;
            	system("pause");
            	system("cls");
            	contaaluno(usuario);
            	break;
				}
				tipo = 0;
    		}
		}
	}
	
	if(!encontrado){
		printf("Matricula nao encontrada!\n");
	}
	
	fclose(arquivo);
	
	system("pause");
	system("cls");
}

int main() {

	int logar;

	do{
		printf("     _    __     __     _    \n");
    	printf("    / \\   \\ \\   / /    / \\   \n");
    	printf("   / _ \\   \\ \\ / /    / _ \\  \n");
    	printf("  / ___ \\   \\ V /    / ___ \\ \n");
    	printf(" /_/   \\_\\   \\_/    /_/   \\_\\\n");
    	printf("                              \n");

		printf("-----Logar-----\n");
		printf("1. Admin\n");
		printf("2. Professor\n");
		printf("3. Aluno\n");
		printf("4. Sair\n");
		
		printf("\nEscolha uma opcao: ");
		scanf("%d", &logar);
		
		switch(logar){
			case 1:
				contaadmin();
				break;
			case 2:
				conta(logar);
				break;
			case 3:
				conta(logar);
				break;
			case 4:
				break;
			default:
				system("cls");
		}

	}while(logar!=4);

	return 0;
}
