#include <stdio.h>
#include <string.h>

// Compiler function (unused for now)
int CompilerMain() {
  printf("No input file and no output file.\n");
  return 1;
}

int main(int argc, char *argv[]) {
    char *input_file = NULL;
    char *output_file = "output.bin";
    int hex_mode = 0;

    // 1. Loop para identificar o arquivo de entrada e as flags
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            output_file = argv[i + 1];
            i++;
        } else if (strcmp(argv[i], "-H") == 0) {
            hex_mode = 1;
        } else if (argv[i][0] != '-') {
            // Se não começa com '-', assumimos que é o arquivo de entrada
            input_file = argv[i];
        }
    }

    // 2. Verifica se o usuário passou um arquivo de entrada
    if (input_file == NULL) {
        printf("crx-bar: \033[1;31merror:\033[0m no input file specified\n");
        return 1;
    }

    // 3. Tenta procurar/abrir o arquivo de entrada
    FILE *in = fopen(input_file, "r");
    if (!in) {
        printf("crx-bar: \033[1;31merror:\033[0m %s: file not found\n", input_file);
        return 1;
    }
    fclose(in); // Por enquanto só queríamos saber se ele existe

    // O "coração" do seu binário
    unsigned char data[] = {0xFF, 0x43, 0xA1, 0x00};
    int size = 4;

    // 4. Abre a saída
    FILE *f = fopen(output_file, hex_mode ? "w" : "wb");
    if (!f) {
        printf("crx-bar: \033[1;31merror:\033[0m could not create output file\n");
        return 1;
    }

    if (hex_mode) {
        for (int i = 0; i < size; i++) {
            fprintf(f, "%02X%s", data[i], (i < size - 1) ? " " : "");
        }
    } else {
        fwrite(data, 1, size, f);
    }

    printf("crx-bar: \033[1;33mwarning:\033[0m compilation of '%s' finished successfully\n", input_file);

    fclose(f);
    return 0;
}

