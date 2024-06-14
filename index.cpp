#include <iostream>
#include <conio.h>
#include <cstdlib>  // Necessário para rand() e srand()
#include <ctime>    // Necessário para time()

#define RESET   "\033[0m"
#define RED     "\033[31m"      
#define GREEN   "\033[32m"     
#define YELLOW  "\033[33m"    

using namespace std;


/*
    Calcula a pontução de forma inversamente proporcional a quantidade de tentivas.
*/
int calcScore(int maxTries, int tries, int maxScore) {
    if (tries >= maxTries) {
        return 0;
    }
    double scoreProportion = 1 - (double(--tries)/maxTries);
    return scoreProportion * maxScore;
}

/*
    Verifica a letra inserida pelo usuário contra a palavra secreta
    Retorna 1 se a letra estiver correspondente
    Retorna 0 se não estiver
*/
int checkWord(char first, char second, char third, char fourth, char fifth, char currentChar, int position) {
    char checkChar;
    int status = 0;
    switch (position) {
        // position determina qual caractere deve ser verificado
        case 1: checkChar = first; break;
        case 2: checkChar = second; break;
        case 3: checkChar = third; break;
        case 4: checkChar = fourth; break;
        case 5: checkChar = fifth; break;
   }
    // Compara e imprime o resultado com a cor correspondente
    if (checkChar != currentChar) {
        if (first != currentChar && second != currentChar && third != currentChar && fourth != currentChar && fifth != currentChar) {
            cout << RED << currentChar;
        }
        else {
            cout << YELLOW << currentChar;
        }
    }
    else {
        cout << GREEN << currentChar;
        status = 1;
    }    
    // Resetar a cor e imprimir nova linha no fim da palavra
    if (position == 5) {
        cout << RESET << endl;
    }
    return status;


}
// Seleciona um índice de palavra aleatório
int pickRandomI() {
    srand(time(0));
    return rand() % 10 + 1;
}

/*
    Esta função associa cada número a uma palavra (charI), e cada letra da palavra está associada a sua posição (charP)
*/
char getWordChar(int charI, int charP) {
    switch (charI) {
    case 1: //palavra=carro
        switch (charP) { case 1: return 'c'; case 2: return 'a';  case 3: return 'r';  case 4: return 'r'; case 5: return 'o'; }
    case 2: //palavra=letra
        switch (charP) {  case 1: return 'l'; case 2: return 'e';  case 3: return 't'; case 4: return 'r'; case 5: return 'a'; }
    case 3: //palavra=ponte
        switch (charP) { case 1: return 'p';  case 2: return 'o'; case 3: return 'n'; case 4: return 't'; case 5: return 'e'; }
    case 4: //palavra=corte
        switch (charP) { case 1: return 'c'; case 2: return 'o'; case 3: return 'r'; case 4: return 't'; case 5: return 'e'; }
    case 5: //palavra=barba
        switch (charP) { case 1: return 'b'; case 2: return 'a'; case 3: return 'r'; case 4: return 'b'; case 5: return 'a'; }
    case 6: //palavra=mosca
        switch (charP) { case 1: return 'm'; case 2: return 'o'; case 3: return 's'; case 4: return 'c'; case 5: return 'a'; }
    case 7: //palavra=lagoa
        switch (charP) { case 1: return 'l'; case 2: return 'a'; case 3: return 'g'; case 4: return 'o'; case 5: return 'a'; }
    case 8: //palavra=termo
        switch (charP) { case 1: return 't'; case 2: return 'e'; case 3: return 'r'; case 4: return 'm'; case 5: return 'o'; }
    case 9: //palavra=baixo
        switch (charP) { case 1: return 'b'; case 2: return 'a'; case 3: return 'i'; case 4: return 'x'; case 5: return 'o'; }
    case 10: //palavra=piano
        switch (charP) { case 1: return 'p'; case 2: return 'i'; case 3: return 'a'; case 4: return 'n';case 5: return 'o'; }
    }
}

void printTutorial() {
    cout << "O Termo é um jogo onde os jogadores tentam adivinhar uma palavra de cinco letras em seis tentativas." << endl;
    cout << "Para cada tentativa, os jogadores recebem uma dica sobre quais letras estão na palavra e quais não estão." << endl;
    cout << "para jogar, basta digitar um palpite de cinco letras.\n O jogo então retornará uma dica com base no seu palpite.A dica consistirá em cinco símbolos:" << endl;
    cout << GREEN << "Verde:" << "A letra está na palavra secreta e na posição correta." << endl;
    cout << YELLOW << "Amarelo" << " A letra está na palavra secreta, mas não na posição correta." << endl;
    cout << RED << "Vermelho:" << "A letra não está na palavra secreta." << endl;
    cout << RESET << "Use as dicas para refinar seus palpites e adivinhar a palavra secreta antes de ficar sem tentativas." << endl;
    cout << "Aperte qualquer tecla quando estiver pronto pra jogar";
}

int main()
{
    cout << "Seja bem-vindo ao termo!" << endl;
    int tutorial;
    cout << "Gostaria de ver o tutorial?\n Sim(1), Não (0)" << endl;
    cin >> tutorial;
    if (tutorial) {
        printTutorial();
        getch(); // Aguardar input antes de prosseguir
    }

    int dificulty;
    cout << "Selecione o seu nível de dificuldade\n";
    cout << "Digite (1) para fácil, (2) para médio e (3) para díficil";
    cin >> dificulty;

    int attempts = 0;
    int maxAttempts;
    switch (dificulty) {
        case 1:  maxAttempts = 8; break;
        case 2:  maxAttempts = 6; break;
        case 3:  maxAttempts = 4; break;
        default: 
            maxAttempts = 6;
    }

    int wordIdentifier = pickRandomI();
    char first = getWordChar(wordIdentifier, 1);
    char second = getWordChar(wordIdentifier, 2);
    char third = getWordChar(wordIdentifier, 3);
    char fourth = getWordChar(wordIdentifier, 4);
    char fifth = getWordChar(wordIdentifier, 5);

    char l1, l2, l3, l4, l5;
    while (attempts < maxAttempts) {
        // Como a função checkWord retorna 1 no caso de sucesso, se todas as verificações estiverem corretas a soma dos seus outputs será 5
        if ( attempts != 0 && (
            checkWord(first, second, third, fourth, fifth, l1, 1) +
            checkWord(first, second, third, fourth, fifth, l2, 2) +
            checkWord(first, second, third, fourth, fifth, l3, 3) +
            checkWord(first, second, third, fourth, fifth, l4, 4) +
            checkWord(first, second, third, fourth, fifth, l5, 5)
            ) == 5) {
            cout << "Parabéns, você conseguiu atingir a palavra em " << attempts << " tentativas!\n";
            cout << "Sua pontuação final foi de: " << calcScore(maxAttempts, attempts, 500);
            return 0;
        }
        cout << "(Tentativa " << (++attempts) << " de "<< maxAttempts << ") | Insira sua tentativa letra por letra : \n";
        cout << "Primeira letra: ";
        cin >> l1;
        cout << "Segunda letra: ";
        cin >> l2;
        cout << "Terceira letra: ";
        cin >> l3;
        cout << "Quarta letra: ";
        cin >> l4;
        cout << "Quinta letra: ";
        cin >> l5;
    }
    cout << "Suas tentativas acabaram, você perdeu.\nA palavra secreta era: " << first << second << third << fourth << fifth << ".";
}
