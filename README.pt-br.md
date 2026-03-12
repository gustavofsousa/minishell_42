<h1 align="center">minishell</h1>

<p align="center">
  <img src="https://img.shields.io/badge/linguagem-C-blue.svg" alt="Linguagem">
  <img src="https://img.shields.io/badge/42-School-black.svg" alt="42 School">
  <img src="https://img.shields.io/badge/status-completo-brightgreen.svg" alt="Status">
</p>

<p align="center">
  Uma implementação de shell completamente funcional em C — com lexer, parser, built-ins, pipes, redirecionamentos e tratamento de sinais.
</p>

<p align="center">
  <a href="README.md">🇺🇸 Read in English</a>
</p>

---

## Por que este projeto importa

> "Este projeto me ensinou como todo terminal que você já usou funciona de verdade — como um shell tokeniza o input, constrói uma árvore de comandos, cria processos com fork e conecta pipes e redirecionamentos. Agora entendo o que acontece por baixo dos panos toda vez que você executa um comando, o que torna debug, scripting e design de sistemas muito mais intuitivos."

Entender shells profundamente separa os desenvolvedores que adivinham o comportamento do terminal daqueles que o compreendem. Esse conhecimento se aplica diretamente a DevOps, pipelines de CI/CD, internos de containers e qualquer backend que envolva gerenciamento de processos.

---

## O que foi construído

Um shell similar ao POSIX com:

### Comandos built-in
| Comando | Descrição |
|---|---|
| `echo` | Imprime argumentos (com suporte a `-n`) |
| `cd` | Muda diretório |
| `pwd` | Imprime diretório atual |
| `export` | Define variáveis de ambiente |
| `unset` | Remove variáveis de ambiente |
| `env` | Imprime o ambiente |
| `exit` | Sai do shell |

### Funcionalidades principais
- **Lexer + Tokenizador** — classifica o input em tokens `word`, `redirect` e `pipe`
- **Tratamento de aspas** — processa corretamente aspas simples `'` e duplas `"`
- **Expansão de variáveis** — expande `$VAR` e `$?` (último status de saída)
- **Pipes** — encadeia comandos com `|`
- **Redirecionamentos** — `>`, `>>`, `<`, `<<` (heredoc)
- **Tratamento de sinais** — `Ctrl+C`, `Ctrl+D`, `Ctrl+\` se comportam como no bash
- **Histórico de comandos** — via biblioteca readline

---

## Um detalhe técnico que se destaca

O parser usa um design em duas camadas: um lexer que produz uma lista ligada de tokens `t_cell` (cada um com um enum de tipo e flag de espaço), seguido por um montador de sentenças que agrupa tokens em structs `t_sentence` com file descriptors de entrada/saída resolvidos. Essa separação limpa entre lexing e parsing espelha como compiladores e interpretadores em produção são construídos — um padrão de design diretamente aplicável ao desenvolvimento de DSLs, parsers de config ou qualquer ferramenta de linguagem.

---

## Como usar

### Pré-requisitos

```bash
sudo apt-get install libreadline8 libreadline-dev
```

```bash
git clone https://github.com/gustavofsousa/minishell_42.git
cd minishell_42
make
./minishell
```

### Exemplos

```bash
minishell$ echo "Olá, Mundo!"
Olá, Mundo!

minishell$ export MINHA_VAR=42
minishell$ echo $MINHA_VAR
42

minishell$ ls | grep .c | wc -l

minishell$ cat << EOF
> conteúdo do heredoc
> EOF

minishell$ echo $?
0
```

---

## Estrutura do projeto

```
minishell_42/
├── source/
│   ├── main.c              # Loop REPL + readline
│   ├── parser/
│   │   ├── parser.c        # Lógica principal de parsing
│   │   ├── token.c         # Tokenizador
│   │   ├── handle_quotes.c # Processamento de aspas
│   │   ├── expand_variables.c  # Expansão de $VAR
│   │   └── list_cells.c    # Gerenciamento da lista de tokens
│   ├── builtin/            # cd, echo, env, export, unset, exit, pwd
│   ├── external/           # Resolução de caminho para execve
│   ├── pipes.c             # Encadeamento de pipes
│   ├── signal.c            # Ctrl+C / Ctrl+D / Ctrl+\
│   └── finish.c            # Limpeza
├── include/
│   └── minishell.h         # Todos os tipos e protótipos
└── libft/
```

---

## Habilidades demonstradas

- Design de lexer e parser (tokenização, estrutura de comandos similar a AST)
- Gerenciamento de processos (`fork`, `execve`, `waitpid`)
- Encadeamento de pipes e gerenciamento de file descriptors
- Manipulação de variáveis de ambiente
- Tratamento de sinais em programa interativo
- Integração com readline para histórico e edição de comandos

---

## Licença

Este projeto foi desenvolvido como parte do currículo da [42 School](https://42.fr).

---

<p align="center">Feito com ☕ na 42 Rio de Janeiro</p>
