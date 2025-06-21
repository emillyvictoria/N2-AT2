# Jogo de Perguntas de Algoritmos em C

## 📘 Descrição do Projeto

Este projeto consiste em um jogo de perguntas e respostas sobre programação em linguagem C, voltado para fins educacionais. O objetivo é testar o conhecimento do jogador por meio de perguntas de múltipla escolha, com dificuldade progressiva por nível.
﻿
# Jogo de Perguntas de Algoritmos em C

## 📘 Descrição do Projeto

Este projeto consiste em um jogo de perguntas e respostas sobre programação em linguagem C, voltado para fins educacionais. O objetivo é testar o conhecimento do jogador por meio de perguntas de múltipla escolha, com dificuldade progressiva por nível.

As perguntas são carregadas dinamicamente a partir de arquivos de texto, e o programa foi desenvolvido utilizando conceitos fundamentais como alocação dinâmica de memória, structs, enumerações e manipulação de arquivos.

---

## 🎯 Objetivos Técnicos

- Praticar alocação dinâmica de memória
- Utilizar `struct`, `enum` e `union` (conceito aplicado com struct e enum)
- Carregar dados externos via arquivos `.txt`
- Criar um menu interativo em terminal
- Implementar controle de fluxo com validação de entradas

---

## 📂 Estrutura dos Arquivos

O programa espera encontrar os seguintes arquivos no mesmo diretório do executável:

- `nivel1.txt`
- `nivel2.txt`
- `nivel3.txt`
- `nivel4.txt`
- `nivel5.txt`

Cada arquivo contém perguntas no seguinte formato:

```
[Enunciado da pergunta]
A) Alternativa A
B) Alternativa B
...
RESPOSTA:C
```
---
## 📦 Estruturas de Dados Utilizadas

### `struct Pergunta`
```c
typedef struct {
    char* texto;
    char** alternativas;
    char resposta_correta;
    int num_alternativas;
} Pergunta;
```

### `struct Nivel`
```c
typedef struct {
    Pergunta* perguntas;
    int num_perguntas;
} Nivel;
```

### `enum OpcaoMenu`
```c
typedef enum {
    JOGAR = 1,
    SAIR
} OpcaoMenu;
```

---

## 🚀 Funcionalidades

- Menu inicial com opções de jogar ou sair
- Leitura automática de arquivos de perguntas
- Verificação de resposta com tolerância a letras minúsculas/maiúsculas
- Contador de erros (máximo de 3)
- Avanço automático por nível em caso de acertos
- Liberação de memória no final da execução

---

## 📄 Licença

Projeto acadêmico desenvolvido para fins de aprendizado e avaliação na disciplina de Algoritmos e Programação Estruturada.

---
