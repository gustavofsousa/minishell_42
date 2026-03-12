<h1 align="center">minishell</h1>

<p align="center">
  <img src="https://img.shields.io/badge/language-C-blue.svg" alt="Language">
  <img src="https://img.shields.io/badge/42-School-black.svg" alt="42 School">
  <img src="https://img.shields.io/badge/status-complete-brightgreen.svg" alt="Status">
</p>

<p align="center">
  A fully functional shell implementation in C — with a lexer, parser, built-ins, pipes, redirections, and signal handling.
</p>

<p align="center">
  <a href="README.pt-br.md">🇧🇷 Leia em Português</a>
</p>

---

## Why this project matters

> "This project taught me how every terminal you've ever used actually works — how a shell tokenizes input, builds an abstract command tree, forks processes, and wires up pipes and redirections. I now understand what happens under the hood every time you run a command, which makes debugging, scripting, and systems design significantly more intuitive."

Understanding shells deeply is what separates developers who guess at terminal behavior from those who understand it. This knowledge directly applies to DevOps, CI/CD pipelines, container internals, and any backend involving process management.

---

## What was built

A POSIX-like shell with:

### Built-in commands
| Command | Description |
|---|---|
| `echo` | Print arguments (with `-n` support) |
| `cd` | Change directory |
| `pwd` | Print working directory |
| `export` | Set environment variables |
| `unset` | Remove environment variables |
| `env` | Print environment |
| `exit` | Exit the shell |

### Core features
- **Lexer + Tokenizer** — classifies input into `word`, `redirect`, and `pipe` tokens
- **Quote handling** — correctly processes single `'` and double `"` quotes
- **Variable expansion** — expands `$VAR` and `$?` (last exit status)
- **Pipes** — chains commands with `|`
- **Redirections** — `>`, `>>`, `<`, `<<` (heredoc)
- **Signal handling** — `Ctrl+C`, `Ctrl+D`, `Ctrl+\` behave as in bash
- **Command history** — via readline library

---

## A standout technical detail

The parser uses a two-layer design: a lexer that produces a linked list of `t_cell` tokens (each with a type enum and space flag), followed by a sentence builder that groups tokens into `t_sentence` structs with resolved input/output file descriptors. This clean separation between lexing and parsing mirrors how production compilers and interpreters are built — a design pattern directly applicable to building DSLs, config parsers, or any language tooling.

---

## Getting Started

### Prerequisites

```bash
sudo apt-get install libreadline8 libreadline-dev
```

```bash
git clone https://github.com/gustavofsousa/minishell_42.git
cd minishell_42
make
./minishell
```

### Examples

```bash
minishell$ echo "Hello, World!"
Hello, World!

minishell$ export MY_VAR=42
minishell$ echo $MY_VAR
42

minishell$ ls | grep .c | wc -l

minishell$ cat << EOF
> heredoc content
> EOF

minishell$ echo $?
0
```

---

## Project structure

```
minishell_42/
├── source/
│   ├── main.c              # REPL loop + readline
│   ├── parser/
│   │   ├── parser.c        # Main parsing logic
│   │   ├── token.c         # Tokenizer
│   │   ├── handle_quotes.c # Quote processing
│   │   ├── expand_variables.c  # $VAR expansion
│   │   └── list_cells.c    # Token list management
│   ├── builtin/            # cd, echo, env, export, unset, exit, pwd
│   ├── external/           # execve path resolution
│   ├── pipes.c             # Pipe chaining
│   ├── signal.c            # Ctrl+C / Ctrl+D / Ctrl+\
│   └── finish.c            # Cleanup
├── include/
│   └── minishell.h         # All types and prototypes
└── libft/
```

---

## Skills demonstrated

- Lexer and parser design (tokenization, AST-like command structure)
- Process management (`fork`, `execve`, `waitpid`)
- Pipe chaining and file descriptor management
- Environment variable handling
- Signal handling in an interactive program
- Readline integration for command history and editing

---

## License

This project was developed as part of the [42 School](https://42.fr) curriculum.

---

<p align="center">Made with ☕ at 42 Rio de Janeiro</p>
