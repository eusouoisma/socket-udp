#ifndef __ARQUIVO_H__
#define __ARQUIVO_H__

char** str_split(char* a_str, const char a_delim);
char* filterByCourse(char course[1000]);
char* filterBySkill(char skill[1000]);
char* filterByGraduateYear(char year[1000]);
char* filterByEmail(char email[1000]);
char* listAll();
char* create(char new_profile[10][1000]);
int checkEmail(char email[1000]);
char* removeProfile(char email[1000]);
char* addExperience(char email[1000], char experience[1000]);
#endif