#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/file.h>
#include <signal.h>

char *input_file(char *str) 
{
	int i = 0;
	while (str[i] != '\n' && str[i] != '<')
		i += 1;
	if (str[i] == '\n')
		return NULL;
	str[i] = ' '; 
	while (str[i] == ' ')
		i += 1; 
	int j = i;	
	while (str[i] != ' ' && str[i] != '\n' && str[i] != '|')
		i += 1;			
	char buf = str[i];
	str[i] = '\0';
	char *c = strdup(str + j); 
	str[i] = buf;			

	while (j < i) { 
		str[j] = ' ';
		j += 1;
	}
	return c;
}

char *output_file(char *str, int *append) {
	int i = 0;
	while (str[i] != '\n' && str[i] != '>')
		i += 1;
	if (str[i] == '\n')
		return NULL;
	str[i] = ' ';
	i += 1;
	if (str[i] == '>') {
		str[i] = ' ';	 
		*append = 1;
	}
	while (str[i] == ' ')
		i += 1;
	int j = i;
	while (str[i] != ' ' && str[i] != '\n' && str[i] != '|')
		i += 1;

	char buf = str[i];
	str[i] = '\0';
	char *c = strdup(str + j);
	str[i] = buf;

	while (j < i) {
		str[j] = ' ';
		j += 1;
	}

	return c;
}

char **make_arg(char *str, int n) 
{ 
	char *c = str; 

	for (int i = 0; i < n;) 
	{
		if (*c == '|')
			i += 1; 
		c += 1;
	}
	if (*c == '|') c += 1;

	char *d = c; 
	int argc = 0;
	while (*c == ' ')
		c += 1; 
	while (*c != '|' && *c != '\n') 
	{ 
		while (*c != '|' && *c != '\n' && *c != ' ') 
			c += 1;
		while (*c == ' ')
			c += 1;
		argc += 1;	
	}

	char **argv = (char**)malloc(sizeof(char *) * (argc + 1));
	argv[argc] = NULL;

	c = d; 
	for (int i = 0; i < argc; i += 1) 
	{
		
		while (*c == ' ')
			c += 1;
		d = c;
		while (*c != '|' && *c != '\n' && *c != ' ')
		 {
			c += 1;
		}
		*c = '\0';
		argv[i] = strdup(d); 
		c += 1;
	}

	return argv;
}

int conv(char *str) 
{
	int n = 1;
	char *c = str;
	char *fInput = input_file(str);
	int append = 0;
	char *fOutput = output_file(str, &append); 
	while (*c != '\n') 
	{
		if (*c == '|')
			n += 1;
		c += 1;
	}
	int *sons = (int *)malloc(sizeof(int) * n); 

	int fd[2], buf_pipe;


	for (int i = 0; i < n; i += 1) 
	{
		if (i != n - 1) 
			pipe(fd);
		if ((sons[i] = fork()) == 0) 
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
			char **argv = make_arg(str, i); 
			printf("%s\n",argv[0]);
			execvp(argv[0], argv); 
			printf("Команда не определена: %s\n", argv[0]); 
			exit(1);
		}
		if (n != 1) { 
			if (i == 0) { 
				buf_pipe = fd[0];
				close(fd[1]); 
			}
			else if (i == n - 1) { 
				close(buf_pipe); 
			}
			else {
				close(buf_pipe);
				buf_pipe = fd[0];
				close(fd[1]); 
			}
		}
	}

	int k;
	for (int i = 0; i < n; i += 1)
		waitpid(sons[i], &k, 0); 
	free(sons);
	return k;
}






int main(int argc, char **argv)
 {
	while (1) 
	{
		char str[1000];
		fgets(str,1000,stdin);
		int s=conv(str); 
		printf("Conv end with code exit %d\n",s);
	}
}
