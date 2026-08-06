# Programação Estruturada II

Material da disciplina de **Programação Estruturada II**, ministrada para o **2º período do Curso de Bacharelado em Engenharia de Computação**.

## Sobre a disciplina

A disciplina de **Programação Estruturada II** tem como objetivo aprofundar os conhecimentos adquiridos em Programação Estruturada I, consolidando conceitos fundamentais para o desenvolvimento de software utilizando a linguagem **C**.

Ao longo do semestre serão abordados temas essenciais para a formação do engenheiro de computação, incluindo:

* Recursão;
* Ponteiros e manipulação de memória;
* Vetores e matrizes (revisão e aprofundamento);
* Arquivos texto e binários;
* Depuração de programas;
* Documentação e boas práticas de programação;
* Desenvolvimento de programas de maior complexidade.

A disciplina enfatiza a resolução de problemas, o desenvolvimento do raciocínio lógico e a implementação de soluções eficientes, preparando os estudantes para disciplinas mais avançadas da área de computação.

---

# Objetivo deste repositório

Este repositório será utilizado para armazenar o material produzido ao longo da disciplina, incluindo:

* códigos desenvolvidos durante as aulas;
* exemplos apresentados em sala;
* exercícios de implementação;
* projetos e atividades práticas;
* materiais de apoio.

Recomenda-se que cada estudante faça um **clone** deste repositório para acompanhar as aulas, executar os exemplos e desenvolver os exercícios propostos.

---

# Estrutura do repositório

```text
Programacao-Estruturada-II/
│
├── aulas/
├── exemplos/
├── exercicios/
├── projetos/
├── slides/
├── .vscode/
└── README.md
```

---

# Ambiente de desenvolvimento

Durante toda a disciplina serão utilizadas as seguintes ferramentas:

* Linguagem **C**
* Compilador **GCC**
* **Visual Studio Code**
* **GDB** (depuração)

---

# Configuração no Windows

## 1. Instalar o Visual Studio Code

Faça o download em:

https://code.visualstudio.com/

Durante a instalação, recomenda-se habilitar a opção para adicionar o VS Code ao menu de contexto do Windows.

---

## 2. Instalar o GCC

A forma recomendada é utilizar o **MSYS2**.

Download:

https://www.msys2.org/

Após instalar, abra o terminal do MSYS2 e execute:

```bash
pacman -Syu
```

Caso seja solicitado, feche o terminal e abra novamente.

Instale o compilador:

```bash
pacman -S mingw-w64-ucrt-x86_64-gcc
```

Instale também o depurador:

```bash
pacman -S mingw-w64-ucrt-x86_64-gdb
```

Adicione o seguinte diretório ao **PATH** do Windows:

```text
C:\msys64\ucrt64\bin
```

Verifique a instalação:

```bash
gcc --version
gdb --version
```

---

## 3. Instalar as extensões do Visual Studio Code

Instale as seguintes extensões:

* C/C++ (Microsoft)
* C/C++ Extension Pack (Microsoft)

---

# Configuração no Linux (Ubuntu e derivados)

Atualize os repositórios:

```bash
sudo apt update
```

Instale o GCC e o GDB:

```bash
sudo apt install build-essential gdb
```

Verifique a instalação:

```bash
gcc --version
gdb --version
```

Caso ainda não possua o Visual Studio Code instalado:

```bash
sudo snap install code --classic
```

ou faça o download em:

https://code.visualstudio.com/

---

# Primeiro programa

Crie um arquivo chamado:

```text
hello.c
```

Conteúdo:

```c
#include <stdio.h>

int main(void)
{
    printf("Olá, Engenharia de Computação!\n");
    return 0;
}
```

---

# Compilando programas

## Linux

Compilação:

```bash
gcc hello.c -o hello
```

Execução:

```bash
./hello
```

---

## Windows

Compilação:

```bash
gcc hello.c -o hello.exe
```

Execução:

```bash
hello.exe
```

ou

```bash
.\hello.exe
```

---

# Depuração

Durante a disciplina será utilizada a depuração de programas para análise da execução do código, identificação de erros e acompanhamento do comportamento das variáveis.

Os exemplos poderão ser depurados diretamente no Visual Studio Code utilizando o **GDB** e os arquivos de configuração presentes na pasta **.vscode** deste repositório.

---

## Clonando o Repositório

Antes de iniciar as atividades, faça uma cópia (clone) deste repositório para a sua máquina.

### Opção 1 – HTTPS (mais simples)

Copie a URL do repositório no GitHub e execute:

```bash
git clone https://github.com/LenioJunior/pe2.git
```

### Opção 2 – SSH (recomendado para quem já configurou uma chave SSH)

Caso sua conta do GitHub esteja configurada com uma chave SSH:

```bash
git clone git@github.com:LenioJunior/pe2.git
```

### Acessando o projeto

Após o clone, entre na pasta do projeto:

```bash
cd programacao_estruturada
```

Sempre que houver novos arquivos disponibilizados durante a disciplina, atualize sua cópia local executando:

```bash
git pull
```

> **Dica:** Caso ainda não tenha configurado o Git ou uma chave SSH, utilize o método **HTTPS**, que é o mais simples para começar. Se desejar, posteriormente você poderá configurar o acesso via SSH.

# Organização recomendada

Mantenha os códigos organizados por aula ou atividade.

Exemplo:

```text
Aula01/
    exemplo01.c
    exemplo02.c

Aula02/
    exercicio01.c
    exercicio02.c

Projeto01/
    main.c
    aluno.c
    aluno.h
```

Essa organização facilita a localização dos exemplos e a evolução dos exercícios ao longo do semestre.

---

# Boas práticas

Durante a disciplina serão incentivadas boas práticas de desenvolvimento, tais como:

* código bem indentado;
* nomes de variáveis significativos;
* modularização do código;
* utilização de funções;
* documentação adequada;
* organização dos arquivos do projeto;
* utilização de ferramentas de depuração.

---

# Como aproveitar melhor a disciplina

Para obter um bom desempenho, recomenda-se:

1. Participar ativamente das aulas.
2. Implementar todos os exemplos apresentados.
3. Resolver os exercícios antes de consultar soluções.
4. Testar diferentes abordagens para o mesmo problema.
5. Utilizar o depurador para compreender o funcionamento dos programas.
6. Praticar regularmente, pois a programação é uma habilidade desenvolvida por meio da implementação e da experimentação.

---

# Licença

Este repositório destina-se ao apoio das atividades da disciplina **Programação Estruturada II** do Curso de Bacharelado em Engenharia de Computação. O material pode ser utilizado para fins educacionais, desde que sua autoria e origem sejam preservadas.
