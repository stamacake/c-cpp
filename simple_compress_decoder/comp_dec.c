
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 1000
#define LEN 255
char text[MAX][LEN];

struct entry_0{ // вхождение символов
	char orig;
	int count;
};

struct pairs_0{ // пары символов
	char data_1;
	char data_2;
	int count;
};
struct codes{ // коды сжатых пар

	char repl;// замена
	char orig_1; // оригинал
	char orig_2;

};
void check_entry(char *current_line, struct entry_0* entry, int *entr);
void compress(struct codes* reps, char *current_line, int  replaces, FILE *file, char *repl12, int *ii);
void decoder(struct codes* reps, char *repl11, int  ii,int replaces, FILE *qwe);

int main(void) {
	int entrys =0;
	struct entry_0 entry[256];
	for (int i=0; i<256;i++){
		entry[i].orig=i;
		entry[i].count=0;
	}


	char current[256];
	int str_count = 0;
	FILE *fin = fopen( "C:\\Users\\stamacake\\eclipse-workspace\\kkkk\\file1.txt", "r+" );

	if (fin == NULL){
					printf("ошибка с файлом");
					return EXIT_SUCCESS;
				} else {
					while(fgets(current,256,fin) != NULL){
						strcpy(text[str_count],current);

						check_entry(text[str_count], entry, &entrys);
						if(entrys>254){
							printf("Текст слишком велик для сжатия");
							return EXIT_SUCCESS;
						}
						str_count++;

					}
				}
	struct pairs_0 pairs [256];
	int pairs_count =0;
	int check=0;

	for (int i=0;i<str_count;i++){
		int current_size = 	strlen(text[i]);

		if((text[i][current_size+1]=='\n')){ // если последний символ == новая строка
			current_size++;
		}
		int j =0;

		for(j;j<current_size;j++){
			if(j!=current_size-1){

				char a1 = text[i][j];
				char a2 = text[i][j+1];

				if( (a1 >= 'A' && a1 <= 'Z' || a1 >= 'a' && a1 <= 'z' ||
					a1 >= 'А' && a1 <= 'Я' || a1 >= 'а' && a1 <= 'я')&&
					(a2 >= 'A' && a2 <= 'Z' || a2 >= 'a' && a2 <= 'z' ||
					a2 >= 'А' && a2 <= 'Я' || a2 >= 'а' && a2 <= 'я')	){

				int check_pair=0;

				for(int k=0;k<pairs_count;k++){
					if(a1==pairs[k].data_1 && a2 == pairs[k].data_2){
						pairs[k].count++;
						check_pair=1;
					}
				}

				if(check_pair == 0){
					pairs[pairs_count].data_1 = a1;
					pairs[pairs_count].data_2 = a2;
					pairs[pairs_count].count=1;
					pairs_count++;
				}
			}

		}
	}
	}

	int replaces = 0;
	static struct codes reps[255]; // без статик меняет переменные

	//				Создание замен
	for(int i=0;i<pairs_count;i++){
		if(pairs[i].count>7){ // задание кол-ва вхождений для замены

			reps[replaces].orig_1=pairs[i].data_1;
			reps[replaces].orig_2=pairs[i].data_2;
			int k =254;
			if(replaces>254-entrys){
				printf("Текст слишком велик для сжатия");
				return EXIT_SUCCESS;

			}
			while(entry[k].count!=0 && k!=0){
				k--;
			}
			if(k==0){
				printf("Текст слишком велик для сжатия");
				return EXIT_SUCCESS;
			}
			reps[replaces].repl= entry[k].orig;
			entry[k].count= 1;
			entrys++;
			replaces++;
		}

	}

	FILE *file;
			 if ((file = fopen("file_compress1.txt","w")) == NULL){
						printf("Файл невозможно создать \n");
			 }
	char repl11[5000]; // закодированный текст
	int ii = 0;

	for(int q=0; q<str_count;q++){
		compress(reps, text[q], replaces, file, repl11, &ii);
	}
	FILE *qwe;
	if ((qwe = fopen("file_decode.txt","w+")) == NULL){
		printf("Файл невозможно создать \n");
	}
	decoder(reps, repl11,ii,replaces, qwe);
	for (int i=0; i<replaces;i++){
		printf("REPS # %d:\n%c%c - '%c'\n",i+1,reps[i].orig_1,reps[i].orig_2, reps[i].repl);
	}
	return EXIT_SUCCESS;
}
void check_entry(char *current_line, struct entry_0* entry, int *entr){ //проверка вхождения символов
	int current_size = 	strlen(current_line); // длина
	int i =0; // счетчик в строке
	while (i<current_size){
		for(int j=0;j<255;j++){
			if(current_line[i]==entry[j].orig){
				if(entry[j].count==0){
					*entr = *entr +1;
				}
				entry[j].count = 1;


			}
		}
		i++;
	}
}

void compress(struct codes* reps, char *current_line, int  replaces, FILE *file, char *repl12, int *ii){
	char strr[255]="";

	int current_size = 	strlen(current_line); // длина
	int i =0; // счетчик в строке
	while (i<current_size){
		int check_pair = 0;
		int j=0;
		while(j<replaces+1 && check_pair==0 && i<current_size){

			if(current_line[i]==reps[j].orig_1 && current_line[i+1]==reps[j].orig_2 ){
				check_pair = 1;
			}
			j = j+1;
		}

		if(check_pair == 1){
			fputc(reps[j-1].repl,file );
			repl12[*ii] = reps[j-1].repl;
			*ii= *ii+1;
			i= i+1;
		} else {
			fputc(current_line[i], file);
			char qqqq[10] = {current_line[i]};
			repl12[*ii] = current_line[i];
			*ii= *ii+1;
		}
		i = i +1;
	}

}
void decoder(struct codes* reps, char *repl11, int  ii,int replaces, FILE *qwe){
	for(int i=0;i<ii;i++){
			int k =0;
			int check= 0;
			while(check==0 && k<replaces){
				if(repl11[i]==reps[k].repl){
					check=1;
				}
				k++;
			}
			if(check==1){
				char a[2]= {reps[k-1].orig_1, reps[k-1].orig_2};
				fputc(reps[k-1].orig_1, qwe);
				fputc(reps[k-1].orig_2, qwe);
			}else {
				fputc(repl11[i], qwe);
			}
		}
}
