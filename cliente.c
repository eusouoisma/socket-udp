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

void newUser(char * json){
	char email[100];
	char name[100];
	char lastName[100];
	char city[100];
	char graduation[100];
	char graduationYear[100];
	char habilities[1000];
	char experiences[1000];
	char aux[1000];

	printf("Digite o email: ");
	fgets (email, 200, stdin); 
	email[strcspn(email, "\n")] = 0;

	printf("Nome: ");
	fgets (name, 200, stdin); 
	name[strcspn(name, "\n")] = 0;

	printf("Sobrenome: ");
	fgets (lastName, 200, stdin); 
	lastName[strcspn(lastName, "\n")] = 0;
	
	printf("Cidade de residência: ");
	fgets (city, 200, stdin); 
	city[strcspn(city, "\n")] = 0;	
	
	printf("Formação acadêmica: ");
	fgets (graduation, 200, stdin); 
	graduation[strcspn(graduation, "\n")] = 0;
	
	printf("Ano de formatura: ");
	fgets (graduationYear, 200, stdin); 
	graduationYear[strcspn(graduationYear, "\n")] = 0;	
	
	printf("Habilidades (separadas por ,): ");
	fgets (habilities, 200, stdin); 
	habilities[strcspn(habilities, "\n")] = 0;
	
	printf("Experiências (separadas por ,): ");
	fgets (experiences, 200, stdin); 
	experiences[strcspn(experiences, "\n")] = 0;

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
	strcat(json,"'}");
}

void insertExperiences(char * json) {
	char email[100];
	char experiences[1000];

	printf("Digite o email: ");
	fgets (email, 200, stdin); 
	email[strcspn(email, "\n")] = 0;
	
	printf("Experiências (separadas por ,): ");
	fgets (experiences, 200, stdin); 
	experiences[strcspn(experiences, "\n")] = 0;

	strcat(json, "{'option': '2',");
	strcat(json, "'email': '");
	strcat(json, email);

	strcat(json, "', 'experiences': '");
	strcat(json, experiences);
	strcat(json,"'}");
}

void findByCourse(char * json) {
	char course[1000];

	printf("Digite o curso: ");
	fgets (course, 200, stdin); 
	course[strcspn(course, "\n")] = 0;

	strcat(json, "{'option': '3',");
	strcat(json, "'course': '");
	strcat(json, course);
	strcat(json,"'}");
}

void findByHability(char * json) {
	char hability[1000];

	printf("Digite a habilidade: ");
	fgets (hability, 200, stdin); 
	hability[strcspn(hability, "\n")] = 0;

	strcat(json, "{'option': '4',");
	strcat(json, "'hability': '");
	strcat(json, hability);
	strcat(json,"'}");
}

void findByYear(char * json) {
	char year[1000];

	printf("Digite o ano de Formação: ");
	fgets (year, 200, stdin); 
	year[strcspn(year, "\n")] = 0;

	strcat(json, "{'option': '5',");
	strcat(json, "'graduationYear': '");
	strcat(json, year);
	strcat(json,"'}");
}

void findByEmail(char * json) {
	char email[1000];

	printf("Digite o email: ");
	fgets (email, 200, stdin); 
	email[strcspn(email, "\n")] = 0;

	strcat(json, "{'option': '6',");
	strcat(json, "'email': '");
	strcat(json, email);
	strcat(json,"'}");
}

void findAll(char * json) {
	strcat(json, "{'option': '7'}");
}

void delete(char * json) {
	char email[1000];

	printf("Digite o email: ");
	fgets (email, 200, stdin); 
	email[strcspn(email, "\n")] = 0;

	strcat(json, "{'option': '8',");
	strcat(json, "'email': '");
	strcat(json, email);
	strcat(json,"'}");
}

// Driver code
int main()
{
	int sockfd;
	char buffer[MAXLINE];
	char *hello = "Hello from client";
	struct sockaddr_in servaddr;

	// Creating socket file descriptor
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr));

	// Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;

	int n, len;

	int action;

	char menu[] = "\nOlá! Escolha uma opção abaixo: \n\n1-Cadastrar novo perfil\n2-Adicionar experiência profissional\n3-Busca por curso\n4-Busca por habilidade\n5-Busca por ano de formação\n6-Busca por email\n7-Listar todos perfis\n8-Apagar perfil\nOpção: ";

	printf("%s", menu);
	scanf("%d", &action);
	char c;
	while ((c = getchar()) != '\n' && c != EOF) {}

	char json[10000];

	switch (action)
	{
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
		delete(json);
		break;
	default:
		break;
	}

	sendto(sockfd, (const char *)json, strlen(json),
		   MSG_CONFIRM, (const struct sockaddr *)&servaddr,
		   sizeof(servaddr));

	n = recvfrom(sockfd, (char *)buffer, MAXLINE,
				 MSG_WAITALL, (struct sockaddr *)&servaddr,
				 &len);
	buffer[n] = '\0';
	printf("%s\n", buffer);

	close(sockfd);
	return 0;
}
