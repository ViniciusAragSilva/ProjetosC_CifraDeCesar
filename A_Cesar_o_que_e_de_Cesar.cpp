/*********************************************************************
* @author Rafael Soares Baierle & Vin�cius Arag�o
* @version 0.1
* @date 2020
***********************************************************************/
// Includes
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>


int main ()
{
	setlocale(LC_ALL,"");
	
	FILE *fp2;
	FILE *fp;
	int  letra;       // armazena os caracteres do arquivo
	int  desl;		  // armazena o valor de deslocamento das letras
	int  alfa[26]={65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90}; 			//letras do alfabeto
	int  quant[26]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; 									//cada valor representa a quantidade de cada letra contida no arquivo lido
	int  indice;	 																						// armazena o indice do maior valor de quant[26]
	int  maior=0;	  																						// armazena o maior valor de letras repitidas do vetor quant[26]
	int  i=0;
	char nome[25];    																						// string que armazena o nome do arquivo
	char nome_dec[25];																						// string que armazena o nome do arquivo decodificado
	
	printf("Nomes: Rafael S.B. e Vin�cius A.\n");
	printf("Turma: 4323\n\n");
	
	printf("*********** A C�SAR O QUE � DE C�SAR ***********\n");
	
	printf("Digite o nome do arquivo que deseja decodificar:");
	scanf("%s",&nome);
	
	strcpy(nome_dec,nome);
	strcat(nome,".txt");																					//ajustando a extens�o do arquivo a ser aberto
	strcat(nome_dec,"_dec.txt");																			//ajustando a extens�o do arquivo que ir� conter a resposta
	
	fp=fopen(nome, "rt");     																				//abrindo arquivo codificado para leitura
	fp2=fopen(nome_dec, "wt");																				//abrindo arquivo que armazenara a decodifica��o para escrita
	
////////////////////////encontrando a quantidade de cada letra contida no arquivo codificado///////////////////////////////////////////

	for(i=0;i<26;i++){
		do{
			letra=getc(fp);																					// fun��o getc() retorna cada caractere do arquivo lido
			if(letra>=65 && letra<=90){
				if(alfa[i]==letra){																			// se a letra de alfa for igual a letra do arquivo
					quant[i]++;																				// soma +1 a quantidade de tal letra em i posi��o
				}
			}
		}while(!feof(fp));		
		fclose(fp);
		fp=fopen(nome, "rt");
	}
	
/////////////////////////////////encontrando o maior valor de letras repitidas do vetor quant e o indice do mesmo//////////////////////////

	for(i=0;i<26;i++){																						
		if(quant[i]>maior){																					// aqui ve se a quantidade de numeros repetidos em tal posicao � maior
			maior=quant[i];																					// se for o maior numero de repetidos vira a quantidade na tal posicao
			indice=i;																						// indice guarda qual a letra 
		}
	}
	fclose(fp);           																					//fechando arquivo codificado
	fp=fopen(nome, "rt"); 																					//abrindo arquivo codificado para leitura
	
//////////////////////////////////// decodificando o arquivo uilizando a letra mais repitida e trocando ela pelas letras mais provaveis//////////////////////////

	for(i=0;i<=3;i++){
		if(i==0){
// primeiro, todas as letras s�o deslocadas a partir da diferen�a entre 
			// a letra mais repitida do arquivo codificado e a letra A
			
			fprintf(fp2,"\n\nMensagem mais provavel:\n");
			desl=alfa[indice]-65;//65=A
			printf("\n%d deslocamentos\n", desl);
		}
		else if(i==1){
			// Segundo, todas as letras s�o deslocadas a partir da diferen�a entre 
			// a letra mais repitida do arquivo codificado e a letra E	
			fprintf(fp2,"\n\nSegunda mais provavel:\n");
			desl=alfa[indice]-69;//69=E
			printf("\n%d deslocamentos\n", desl);
		}
		else if(i==2){
			// primeiro, todas as letras s�o deslocadas a partir da diferen�a entre 
			// a letra mais repitida do arquivo codificado e a letra O
			fprintf(fp2,"\n\nTerceira mais provavel:\n");
			desl=alfa[indice]-79;
			printf("\n%d deslocamentos\n", desl);
		}
		else{
				fprintf(fp2,"\n\nQuarta mais provavel:\n");
				desl=alfa[indice]-73;
				printf("\n%d deslocamentos\n", desl);
		}
		// realizando os deslocamentos
		do{
			letra=getc(fp);// fun��o getc() retorna cada caractere do arquivo lido
		
			if(letra>=65 && letra<=90){     //letras
				if(letra-desl<65){
					letra=letra+26-desl;
					fprintf(fp2,"%c",letra);//escrevendo no arquivo resposta
				}
				else if( letra-desl>90){
					letra=letra-26-desl;
					fprintf(fp2,"%c",letra);//escrevendo no arquivo resposta
				}
				else{
					letra=letra-desl;
					fprintf(fp2,"%c",letra);//escrevendo no arquivo resposta
				}	
			}
			else if(letra>=0 && letra<=127){//Outros caracteres al�m das letras
				fprintf(fp2,"%c",letra);
				}
		}while(!feof(fp));
		fclose(fp);
		fp=fopen(nome, "rt");
	}
	
	printf("\nO arquivo foi decodificado!\n\n");
	fclose(fp2); //fechando arquivo decodificado
	fclose(fp);  //fechando arquivo codificado
	
	printf("Aqui est� o segredo revelado:\n");
	fp2=fopen(nome_dec, "rt"); //abrindo arquivo decodificado para leitura
	
	//Exibindo na tela do console os dados do arquivo decodificado
	while(!feof(fp2)){
		letra=getc(fp2);
		
		if(letra>=0 && letra<=127){
			printf("%c",letra);
		}
	}
	fclose(fp2);//fechando arquivo decodificado
	printf("\n\nO resultado foi inserido no arquivo %s",nome_dec);

    return(0);
}

