/*
IZP - projekt 1
Roman Vintoňak
xvinto00
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

/*
 * Vypíše počet delimů podle počtu buněk v prvním řádku a nový řádek
*/
void InsertRow(int row, char *arg, int NumberOfCells, char delim){
    int ArgInt  = atoi(arg);
    if(ArgInt == row){
        for(int i = 1; i < NumberOfCells; i++){
            printf("%c", delim);
        }
        printf("\n");
    }
}

/*
 * Zkontroluje, jestli se jedná a správný sloupec a jestli je v buňce desetinné číslo
 * pokud ano zaokrouhlí číslo v dané buňce, vypíše ho a vrací 1
 * jinak nedělá nic a vrací 0
*/
int RoundColumn(int column, char *arg, char *cell, char delim){
    int ArgInt  = atoi(arg);
    if(ArgInt == column){
        char *str = {'\0'};
        double CurrentCellFloat = strtof(cell, &str);
        if((strlen(str) == 1) && (str[0] == delim)){
            int CurrentCellRounded;
            CurrentCellFloat > 0 ? (CurrentCellRounded = CurrentCellFloat + 0.5):(CurrentCellRounded = CurrentCellFloat - 0.5);
            printf("%d%c", CurrentCellRounded, delim);
            return 1;
        }
        else if((strlen(str) == 0) && (str[0] == '\0')){
            int CurrentCellRounded;
            CurrentCellFloat > 0 ? (CurrentCellRounded = CurrentCellFloat + 0.5):(CurrentCellRounded = CurrentCellFloat - 0.5);
            printf("%d", CurrentCellRounded);
            return 1;
        }
    }
    return 0;
}

/*
 * Zkontroluje, jestli se jedná a správný sloupec a jestli je v buňce desetinné číslo
 * pokud ano odstraní desetinnou část z čísla, vypíše ho a vrací 1
 * jinak nedělá nic a vrací 0
*/
int ToIntColumn(int column, char *arg, char *cell, char delim){
    int ArgInt  = atoi(arg);
    if(ArgInt == column){
        char *str = {'\0'};
        double CurrentCellFloat = strtof(cell, &str);
        if((strlen(str) == 1) && (str[0] == delim)){
            printf("%d%c", (int)CurrentCellFloat, delim);
            return 1;
        }
        else if((strlen(str) == 0) && (str[0] == '\0')){
            printf("%d", (int)CurrentCellFloat);
            return 1;
        }
    }
    return 0;
}



/*
 * Funkce, která by měla fungovat podobně jako strtok
 * s rozdílem, že funguje i s prazdýma buňkama
 * do CurrentCell nastaví aktuální buňku včetně delimu
 * do RestOfTheLine nastaví zbytek řádku
*/
int MyStrtok(char delim, char *RestOfTheLine, char *CurrentCell){
    char LocalCell[102] = {'\0'};
    char LocalRestOfTheLine[10242] = {'\0'};
    int i = 0;
    while((RestOfTheLine[i-1] != delim) && (RestOfTheLine[i] != '\0')){
        LocalCell[i] = RestOfTheLine[i];
        i++;
        if(i == 100){
            return 1;
        }
    }
    int j = 0;
    while(RestOfTheLine[i] != '\0'){
        LocalRestOfTheLine[j] = RestOfTheLine[i];
        i++;
        j++;
    }
    strcpy(RestOfTheLine, LocalRestOfTheLine);
    strcpy(CurrentCell, LocalCell);
    return 0;
}

/*
 * Najde hodnotu, kterou má kopírovat a uloží ji do proměnné CellToCopy
*/
void CopySetValue(char *arg, char delim, int NumberOfCells, char *CellToCopy, char *line){
    char CurrentCellA[102] = {'\0'};
    char RestOfTheLineA[10242] = {'\0'};
    strcpy(RestOfTheLineA, line);
    int ArgInt  = atoi(arg);
    int j = 1;
    while((RestOfTheLineA[0] != '\0') && (j <= NumberOfCells)){
        MyStrtok(delim, RestOfTheLineA, CurrentCellA);
        if(ArgInt == j){
            if(CurrentCellA[strlen(CurrentCellA)-1] == delim){
                CurrentCellA[strlen(CurrentCellA)-1] = '\0';
            }
            strncpy(CellToCopy, CurrentCellA, strlen(CurrentCellA));
        }
        j++;
    }
}

/*
 * Najde hodnoty, které má měnit a uloží je do proměnných CellToSwap1 a CellToSwap2
*/
void SwapSetValues(char *arg1, char *arg2, char delim, int NumberOfCells, char *CellToSwap1, char *CellToSwap2, char *line){
    char CurrentCellA[102] = {'\0'};
    char RestOfTheLineA[10242] = {'\0'};
    strcpy(RestOfTheLineA, line);
    int ArgInt1  = atoi(arg1);
    int ArgInt2  = atoi(arg2);
    int j = 1;
    while(((RestOfTheLineA[0] != '\0') || (CurrentCellA[0] != '\0')) && (j <= NumberOfCells)){
        MyStrtok(delim, RestOfTheLineA, CurrentCellA);
        if(ArgInt1 == j){
            if(CurrentCellA[strlen(CurrentCellA)-1] == delim){
                CurrentCellA[strlen(CurrentCellA)-1] = '\0';
            }
            strncpy(CellToSwap1, CurrentCellA, strlen(CurrentCellA));
        }
        if(ArgInt2 == j){
            if(CurrentCellA[strlen(CurrentCellA)-1] == delim){
                CurrentCellA[strlen(CurrentCellA)-1] = '\0';
            }
            strncpy(CellToSwap2, CurrentCellA, strlen(CurrentCellA)); 
        }
        j++;
    }
}

/*
 * Najde hodnotu, kterou má někam posouvat a uloží ji do proměnné CellToMove
*/
void MoveSetValue(char *arg, char delim, int NumberOfCells, char *CellToMove, char *line){
    char CurrentCellA[102] = {'\0'};
    char RestOfTheLineA[10242] = {'\0'};
    strcpy(RestOfTheLineA, line);
    int ArgInt  = atoi(arg);
    int j = 1;
    while((RestOfTheLineA[0] != '\0') && (j <= NumberOfCells)){
        MyStrtok(delim, RestOfTheLineA, CurrentCellA);
        if(ArgInt == j){
            if(CurrentCellA[strlen(CurrentCellA)-1] == delim){
                CurrentCellA[strlen(CurrentCellA)-1] = '\0';
            }
            strncpy(CellToMove, CurrentCellA, strlen(CurrentCellA));
        }
        j++;
    }
}

/*
 * Zkontroluje, jestli se jedná a správný sloupec
 * pokud ano - vypíše hodnotu uloženou v CellToCopy a vrací 1
 * jinak nedělá nic a vrací 0
*/
int CopyPrintValue(int column, char *arg, char delim, char *CellToCopy, int NumberOfCells){
    int ArgInt  = atoi(arg);
    if(ArgInt == column){
        if(CellToCopy[0] == '\0'){
            printf("%c", delim);
            return 1;
        }
        if((CellToCopy[strlen(CellToCopy) - 1] != delim) && (column != NumberOfCells)){
            printf("%s%c", CellToCopy, delim);
        }
        else{
            printf("%s", CellToCopy);
        }
        return 1;
    }
    return 0;
}

/*
 * Zkontroluje, jestli se jedná a správný sloupec pro výpis jedné z hodnot
 * pokud se jedná o sloupec v prvním argumentu vypíše hodnotu CellToSwap2 a vrací 1
 * pokud se jedná o hodnotu v druhém argumentu vypíše hodnotu CellToSwap1 a vrací 1
 * jinak nedělá nic a vrací 0
*/
int SwapPrintValues(int column, char *arg1, char *arg2, char delim, int NumberOfCells, char *CellToSwap1, char *CellToSwap2){
    int ArgInt1  = atoi(arg1);
    int ArgInt2  = atoi(arg2);
    if(ArgInt1 != ArgInt2){
        if(ArgInt1 == column){
            printf("%s", CellToSwap2);
            if(column != NumberOfCells){
                printf("%c", delim);
            }
            return 1;
        }
        if(ArgInt2 == column){
            printf("%s", CellToSwap1);
            if(column != NumberOfCells){
                printf("%c", delim);
            }
            return 1;
        }
    }
    return 0;
}

/*
 * Zkontroluje, jestli se jedná o sloupec, před který se má hodnota posouvat
 * pokud ano - vypíše hodnotu uloženou v CellToMove a vrací 0, aby se poté vypsala i původní hodnota na této pozici
 * Zkontroluje jestli se jedná o sloupec, ve kterém byla hodnota původně
 * pokud ano - vrací 1
*/
int MovePrintValue(int column, char *arg1, char *arg2, char delim, char *CellToMove, int NumberOfCells, char *CurrentCell){
    int ArgInt1 = atoi(arg1);
    int ArgInt2 = atoi(arg2);
    if(ArgInt2 == column){
        printf("%s%c", CellToMove, delim);
    }
    if(ArgInt1 == NumberOfCells){
        if(column == NumberOfCells - 1){
            CurrentCell[strlen(CurrentCell) - 1] = '\0';
        }
    }
    if(ArgInt1 == column){
        return 1;
    }
    return 0;
}

/*
 * Projde všechny buňky a pokud má nějaká víc než 100 znaků, vrací 1
 * jinak vrací 0
*/
int CellLengthCheck(char delim, char *line){
    char CurrentCellA[102] = {'\0'};
    char RestOfTheLineA[10242] = {'\0'};
    strcpy(RestOfTheLineA, line);
    while(RestOfTheLineA[0] != '\0'){
        if(MyStrtok(delim, RestOfTheLineA, CurrentCellA) == 1){
            return 1;
        }
    }
    return 0;
}

/*
 * Zkontroluje jestli se jedná o správný sloupec
 * pokud ano - vrací 1
 * pokud ne - vrací 0
*/
int DeleteRow(int row, char *arg){
    int ArgInt  = atoi(arg);
    if(ArgInt == row){
        return 1;
    }
    return 0;
}

/*
 * Zkontroluje jestli se jedná o správný sloupec
 * pokud ano - vrací 1
 * pokud ne - vrací 0
*/
int DeleteRows(int row, char *arg1, char *arg2){
    int ArgInt1  = atoi(arg1);
    int ArgInt2  = atoi(arg2);
    if((ArgInt1 <= row) && (ArgInt2 >= row)){
        return 1;
    }
    return 0;
}

/*
 * Zkontroluje jestli se jedná o správný sloupec 
 * pokud ano - vypíše delim navíc
*/
void InsertColumn(int column, char *arg, char delim){
    int ArgInt  = atoi(arg);
    if(ArgInt == column){
        printf("%c", delim);
    }
}

/*
 * Zkontroluje jestli se jedná o správný sloupec 
 * pokud ano - vrací 1
 * pokud ne - vrací 0
*/
int DeleteColumn(int column, char *arg, int NumberOfCells, char *CurrentCell){
    int ArgInt  = atoi(arg);
    if(ArgInt == NumberOfCells){
        if(ArgInt == column + 1){
            CurrentCell[strlen(CurrentCell) - 1] = '\0';
        }
    }
    if(ArgInt == column){
        return 1;
    }
    return 0;
}

/*
 * Zkontroluje jestli se jedná o správný sloupec 
 * pokud ano - vrací 1
 * pokud ne - vrací 0
*/
int DeleteColumns(int column, char *arg1, char *arg2, int NumberOfCells, char *CurrentCell){
    int ArgInt1  = atoi(arg1);
    int ArgInt2  = atoi(arg2);
    if(ArgInt2 == NumberOfCells){
        if(ArgInt1 == column + 1){
            CurrentCell[strlen(CurrentCell) - 1] = '\0';
        }
    }
    if((ArgInt1 <= column) && (ArgInt2 >= column)){
        return 1;
    }
    return 0;
}

/*
 * Zkontroluje jestli se jedná o správný sloupec 
 * pokud ano - vypíše novou hodnotu a vrací 1
 * pokud ne - vrací 0
*/
int SetColumn(int column, char * arg1, char *arg2, char delim, int NumberOfCells){
    int ArgInt  = atoi(arg1);
    if(ArgInt == column){
        if(ArgInt == NumberOfCells){
            printf("%s", arg2);
        }
        else{
            printf("%s%c", arg2, delim);
        }
        return 1;
    }
    return 0;
}

/*
 * Projde pro danou buňky všechny argumenty, kterou slouží pro úpravu sloupců
 * pokud se během průchodu už vypsala daná buňka vrací 1
 * jinak vrací 0
*/
int ColumnArgumentsIteration(int column, int argc, char **argv, char delim, char *CurrentCell, int NumberOfCells, char *CellToCopy, char *CellToSwap1, char *CellToSwap2, char *CellToMove){
    int CellPrinted = 0;
    for(int i = 1; i < argc; i++){
        if(strcmp(argv[i],"icol") == 0){
            InsertColumn(column, argv[i+1], delim);
        }
        else if(strcmp(argv[i],"dcol") == 0){
            CellPrinted = DeleteColumn(column, argv[i+1], NumberOfCells, CurrentCell);
        }
        else if(strcmp(argv[i],"dcols") == 0){
            CellPrinted = DeleteColumns(column, argv[i+1], argv[i+2], NumberOfCells, CurrentCell);
        }
        else if(strcmp(argv[i],"cset") == 0){
            CellPrinted = SetColumn(column, argv[i+1], argv[i+2], delim, NumberOfCells);
        }
        else if(strcmp(argv[i],"tolower") == 0){
            int ArgInt  = atoi(argv[i+1]);
            if(ArgInt == column){
                for(int CharPos = 0; CurrentCell[CharPos] != '\0'; CharPos++){
                    CurrentCell[CharPos] = tolower(CurrentCell[CharPos]);
                }
            }
        }
        else if(strcmp(argv[i],"toupper") == 0){
            int ArgInt  = atoi(argv[i+1]);
            if(ArgInt == column){
                for(int CharPos = 0; CurrentCell[CharPos] != '\0'; CharPos++){
                    CurrentCell[CharPos] = toupper(CurrentCell[CharPos]);
                }
            }
        }
        else if(strcmp(argv[i],"round") == 0){
            CellPrinted = RoundColumn(column, argv[i+1], CurrentCell, delim);
        }
        else if(strcmp(argv[i],"int") == 0){
            CellPrinted = ToIntColumn(column, argv[i+1], CurrentCell, delim);
        }
        
        else if(strcmp(argv[i],"copy") == 0){
            if(strcmp(argv[i+1], argv[i+2]))
                CellPrinted = CopyPrintValue(column, argv[i+2], delim, CellToCopy, NumberOfCells);
        }
        else if(strcmp(argv[i],"swap") == 0){
            if(strcmp(argv[i+1], argv[i+2]))
                CellPrinted = SwapPrintValues(column, argv[i+1], argv[i+2], delim, NumberOfCells, CellToSwap1, CellToSwap2);
        }
        else if(strcmp(argv[i],"move") == 0){
            if(strcmp(argv[i+1], argv[i+2]))
                CellPrinted = MovePrintValue(column, argv[i+1], argv[i+2], delim, CellToMove, NumberOfCells, CurrentCell);
        }
    }
    return CellPrinted;
}

int LastLineCheck(){
    char NextChar = fgetc(stdin);
    if(NextChar == EOF){
        return 1;
    }
    else{
        ungetc(NextChar, stdin);
        return 0;
    }
}

/*
 * Kontroluje, jestli byl zadán správný počet parametrů a jestli je parametr číslo větší než 0
 * pokud je něco špatně, vrací 1
 * pokud je vše v pořádku vrací 0
*/
int SingleArgCheck(int i, int argc, char *argv[]){
    if(argc < i+1){
        return 1;
    }
    char *str;
    int ArgInt  = strtol(argv[i+1], &str, 10);
    if ((ArgInt < 1) || (strcmp(str, "") != 0)){
        return 1;   
    }
    return 0;
}

/*
 * Kontroluje, jestli byl zadán správný počet parametrů a jestli jsou oba parametry čísla větší než 0
 * pokud je něco špatně, vrací 1
 * pokud je vše v pořádku vrací 0
*/
int DoubleArgCheck(int i, int argc, char *argv[]){
    if(argc < i+2){
        return 1;
    }
    char *str1 = {'\0'};
    char *str2 = {'\0'};
    int ArgInt1  = strtol(argv[i+1], &str1, 10);
    int ArgInt2  = strtol(argv[i+2], &str2, 10);
    if ((ArgInt1 < 1) || (strcmp(str1, "") != 0) || (ArgInt2 < 1) || (strcmp(str2, "") != 0)){
        return 1;
    }
    return 0;
}

/*
 * Kontroluje, jestli byl zadán správný počet parametrů a jestli jsou oba parametry čísla větší než 0 nebo -
 * pokud je něco špatně, vrací 1
 * pokud je vše v pořádku vrací 0
*/
int RowsArgCheck(int i, int argc, char *argv[]){
    if(argc < i+2){
        return 1;
    }
    char *str1 = {'\0'};
    char *str2 = {'\0'};
    int ArgInt1  = strtol(argv[i+1], &str1, 10);
    int ArgInt2  = strtol(argv[i+2], &str2, 10);
    if(strcmp(str1, "-") == 0){
        ArgInt1 = INT_MAX;
    }
    if(strcmp(str2, "-") == 0){
        ArgInt2 = INT_MAX;
    }
    if ((ArgInt1 < 1) || ((strcmp(str1, "") != 0) && (strcmp(str1, "-") != 0)) || (ArgInt2 < 1) || ((strcmp(str2, "") != 0)  && (strcmp(str2, "-") != 0)) || (ArgInt2 < ArgInt1)){
        return 1;
    }
    return 0;
}

/*
 * Kontroluje, jestli byl zadán správný počet parametrů a jestli je první parametr číslo větší než 0
 * pokud je něco špatně, vrací 1
 * pokud je vše v pořádku vrací 0
*/
int IntStrArgCheck(int i, int argc, char *argv[]){
    //fprintf(stderr,"avc");
    if(argc < i+2){
        return 1;
    }
    char *str = {'\0'};
    int ArgInt  = strtol(argv[i+1], &str, 10);
    //fprintf(stderr, "%d", ArgInt);
    if ((ArgInt < 1) || (strcmp(str, "") != 0) || (strlen(argv[i+2]) > 102)){
        return 1;
    }
    return 0;
}

/*
 * Tato funkce kontroluje jestli jsou všechny zadané argumenty v pořádku,
 * aby nebylo potřeba už dále nic kontrolovat a nemohlo dojít k pádům a jiným problémům za běhu
 * pokud je vše správně, funkce vrací 0
 * při špatně zadaných argumentech vrací 1
 * při kombinaci argumnetů na úpravu tabulky a dat v tabulce vrací 2
*/
int ArgumentCheck(int argc, char *argv[]){
    int EditingTable = 0;
    int EditingData = 0;
    for(int i = 1;i < argc; i++){
        if(strcmp(argv[i],"-d") == 0){
            i++;
        }
        //Kontrola argumentů na úpravu tabůlky bez parametrů
        else if((!strcmp(argv[i],"arow")) || (!strcmp(argv[i],"acol"))){
            EditingTable = 1;
        }
        //Kontrola argumentů na úpravu tabůlky s jedním číselným parametrem
        else if((!strcmp(argv[i],"irow")) || (!strcmp(argv[i],"drow")) || (!strcmp(argv[i],"icol")) || (!strcmp(argv[i],"dcol"))){
            if(SingleArgCheck(i, argc, argv) == 1){
                return 1;
            }
            EditingTable = 1;
            i++;
        }
        //Kontrola argumentů na úpravu tabůlky se dvěma proměnnými
        else if((!strcmp(argv[i],"drows")) || (!strcmp(argv[i],"dcols"))){
            if(DoubleArgCheck(i, argc, argv) == 1){
                return 1;
            }
            EditingTable = 1;
            i += 2;
        }
        //Kontrola argumentů u rows
        else if(strcmp(argv[i],"rows") == 0){
            if(RowsArgCheck(i, argc, argv) == 1){
                return 1;
            }
            i += 2;
        }
        //Kontrola parametrů u argumentů s jedním číslem a jedním řetězcem
        else if((!strcmp(argv[i],"beginswith")) || (!strcmp(argv[i],"contains"))){
            if(IntStrArgCheck(i, argc, argv) == 1){
                return 1;
            }
            fprintf(stderr,"aaaa");
            i += 2;
        }
        else if(strcmp(argv[i],"cset") == 0){
            if(IntStrArgCheck(i, argc, argv) == 1){
                return 1;
            }
            EditingData = 1;
            i += 2;
        }
        //Kontrola argumentů na úpravu dat v tabůlce s jedním číselným parametrem
        else if((!strcmp(argv[i],"tolower")) || (!strcmp(argv[i],"toupper")) || (!strcmp(argv[i],"round")) || (!strcmp(argv[i],"int"))){
            if(SingleArgCheck(i, argc, argv) == 1){
                return 1;
            }
            EditingData = 1;
            i++;
        }
        //Kontrola argumentů na úpravu dat v tabůlce se dvěma číselnými parametry
        else if((!strcmp(argv[i],"copy")) || (!strcmp(argv[i],"swap")) || (!strcmp(argv[i],"move"))){
            if(DoubleArgCheck(i, argc, argv) == 1){
                return 1;
            }
            EditingData = 1;
            i += 2;
        }
        else{
            return 1;
        }
    }
    if((EditingData == 1) && (EditingTable == 1)){
        return 2;
    }
    return 0;
}

int main(int argc, char *argv[]){
    

    int ArgumentCheckResult = ArgumentCheck(argc, argv);
    if(ArgumentCheckResult == 1){
        fprintf(stderr, "You have used invalid argument!");
        return 1;
    }
    else if(ArgumentCheckResult == 2){
        fprintf(stderr, "You are trying to edit both table and data at the same time!");
        return 2;
    }
    char *delim;

    //nastavení delimu
    if(argc > 1){
        if(strcmp(argv[1],"-d") == 0){
            if(argc > 2){
                delim = argv[2];
            }
            else{
                delim = " ";
            }
        }
        else{
            delim = " ";
        }
    }
    else{
        delim = " ";
    }


    int FilterRowsByNum = 0;
    int StartingRow = 0;
    int EndingRow = 0;

    int FilterRowsByBeginsWith = 0;
    int ColToCheckForBeginsWith = 0;
    char *StringToMatchForBeginsWith;

    int FilterRowsByIfContains = 0;
    int ColToCheckForIfContains = 0;
    char *StringToMatchForIfContains;

    //Kontrola, jestli argumenty obsahují nějakou selekci řádků
    for(int i = 1; i < argc; i++){
        if(strcmp(argv[i], "rows") == 0){
            FilterRowsByNum = 1;
            if(strcmp(argv[i+1], "-") == 0){
                StartingRow = -1;
            }
            else{
                StartingRow = atoi(argv[i+1]);
            }
            if(strcmp(argv[i+2], "-") == 0){
                EndingRow = -1;
            }
            else{
                EndingRow = atoi(argv[i+2]);
            }
        }
        else if(strcmp(argv[i], "beginswith") == 0){
            FilterRowsByBeginsWith = 1;
            ColToCheckForBeginsWith = atoi(argv[i+1]);
            StringToMatchForBeginsWith = argv[i+2];
        }
        else if(strcmp(argv[i], "contains") == 0){
            FilterRowsByIfContains = 1;
            ColToCheckForIfContains = atoi(argv[i+1]);
            StringToMatchForIfContains = argv[i+2];
        }
    }

    int CellsInFirstRow = 1;
    char line[10242];
    for(int row = 1; fgets(line, 10240, stdin) != NULL; row++){

        if(strchr(line, '\n') == NULL){
            fprintf(stderr, "The table contains line longer than 10KiB!");
            return 3;
        }

        if(CellLengthCheck(delim[0], line) == 1){
            fprintf(stderr, "The table contains cell longer than 100 characters!");
            return 4;
        }

        int CellsInThisRow = 1;
        int RowPrinted = 0;
        for(int i = 0; line[i] != '\0'; i++){
            for(int j = 0; delim[j] != '\0'; j++){
                if(line[i] == delim[j]){
                    line[i] = delim[0];
                    if(row == 1){
                        CellsInFirstRow++;
                    }
                    else{
                        CellsInThisRow++;
                    }
                }
            }
            if(line[i] == '\n'){
                line[i] = '\0';
            }
        }

        //přidání prázdých buňek, pokud je v daném řádku míň buňěk něž v prvním
        if(row != 1){
            int aaa = 0;
            int LineLength = (int)strlen(line);
            while(CellsInThisRow < CellsInFirstRow){
                line[LineLength+aaa] = delim[0];
                CellsInThisRow++;
                aaa++;
            }
            line[LineLength+aaa] = '\0';
        }
        if(FilterRowsByNum == 1){
            if((StartingRow != -1) && (EndingRow != -1)){
                if((row < StartingRow) || (row > EndingRow)){
                    printf("%s\n", line);
                    continue;
                }
            }
            else if(StartingRow != -1){
                if(row < StartingRow){
                    printf("%s\n", line);
                    continue;
                }
            }
            else if((StartingRow == -1) && (EndingRow == -1)){
                int IsLastLine = LastLineCheck();
                if(IsLastLine == 0){
                    printf("%s\n", line);
                    continue;
                }
            }
        }


        if(FilterRowsByBeginsWith == 1){
            int ColNumBW = 0;
            char CurrentCellBW[102] = {'\0'};
            char RestOfTheLineBW[10242] = {'\0'};
            strcpy(RestOfTheLineBW, line);
            while(ColNumBW != ColToCheckForBeginsWith){
                MyStrtok(delim[0], RestOfTheLineBW, CurrentCellBW);
                ColNumBW++;
            }
            int IsSame = 1;
            for(int i = 0; i < (int)strlen(StringToMatchForBeginsWith); i++){
                if(StringToMatchForBeginsWith[i] != CurrentCellBW[i]){
                    IsSame = 0;
                }
            }
            if(IsSame == 0){
                printf("%s\n", line);
                continue;
            }
        }

        if(FilterRowsByIfContains == 1){
            int ColNumC = 0;
            char CurrentCellC[102] = {'\0'};
            char RestOfTheLineC[10242] = {'\0'};
            strcpy(RestOfTheLineC, line);
            while(ColNumC != ColToCheckForIfContains){
                MyStrtok(delim[0], RestOfTheLineC, CurrentCellC);
                ColNumC++;
            }
            if(strstr(CurrentCellC, StringToMatchForIfContains) == NULL){
                printf("%s\n", line);
                continue;
            }
        }
        char CellToCopy[101] = {'\0'};
        char CellToSwap1[101] = {'\0'};
        char CellToSwap2[101] = {'\0'};
        char CellToMove[101] = {'\0'};

        for(int i = 1; i < argc; i++){
            if(strcmp(argv[i],"copy") == 0){
                CopySetValue(argv[i+1], delim[0], CellsInFirstRow, CellToCopy, line);
            }
            else if(strcmp(argv[i],"swap") == 0){
                SwapSetValues(argv[i+1], argv[i+2], delim[0], CellsInFirstRow, CellToSwap1, CellToSwap2, line);
            }
            else if(strcmp(argv[i],"move") == 0){
                MoveSetValue(argv[i+1], delim[0], CellsInFirstRow, CellToMove, line);
            }
        }

        for(int i = 1;i < argc; i++){
            if(strcmp(argv[i],"irow") == 0){
                InsertRow(row, argv[i+1], CellsInFirstRow, delim[0]);
            }
            else if(strcmp(argv[i],"drow") == 0){
                RowPrinted = DeleteRow(row, argv[i+1]);
            }
            else if(strcmp(argv[i],"drows") == 0){
                RowPrinted = DeleteRows(row, argv[i+1], argv[i+2]);
            }
        }
        if(RowPrinted == 0){
            char CurrentCell[102];
            char RestOfTheLine[10242];
            strcpy(RestOfTheLine, line);
            int j = 1;
            while(((RestOfTheLine[0] != '\0') || (CurrentCell[0] != '\0')) && (j <= CellsInFirstRow)){
                MyStrtok(delim[0], RestOfTheLine, CurrentCell);
                int CellPrinted = 0;
                CellPrinted = ColumnArgumentsIteration(j, argc, argv, delim[0], CurrentCell, CellsInFirstRow, CellToCopy, CellToSwap1, CellToSwap2, CellToMove);
                if(CellPrinted == 0){
                    printf("%s", CurrentCell);
                }
                j++;
            }
            for(int i = 1; i < argc; i++){
                if(strcmp(argv[i],"acol") == 0){
                    printf("%c", delim[0]);
                }
            }
            printf("\n");
        }
    }
    for(int i = 1; i < argc; i++){
        if(strcmp(argv[i],"arow") == 0){
            for(int i = 1; i < CellsInFirstRow; i++){
                printf("%c", delim[0]);
            }
        }
    }
    return 0;
}