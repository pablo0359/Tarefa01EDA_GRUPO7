#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>


FILE *openFile(char *filename) {
    return fopen(filename, "r");
}

FILE *writeFile(char *filename) {
    return fopen(filename, "w");
}

int isNumber(char c) {
    if(c >= 48 && c <= 57) {
        return 1;
    }
    return 0;
}

int isEndWord(char c){
    int isEnd = 0, i;
    char ends[8] = {' ', ',', ';', '\n', '.', ':', '\\', '/'};
    for(i = 0; i<8; i++){
        if(c == ends[i]){
            isEnd = 1;
            break;
        }
    }
    return isEnd;
}

int countCharsInFile(FILE *fileName) {
    int count = 0, i;
    char word[30], c;

    while((c = fgetc(fileName)) != EOF){

        if(!isEndWord(c)) {
            i = 0;

            while(!isEndWord(c)) {
                word[i] = c;
                c = fgetc(fileName);
                i++;
            }

            if(i > 3) {
                i ++;
                count = count + i;
            }
        } 
    }
    return count;
}

int wordCountInFile(char *word, FILE *fp) {
    int count = 0, i;
    char wordInFile[100], c;
    
    fseek(fp, 0, SEEK_SET);
    while((c = fgetc(fp)) != EOF) {
        i = 0;
        
        while(!isEndWord(c)) {
            wordInFile[i] = c;
            c = fgetc(fp);
            i++;
        }

        if(strcmp(word, wordInFile) == 0)
            count++;

        memset(wordInFile, 0, 100);
    }
    //if(count > 0)
    //    printf("%d ", count); 
    return count;
}

int numberOfWordsInFile(FILE *fp) {
    int count = 1;
    char c;

    fseek(fp, 0, SEEK_SET);
    while((c = fgetc(fp)) != EOF) {
        if(isEndWord(c))
            count++;
    }
    return count;
}

int checkForRepeatedWords(char *word, FILE *fp, long int wordPosition){
    char c, word2[50];
    int i;
   
   
    fseek(fp, 0, SEEK_SET); 

    c = fgetc(fp);

    while(ftell(fp) <  wordPosition) {
    
        if(c == '"') {
            while((c = fgetc(fp)) != '"') {
                i = 0;
                while(!isEndWord(c)) {
                    word2[i] = c;
                    c = fgetc(fp);
                    i++;
                }
                word2[i] = ' ';
        
                if(strcmp(word,word2) == 0)
                     return 1;

                memset(word2, 0, 50);
           }
        }

        c = fgetc(fp);
    }

    return 0;
}

int checkForRepeatedWords2(char *word, FILE *fp){
    char c, word2[100];
    int i;

    fseek(fp, 0, SEEK_SET);
  
    while((c = fgetc(fp)) != EOF) {
        i = 0;

        while(c != '\n') {

            word2[i] = c;
            c = fgetc(fp);
            i++;
        } 
        word2[i] = '\n';
 
        if(strcmp(word, word2) == 0)
            return 1;

        memset(word2, 0, 100);
    }
       ; 
    return 0;
}

int sortByRating(FILE *Reviews, FILE *Nota1, FILE *Nota2, FILE *Nota3, FILE *Nota4, FILE *Nota5) {
    char buff[20000], c;
    int i;

    c = fgetc(Reviews);
    while (c != EOF) {
        if(c == '"') {
            memset(buff, 0, 20000);
            c = fgetc(Reviews);
            i = 0;
            while (c != '"') { 
                buff[i] = c;   
                c = fgetc(Reviews); 
                i++;
            }
            buff[i] = '\n';
        }

        switch (c) {
            case '1':
                fputs(buff, Nota1);
                break;
            case '2':
                fputs(buff, Nota2);
                break;
            case '3':
                fputs(buff, Nota3);
                break;
            case '4':
                fputs(buff, Nota4);
                break;
            case '5':
                fputs(buff, Nota5);
                break;
            default:
                break;
        }

        c = fgetc(Reviews); 
    }
    memset(buff, 0, 20000);
    return 0;
}

int countLinesTFIDF(FILE *TF_IDFfile) {
    int count = -1;
    char c;
    
    fseek(TF_IDFfile, 0, SEEK_SET);
    while((c = fgetc(TF_IDFfile)) != EOF) {
        if(c == '\n')
            count++;
    }
    return count;
}


struct WordTFIDF {
    char word[100];
    char tfidf[20];
};

int structCompare(const void* s1, const void* s2) {
    
    struct WordTFIDF *n1 = (struct WordTFIDF *)s1;
    struct WordTFIDF *n2 = (struct WordTFIDF *)s2;
    int tfidfCompare = strcmp(n1->tfidf, n2->tfidf);
    return -tfidfCompare;
}


int sortTFIDF(FILE *fp, int notaNum) {
    char c;
    int i, j =0, numLines, numWords;

    numLines = countLinesTFIDF(fp);

    struct WordTFIDF *NotaX;
    
    NotaX = (struct WordTFIDF *) malloc(sizeof(char) * 120 * numLines);
    
    fseek(fp, 0, SEEK_SET);

    printf("Escolha quantas palavras voc� deseja mostrar: ");
    scanf("%d", &numWords);
    printf("\nPalavra | TF-IDF\n");

    while((c = fgetc(fp)) != EOF) {

        if(c == '"') {
            i = 0;
            c = fgetc(fp);
       
            while(c != '"') {
       
                NotaX[j].word[i] = c;
                c = fgetc(fp);
                i++;
            }
            
            c = fgetc(fp);

            switch(notaNum) {
                case 1:
                    c = fgetc(fp);
                    break;
                case 2:
                    for(i=0; i<14; i++) {
                        c = fgetc(fp);
                    }
                    break;
                case 3:
                    for(i=0; i<27; i++) {
                        c = fgetc(fp);
                    }
                    break;
                case 4:
                    for(i=0; i<40; i++) {
                        c = fgetc(fp);
                    }
                    break;
                case 5:
                    for(i=0; i<53; i++) {
                        c = fgetc(fp);
                    }
                    break;
            } 
                    
            for(i = 0; i < 12; i++) { 
                NotaX[j].tfidf[i] = c;
                c = fgetc(fp);
            }
            //printf("%s\n", NotaX[j].tfidf);
            j++; 
        }
    } 
    
    qsort(NotaX, numLines, sizeof(struct WordTFIDF), structCompare);

    for(i = 0; i < numWords; i++) {
        printf("%s | %s\n", NotaX[i].word, NotaX[i].tfidf);
    }

    free(NotaX);
    return 0;
}
