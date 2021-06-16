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

    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
      
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
      
    // Filling server information
    servaddr.sin_family    = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);
      
    // Bind the socket with the server address
    if ( bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 ){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
      
    int len, n;
  
    len = sizeof(cliaddr);  //len is value/resuslt

    while (1){
        n = recvfrom(sockfd, (char *)buffer, MAXLINE, 
                MSG_WAITALL, ( struct sockaddr *) &cliaddr,
                &len);
        buffer[n] = '\0';

        printf("JSON recebido: %s\n", buffer);
        
        parsed_json = json_tokener_parse(buffer);

        json_object_object_get_ex(parsed_json, "option", &option);

        switch (json_object_get_int(option)){
            case 1:
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
                json_object_object_get_ex(parsed_json, "course", &json_field);
                strcpy(course, (char *) json_object_get_string(json_field));

                strcpy(return_message, filterByCourse(course));

                break;
            case 4:
                json_object_object_get_ex(parsed_json, "hability", &json_field);
                strcpy(hability, (char *) json_object_get_string(json_field));

                strcpy(return_message, filterBySkill(hability));

                break;
            case 5:
                json_object_object_get_ex(parsed_json, "graduationYear", &json_field);
                strcpy(graduationYear, (char *) json_object_get_string(json_field));

                strcpy(return_message, filterByGraduateYear(graduationYear));

                break;
            case 6:
                json_object_object_get_ex(parsed_json, "email", &json_field);
                strcpy(email, (char *) json_object_get_string(json_field));

                strcpy(return_message, filterByEmail(email));

                break;
            case 7:
                strcpy(return_message, listAll());
                break;
            case 8:
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

        sendto(sockfd, &return_message, strlen(return_message), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len);
    }

    return 0;
}