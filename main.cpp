#include <iostream>
#include <fstream>
#include <string>
#include <istream>
#include <vector>
#include <regex>

// =========================================================
// File: main.cpp
// Author: Pablo César Jiménez Villeda - Ariann Fernando Arriaga Alcántara
// Date: 16 de noviembre del 2021
//
// Implementación de un DFA.
// =========================================================

using namespace std;

// =================================================================
// Función que imprime los tokens encontrados en un archivo.
//
// Análsis de complejidad:
/*
La complejidad es de este algoritmo es de O(n*m), donde n es la cantidad 
de posible matches que se pueden encontrar en el string y m es la 
cantidad de tokens que se buscan.
*/
// @param row, un string de cada línea del archivo que se lee
// =================================================================
void analizeRow(string row) {
  // Expresiones regulares para encontrar todos los tokens
  string variables = "[a-zA-Z][a-zA-Z0-9_]*";
  string operands = "\\/|\\+|\\-|\\*|\\=|\\(|\\)|\\^";
  string comments = "\\/\\/.*";
  string integers = "\\-*[0-9]+";
  string real = "\\-*[0-9]+\\.[0-9]+((E|e)(\\+|\\-)?[0-9]+)?";
  std::regex e(comments + "|" + real +"|" + variables + "|" + operands  + "|" + integers);
  
  // Iterador de todos los matches de las expresiones regulares
  std::regex_iterator<std::string::iterator> rit( row.begin(), row.end(), e);
  std::regex_iterator<std::string::iterator> rend;

  // Buscar qué regex ha provocado el match para identificar el token
  while (rit!=rend) {
    if(regex_match(rit->str(), regex(variables))) {
      cout << "Variable: " << rit->str() << endl;
    } else if(regex_match(rit->str(), regex(comments))) {
      cout << "Comment: " << rit->str() << endl;
    } else if(regex_match(rit->str(), regex(integers))) {
      cout << "Integer: " << rit->str() << endl;
    } else if(regex_match(rit->str(), regex(real))) {
      cout << "Real: " << rit->str() << endl;
      // identificar operadores
    } else if(regex_match(rit->str(), regex(operands))) {
      char curr = rit->str()[0];
      switch (curr) {
        case '=':
            cout << "Assignment: =" << endl;
            break;
        case '-':
            cout << "Substraction: -" << endl;
            break;
        case '+':
            cout << "Sum: +" << endl;
            break;
        case '^':
            cout << "Power: ^" << endl;
            break;
        case '*':
            cout << "Multiplication: *" << endl;
            break;
        case '/':
            cout << "Division: /" << endl;
            break;
        case '(':
            cout << "Left parenthesis: (" << endl;
            break;
        case ')':
            cout << "Right parenthesis: )" << endl;
            break;
        default:
          break;
      }
    }
    ++rit;
  }

  
}

// =================================================================
// Función implementa un lexer aritmético
//
// Análsis de complejidad:
/*
La complejidad es de esta función es de O(n*m*l), donde l es la 
cantidad de líneas del archivo, m es la camtidad de matches y n 
el número de tokens a buscar.
*/
// @param archivo, un string del nombre del archivo a analizar
// =================================================================
void lexerAritmetico(string archivo) {
  fstream contentDataFile;
  contentDataFile.open(archivo, ios::in);

  string currentLine;
  cout << "Type                                   : Value"<< endl;
  while(getline(contentDataFile, currentLine)) {
    // O(n*m)
    analizeRow(currentLine);
  }
  
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cout << "usage: " << argv[0] << " pathname\n";
    return -1;
  }

  lexerAritmetico(argv[1]);

  return 0;
}
