/**************************************
 *
 * University of Haifa
 *
 * Theory of compilation
 *
 * P machine compiler - code generation project
 *
 * Yosi Ben Asher
 * Email: yosibenasher@gmail.com
 *
 * Mariah Akree
 * Email: mariah.uni.haifa@gmail.com
 *
 **************************************/

#include "main.h"
int counter = 0; 
int rightSon = 0;
int addFlag = 0; 
int addFlag2 = 0;  
int subFlag = 0; 
int indFlag = 1; 
int ifCounter = 0;
int loopCounter = 0;
int unary = 0;
int constFlag = 0;
int caseCounter = 0; 
int counterOfUjp = 0;
int imInCaseStatment = 0;
int caseTimes = 0;
int arraySum = 1;
int varibleDeclarationFlag = 0; //tells us were in a variable decleration 
int ArrayTypeFlag = 0; //tells us if were in a array creation/allocation
int addressTypeFlag = 0;
string* pointerName; //used for creating new pointer in pointertable
int pointerFlag = 0; //when were going to use inc for pointers and stuff
int RecordTypeFlag = 0;
vector<symbol> symboltable;
vector<pointer> pointertable;
extern int yydebug;


void writeAST(Object* r, fstream& file)
{
	//Perform recursive tree print
	r->print(file);
}
void Pcode(Object* r, fstream& file)
{
	//Perform recursive tree print
	r->pcodegen(file);
}

Object* getTree(char* progFile)
{

	yydebug = 1;
	assert(progFile);

	// yyin is an external variable that been used in yyparse as pointer to the source file.
	yyin = fopen(progFile, "r");
	if (!yyin) {
		cerr << "Error: file " << progFile << " does not exst. Aborting ..." << endl;;
		exit(1);
	}
	assert(yyin);

	// yyparse is yacc function that parse the program, checks syntax and builds the program AST.
	yyparse();

	fclose(yyin);

	// root was initialized in yyparse while it was building the tree.
	// root is the pointer of the returning tree.
	assert(root);
	return(root);
}



int main(int argc, char* argv[])
{
 	CodeGenerator codeGen;

	//check input arguments.
	if (argc < 2) {
		cerr << endl << "Input file is missing. Aborting ..." << endl;
		exit(1);
	}
	Object* theProgram = getTree(argv[1]);
	assert(theProgram == root);
	fstream treeFile(TREE_OUTPUT_TEXT_FILE, ios::out);
	fstream pcodeFile(OUTPUT_CODE_TEXT, ios::out);
	treeFile << AST_FILE_HEADER << endl;
	writeAST(theProgram, treeFile);
	Pcode(theProgram, pcodeFile);
	/*for(int i = 0; i<7; i++) {
 		cout << "i = " << i <<":" << *(symboltable.at(i).variableName_) << " ,address: "<<symboltable.at(i).address_<<endl;
	}
	int i = 0;*/
	/*for(pointer p : pointertable) {
 		cout << "i = " << i <<":" << *(pointertable.at(i).pointer_) << " ,address: "<<pointertable.at(i).addressPointing_;
		cout <<" ,pointed:"<< *(pointertable.at(i).pointedName_) << endl;
		i++;
	}*/
	treeFile.close();
	return (0);
}
