// Server side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <json-c/json.h>
#include "arquivo.h"

#define PORT     8080
#define MAXLINE 1024
  
// Driver code
int main() {
    int sockfd;
    char buffer[MAXLINE];
    char return_message[10000];
    struct sockaddr_in servaddr, cliaddr;
    char new_profile[10][1000];
    char email[1000];
    char experiences[1000];
    char course[1000];
    char hability[1000];
    char graduationYear[1000];

    struct json_object *parsed_json;
    struct json_object *option;
    struct json_object *json_field;

    // Cria o socket
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
      
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
      
    // Preenche as informaç~eos do servidor
    servaddr.sin_family    = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);
      
    // Vincula o endereço do servidor ao socket
    if ( bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 ){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
      
    int len, n;
  
    len = sizeof(cliaddr);

    // loop para manter o servidor ativo
    while (1){
        // recebe os dados do cliente
        n = recvfrom(sockfd, (char *)buffer, MAXLINE, 
                MSG_WAITALL, ( struct sockaddr *) &cliaddr,
                &len);
        buffer[n] = '\0';

        printf("JSON recebido: %s\n", buffer);

        // converte o que foi recebido para JSON        
        parsed_json = json_tokener_parse(buffer);
        
        // verifica qual opção do menu foi selecionada pelo cliente
        json_object_object_get_ex(parsed_json, "option", &option);
        switch (json_object_get_int(option)){
            case 1:
                // Opção 1 - cadastro de um novo usuário
                // verifica se o email não está cadastrado e cria o novo perfil
                json_object_object_get_ex(parsed_json, "email", &json_field);
                strcpy(email, (char *) json_object_get_string(json_field));

                if (checkEmail(email)>0){
                    strcpy(return_message, "\nErro: Email já cadastrado.");
                }else{
                    strcpy(new_profile[0], email);

                    json_object_object_get_ex(parsed_json, "name", &json_field);
                    strcpy(new_profile[1], (char *) json_object_get_string(json_field));

                    json_object_object_get_ex(parsed_json, "lastName", &json_field);
                    strcpy(new_profile[2], (char *) json_object_get_string(json_field));

                    json_object_object_get_ex(parsed_json, "city", &json_field);
                    strcpy(new_profile[3], (char *) json_object_get_string(json_field));

                    json_object_object_get_ex(parsed_json, "graduation", &json_field);
                    strcpy(new_profile[4], (char *) json_object_get_string(json_field));

                    json_object_object_get_ex(parsed_json, "graduationYear", &json_field);
                    strcpy(new_profile[5], (char *) json_object_get_string(json_field));

                    json_object_object_get_ex(parsed_json, "habilities", &json_field);
                    strcpy(new_profile[6], (char *) json_object_get_string(json_field));

                    json_object_object_get_ex(parsed_json, "experiences", &json_field);
                    strcpy(new_profile[7], (char *) json_object_get_string(json_field));
                    
                    strcpy(return_message, create(new_profile));
                }
                break;
            case 2:
                // Opção 2 - Adiciona experiência a um perfil
                // verifica se o perfil é válido (email cadastrado) e atualiza o cadastro
                json_object_object_get_ex(parsed_json, "email", &json_field);
                strcpy(email, (char *) json_object_get_string(json_field));
                
                if (checkEmail(email)>0){
                    json_object_object_get_ex(parsed_json, "experiences", &json_field);
                    strcpy(experiences, (char *) json_object_get_string(json_field));

                    strcpy(return_message, addExperience(email, experiences));
                }else{
                    strcpy(return_message, "\nErro: Email não encontrado.");
                }
                break;
            case 3:
                // Opção 3 - Busca por curso
                json_object_object_get_ex(parsed_json, "course", &json_field);
                strcpy(course, (char *) json_object_get_string(json_field));

                strcpy(return_message, filterByCourse(course));

                break;
            case 4:
                // Opção 4 - Busca por habilidade
                json_object_object_get_ex(parsed_json, "hability", &json_field);
                strcpy(hability, (char *) json_object_get_string(json_field));

                strcpy(return_message, filterBySkill(hability));

                break;
            case 5:
                // Opção 5 - Busca por ano de graduação
                json_object_object_get_ex(parsed_json, "graduationYear", &json_field);
                strcpy(graduationYear, (char *) json_object_get_string(json_field));

                strcpy(return_message, filterByGraduateYear(graduationYear));

                break;
            case 6:
                // Opção 6 - Busca por email
                json_object_object_get_ex(parsed_json, "email", &json_field);
                strcpy(email, (char *) json_object_get_string(json_field));

                strcpy(return_message, filterByEmail(email));

                break;
            case 7:
                // Opção 7 - lista todos os usuários
                strcpy(return_message, listAll());
                break;
            case 8:
                // Opção 7 - reove um usuário
                // verifica se o usuário existe
                json_object_object_get_ex(parsed_json, "email", &json_field);
                strcpy(email, (char *) json_object_get_string(json_field));
                
                if (checkEmail(email)>0){
                    strcpy(return_message, removeProfile(email));
                }else{
                    strcpy(return_message, "\nErro: Email não encontrado.");
                }
                break; 
            default:
                strcpy(return_message, "\nErro: Opção inválida.");
        }

        // retorna para o cliente uma mensagem informando o resultado da operação solicitada
        sendto(sockfd, &return_message, strlen(return_message), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len);
    }

    return 0;
}
