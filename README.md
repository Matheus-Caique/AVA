#  Sistema Educacional em C

Este projeto é um sistema educacional simples, desenvolvido em linguagem C, com funcionalidades para cadastro e gerenciamento de **alunos**, **professores**, **atividades** e **respostas**. Ele utiliza **arquivos de texto** para persistência de dados e **filas dinâmicas** para organização temporária dos dados em memória.

##  Funcionalidades

###  Admin
- Cadastrar professores
- Cadastrar alunos
- Listar todos os cadastros
- Deletar Cadastros

## Estrutura Matricula
![estrutura_matricula](https://github.com/user-attachments/assets/b95b79d7-2b58-4695-b279-db56ddd66134)



###  Professor
- Visualizar lista de alunos
- Criar atividades com questões
- Ver respostas enviadas pelos alunos para uma atividade específica

## Estrutura Atividade
![estrutura_atividade](https://github.com/user-attachments/assets/ab448200-dd1a-4f62-9392-c39e8257d7df)



###  Aluno
- Listar atividades disponíveis
- Responder questões das atividades

## Arquivos Utilizados

- matriculas.txt: Guarda informações de alunos e professores.
- atividades.txt: Contém as atividades e suas questões.
- respostas.txt: Armazena as respostas dos alunos.

##  Estrutura de Dados

O sistema utiliza **filas genéricas com ponteiros void** para armazenar dinamicamente dados de alunos, professores, atividades e respostas durante a execução.

### Estrutura da Fila:
![fila_dinamica](https://github.com/user-attachments/assets/8ec8e828-430e-4da2-b6e0-74e61dc60981)

