/**
 * Calculadora de Conversão Didática
 * Author: Ana Clara Gomes - 3° B
 * Created on Aug, 26th 2024
 * 
 * Questão 1 - 26/08/2024 17:49
 * Questão 2 - 26/08/2024 19:20
 * 
 * Version: 0.2
 * 
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void secondMenu();
void complementTwo(int decimal);
void decimalToBase(int decimal, int base);
void decimalToBCD (int decimal);


int main(){
    int button, number;
    printf("===================================================================");
    printf("\n\t\t\tCalculadora didática\n");
    printf("\n1. Converter decimal\n2. Converter decimal com sinal\n3. Converter decimal real em float e double\n");
    scanf("%d", &button);
    printf("-----------------\n\n");

    switch (button){
    case 1:
        secondMenu();
        break;
    
    case 2:
        printf("Decimal: ");
        scanf("%d", &number);
        printf("\n");
        complementTwo(number);
        break;
    
    default:
        printf("Comando invalido.");
        break;
    }

    printf("\n==================================================================\n");

    return 0;
}

void secondMenu(){
    int button, number;

    printf("Converter decimal para:\n 1. base 2\n 2. base 8\n 3. base 16\n 4. codigo BCD\n ");
    scanf("%d", &button);

    printf("\nDecimal: ");
    scanf("%d", &number);

    switch (button){
    case 1:
        decimalToBase(number, 2);
        break;
    case 2:
        decimalToBase(number, 8);
        break;
    case 3:
        decimalToBase(number, 16);
        break;
    case 4:
        decimalToBCD(number);
        break;
    
    default:
        printf("Comando invalido");
        break;
    }
}

void complementTwo(int decimal){
    char number[17], aux[17]; 
    int i, j, first = 0, cont = 0;;
    
    for (int g = 0; g < 17; g++){
        number[g] = 0;
        aux[g] = 0;
    }
    
    for (i = 0; decimal > 0; i++){
        number[i] = decimal % 2;
        decimal /= 2;
        
    }

    for (j = 0 ; j <= 16; j++){
        
        if (first == 0){
            if (number[j] == 1){
                first = 1;
                aux[j] = 1;
            }else {
                aux[j] = number[j];
            }
            
        }else {
            if (first == 1 && number[j] == 1){
                aux[j] = 0;
                
            }else if (first == 1 && number[j] == 0){
                aux[j] = 1;
            }
        }
        
        
    }

    printf("Procure o primeiro digito '1' no seu binario, e entao inverta todos os outros digitos apos ele:\n");
    printf("\nNumero em binario: ");
    for (j = 16; j >= 0; j--){
        printf("%d", number[j]);
    }
    printf("\n");
    
    printf("\nComplemento a dois: ");
    for (j = 16; j >= 0; j--){
        printf("%d", aux[j]);
    }
    printf("\n");
    
}

void decimalToBase(int decimal, int base){
    char number[32];
    int temp, i = 0, j;

    printf("Para calcular a conversao, basta efetuar sucetivas divisoes pela base: \n");
    if (base == 8 || base == 2){
        
        while (decimal > 0){
            number[i] = decimal % base;
            printf("\t%d |▁ %d = %d\n", decimal, base, number[i]);
            decimal /= base;
            i++; 
        }
        printf("\n");

        if (base == 2){
            printf("Decimal em binario: ");
        
        }else {
            printf("Decimal em Octal: ");
        }
        
        for ( j = i - 1; j >= 0; j--){
            printf("%d", number[j]);
        }
        printf("\n");

    }else {
        while (decimal > 0){
            temp = decimal % base;
            printf("\t%d |▁ %d = %d\n", decimal, base, temp);
            if (temp < 10){
                number[i] = temp + 48;

            }else number[i] = temp + 55;

            decimal /= base;
            i++;
        }

        printf("Decimal em hexadecimal: ");
        for ( j = i - 1; j >= 0; j--){
            printf("%c", number[j]);
        }
        printf("\n");
        
        
    }
}

void decimalToBCD (int decimal){
    char *list[] = {"0000", "0001", "0010", "0011", "0100", 
                    "0101", "0110", "0111", "1000", "1001"};
    char bcd[512] = "";  
    char temp[5];
    char result[512] = ""; 
    int digit;

    if (decimal == 0) {
        printf("\nDecimal para BCD: %s\n", list[0]);
        return;
    }

    printf("\nPara converter para BCD basta analisar os valores dos digitos isoladamente: ");
    while (decimal > 0) {
        digit = decimal % 10;
        strcpy(temp, list[digit]);
        
        if (strlen(result) == 0) {
            strcpy(result, temp);
        
        } else {
            strcat(temp, " ");
            strcat(temp, result);
            strcpy(result, temp);
        }

        decimal /= 10;
    }
    printf("\nDecimal para BCD: %s\n", result);
}