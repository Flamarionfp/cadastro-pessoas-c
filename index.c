#include <stdio.h>
#include <string.h>

#define FILE_NAME "pessoas.txt"

void showMenu() {
  printf("\n");
  printf("Digite a opcao desejada: \n");
  printf("1 - Apresentar todo conteudo do arquivo\n");
  printf("2 - Apresentar conteudo de um registro\n");
  printf("3 - Cadastrar um registro\n");
  printf("4 - Fechar o programa\n");
}

void writeFile(const char *file, const char *record) {
  FILE *fp = fopen(file, "a");
  if (fp != NULL) {
    fprintf(fp, "%s\n", record);
    fclose(fp);
  }
}

void showFileContent(const char *file) {
  FILE *fp = fopen(file, "r");
  if (fp != NULL) {
    char line[100];
    while (fgets(line, sizeof(line), fp) != NULL) {
      printf("%s", line);
    }
    fclose(fp);
  }
}

void handleShowFileContent() {
  showFileContent(FILE_NAME);
  printf("\n");
}

void handleShowFileRegister() {
  int fileLine;
  int currentLine = 1;
  char line[100];

  printf("Qual linha voce deseja ver? \n");
  scanf("%d", &fileLine);
  getchar();

  FILE *fp = fopen(FILE_NAME, "r");
  if (fp != NULL) {
    while (fgets(line, sizeof(line), fp) != NULL) {
      if (currentLine == fileLine) {
        printf("%s", line);
        fclose(fp);
        return;
      }
      currentLine++;
    }

    fclose(fp);

    printf("Linha %d nao encontrada\n", fileLine);
  }
}

void handleWriteRegister(char *record, int recordSize) {
  char fullName[50];
  int age;

  printf("Digite o nome completo: \n");
  fgets(fullName, sizeof(fullName), stdin);
  fullName[strcspn(fullName, "\n")] = '\0'; // Remover a quebra de linha

  printf("Digite a idade: \n");
  scanf("%d", &age);
  getchar();

  snprintf(record, recordSize, "%s,%d", fullName, age);

  writeFile(FILE_NAME, record);
}

int main() {
  int selectedOption = 0;
  char record[100];

  printf("Cadastro de Pessoas\n");
  printf("-------------------\n");

  do {
    showMenu();
    scanf("%d", &selectedOption);
    getchar();

    switch(selectedOption) {
      case 1:
        handleShowFileContent();
        break;
      case 2: 
        handleShowFileRegister();
        break;
      case 3:
        handleWriteRegister(record, sizeof(record));
        break;
      case 4: 
        break;
      default:
        printf("Opcao invalida\n");
    }

  } while (selectedOption != 4);

  return 0;
}
