/**
 * Calculadora de Conversão Didática
 * Author: Ana Clara Gomes - 3° B
 * Created on Aug, 26th 2024
 * 
 * Questão 1 - 26/08/2024 17:49
 * Questão 2 - 26/08/2024 19:20
 * Questão 3 - 29/08/2024 07:58
 * 
 * Version: 0.3
 * 
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


void secondMenu();
void complementTwo(int decimal);
void decimalToBase(int decimal, int base);
void decimalToBCD (int decimal);
void printFloatBinary(float real);
void printDoubleBinary(float real);

int main(){
    int button, number;
    printf("===================================================================");
    printf("\n\t\t\tCalculadora didática\n");
    printf("\n1. Converter decimal\n2. Converter decimal com sinal\n3. Converter real em float e double\n");
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
    
    case 3:
        printf("Calcular:\n1.Float\n2.Double\n");
        scanf("%d", &button);

        if(button != 2 && button != 1){
            printf("Comando inválido.\n");
        }else {
            float value;
            printf("Real: ");
            scanf("%f", &value);
            
            printf("O passo a passo para calcular o float e o double é o mesmo, a unica diferença é na hora de calcular o expoente.\n");
            printf("No float usamos 127, e no double 1023. Por causa do numero de bits");

            if(button == 1){
                printFloatBinary(value);

            }else {
                printDoubleBinary(value);

            }
        }

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
    char number[17] = {0};
    char aux[17] = {0}; 
    int i, j, first = 0, cont = 0;
    
    for (i = 0; decimal > 0; i++){
        number[i] = decimal % 2;
        decimal /= 2;
        
    }

    for (j = 0 ; j <= 16; j++){
        
        if (first == 0){
            if (number[j] == 1){
                first = 1;
                aux[j] = number[j];
            }else {
                aux[j] = number[j];
            }
            
        }else {
            if ( number[j] == 1){
                aux[j] = 0;
                
            }else if ( number[j] == 0){
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

  /*
    Passo a passo para transformar

    1- transformar a parte decimal em binário
    2- transformar a parte real em binario
    3- notação cientifica (achar o 1 mais proximo)
    4- usar o expoente da notação para calcular o bias (n - 1 + 127) ou (n - 1 + 1023)
    5- calcular a nova parte decimal a partir do expoente do bias
    6- por a parte fracionaria q vc consegiu na notação cientifica na parte real
    7- vc tem um ponto flutuante
  */

void printFloatBinary(float real){

    char sign = (real < 0) ? '1' : '0' ;    //0.
    if (real < 0) real = -real;

    int integerPart = (int)real;
    float fractPart = real - integerPart;

    char integerBinary[32] = {0};
    char fractBinary[23] = {0};
    //-------------------------------
    printf("\n==================================================\n");
    printf("\tPasso a passo Float Binário\n\n");

    printf("----------\n");
    printf("1. Defina o valor do bit de sinal\n\n");
    printf(" %f -> Sinal: %c\n\n", real, sign);
    
    printf("----------\n");
    printf("2. Separe a parte decimal da fracionaria e as transforme em binário.\n\n");
    for (int i = 0; i < 32; i++){   //1.
        integerBinary[31 - i] = (integerPart % 2) + '0';
        integerPart /= 2;
    }

    for (int i = 0; i < 23; i++){   //2.
        
        fractPart *= 2;
        
        if (fractPart >= 1.0){
            fractBinary[i] = '1';
            fractPart -= 1.0;

        }else {
            fractBinary[i] = '0';
        }
    }

    printf("Número: %f\n", real);
    printf("Parte decimal em binário: ");
    for (int i = 0; i < 32; i++){
        printf("%c", integerBinary[i]);
    }
    printf("\n");
    printf("Parte fracionaria em binário: x.");
    for(int i = 0; i < 23; i++){
        printf("%c", fractBinary[i]);
    }
    printf("\n\n");

    //---------------------------  
    printf("----------\n");
    printf("3. Achar o '1' mais próximo do bit de magnitude e calcular o expoente a partir da notação científica.\n\n"); 

    int firtOneIndex = -1;          //3.
    for (int i = 0; i < 32; i++){
        if(integerBinary[i] == '1'){
            firtOneIndex = i;
            break;
        }
    }

    int expoent;
    if (firtOneIndex != -1){        //4.
        expoent = 127 + (31 - firtOneIndex);
    }else {
        for (int i = 0; i < 23; i++){
            fractBinary[i] == '1';
            firtOneIndex = -(i + 1);
            break;
        }
        
        expoent = 127 + firtOneIndex;
    }
    printf("Notação científica: x10^%d\n", firtOneIndex);
    printf("No caso do float binário, para calcular o expoente vamos usar 127\n");
    printf("%d = 127(bits de valor) + %d(notação científica) - 1(bit de sinal)\n", expoent, firtOneIndex);
    printf("\n");

    //---------------------------  
    printf("----------\n");
    printf("4. Calcular a nova parte decimal a partir do expoente.\n\n");

    char expoentBinary[8] = {0};
    for (int i = 0; i < 8; i++){    //5.
        expoentBinary[7 - i] = (expoent % 2) + '0';
        expoent /= 2;
    }
    printf("Nova parte decimal em binário: ");
    for (int i = 0; i < 8; i++){
        printf("%c", expoentBinary[i]);
    }
    printf("\n\n");

    //---------------------------  
    printf("----------\n");
    printf("5. Mover a virgula da primeira parte decimal de acordo com a notação científica para a parte fracionária.\n\n");

    printf("Nova parte fracionária: ");
    int bitsPrinted = 0;
    if (firtOneIndex >= 0){
        for (int i = firtOneIndex + 1; i < 32 && bitsPrinted < 23; i++){
            printf("%c", integerBinary[i]);
            bitsPrinted++;
        }
        for (int i = 0; bitsPrinted < 23; i++) {
            printf("%c", fractBinary[i]);
            bitsPrinted++;
        }
    }else {
        for (int i = -firtOneIndex - 1; i < 23 && bitsPrinted < 23; i++) {
            printf("%c", fractBinary[i]);
            bitsPrinted++;
        }
    }
    printf("\n");

    printf("----------\n");
    printf("6. Representação Binaria.\n");

    printf("%c", sign);
    for (int i = 0; i < 8; i++) {
        printf("%c", expoentBinary[i]); 
    }
    printf(".");

    bitsPrinted = 0;
    if (firtOneIndex >= 0){
        for (int i = firtOneIndex + 1; i < 32 && bitsPrinted < 23; i++){
            printf("%c", integerBinary[i]);
            bitsPrinted++;
        }
        for (int i = 0; bitsPrinted < 23; i++) {
            printf("%c", fractBinary[i]);
            bitsPrinted++;
        }
    }else {
        for (int i = -firtOneIndex - 1; i < 23 && bitsPrinted < 23; i++) {
            printf("%c", fractBinary[i]);
            bitsPrinted++;
        }
    }
    printf("\n\n");
}

void printDoubleBinary(float real){

    char sign = (real < 0) ? '1' : '0' ;    //0.
    if (real < 0) real = -real;

    int integerPart = (int)real;
    float fractPart = real - integerPart;

    char integerBinary[64] = {0};
    char fractBinary[52] = {0};
    //-------------------------------
    printf("\n==================================================\n");
    printf("\tPasso a passo Double Binário\n\n");

    printf("----------\n");
    printf("1. Defina o valor do bit de sinal\n\n");
    printf(" %f -> Sinal: %c\n\n", real, sign);
    
    printf("----------\n");
    printf("2. Separe a parte decimal da fracionaria e as transforme em binário.\n\n");
    for (int i = 0; i < 64; i++){   //1.
        integerBinary[63 - i] = (integerPart % 2) + '0';
        integerPart /= 2;
    }

    for (int i = 0; i < 52; i++){   //2.
        
        fractPart *= 2;
        
        if (fractPart >= 1.0){
            fractBinary[i] = '1';
            fractPart -= 1.0;

        }else {
            fractBinary[i] = '0';
        }
    }

    printf("Número: %f\n", real);
    printf("Parte decimal em binário: ");
    for (int i = 0; i < 64; i++){
        printf("%c", integerBinary[i]);
    }
    printf("\n");
    printf("Parte fracionaria em binário: x.");
    for(int i = 0; i < 52; i++){
        printf("%c", fractBinary[i]);
    }
    printf("\n\n");

    //---------------------------  
    printf("----------\n");
    printf("3. Achar o '1' mais próximo do bit de magnitude e calcular o expoente a partir da notação científica.\n\n"); 

    int firtOneIndex = -1;          //3.
    for (int i = 0; i < 64; i++){
        if(integerBinary[i] == '1'){
            firtOneIndex = i;
            break;
        }
    }

    int expoent;
    if (firtOneIndex != -1){        //4.
        expoent = 1023 + (63 - firtOneIndex);
    }else {
        for (int i = 0; i < 52; i++){
            fractBinary[i] == '1';
            firtOneIndex = -(i + 1);
            break;
        }
        
        expoent = 1023 + firtOneIndex;
    }
    printf("Notação científica: x10^%d\n", firtOneIndex);
    printf("No caso do double binário, para calcular o expoente vamos usar 1023\n");
    printf("%d = 1023(bits de valor) + %d(notação científica) - 1(bit de sinal)\n", expoent, firtOneIndex);
    printf("\n");

    //---------------------------  
    printf("----------\n");
    printf("4. Calcular a nova parte decimal a partir do expoente.\n\n");

    char expoentBinary[11] = {0};
    for (int i = 0; i < 11; i++){    //5.
        expoentBinary[10 - i] = (expoent % 2) + '0';
        expoent /= 2;
    }
    printf("Nova parte decimal em binário: ");
    for (int i = 0; i < 11; i++){
        printf("%c", expoentBinary[i]);
    }
    printf("\n\n");

    //---------------------------  
    printf("----------\n");
    printf("5. Mover a virgula da primeira parte decimal de acordo com a notação científica para a parte fracionária.\n\n");

    printf("Nova parte fracionária: ");
    int bitsPrinted = 0;
    if (firtOneIndex >= 0){
        for (int i = firtOneIndex + 1; i < 64 && bitsPrinted < 52; i++){
            printf("%c", integerBinary[i]);
            bitsPrinted++;
        }
        for (int i = 0; bitsPrinted < 52; i++) {
            printf("%c", fractBinary[i]);
            bitsPrinted++;
        }
    }else {
        for (int i = -firtOneIndex - 1; i < 52 && bitsPrinted < 52; i++) {
            printf("%c", fractBinary[i]);
            bitsPrinted++;
        }
    }
    printf("\n");

    printf("----------\n");
    printf("6. Representação Binaria.\n");

    printf("%c", sign);
    for (int i = 0; i < 11; i++) {
        printf("%c", expoentBinary[i]); 
    }
    printf(".");

    bitsPrinted = 0;
    if (firtOneIndex >= 0){
        for (int i = firtOneIndex + 1; i < 64 && bitsPrinted < 52; i++){
            printf("%c", integerBinary[i]);
            bitsPrinted++;
        }
        for (int i = 0; bitsPrinted < 52; i++) {
            printf("%c", fractBinary[i]);
            bitsPrinted++;
        }
    }else {
        for (int i = -firtOneIndex - 1; i < 52 && bitsPrinted < 52; i++) {
            printf("%c", fractBinary[i]);
            bitsPrinted++;
        }
    }
    printf("\n\n");
}