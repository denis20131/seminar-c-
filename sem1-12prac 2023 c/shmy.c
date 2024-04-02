#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/file.h>
#include <signal.h>
char *input_string(); 
void first_parser(char *s);
void second_parser(char *s);


char *input_file(char *s) {
	//прочитали строку и убрали всё что связано с ней
	int i = 0;
	while (s[i] != '\0' && s[i] != '<')
		i += 1;
	if (s[i] == '\0')
		return NULL;
	s[i] = ' '; // <
	while (s[i] == ' ')
		i += 1; // пропускаем все пробелы, в том числе бывшего <
	int j = i;	// s[j] - первый символ имени файла
	while (s[i] != ' ' && s[i] != '\0' && s[i] != '|')
		i += 1;			// пропускаем имя файла
	// j - первый символ имени файла, i - первый символ после имени файла
	char buf = s[i]; // символ после слова
	s[i] = '\0';
	char *c = strdup(s + j); // указатель на 1й символ имени файла
	s[i] = buf;			 // вернули исходный символ

	while (j < i) { 
		s[j] = ' ';
		j += 1;
	}
	return c;
}

char *output_file(char *s, int *append) {
	int i = 0;
	while (s[i] != '\0' && s[i] != '>')
		i += 1;
	if (s[i] == '\0')
		return NULL;
	s[i] = ' ';
	i += 1;
	if (s[i] == '>') {
		s[i] = ' ';	 // затираем пробелом
		*append = 1; // если двойная > => дозапись файла
	}
	while (s[i] == ' ')
		i += 1;
	int j = i;
	while (s[i] != ' ' && s[i] != '\0' && s[i] != '|')
		i += 1;

	char buf = s[i];
	s[i] = '\0';
	char *c = strdup(s + j);
	s[i] = buf;

	while (j < i) {
		s[j] = ' ';
		j += 1;
	}

	return c;
}

char **make_arg(char *s, int n) { 
	char *c = s; 

	int bracketsCounter = 0;
	for (int i = 0; i < n;) {
		if (*c == '|')
			i += 1; 
		c += 1;
	}
	if (*c == '|') c += 1;

	char *d = c; 
	int argc = 0;
	while (*c == ' ')
		c += 1; // пробелы
	while (*c != '|' && *c != '\0') { // все слова в одной команде
		while (*c != '|' && *c != '\0' && *c != ' ') { // одно слово в выбранной команде
			c += 1; // все буквы в команде
		}
		while (*c == ' ')
			c += 1; // пробелы
		argc += 1;	// число слов
	}

	char **argv = (char**)malloc(sizeof(char *) * (argc + 1));
	argv[argc] = NULL;

	c = d; 
	for (int i = 0; i < argc; i += 1) 
	{
		while (*c == ' ')
			c += 1;
		d = c;
		while (*c != '|' && *c != '\0' && *c != ' ')
		 {
			c += 1;
		}
		*c = '\0';
		argv[i] = strdup(d); 
		c += 1;
	}

	return argv; // указатель на вектор аргументов
}

int conv(char *s) {
	// n - число | + 1
	char *fInput = input_file(s);
	int append = 0;	// если 1 - то файл будет дописываться
	char *fOutput = output_file(s, &append); // передаем по ссылке, чтобы он изменился
	//printf("%s\n",s);
	int n = 1;
	char *c = s;
	
	int *sons = (int *)malloc(sizeof(int) * n); // PIDs of son processes 

	int fd[2], prevpipe;

	signal(SIGINT,SIG_IGN);
	if ((sons[0] = fork()) == 0) 
			{
				if (fInput != NULL) 
					{
						int j = open(fInput, O_RDONLY);
						if (j == -1) { // нет такого файла
							j = open("/dev/null", O_RDONLY); // то вообще ничего не подаём на вход
						}
						dup2(j, 0); // стандартный ввод из файла fInput
					}

				if (fOutput != NULL) 
					{
						int j;
						if (append == 0) // перезаписываем файл
								j = open(fOutput, O_WRONLY | O_CREAT | O_TRUNC, 0777); // 0777 права доступа на чтения запись и exe
						else // дозаписываем в файл
								j = open(fOutput, O_WRONLY | O_CREAT | O_APPEND, 0777);
						dup2(j, 1); // стандартный вывод из файла fOutput
					}
			//printf("%s\n",s);
			char **argv = make_arg(s, 0);
			execvp(argv[0], argv); // -1 не нашел такой команды
			printf("Такой команды не существует: %s\n", argv[0]); // только при -1
			exit(1);
			}
	int k;
	waitpid(sons[0], &k, 0);
	free(sons);
	free(fInput);
	free(fOutput);
	return k;
}

void first_parser(char *s) {
	char *c = s + 1; // s - начало каждой str, c - указатель на текущей символ,
	char buf;
	while (*c == ' ')// пропускаем пробелы
		c += 1;
	int brackets = 0;
	/* считает сбалансированность скобок */
	if ( *s == '(' )
		brackets += 1;

	while (*c != '\0') {
		while (*c != '\0') { 
			if (*c == '&' && *(c + 1) != '&' && *(c - 1) != '&' && brackets == 0)
				break; 
			c += 1;
		}
		buf = *c;
		*c = '\0';
		//printf("%s\n",s);
		if (!(buf == '&'))
			conv(s);
		else { //buf=='&';запускаем фоновый процесс
			// если сын - фоновый процесс, то после выполнения он станет зомби тк предок метрв
			// а если отец ждет - то это не фоновый процесс
			int k = fork(); // создается сын
			if (k == 0) {
				if (fork() == 0) 
				{ // создается внук
					signal(SIGINT, SIG_IGN); 
					// фоновый процесс не должен читать с STDIN
					int fd = open("/dev/null", O_RDONLY);
					dup2(fd, 0); // дескриптор номер 0 (сейчас STDIN) заменить на fd
					// внук считает своим стандартном вводом dev/null
					close(fd);
					second_parser(s);
					exit(0);
				}
				exit(0); // убиваем сына
			}
			waitpid(k, NULL, 0); // ловим сына, чтобы не стал зомби
		}
		*c = buf; 
		if (*c == '\0')
			break;
		c += 1;
		while (*c == ' ')
			c += 1;
		s = c;// с новым началом
	}
	return;
}

int main(int argc, char **argv)
 {
	while (1) {
		char *s = input_string(); //считал всю строку
		if ( strcmp(s,"exit") == 0 ) 
		{ //написаное exit == завершение shell
			free(s);
			return 0;
		}
		first_parser(s); //запускаем первый парсер
		free(s);
	}
}
