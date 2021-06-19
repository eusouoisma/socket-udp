// Client side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080
#define MAXLINE 1024

/* Função que requisita as informações para o cadastro de um usuário.
   Parâmetro: ponteiro para string que guardará um json com as informações a serem enviadas para o servidor.
*/
void newUser(char *json)
{
	/* Strings que guardarão os dados do usuário */
	char email[100];
	char name[100];
	char lastName[100];
	char city[100];
	char graduation[100];
	char graduationYear[100];
	char habilities[1000];
	char experiences[1000];
	char aux[1000];

	/* Solicita os dados do usuário */
	printf("Digite o email: ");
	fgets(email, 200, stdin);
	email[strcspn(email, "\n")] = 0;

	printf("Nome: ");
	fgets(name, 200, stdin);
	name[strcspn(name, "\n")] = 0;

	printf("Sobrenome: ");
	fgets(lastName, 200, stdin);
	lastName[strcspn(lastName, "\n")] = 0;

	printf("Cidade de residência: ");
	fgets(city, 200, stdin);
	city[strcspn(city, "\n")] = 0;

	printf("Formação acadêmica: ");
	fgets(graduation, 200, stdin);
	graduation[strcspn(graduation, "\n")] = 0;

	printf("Ano de formatura: ");
	fgets(graduationYear, 200, stdin);
	graduationYear[strcspn(graduationYear, "\n")] = 0;

	printf("Habilidades (separadas por ,): ");
	fgets(habilities, 200, stdin);
	habilities[strcspn(habilities, "\n")] = 0;

	printf("Experiências (separadas por ,): ");
	fgets(experiences, 200, stdin);
	experiences[strcspn(experiences, "\n")] = 0;

	/* Forma um json, como string, contendo todos os dados do usuário a ser inserido, e a opção referente à função de inserção. */
	strcat(json, "{'option': '1',");
	strcat(json, "'email': '");
	strcat(json, email);
	strcat(json, "', 'name': '");
	strcat(json, name);
	strcat(json, "', 'lastName': '");
	strcat(json, lastName);
	strcat(json, "', 'city': '");
	strcat(json, city);
	strcat(json, "', 'graduation': '");
	strcat(json, graduation);
	strcat(json, "', 'graduationYear': '");
	strcat(json, graduationYear);
	strcat(json, "', 'habilities': '");
	strcat(json, habilities);
	strcat(json, "', 'experiences': '");
	strcat(json, experiences);
	strcat(json, "'}");
}

/* Função que requisita as informações para inserir uma nova experiência a um usuário.
   Parâmetro: ponteiro para string que guardará um json com as informações a serem enviadas para o servidor.
*/
void insertExperiences(char *json)
{
	/* Strings que guardarão os dados do usuário */
	char email[100];
	char experiences[1000];

	/* Solicita os dados do usuário */
	printf("Digite o email: ");
	fgets(email, 200, stdin);
	email[strcspn(email, "\n")] = 0;

	printf("Experiências (separadas por ,): ");
	fgets(experiences, 200, stdin);
	experiences[strcspn(experiences, "\n")] = 0;

	/* Forma um json, como string, contendo o email do usuário e a lista de experiências, e a opção referente à função de adicionar experiência. */
	strcat(json, "{'option': '2',");
	strcat(json, "'email': '");
	strcat(json, email);
	strcat(json, "', 'experiences': '");
	strcat(json, experiences);
	strcat(json, "'}");
}

/* Função que requisita as informações para buscar os usuários a partir de um curso.
   Parâmetro: ponteiro para string que guardará um json com as informações a serem enviadas para o servidor.
*/
void findByCourse(char *json)
{
	/* String que guardará o curso a ser buscado */
	char course[1000];

	/* Solicita o curso a ser buscado */
	printf("Digite o curso: ");
	fgets(course, 200, stdin);
	course[strcspn(course, "\n")] = 0;

	/* Forma um json, como string, contendo o curso a ser buscado, e a opção referente à busca por curso. */
	strcat(json, "{'option': '3',");
	strcat(json, "'course': '");
	strcat(json, course);
	strcat(json, "'}");
}

/* Função que requisita as informações para buscar os usuários a partir de uma habilidade.
   Parâmetro: ponteiro para string que guardará um json com as informações a serem enviadas para o servidor.
*/
void findByHability(char *json)
{	
	/* String que guardará a habilidade a ser buscada */
	char hability[1000];

	/* Solicita a habilidade a ser buscada */
	printf("Digite a habilidade: ");
	fgets(hability, 200, stdin);
	hability[strcspn(hability, "\n")] = 0;

	/* Forma um json, como string, contendo o a habilidade a ser buscada, e a opção referente à busca por habilidade. */
	strcat(json, "{'option': '4',");
	strcat(json, "'hability': '");
	strcat(json, hability);
	strcat(json, "'}");
}

/* Função que requisita as informações para buscar os usuários a partir de um ano de formatura.
   Parâmetro: ponteiro para string que guardará um json com as informações a serem enviadas para o servidor.
*/
void findByYear(char *json)
{
	/* String que guardará o ano de formatura a ser buscado */
	char year[1000];

	/* Solicita o ano de formatura a ser buscado */
	printf("Digite o ano de Formação: ");
	fgets(year, 200, stdin);
	year[strcspn(year, "\n")] = 0;

	/* Forma um json, como string, contendo o ano de formatura a ser buscado, e a opção referente à busca por ano de formatura. */
	strcat(json, "{'option': '5',");
	strcat(json, "'graduationYear': '");
	strcat(json, year);
	strcat(json, "'}");
}

/* Função que requisita as informações para buscar os usuários a partir de um email.
   Parâmetro: ponteiro para string que guardará um json com as informações a serem enviadas para o servidor.
*/
void findByEmail(char *json)
{
	/* String que guardará o email a ser buscado*/
	char email[1000];

	/* Solicita o email a ser buscado */
	printf("Digite o email: ");
	fgets(email, 200, stdin);
	email[strcspn(email, "\n")] = 0;

	/* Forma um json, como string, contedo o email a ser buscado, e a opção referente à busca por email. */
	strcat(json, "{'option': '6',");
	strcat(json, "'email': '");
	strcat(json, email);
	strcat(json, "'}");
}

/* Função que requisita as informações para buscar os usuários a partir de um email.
   Parâmetro: ponteiro para string que guardará um json com as informações a serem enviadas para o servidor.
*/
void findAll(char *json)
{
	/* Forma um json, como string, contedo a opção referente à busca por todos os usuários. */
	strcat(json, "{'option': '7'}");
}

/* Função que requisita as informações para buscar os usuários a partir de um email.
   Parâmetro: ponteiro para string que guardará um json com as informações a serem enviadas para o servidor.
*/
void delete (char *json)
{
	/* String que guardará o email a ser deletado*/
	char email[1000];

	/* Solicita o email a ser deletado */
	printf("Digite o email: ");
	fgets(email, 200, stdin);
	email[strcspn(email, "\n")] = 0;
	
	/* Forma um json, como string, contedo o email a ser deletado, e a opção referente à deleção. */
	strcat(json, "{'option': '8',");
	strcat(json, "'email': '");
	strcat(json, email);
	strcat(json, "'}");
}

int main()
{
	int sockfd;
	char buffer[MAXLINE];
	struct sockaddr_in servaddr;

	/* Cria um socket */
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("Erro na criação do socket");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr));

	// Guarda as informações do servidor
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;

	int n, len;

	int action = -1;
	
	/* Mantém a execução ativa até que o usuário decida sair */
	while (action != 0)
	{

		/* Exibe as opções ao usuário */
		char menu[] = "\nOlá! Escolha uma opção abaixo: \n\n1-Cadastrar novo perfil\n2-Adicionar experiência profissional\n3-Busca por curso\n4-Busca por habilidade\n5-Busca por ano de formação\n6-Busca por email\n7-Listar todos perfis\n8-Apagar perfil\n0-Sair\nOpção: ";
		printf("%s", menu);
		
		/* Recebe a opção solicitada */
		scanf("%d", &action);
		char c;

		/* Limpa o buffer da entrada */
		while ((c = getchar()) != '\n' && c != EOF){}

		/* String que será usada para guardar um json que será enviado para o servidor */
		char json[10000];

		/* Chama uma determinada função de acordo com a solicitação do usuário */
		switch (action){
		case 1:
			newUser(json);
			break;
		case 2:
			insertExperiences(json);
			break;
		case 3:
			findByCourse(json);
			break;
		case 4:
			findByHability(json);
			break;
		case 5:
			findByYear(json);
			break;
		case 6:
			findByEmail(json);
			break;
		case 7:
			findAll(json);
			break;
		case 8:
			delete (json);
			break;
		case 0:
			break;
		default:
			printf("Opção inválida.\n");
			close(sockfd);
			return 0;
			break;
		}

		/* Envia uma mensagem no socket contendo o json construído */
		sendto(sockfd, (const char *)json, strlen(json),
			   MSG_CONFIRM, (const struct sockaddr *)&servaddr,
			   sizeof(servaddr));

		/* Recebe uma mensagem pelo socket */
		n = recvfrom(sockfd, (char *)buffer, MAXLINE,
					 MSG_WAITALL, (struct sockaddr *)&servaddr,
					 &len);
		buffer[n] = '\0';

		/* Imprime a mensagem recebida pelo socket */
		printf("%s\n", buffer);

		/* Encerra o socket */
		close(sockfd);
	}

	return 0;
}
